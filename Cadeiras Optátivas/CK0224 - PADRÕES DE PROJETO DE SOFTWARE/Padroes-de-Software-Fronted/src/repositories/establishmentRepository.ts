// gen/src/repositories/establishmentRepository.ts

import { establishmentService } from '@/services/establishmentService';
import { Estabelecimento } from '@/types/Estabelecimento';
import { IEstablishmentRepository } from './interfaces/IEstablishmentRepository';

// Implementação concreta que busca dados da API
export class ApiEstablishmentRepository implements IEstablishmentRepository {
  private cache: Estabelecimento[] | null = null;
  private lastFetchTimestamp: number | null = null;
  private readonly CACHE_DURATION_IN_MINUTES = 5;

  private isCacheValid(): boolean {
    if (!this.cache || !this.lastFetchTimestamp) {
      return false;
    }
    const now = Date.now();
    const diffInMinutes = (now - this.lastFetchTimestamp) / (1000 * 60);
    return diffInMinutes < this.CACHE_DURATION_IN_MINUTES;
  }

  async getAll(): Promise<Estabelecimento[]> {
    console.log("Tentando buscar estabelecimentos...");
    if (this.isCacheValid() && this.cache) {
      console.log("Retornando dados do cache.");
      return this.cache;
    }

    console.log("Cache inválido ou inexistente. Buscando da API.");
    const data = await establishmentService.getAll();
    this.cache = data;
    this.lastFetchTimestamp = Date.now();
    
    return data;
  }
}

const establishmentRepository: IEstablishmentRepository = new ApiEstablishmentRepository();

export default establishmentRepository;