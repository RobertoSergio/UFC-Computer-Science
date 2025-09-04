// gen/src/services/evaluationService.ts

import apiClient from './apiClient';
import { Avaliacao } from '@/types/Avaliacao';
import AsyncStorage from '@react-native-async-storage/async-storage';

type NewEvaluationData = {
  estabelecimento: string;
  usuario_avaliador: string;
  nota: number;
  descricao: string;
};

export const evaluationService = {
  getByEstablishmentId: async (id: string): Promise<Avaliacao[]> => {
    try {
        const token = await AsyncStorage.getItem('userToken');
        const response = await apiClient.get<Avaliacao[]>(`/evaluations/`, {
            params: { estabelecimento: id },
            headers: { 'Authorization': `Token ${token}` }, // Ajuste 'Token' ou 'Bearer' conforme seu backend
        });
        return response.data;
    } catch (error) {
        console.error('Erro ao buscar avaliações:', error);
        return []; // Retorna um array vazio em caso de erro para não quebrar a UI
    }
  },

  submit: async (data: NewEvaluationData): Promise<void> => {
    try {
        const token = await AsyncStorage.getItem('userToken');
        await apiClient.post(`/evaluations/`, data, {
            headers: { 'Authorization': `Token ${token}` }, // Ajuste 'Token' ou 'Bearer'
        });
    } catch (error) {
        console.error('Erro ao enviar avaliação:', error);
        throw new Error('Não foi possível enviar a sua avaliação.');
    }
  },
};