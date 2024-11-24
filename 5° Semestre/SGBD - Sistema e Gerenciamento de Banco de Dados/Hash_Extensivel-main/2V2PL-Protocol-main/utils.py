# Funções utilitário
from objects import Objects

def create_environment():
    #Banco de dados
    BD = Objects(None, 'BD')
    #Areas
    BD.new_object('BD', 'A1')
    BD.new_object('BD', 'A2')
    BD.new_object('BD', 'A3')
    #Tables
    BD.new_object('A1', 'T1')
    BD.new_object('A1', 'T2')
    BD.new_object('A2', 'T3')
    BD.new_object('A2', 'T4')
    BD.new_object('A3', 'T5')
    BD.new_object('A3', 'T6')
    #Pages
    BD.new_object('T1', 'P1')
    BD.new_object('T1', 'P2')
    BD.new_object('T2', 'P3')
    BD.new_object('T2', 'P4')
    BD.new_object('T3', 'P5')
    BD.new_object('T3', 'P6')
    BD.new_object('T4', 'P7')
    BD.new_object('T4', 'P8')
    BD.new_object('T5', 'P9')
    BD.new_object('T5', 'P10')
    BD.new_object('T6', 'P11')
    BD.new_object('T6', 'P12')
    #Rows
    BD.new_object('P1', 'R1')
    BD.new_object('P1', 'R2')
    BD.new_object('P2', 'R3')
    BD.new_object('P2', 'R4')
    BD.new_object('P3', 'R5')
    BD.new_object('P3', 'R6')
    BD.new_object('P4', 'R7')
    BD.new_object('P4', 'R8')
    BD.new_object('P5', 'R9')
    BD.new_object('P5', 'R10')
    BD.new_object('P6', 'R11')
    BD.new_object('P6', 'R12')
    BD.new_object('P7', 'R13')
    BD.new_object('P7', 'R14')
    BD.new_object('P8', 'R15')
    BD.new_object('P8', 'R16')
    BD.new_object('P9', 'R17')
    BD.new_object('P9', 'R18')
    BD.new_object('P10', 'R19')
    BD.new_object('P10', 'R20')
    BD.new_object('P11', 'R21')
    BD.new_object('P11', 'R22')
    BD.new_object('P12', 'R23')
    BD.new_object('P12', 'R24')
    return BD

# supondo que cada transação tem 3 operações
def parse_schedule(input_str):
    parsed_schedule = []

    for element in range(0, len(input_str), 3):
        line = [input_str[element], input_str[element + 1], input_str[element + 2]]

        parse_schedule.append(line)

    # Função para converter uma string de entrada de transações em uma lista estruturada
    # Exemplo de input: "T1: R(A), W(A); T2: R(B), W(B)"
    # Saída: [('T1', 'R', 'A'), ('T1', 'W', 'A'), ('T2', 'R', 'B'), ('T2', 'W', 'B')]
    return parsed_schedule


"""
Seja S uma string, 

S[0] é a transação. Ex: 'T1'

S[1] é a operação. Ex: 'R'.

S[2] é o recurso (onde será aplicada a operação). Ex: 'A'.

"""
