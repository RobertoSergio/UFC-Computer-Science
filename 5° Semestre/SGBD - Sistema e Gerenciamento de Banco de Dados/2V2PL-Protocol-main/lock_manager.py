class LockManager:
    def __init__(self):
        # Armazena os locks para cada recurso
        self.locks = {}
        # Armazena as tentativas de aquisição de locks
        self.lock_attempts = {}
        # Armazena os bloqueios que passaram
        self.locks_approved = []
        # Armazena os bloqueios em espera
        self.transactions_waiting = []
        # Pega a matriz com as comparações
        self.lock_compatibility_matrix = LockCompatibilityMatrix()

    # Tentativa de adicionar bloqueio de leitura
    def acquire_shared_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        if not self.is_lock_compatible(transaction_id, 'R', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'R', resource, success=False)
            return False
        self.add_lock(transaction_id, 'R', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'R', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio de escrita
    def acquire_exclusive_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        if not self.is_lock_compatible(transaction_id, 'W', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'W', resource, success=False)
            return False
        self.add_lock(transaction_id, 'W', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'W', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio intencional de leitura
    def acquire_intent_read_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        if not self.is_lock_compatible(transaction_id, 'IR', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'IR', resource, success=False)
            return False
        self.add_lock(transaction_id, 'IR', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'IR', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio intencional de escrita
    def acquire_intent_write_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):

        if not self.is_lock_compatible(transaction_id, 'IW', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'IW', resource, success=False)
            return False
        self.add_lock(transaction_id, 'IW', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'IW', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio de update
    def acquire_update_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):

        if not self.is_lock_compatible(transaction_id, 'U', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'U', resource, success=False)
            return False
        self.add_lock(transaction_id, 'U', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'U', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio de certify lock
    def acquire_certify_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):

        if not self.is_lock_compatible(transaction_id, 'C', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'C', resource, success=False)
            return False
        self.add_lock(transaction_id, 'C', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'C', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio intencional de update
    def acquire_intent_update_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):

        if not self.is_lock_compatible(transaction_id, 'IU', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'IU', resource, success=False)
            return False
        self.add_lock(transaction_id, 'IU', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'IU', resource, success=True)
        return True

    # Tentativa de adicionar bloqueio intencional de certify lock
    def acquire_intent_certify_lock(self, transaction_id, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):

        if not self.is_lock_compatible(transaction_id, 'IC', resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            self.add_lock_attempt(transaction_id, 'IC', resource, success=False)
            return False
        self.add_lock(transaction_id, 'IC', resource_original, resource)
        self.add_lock_attempt(transaction_id, 'IC', resource, success=True)
        return True

    # adiciona o bloqueio em um recurso ( tupla, página, tabela)
    # Estou usando um dicionário locks que recebe locks[recurso] = [transação_id, lock_type]
    def add_lock(self, transaction_id, lock_type, resource_original, resource):
        """ Adiciona o lock ao recurso no formato (transaction_id, lock_type) """
        if resource not in self.locks:
            self.locks[resource] = []
        self.locks[resource].append([transaction_id, lock_type])
        if (resource_original == resource):
            if [transaction_id, lock_type, resource_original, 'Passou'] not in  self.locks_approved:
                self.locks_approved.append([transaction_id, lock_type, resource, 'Passou'])

    # Checa se o bloqueio que quero adicionar é compátivel com os bloqueios existentes no recurso
    def is_lock_compatible(self, transaction_id, new_lock_type, resource_original, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        """ Verifica se o lock que está sendo requisitado é compatível com os locks existentes """
        existing_locks = self.locks.get(resource, [])
        for lock in existing_locks:
            existing_transaction_id, existing_lock_type = lock
            
            # Exceção: Não verificar conflito se a mesma transação está tentando adquirir o lock
            if existing_transaction_id == transaction_id:
                continue
            
            if not self.lock_compatibility_matrix.is_compatible(new_lock_type, existing_lock_type):
                
                # Chama a função add_wait passando as transações em conflito
                deadlock_manager.add_wait(existing_transaction_id, transaction_id)
                if deadlock_manager.detect_deadlock(existing_transaction_id, deadlock_manager.wait_grafo[existing_transaction_id], []):
                    recent = deadlock_manager.recent_transaction()
                    new_schedule = transaction_manager.abort_transaction(recent, schedule)
                    deadlock_manager.apagar_grafo(new_schedule)
                    self.reset_locks()
                    print("Recomeçando o schedule depois de abortar uma transação")
                    transaction_manager.start_processing(new_schedule, lock_manager, deadlock_manager, BD)
                    lock_manager.display_locks_approved()
                    exit()

                if(resource_original == resource):
                    if [transaction_id, new_lock_type, resource] not in self.transactions_waiting:
                        self.add_waiting_transaction(transaction_id, new_lock_type, resource)
                    
                return False
            
        return True

    # Adicionar um bloqueio na lista de espera
    def add_waiting_transaction(self, transaction_id, lock_type, resource):
        """ Adiciona a transacao em espera a lista transactions_waiting """
        self.transactions_waiting.append([transaction_id, lock_type, resource])
    
    # Plotar os resultados da lista de bloqueios que passaram
    def display_locks_approved(self):
        """ Exibe todas as transações em espera de lock """
        if not self.locks_approved:
            print("Nenhuma transação aguardando lock.")
        else:
            print("Transações que passaram:")
            for transaction_id, lock_type, resource, status in self.locks_approved:
                if lock_type != 'C':
                    print(f"Transacao {transaction_id} -> Tipo de lock: {lock_type}")
                    # com status de no recurso {resource} com status de {status}
                else:
                    print(f"Transacao {transaction_id} -> Tipo de lock: {lock_type}")

    # Plotar os bloqueios que estão na espera
    def display_waiting_transactions(self):
        """ Exibe todas as transações em espera de lock """
        if not self.transactions_waiting:
            print("Nenhuma transação aguardando lock.")
        else:
            print("Transacoes aguardando liberação de outros bloqueios:")
            for transaction_id, lock_type, resource in self.transactions_waiting:
                print(f"Transacao {transaction_id} -> Tipo de lock: {lock_type} no recurso {resource}")

    # Exibir os bloqueios de cada recurso
    def display_locks(self):
        """ Exibe todos os locks atualmente adquiridos em cada recurso """
        if not self.locks:
            print("Nenhum lock foi adquirido.")
        else:
            print("Locks adquiridos:")
            for resource, lock_list in self.locks.items():
                print(f"Recurso {resource}:")
                for transaction_id, lock_type in lock_list:
                    print(f"  Transacao {transaction_id} -> Tipo de lock: {lock_type}")

    def display_lock_attempts(self):
        """ Exibe todas as tentativas de aquisição de locks para todos os recursos """
        if not self.lock_attempts:
            print("Nenhuma tentativa de lock foi registrada.")
        else:
            print("Tentativas de lock registradas:")
            for resource, attempts in self.lock_attempts.items():
                print(f"Recurso {resource}:")
                for attempt in attempts:
                    transaction_id, lock_type, status = attempt
                    status_str = 'Sucesso' if status == 1 else 'Falha'
                    print(f"  Transacao {transaction_id} tentou {lock_type} -> {status_str}")

    def add_lock_attempt(self, transaction_id, lock_type, resource, success):
        """ Registra a tentativa de aquisição de um lock, com o resultado (1 para sucesso, 2 para falha) """
        if resource not in self.lock_attempts:
            self.lock_attempts[resource] = []

        status = 1 if success else 2
        self.lock_attempts[resource].append((transaction_id, lock_type, status))

    def plot_lock_attempts(self, resource):
        """ Exibe a lista de tentativas de bloqueios de um recurso específico """
        attempts = self.lock_attempts.get(resource, [])
        if not attempts:
            print(f"Não há tentativas de bloqueio registradas para o recurso {resource}.")
            return
        
        print(f"Tentativas de bloqueio para o recurso {resource}:")
        for attempt in attempts:
            transaction_id, lock_type, status = attempt
            status_str = 'Sucesso' if status == 1 else 'Falha'
            print(f"Transacao {transaction_id} tentou {lock_type} -> {status_str}")
            
    # Reseta as listas/dicionários
    def reset_locks(self):
        self.locks = {}
        self.lock_attempts = {}
        self.locks_approved = []
        self.transactions_waiting = []

    # Função que é chamada na operação de Commit
    def commit_transaction(self, transaction_id_1, resource, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        # print(f"Committing transaction {transaction_id_1}")
        # Checa se é possivel e libera todos os bloqueios
        self.release_locks(transaction_id_1, deadlock_manager, transaction_manager, schedule, lock_manager, BD)
        
        # Com alguns bloqueios liberados, checamos os bloqueios da lista de espera podem acontecer
        for element in self.transactions_waiting:
            transaction_id = element[0]
            operation = element[1]
            resource_original = element[2]

            # Apago o bloqueio da lista de espera, para que não ocorra duplicação
            self.transactions_waiting = [
                el for el in self.transactions_waiting
                if not (el[0] == transaction_id and el[1] == operation and el[2] == resource)
            ]

            # Checa se o bloqueio da lista de espera pode acontecer
            for aux in self.locks_approved:
                # [transaction_id, operation, resource]
                transaction_id2 = aux[0]
                operation2 = aux[1]
                resource_original2 = aux[2]
                status = aux[3]
                if (status == "Liberado") and transaction_id != transaction_id2 and [transaction_id, operation, resource_original, 'Passou'] not in  self.locks_approved:
                    if operation == 'C':
                        transaction_manager.process(transaction_id, operation, resource_original, resource_original2, lock_manager, deadlock_manager, schedule, BD)

                    elif transaction_manager.process(transaction_id, operation, resource_original, resource_original, lock_manager, deadlock_manager, schedule, BD):
                        childrens = BD.search_parent(resource_original).all_children()
                        parents = BD.search_parent(resource_original).all_parents()
                        for parent in parents:
                            transaction_manager.process(transaction_id, "I"+operation, resource_original, parent, lock_manager, deadlock_manager, schedule, BD)
                        for children in childrens:
                            transaction_manager.process(transaction_id, operation, resource_original, children, lock_manager, deadlock_manager, schedule, BD)
                elif (status=="Passou") and [transaction_id, operation, resource_original] not in self.transactions_waiting and [transaction_id, operation, resource_original, 'Passou'] not in self.locks_approved:
                    self.add_waiting_transaction(transaction_id, operation, resource_original)
                    break

        already_committed = any(k[0] == transaction_id_1 and k[1] == 'C' for k in self.locks_approved)
        # Só adicionar se ainda não houver commit
        if not already_committed:
            for k in self.locks_approved:
                if k[0] == transaction_id_1 and k[3] == 'Liberado' and k[1] != 'C':
                    self.locks_approved.append([transaction_id_1, 'C', '', ''])
                    break
    
    def release_locks(self, transaction_id, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        # Libera todos os locks associados à transação
        for element in self.transactions_waiting:
            if transaction_id == element[0]:
                # print("Há transações esperando, liberar os locks pode não ser imediato.")
                self.add_waiting_transaction(transaction_id, 'C', '')
                break
        
        # se conseguir modificar os de escrita para certify lock libera os bloqueios daquela transação
        if self.write_in_read_is_possible(transaction_id, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
            for resource, locks in list(self.locks.items()): 
                # Filtra apenas os locks que pertencem à transação atual
                new_locks = [lock for lock in locks if lock[0] != transaction_id]
                # Se havia locks da transação atual, liberá-los
                if len(new_locks) != len(locks):
                    # print(f"Liberando locks da Transação {transaction_id} no recurso {resource}")
                    # Atualiza os locks do recurso com a lista filtrada
                    if new_locks:
                        self.locks[resource] = new_locks
                    else:
                        del self.locks[resource]

                    # Atualiza o status em locks_approved
                    for lock in locks:
                        if lock[0] == transaction_id:
                            lock_type = lock[1]
                            # Registra a liberação no histórico de locks aprovados
                            # self.locks_approved -> (transaction_id, lock_type, resource, "Liberado")
                            for i in self.locks_approved:
                                if (i[0] == transaction_id):
                                    i[3] = "Liberado"
        
            deadlock_manager.liberar_transacao(transaction_id)

    def write_in_read_is_possible(self, transaction_id, deadlock_manager, transaction_manager, schedule, lock_manager, BD):
        # Primeiro, verificar se existe um bloqueio de escrita para a transação no recurso especificado
        has_write_lock = []
        for lock in self.locks_approved:
            approved_transaction_id = lock[0] 
            lock_type = lock[1]
            approved_resource = lock[2]
            status = lock[3]
            if approved_transaction_id == transaction_id and lock_type == 'W' and status == 'Passou':
                has_write_lock.append([transaction_id, lock_type , approved_resource, status])

        if not has_write_lock:
            # print(f"A transação {transaction_id}")
            return True

        # Olha se tem bloqueio de leitura de uma transação diferente.
        for lock in self.locks_approved:
            for write in has_write_lock:
                approved_transaction_id = lock[0] 
                lock_type = lock[1]
                approved_resource = lock[2]
                status = lock[3]
                write_transaction_id = write[0] 
                write_lock_type = write[1]
                write_resource = write[2]
                write_status = write[3]

                # Se o bloqueio de escrita for bloqueado, adiciona o commit na espera
                # Se ocorrer deadlock, abortar transação mais recente e recomeça o schedule
                if approved_transaction_id != write_transaction_id and approved_resource == write_resource and lock_type == 'R' and status == 'Passou':
                    # print(f"A transação {transaction_id} não pode converter o bloqueio de escrita em leitura porque há um bloqueio de leitura no recurso {write_resource}.")
                    self.add_waiting_transaction(transaction_id, 'C', '')
                    deadlock_manager.add_wait(approved_transaction_id, write_transaction_id)
                    if deadlock_manager.detect_deadlock(approved_transaction_id, deadlock_manager.wait_grafo[approved_transaction_id], []):
                        recent = deadlock_manager.recent_transaction()
                        new_schedule = transaction_manager.abort_transaction(recent, schedule)
                        deadlock_manager.apagar_grafo(new_schedule)
                        self.reset_locks()
                        print("Recomeçando o schedule depois de abortar uma transação")
                        transaction_manager.start_processing(new_schedule, lock_manager, deadlock_manager, BD)
                        for i in self.transactions_waiting:
                            if i[1] == 'C':
                                transaction_manager.process(i[0], i[1], i[2], i[2], lock_manager, deadlock_manager, new_schedule, BD)
                        lock_manager.display_locks_approved()
                        exit()
                    return False

        for write in has_write_lock:
            approved_transaction_id = write[0] 
            lock_type = write[1]
            approved_resource = write[2]
            status = write[3]

            # Converte o bloqueio de escrita para certify lock
            if approved_transaction_id == transaction_id and lock_type == 'W':
                # Libera os bloqueios
                for i in self.locks_approved:
                                if (i[0] == approved_transaction_id) and (i[1] == lock_type) and (i[2] == approved_resource):
                                    i[3] = "Liberado"

                # Converte os filhos e pais
                self.locks[approved_resource] = 'CL'
                childrens = BD.search_parent(approved_resource).all_children()
                parents = BD.search_parent(approved_resource).all_parents()
                for parent in parents:
                    transaction_id, lock_type = self.locks[parent][0]
                    if lock_type=='IW':
                        self.locks[parent] = [transaction_id, 'ICL']

                for children in childrens:
                    transaction_id, lock_type = self.locks[children][0]
                    if lock_type=='W':
                        self.locks[children] = [transaction_id, 'CL']

                return True

class LockCompatibilityMatrix:
    def __init__(self):
        self.matrix = {
            'R': {'R': True, 'W': True, 'C': False, 'U': False, 'IR': True, 'IW': True, 'IU': False, 'IC': False},
            'W': {'R': True, 'W': False, 'C': False, 'U': False, 'IR': True, 'IW': False, 'IU': False, 'IC': False},
            'CL': {'R': False, 'W': False, 'C': False, 'U': False, 'IR': False, 'IW': False, 'IU': False, 'IC': False},
            'U': {'R': True, 'W': False, 'C': False, 'U': False, 'IR': True, 'IW': False, 'IU': False, 'IC': False},
            'IR': {'R': True, 'W': True, 'C': False, 'U': False, 'IR': True, 'IW': True, 'IU': True, 'IC': True},
            'IW': {'R': True, 'W': False, 'C': False, 'U': False, 'IR': True, 'IW': True, 'IU': True, 'IC': True},
            'IU': {'R': True, 'W': False, 'C': False, 'U': False, 'IR': True, 'IW': True, 'IU': True, 'IC': True},
            'ICL': {'R': False, 'W': False, 'C': False, 'U': False, 'IR': True, 'IW': True, 'IU': True, 'IC': True}
        }

    def is_compatible(self, new_lock, existing_lock):
        return self.matrix[new_lock].get(existing_lock, False)