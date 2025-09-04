// gen/src/types/user.ts

export interface User {
  token: string;
  id: string;
  first_name: string;
  last_name: string;
  telefone?: string; // Correção: Campo agora é opcional
  email: string;
  cpf: string;
  username: string;
  photo_url: string;
  data_joined: string;
  city: string;
  state: string;
}