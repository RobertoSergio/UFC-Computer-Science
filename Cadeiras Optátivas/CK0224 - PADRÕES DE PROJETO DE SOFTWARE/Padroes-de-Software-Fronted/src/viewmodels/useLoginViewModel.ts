// gen/src/viewmodels/useLoginViewModel.ts

import { useState } from 'react';
import { authService, LoginCredentials } from '@/services/authService';
import { useAuthStore } from '@/stores/useAuthStore'; // 1. Importa a store

export const useLoginViewModel = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState<string | null>(null);

  // 2. Obtém a ação de login e o estado de loading da store
  const { login } = useAuthStore();
  const [isSubmitting, setIsSubmitting] = useState(false);


  const handleLogin = async () => {
    if (!email || !password) {
      setError('Por favor, preencha todos os campos.');
      return;
    }

    setIsSubmitting(true);
    setError(null);

    try {
      const credentials: LoginCredentials = { email, password };
      const userData = await authService.login(credentials);
      // 3. Chama a ação da store, que cuidará de tudo
      await login(userData);
      // A navegação será tratada automaticamente pelo layout principal
    } catch (e: any) {
      setError(e.message || 'Erro, e-mail ou senha incorretos.');
    } finally {
      setIsSubmitting(false);
    }
  };

  return {
    email,
    setEmail,
    password,
    setPassword,
    isSubmitting, // Renomeado para não confundir com o isLoading da store
    error,
    handleLogin,
  };
};