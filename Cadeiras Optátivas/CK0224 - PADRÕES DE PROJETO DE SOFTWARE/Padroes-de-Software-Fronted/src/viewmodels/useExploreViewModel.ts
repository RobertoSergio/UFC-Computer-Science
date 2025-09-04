// gen/src/viewmodels/useExploreViewModel.ts

import { useState, useEffect } from 'react';
import { useRouter } from 'expo-router';
import { userRepository } from '@/repositories/userRepository';

// Um tipo local para representar os dados do usuário na View
interface UserDisplayData {
  fullName: string;
  email: string;
  cpf: string;
  location: string;
}

export const useExploreViewModel = () => {
  const router = useRouter();
  const [user, setUser] = useState<UserDisplayData | null>(null);
  const [isLoading, setIsLoading] = useState(true);

  // Efeito para carregar os dados do usuário do repositório
  useEffect(() => {
    const loadUserData = async () => {
      try {
        setIsLoading(true);
        // O Partial<User> vem do nosso repositório
        const userDataFromStorage = await userRepository.getUserData();
        
        if (userDataFromStorage.email && userDataFromStorage.first_name) {
          setUser({
            fullName: `${userDataFromStorage.first_name || ''} ${userDataFromStorage.last_name || ''}`,
            email: userDataFromStorage.email,
            cpf: userDataFromStorage.cpf || 'Não informado',
            location: `${userDataFromStorage.city || 'Não fornecida'}, ${userDataFromStorage.state || 'Não fornecido'}`,
          });
        }
      } catch (error) {
        console.error("Erro ao carregar dados do usuário:", error);
        // Poderíamos definir um estado de erro aqui também
      } finally {
        setIsLoading(false);
      }
    };

    loadUserData();
  }, []);

  // Comando para executar o logout
  const handleLogout = async () => {
    try {
      await userRepository.clearUserData();
      router.replace('/'); // Redireciona para a tela de login
    } catch (error) {
      console.error('Erro ao fazer logout:', error);
      alert('Não foi possível sair. Tente novamente.');
    }
  };

  // Expõe o estado e os comandos para a View
  return {
    user,
    isLoading,
    handleLogout,
  };
};