// gen/src/viewmodels/useHomeViewModel.ts

import { useState, useEffect, useCallback } from 'react';
import { useRouter } from 'expo-router';
import { Linking } from 'react-native';
import * as Location from 'expo-location';
import { Estabelecimento } from '@/types/Estabelecimento';
import { useDependencies } from '@/contexts/DependencyContext';

// --- Tipos de ajuda ---
interface UserLocation {
  latitude: number;
  longitude: number;
}

type EstabelecimentoComDistancia = Estabelecimento & {
  distance?: number;
};

// --- Função de cálculo de distância ---
const calculateDistance = (loc1: UserLocation, loc2: UserLocation): number => {
  if (!loc1 || !loc2) return Infinity;
  const toRad = (value: number) => (value * Math.PI) / 180;
  const R = 6371; // Raio da Terra em KM
  const dLat = toRad(loc2.latitude - loc1.latitude);
  const dLon = toRad(loc2.longitude - loc1.longitude);
  const lat1 = toRad(loc1.latitude);
  const lat2 = toRad(loc2.latitude);

  const a =
    Math.sin(dLat / 2) * Math.sin(dLat / 2) +
    Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
  const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
  return R * c;
};

// --- Início do ViewModel ---
export const useHomeViewModel = () => {
  const { establishmentRepository } = useDependencies();
  const router = useRouter();

  const [search, setSearch] = useState('');
  const [allEstablishments, setAllEstablishments] = useState<Estabelecimento[]>([]);
  const [filteredEstablishments, setFilteredEstablishments] = useState<EstabelecimentoComDistancia[]>([]);
  const [userLocation, setUserLocation] = useState<UserLocation | null>(null);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  // --- CORREÇÃO PRINCIPAL AQUI ---
  // 1. Criamos uma função reutilizável para aplicar o filtro e a ordenação
  const applyFilterAndSort = useCallback((searchText: string, baseList: Estabelecimento[], location: UserLocation | null) => {
    // Filtra por texto primeiro
    const filteredByText = searchText
      ? baseList.filter(item => {
          const itemData = `${item.nome_fantasia?.toUpperCase() ?? ''} ${item.endereco_estabelecimento?.toUpperCase() ?? ''} ${item.bairro_estabelecimento?.toUpperCase() ?? ''}`;
          const textData = searchText.toUpperCase();
          return itemData.includes(textData);
        })
      : [...baseList];

    // Calcula a distância para os itens filtrados
    const withDistance = filteredByText.map(item => ({
      ...item,
      distance: location ? calculateDistance(location, {
        latitude: item.latitude_estabelecimento_decimo_grau,
        longitude: item.longitude_estabelecimento_decimo_grau,
      }) : undefined,
    }));

    // Ordena por distância se a localização estiver disponível
    if (location) {
      withDistance.sort((a, b) => (a.distance ?? Infinity) - (b.distance ?? Infinity));
    }
    
    setFilteredEstablishments(withDistance);
  }, []);


  // 2. Efeito para carregar dados iniciais e aplicar a ordenação
  useEffect(() => {
    const loadInitialData = async () => {
      setIsLoading(true);
      setError(null);

      let location: UserLocation | null = null;
      try {
        let { status } = await Location.requestForegroundPermissionsAsync();
        if (status !== 'granted') {
          setError('A permissão para acessar a localização foi negada.');
        } else {
          const locationData = await Location.getCurrentPositionAsync({});
          location = {
            latitude: locationData.coords.latitude,
            longitude: locationData.coords.longitude,
          };
          setUserLocation(location);
        }
      } catch (e) {
          setError("Não foi possível obter sua localização.");
      }

      try {
        const establishmentData = await establishmentRepository.getAll();
        setAllEstablishments(establishmentData);
        // Aplica a ordenação na lista inicial
        applyFilterAndSort('', establishmentData, location); 
      } catch (e: any) {
        setError(e.message || 'Não foi possível carregar os dados.');
      } finally {
        setIsLoading(false);
      }
    };

    loadInitialData();
  }, [establishmentRepository, applyFilterAndSort]);


  // 3. A função de busca agora apenas chama a lógica centralizada
  const searchFilter = (text: string) => {
    setSearch(text);
    applyFilterAndSort(text, allEstablishments, userLocation);
  };


  // ... (outras funções handleDetailsPress e handleOpenGoogleMaps não mudam)
  const handleDetailsPress = (estabelecimento: Estabelecimento) => {
    router.push({
      pathname: '/(tabs)/estabelecimento_info',
      params: { estabelecimento: JSON.stringify(estabelecimento) },
    });
  };

  const handleOpenGoogleMaps = (latitude: number, longitude: number) => {
    const url = `https://www.google.com/maps/search/?api=1&query=${latitude},${longitude}`;
    Linking.openURL(url).catch(err => console.error('Erro ao abrir o Google Maps:', err));
  };


  return {
    search,
    isLoading,
    error,
    filteredEstablishments,
    searchFilter,
    handleDetailsPress,
    handleOpenGoogleMaps,
  };
};