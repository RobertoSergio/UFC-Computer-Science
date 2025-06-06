# Trabalho 2 - Sistemas Operacionais
Este repositório contém a implementação de um mini sistema com gerenciamento de memória e sistema de arquivos próprios, desenvolvido como parte do Trabalho 2 da disciplina de Sistemas Operacionais.

## Descrição do Projeto
O objetivo deste trabalho é criar um mini sistema que inclui:

## Sistema de Arquivos: 
Um sistema de arquivos simples, implementado dentro de um arquivo de 1 GB no sistema hospedeiro. O sistema de arquivos pode ter apenas o diretório raiz e arquivos com nomes de tamanho limitado. Implementações que incluam uma árvore de diretórios receberão pontos extras.

## Gerenciamento de Memória: 
Um gerenciamento de memória que utiliza uma "Huge Page" de 2 MBytes (ou equivalente em outros sistemas operacionais) para realizar a ordenação de listas de números. A memória paginada é necessária apenas para a ordenação, enquanto outras operações podem utilizar a memória comum do sistema hospedeiro.

## Funcionalidades
### O sistema deve aceitar os seguintes comandos:

### 1. Criar Arquivo
Comando: criar nome tam

Cria um arquivo com o nome especificado e preenche-o com uma lista aleatória de números inteiros positivos de 32 bits. O argumento tam define a quantidade de números na lista.

### 2. Apagar Arquivo
Comando: apagar nome

Apaga o arquivo com o nome especificado.

### 3. Listar Arquivos
Comando: listar

Lista todos os arquivos no diretório, mostrando o nome e o tamanho de cada arquivo em bytes. Ao final, exibe o espaço total do "disco" e o espaço disponível.

### 4. Ordenar Arquivo
Comando: ordenar nome

Ordena a lista de números no arquivo especificado. O algoritmo de ordenação é de livre escolha. Ao terminar a ordenação, exibe o tempo gasto em milissegundos.

### 5. Ler Sublista
Comando: ler nome inicio fim

Exibe uma sublista do arquivo especificado, com base no intervalo definido pelos argumentos inicio e fim.

### 6. Concatenar Arquivos
Comando: concatenar nome1 nome2

Concatena dois arquivos especificados. O arquivo resultante pode ter um nome predeterminado ou assumir o nome do primeiro arquivo. Os arquivos originais são removidos após a concatenação.

## Gerenciamento de Memória
Para a ordenação de listas, o sistema utiliza uma "Huge Page" de 2 MBytes. A memória paginada é implementada para garantir que apenas essa área de memória seja utilizada para a ordenação, enquanto outras operações podem utilizar a memória comum do sistema hospedeiro.
