from transaction_manager import TransactionManager
from lock_manager import LockManager
from deadlock_manager import DeadlockDetection
from utils import create_environment

# Iniciar o gerenciador de transações e locks
transaction_manager = TransactionManager()
lock_manager = LockManager()
deadlock_manager = DeadlockDetection()
BD = create_environment()

def main():
    # Exemplo de escalonamento: T1: R(A), W(A), T2: R(B), W(B), ...
    schedule = [
        ['T1', 'R', 'R1'], 
        ['T2', 'R', 'R1'],
        ['T1', 'W', 'R1'], 
        ['T1', 'R', 'R3'],
        ['T1', 'C', ''], 
        ['T2', 'W', 'R2'],
        ['T3', 'R', 'R2'],
        ['T2', 'C', ''],
        ['T3', 'W', 'R3'],
        ['T3', 'C', ''],
    ]

    deadlock_manager.start_grafo(schedule)

    # Processar o escalonamento
    transaction_manager.start_processing(schedule, lock_manager, deadlock_manager, BD)
    
    lock_manager.display_locks_approved()
    lock_manager.display_waiting_transactions()
if __name__ == '__main__':
    main()
