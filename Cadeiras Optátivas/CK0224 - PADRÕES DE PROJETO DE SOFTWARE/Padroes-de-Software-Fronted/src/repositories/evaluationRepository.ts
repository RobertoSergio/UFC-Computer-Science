// gen/src/repositories/evaluationRepository.ts

import { evaluationService } from '@/services/evaluationService';
import { Avaliacao } from '@/types/Avaliacao';

type NewEvaluationData = {
    estabelecimento: string;
    usuario_avaliador: string;
    nota: number;
    descricao: string;
};

export const evaluationRepository = {
  getByEstablishmentId: (id: string): Promise<Avaliacao[]> => {
    return evaluationService.getByEstablishmentId(id);
  },

  submit: (data: NewEvaluationData): Promise<void> => {
    return evaluationService.submit(data);
  },
};