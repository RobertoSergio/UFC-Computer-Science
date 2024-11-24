# Gerenciamento de transações (start, commit, abort)class TransactionManager:

class TransactionManager:
    def __init__(self):
        print('A TransactionManager has been created.\n')
        self.active_transactions = {}  # Armazena transações ativas

    def start_transaction(self, transaction_id):
        print(f"Starting transaction {transaction_id}")
        self.active_transactions[transaction_id] = {'status': 'active'}

    def start_processing(self, schedule, lock_manager, deadlock_manager, BD):
        print(schedule)
        
        for element in schedule:
            if element != None and element != 'C':
                # [transaction_id, operation, resource]
                transaction_id = element[0]
                operation = element[1]
                resource_original = element[2]
                if self.process(transaction_id, operation, resource_original, resource_original, lock_manager, deadlock_manager, schedule, BD):
                    childrens = BD.search_parent(resource_original).all_children()
                    parents = BD.search_parent(resource_original).all_parents()
                    for parent in parents:
                        self.process(transaction_id, "I"+operation, resource_original, parent, lock_manager, deadlock_manager, schedule, BD)
                    for children in childrens:
                        self.process(transaction_id, operation, resource_original, children, lock_manager, deadlock_manager, schedule, BD)
            elif element == 'C':
                transaction_id = element[0]
                operation = element[1]
                resource_original = element[2]
                self.process(transaction_id, operation, resource_original, resource_original, lock_manager, deadlock_manager, schedule, BD)

    def process(self, transaction_id, operation, resource_original, resource, lock_manager, deadlock_manager, schedule, BD):
        # Aqui, gerencie a lógica para processar cada operação (R, W, U, C, IR, IW, IU, IC) em um recurso
        # Adquirir o lock necessário
        if operation == 'R':
            return lock_manager.acquire_shared_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'W':
            return lock_manager.acquire_exclusive_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'U':
            return lock_manager.acquire_update_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'IC':
            return lock_manager.acquire_certify_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'IR':
            return lock_manager.acquire_intent_read_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'IW':
            return lock_manager.acquire_intent_write_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'IU':
            return lock_manager.acquire_intent_update_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'ICI':
            return lock_manager.acquire_intent_certify_lock(transaction_id, resource_original, resource, deadlock_manager, self, schedule, lock_manager, BD)
        elif operation == 'C':
            # print(" transacao com commit feita")
            return lock_manager.commit_transaction(transaction_id, resource, deadlock_manager, self, schedule, lock_manager, BD)

    def abort_transaction(self, transaction_id, schedule):
        print(f"Aborting transaction {transaction_id}")
        self.active_transactions.pop(transaction_id, None)

        for i in range(len(schedule)):
            if schedule[i][0] == transaction_id:
                schedule[i] = None

        new_schedule = [op for op in schedule if op is not None]

        return new_schedule