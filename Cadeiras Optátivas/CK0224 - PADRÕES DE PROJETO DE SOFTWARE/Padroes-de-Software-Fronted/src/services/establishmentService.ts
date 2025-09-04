
import apiClient from './apiClient';
import { Estabelecimento } from '../types/Estabelecimento'; 
import AsyncStorage from '@react-native-async-storage/async-storage';

export const establishmentService = {
  getAll: async (): Promise<Estabelecimento[]> => {
    try {
      const token = await AsyncStorage.getItem('userToken');
      if (!token) {
        throw new Error('Token de autenticação não encontrado.');
      }

      const response = await apiClient.get<Estabelecimento[]>('/establishments/', {
        headers: {
          // O seu backend espera 'Bearer' ou 'Token'? Pelo seu código original, parece ser 'Bearer' na home.
          // E 'Token' em estabelecimento_info. É importante padronizar isso no backend.
          // Vamos usar 'Bearer' como exemplo aqui.
          'Authorization': `Bearer ${token}`
        }
      });
      return response.data;
    } catch (error) {
      console.error('Erro ao buscar estabelecimentos:', error);
      throw new Error('Não foi possível carregar os estabelecimentos.');
    }
  },
};