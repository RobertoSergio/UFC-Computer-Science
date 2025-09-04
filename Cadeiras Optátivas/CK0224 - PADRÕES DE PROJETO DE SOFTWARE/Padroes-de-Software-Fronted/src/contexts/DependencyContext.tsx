// gen/src/contexts/DependencyContext.tsx

import React, { createContext, useContext, ReactNode } from 'react';
import { IEstablishmentRepository } from '@/repositories/interfaces/IEstablishmentRepository';
import { ApiEstablishmentRepository } from '@/repositories/establishmentRepository';
// Importe outros repositórios aqui quando forem refatorados

// 1. Define a "forma" das nossas dependências
interface AppDependencies {
  establishmentRepository: IEstablishmentRepository;
  // Outras dependências, ex: authRepository, evaluationRepository
}

// 2. Cria o Contexto com um valor inicial nulo
const DependencyContext = createContext<AppDependencies | null>(null);

// 3. Cria o Provedor que irá segurar e fornecer as instâncias
export const DependencyProvider = ({ children }: { children: ReactNode }) => {
  // Aqui instanciamos nossas dependências. Este é o único lugar
  // onde as implementações concretas (ApiEstablishmentRepository) são criadas.
  const dependencies: AppDependencies = {
    establishmentRepository: new ApiEstablishmentRepository(),
  };

  return (
    <DependencyContext.Provider value={dependencies}>
      {children}
    </DependencyContext.Provider>
  );
};

// 4. Cria um hook customizado para consumir as dependências facilmente
export const useDependencies = (): AppDependencies => {
  const context = useContext(DependencyContext);
  if (!context) {
    throw new Error('useDependencies deve ser usado dentro de um DependencyProvider');
  }
  return context;
};