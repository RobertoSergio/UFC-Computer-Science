// gen/src/services/authService.ts

import apiClient from './apiClient';
import { User } from '@/types/User';

// Tipo para os dados de ENTRADA do login.
// Corresponde ao que a API de autenticação espera.
export interface LoginCredentials {
  email: string;
  password?: string;
}

// Tipo para os dados de ENTRADA do cadastro.
// Corresponde aos campos que o usuário preenche no formulário de registro.
export type RegisterData = Omit<User, 'id' | 'token' | 'photo_url' | 'data_joined'> & {
  password?: string; // Adicionamos o campo de senha
};


export const authService = {
  login: async (credentials: LoginCredentials): Promise<User> => {
    try {
      const response = await apiClient.post<User>('/users/authentication/', credentials);
      return response.data;
    } catch (error) {
      console.error('Erro na autenticação:', error);
      throw new Error('E-mail ou senha incorretos.');
    }
  },

  register: async (data: RegisterData): Promise<void> => {
    try {
      await apiClient.post('/users/', data);
    } catch (error) {
      console.error('Erro no cadastro:', error);
      throw new Error('Não foi possível realizar o cadastro. Tente novamente.');
    }
  },
};