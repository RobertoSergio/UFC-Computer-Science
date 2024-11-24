# Funções para detecção de deadlocks (grafo de espera) 

class DeadlockDetection:
    def __init__(self):
        self.wait_grafo = {} #'T1': ['T2', 'T3', 'T4'] == T1->T2, T1->T3, T1->T4
        self.past = []

    def start_grafo(self, schedule):
        for transaction in schedule:
            self.wait_grafo[transaction[0]] = []
        print(self.wait_grafo)

    def add_wait(self, espera, esperado):
        aux = self.wait_grafo[espera]
        if esperado not in aux:
            aux.append(esperado)
        self.wait_grafo[espera] = aux
        print(f"add_wait chamado: {espera} agora espera por {esperado}")
        print("----grafo depois de ser adicionado uma aresta____")
        print(self.wait_grafo )

    def detect_deadlock(self, no, prox, past):
        if no in past:
            self.past = past
            return True
        past.append(no)
        for i in prox:
            print(f'{no}->{i}')
            if self.detect_deadlock(i, self.wait_grafo[i], past):
                return True
        return False
    
    def recent_transaction(self):
        for transaction in self.wait_grafo.keys():
            if transaction in self.past:
                recent = transaction
        print(recent)
        return recent

    # apagar todo o grafo dentro do deadlock
    def apagar_grafo(self , schedule):
        self.wait_grafo = {}
        self.start_grafo(schedule)
    
    # Libera transação de dentro do grafo ( tira o vertice )
    def liberar_transacao(self, transacao):
        self.wait_grafo[transacao] = []
        for key in self.wait_grafo.keys():
            if transacao in self.wait_grafo[key]:
                self.wait_grafo[key].remove(transacao)
