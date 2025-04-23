import memory
from array import array

MPC = 0
MIR = 0

MAR = 0
MDR = 0
PC = 0
MBR = 0
X = 0
Y = 0

N = 0
Z = 1

BUS_A = 0
BUS_B = 0
BUS_C = 0

# Registradores novos
R1 = 0
R2 = 0

firmware = array('Q', [0]) * 512

# main: PC <- PC + 1; MBR <- read_byte(PC); GOTO MBR
firmware[0] = 0b0000000001000011010100100000001001000


# X = X + mem[address]
##2: PC <- PC + 1; MBR <- read_byte(PC); GOTO3
firmware[2] = 0b0000000110000011010100100000001001000
##3: MAR <- MBR; MDR <- read_word(MAR); GOTO 4
firmware[3] = 0b0000001000000001010010000000010010000
##4: X = X + MDR; GOTO 0
firmware[4] = 0b0000000000000011110000010000000011000

# mem[address] = X
##5: PC <- PC + 1; MBR <- read_byte(PC); GOTO 6
firmware[5] = 0b0000001100000011010100100000001001000
##6: MAR <- MBR; GOTO 7
firmware[6] = 0b0000001110000001010010000000000010000
##7: MDR <- X; write_word(MAR); GOTO 0
firmware[7] = 0b0000000000000001010001000000100011000

# GOTO address
##8: PC <- PC + 1; MBR <- read_byte(PC); GOTO 9
firmware[8] = 0b0000010010000011010100100000001001000
##9: PC <- MBR; MBR <- read_byte(PC); GOTO MBR
firmware[9] = 0b0000000001000001010000100000001010000

# X = X - mem[address]
##10: PC <- PC + 1; fetch; GOTO 11
firmware[10] = 0b0000010110000011010100100000001001000
##11: MAR <- MBR; MDR <- memory[MAR]; GOTO 12
firmware[11] = 0b0000011000000001010010000000010010000
##12: X <- X - MDR; GOTO 0
firmware[12] = 0b0000000000000011111100010000000011000

# X = X * mem[address]
##13: PC <- PC + 1; fetch; GOTO 14
firmware[13] = 0b0000011100000011010100100000001001000
##14: MAR <- MBR; MDR <- memory[MAR]; GOTO 15
firmware[14] = 0b0000011110000001010010000000010010000
##15: X <- X * MDR; GOTO 0
firmware[15] = 0b0000000000000000110100010000000011000

# if X == 0 then GOTO address
##16: X <- X; IF ALU == 0 then GOTO 273 ELSE GOTO 17
firmware[16] = 0b0000100010010001010000010000000011000
##17: PC <- PC + 1; GOTO 0
firmware[17] = 0b0000000000000011010100100000000001000
##273:GOTO 8
firmware[273] = 0b0000010000000000000000000000000000000

# X = X < mem[address]
##18: PC <- PC + 1; fetch; GOTO 19
firmware[18] = 0b0000100110000011010100100000001001000
##19: MAR <- MBR; MDR <- memory[MAR]; GOTO 20
firmware[19] = 0b0000101000000001010010000000010010000
##20: X <- X < MDR; GOTO 0
firmware[20] = 0b0000000000000001110100010000000000011


# X = X % mem[address]
##26: PC <- PC + 1; fetch; GOTO 27
firmware[26] = 0b0000110110000011010100100000001001000
##27: MAR <- MBR; read; GOTO 256
firmware[27] = 0b1000000000000001010010000000010010000
##256:X <- X - MDR; GOTO 28
firmware[256] = 0b0000111000000011111100010000000011000
##28: R1 <- X < MDR; IF ALU == 0 then GOTO 256 + 0 ELSE then GOTO 0
firmware[28] = 0b0000000000010001110100000100000000011


# X = X == mem[address]
##33: PC <- PC + 1; fetch; GOTO 34
firmware[33] = 0b0001000100000011010100100000001001000
##34: MAR <- MBR; read; GOTO 35
firmware[34] = 0b0001000110000001010010000000010010000
##35: R1 <- X - MDR; IF R1 (ALU) == 0 then GOTO 256 + 36 ELSE then GOTO 36
firmware[35] = 0b0001001000010011111100000100000011000
##36: X <- X - X; GOTO 0
firmware[36] = 0b0000000000000011111100010000000011011
##292:X <- R1 + 1; GOTO 0
firmware[292] = 0b0000000000000011010100010000000101000


# halt
firmware[255] = 0b0000000000000000000000000000000000000


def read_regs(reg_numB, reg_numA):  # parametro para a leitura do registrador para A
    # Adicao dos dois novos registradores
    global MDR, PC, MBR, X, Y, R1, R2, H, BUS_A, BUS_B

    if reg_numA == 0:
        BUS_A = MDR
    elif reg_numA == 1:
        BUS_A = PC
    elif reg_numA == 2:
        BUS_A = MBR
    elif reg_numA == 3:
        BUS_A = X
    elif reg_numA == 4:
        BUS_A = Y
    elif reg_numA == 5:
        BUS_A = R1
    elif reg_numA == 6:
        BUS_A = R2
    elif reg_numA == 7:
        BUS_A = H
    else:
        BUS_A = 0

    if reg_numB == 0:
        BUS_B = MDR
    elif reg_numB == 1:
        BUS_B = PC
    elif reg_numB == 2:
        BUS_B = MBR
    elif reg_numB == 3:
        BUS_B = X
    elif reg_numB == 4:
        BUS_B = Y
    elif reg_numB == 5:
        BUS_B = R1
    elif reg_numB == 6:
        BUS_B = R2
    elif reg_numB == 7:
        BUS_B = H
    else:
        BUS_B = 0


def write_regs(reg_bits):
    global MAR, MDR, PC, X, Y, R2, R1, H, BUS_C

    if reg_bits & 0b10000000:
        MAR = BUS_C
    if reg_bits & 0b01000000:
        MDR = BUS_C
    if reg_bits & 0b00100000:
        PC = BUS_C
    if reg_bits & 0b00010000:
        X = BUS_C
    if reg_bits & 0b00001000:
        Y = BUS_C
    if reg_bits & 0b00000100:
        R1 = BUS_C
    if reg_bits & 0b00000010:
        R2 = BUS_C
    if reg_bits & 0b00000001:
        H = BUS_C


def alu(control_bits):
    global N, Z, BUS_A, BUS_B, BUS_C

    a = BUS_A
    b = BUS_B
    out = 0

    shift_bits = control_bits & 0b11000000
    shift_bits = shift_bits >> 6

    control_bits = control_bits & 0b00111111

    if control_bits == 0b011000:
        out = a
    elif control_bits == 0b010100:
        out = b
    elif control_bits == 0b011010:
        out = ~a
    elif control_bits == 0b101100:
        out = ~b
    elif control_bits == 0b111100:
        out = a + b
    elif control_bits == 0b111101:
        out = a + b + 1
    elif control_bits == 0b111001:
        out = a + 1
    elif control_bits == 0b110101:
        out = b + 1
    elif control_bits == 0b111111:
        out = b - a
    elif control_bits == 0b110110:
        out = b - 1
    elif control_bits == 0b111011:
        out = -a
    elif control_bits == 0b001100:
        out = a & b
    elif control_bits == 0b011100:
        out = a | b
    elif control_bits == 0b010000:
        out = 0
    elif control_bits == 0b110001:
        out = 1
    elif control_bits == 0b110010:
        out = -1

    # CIRCUITOS ADICIONAIS: (MULTIPLICADOR E MENOR QUE)
    elif control_bits == 0b001101:
        out = a * b
    elif control_bits == 0b011101:
        out = int(a < b)

    if out == 0:
        N = 0
        Z = 1
    else:
        N = 1
        Z = 0

    if shift_bits == 0b01:
        out = out << 1
    elif shift_bits == 0b10:
        out = out >> 1
    elif shift_bits == 0b11:
        out = out >> 2

    BUS_C = out


def next_instruction(next, jam):
    global MPC, MBR, N, Z

    if jam == 0b000:
        MPC = next
        return

    # adição:
    if jam == 0b111:
        MPC = next & (~(~N + 1))
        return

    # adição:
    if jam == 0b110:
        MPC = next & (~(~Z + 1))
        return

    if jam & 0b001:
        next = next | (Z << 8)

    if jam & 0b010:
        next = next | (N << 8)

    if jam & 0b100:
        next = next | MBR

    MPC = next


def memory_io(mem_bits):
    global PC, MBR, MDR, MAR

    if mem_bits & 0b001:
        MBR = memory.read_byte(PC)

    if mem_bits & 0b010:
        MDR = memory.read_word(MAR)

    if mem_bits & 0b100:
        memory.write_word(MAR, MDR)


def step():
    global MIR, MPC

    MIR = firmware[MPC]

    if MIR == 0:
        return False

    # Separação das instruções com a word de 37 bits
    #						   ADDR      J    ULA       C	   M   B   A
    #						0b000000000 000 00000000 00000000 000 000 000
    read_regs((MIR & 0b0000000000000000000000000000000111000) >> 3, (MIR & 0b0000000000000000000000000000000000111))
    alu((MIR & 0b0000000000001111111100000000000000000) >> 17)
    write_regs((MIR & 0b0000000000000000000011111111000000000) >> 9)
    memory_io((MIR & 0b0000000000000000000000000000111000000) >> 6)
    next_instruction((MIR & 0b1111111110000000000000000000000000000) >> 28,
                     (MIR & 0b0000000001110000000000000000000000000) >> 25)

    return True