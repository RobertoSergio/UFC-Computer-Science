// gen/src/stores/useAuthStore.ts

import { create } from 'zustand'; // Correção: Importa 'create' como um membro nomeado
import { userRepository } from '@/repositories/userRepository';
import { User } from '@/types/User';
import AsyncStorage from '@react-native-async-storage/async-storage'; // Adicionado: Importação que faltava

// 1. Define a "forma" do nosso estado e das ações
interface AuthState {
  user: Partial<User> | null;
  token: string | null;
  isAuthenticated: boolean;
  isLoading: boolean;
  login: (userData: User) => Promise<void>;
  logout: () => Promise<void>;
  loadUserFromStorage: () => Promise<void>;
}

// 2. Cria a store com o estado inicial e as implementações das ações
export const useAuthStore = create<AuthState>((set) => ({
  // Estado Inicial
  user: null,
  token: null,
  isAuthenticated: false,
  isLoading: true, // Começa como true para verificar o storage na inicialização

  // Ação de Login
  login: async (userData: User) => {
    set({ user: userData, token: userData.token, isAuthenticated: true });
    await userRepository.saveUserData(userData);
  },

  // Ação de Logout
  logout: async () => {
    await userRepository.clearUserData();
    set({ user: null, token: null, isAuthenticated: false });
  },

  // Ação para carregar o usuário do AsyncStorage na inicialização do app
  loadUserFromStorage: async () => {
    try {
      const storedToken = await AsyncStorage.getItem('userToken');
      // Usando o repositório para manter a abstração
      const storedUser = await userRepository.getUserData();
      
      if (storedToken && storedUser.email) {
        set({ user: storedUser, token: storedToken, isAuthenticated: true });
      }
    } catch (e) {
      console.error("Falha ao carregar usuário do storage", e);
      // Garante que o estado de autenticação seja falso em caso de erro
      set({ isAuthenticated: false });
    } finally {
        set({ isLoading: false });
    }
  },
}));