// gen/src/types/estabelecimento.ts

export interface Estabelecimento {
  id: string;
  nome_fantasia: string;
  endereco_estabelecimento: string;
  bairro_estabelecimento: string;
  numero_telefone_estabelecimento: string;
  numero_estabelecimento: string;
  latitude_estabelecimento_decimo_grau: number;
  longitude_estabelecimento_decimo_grau: number;
  endereco_email_estabelecimento: string;
  codigo_cep_estabelecimento: string;
  descricao_turno_atendimento: string;
  estabelecimento_faz_atendimento_ambulatorial_sus: string;
  estabelecimento_possui_centro_cirurgico: boolean;
  estabelecimento_possui_centro_obstetrico: boolean;
  estabelecimento_possui_centro_neonatal: boolean;
  estabelecimento_possui_atendimento_hospitalar: boolean;
  estabelecimento_possui_servico_apoio: boolean;
  estabelecimento_possui_atendimento_ambulatorial: boolean;
}