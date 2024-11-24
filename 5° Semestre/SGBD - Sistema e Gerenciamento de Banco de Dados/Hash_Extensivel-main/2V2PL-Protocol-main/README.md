# Protocolo Conservador 2V2PL com Múltipla Granulosidade e Detecção de Deadlocks

Este projeto implementa um **protocolo de controle de concorrência** baseado no **2V2PL (Two-Phase Locking)** com suporte a **múltipla granulosidade de bloqueio**, **detecção de deadlocks** e **prevenção de deadlocks** usando um **grafo de espera**.

## Índice
- [Descrição](#descrição)
- [Funcionalidades](#funcionalidades)
- [Como Executar](#como-executar)
- [Exemplo de Uso](#exemplo-de-uso)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Contribuições](#contribuições)
- [Licença](#licença)

## Descrição

Este projeto é uma implementação de um protocolo de controle de concorrência usado para sincronizar transações em um sistema de banco de dados, garantindo a **serializabilidade** e evitando problemas de **deadlocks**. O protocolo segue o modelo de **bloqueio de duas fases** com suporte para múltiplos níveis de granularidade e diferentes tipos de bloqueios (compartilhado, exclusivo, e de atualização).

## Funcionalidades

- Implementação do protocolo 2V2PL com duas fases de bloqueio (crescimento e encolhimento).
- Suporte para múltiplas granularidades de bloqueio (tupla, página, tabela, etc.).
- Bloqueios intencionais (IS, IX, S, X) para garantir a consistência entre diferentes níveis de granularidade.
- Detecção de deadlocks através da construção de um **grafo de espera**.
- Prevenção de deadlocks usando a estratégia **Wait-Die** ou **Wound-Wait**.
- Tratamento de bloqueios de atualização para transações que lêem antes de modificar.
- Sincronização automática das operações de transações para evitar conflitos.

## Como Executar

### Pré-requisitos

- [Python 3.x](https://www.python.org/downloads/) ou outra linguagem (especificar)
- Bibliotecas necessárias (listar, caso existam)

### Passos

1. Clone o repositório:
   ```bash
   git clone https://github.com/seuusuario/seuprojeto.git
