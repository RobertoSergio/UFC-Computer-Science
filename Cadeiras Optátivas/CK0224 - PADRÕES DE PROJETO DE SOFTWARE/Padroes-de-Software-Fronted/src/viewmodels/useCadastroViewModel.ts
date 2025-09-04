// gen/src/viewmodels/useCadastroViewModel.ts

import { useState } from 'react';
import { useRouter } from 'expo-router';
import { authService, RegisterData } from '@/services/authService';

export const useCadastroViewModel = () => {
  const router = useRouter();

  // Estado para cada campo do formulário
  const [firstName, setFirstName] = useState('');
  const [lastName, setLastName] = useState('');
  const [username, setUsername] = useState('');
  const [cpf, setCpf] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [city, setCity] = useState('');
  const [state, setState] = useState('');
  
  // Estado para controle da UI
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  // Comando para lidar com o envio do formulário
  const handleCadastro = async () => {
    // Validação dos campos
    if (!firstName || !lastName || !email || !password || !confirmPassword || !cpf || !username || !city || !state) {
      setError('Por favor, preencha todos os campos.');
      return;
    }

    if (password !== confirmPassword) {
      setError('As senhas não coincidem.');
      return;
    }

    setIsLoading(true);
    setError(null);

    const registrationData: RegisterData = {
      first_name: firstName,
      last_name: lastName,
      username,
      cpf,
      email,
      password,
      city,
      state,
      // 'telefone' é omitido, o que agora é permitido.
    };

    try {
      await authService.register(registrationData);
      alert('Cadastro realizado com sucesso!');
      router.push('/');
    } catch (e: any) {
      setError(e.message || 'Erro ao realizar o cadastro. Tente novamente.');
    } finally {
      setIsLoading(false);
    }
  };

  // Expõe tudo que a View precisa
  return {
    firstName, setFirstName,
    lastName, setLastName,
    username, setUsername,
    cpf, setCpf,
    email, setEmail,
    password, setPassword,
    confirmPassword, setConfirmPassword,
    city, setCity,
    state, setState,
    isLoading,
    error,
    handleCadastro,
  };
};