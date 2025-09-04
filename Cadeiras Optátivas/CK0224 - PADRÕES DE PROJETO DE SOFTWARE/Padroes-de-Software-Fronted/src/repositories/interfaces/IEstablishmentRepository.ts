import { Estabelecimento } from "@/types/Estabelecimento";

export interface IEstablishmentRepository {
  getAll(): Promise<Estabelecimento[]>;
  // No futuro, poderíamos adicionar:
  // getById(id: string): Promise<Estabelecimento | null>;
}