// gen/src/viewmodels/useEstabelecimentoInfoViewModel.ts

import { useState, useEffect, useCallback } from 'react';
import { useLocalSearchParams } from 'expo-router';
import { evaluationRepository } from '@/repositories/evaluationRepository';
import { userRepository } from '@/repositories/userRepository';
import { Estabelecimento } from '@/types/Estabelecimento';
import { Avaliacao } from '@/types/Avaliacao';

export const useEstabelecimentoInfoViewModel = () => {
  const { estabelecimento: estabelecimentoJson } = useLocalSearchParams<{ estabelecimento: string }>();
  
  // Estado para os dados da tela
  const [estabelecimento, setEstabelecimento] = useState<Estabelecimento | null>(null);
  const [avaliacoes, setAvaliacoes] = useState<Avaliacao[]>([]);
  
  // Estado do formulário de nova avaliação
  const [nota, setNota] = useState('');
  const [descricao, setDescricao] = useState('');

  // Estado de controle da UI
  const [isLoading, setIsLoading] = useState(true);
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [error, setError] = useState<string | null>(null);

  // Função para carregar as avaliações
  const fetchAvaliacoes = useCallback(async (id: string) => {
    try {
      const fetchedAvaliacoes = await evaluationRepository.getByEstablishmentId(id);
      setAvaliacoes(fetchedAvaliacoes);
    } catch (e) {
      console.error(e);
      setError('Não foi possível carregar as avaliações.');
    }
  }, []);

  // Efeito inicial para carregar todos os dados da tela
  useEffect(() => {
    if (estabelecimentoJson) {
      const parsedEstabelecimento = JSON.parse(estabelecimentoJson);
      setEstabelecimento(parsedEstabelecimento);
      
      const loadInitialData = async () => {
        setIsLoading(true);
        await fetchAvaliacoes(parsedEstabelecimento.id);
        setIsLoading(false);
      };
      
      loadInitialData();
    } else {
      setError("Dados do estabelecimento não encontrados.");
      setIsLoading(false);
    }
  }, [estabelecimentoJson, fetchAvaliacoes]);

  // Comando para submeter uma nova avaliação
  const handleAvaliacaoSubmit = async () => {
    if (!nota || !descricao) {
      alert('Por favor, preencha a nota e a descrição.');
      return;
    }
    if (!estabelecimento) return;

    setIsSubmitting(true);
    try {
      const idUsuario = await userRepository.getUserId();
      if (!idUsuario) {
        throw new Error('Usuário não autenticado.');
      }

      await evaluationRepository.submit({
        estabelecimento: estabelecimento.id,
        usuario_avaliador: idUsuario,
        nota: parseFloat(nota),
        descricao,
      });

      // Limpa o formulário e recarrega a lista de avaliações
      setNota('');
      setDescricao('');
      await fetchAvaliacoes(estabelecimento.id);
      alert('Avaliação enviada com sucesso!');

    } catch (e: any) {
      alert(e.message || 'Erro ao enviar avaliação.');
    } finally {
      setIsSubmitting(false);
    }
  };

  return {
    estabelecimento,
    avaliacoes,
    nota,
    setNota,
    descricao,
    setDescricao,
    isLoading,
    isSubmitting,
    error,
    handleAvaliacaoSubmit,
  };
};