export interface Avaliacao {
  id: string; // Adicionamos um ID para a chave da lista
  nota: number;
  descricao: string;
  // Opcional: podemos adicionar dados do usuário que avaliou
  // usuario_avaliador: { first_name: string; last_name: string; };
}