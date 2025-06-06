dp = {}

def get_dp(jogador, estado):
    return dp.get(f"{jogador},{estado}")

def save_dp(jogador, estado, valor):
    dp[f"{jogador},{estado}"] = valor
    return valor

def possible_new_states(estado):
    for i, fichas in enumerate(estado):
        for num_retirar in range(1, fichas + 1):
            novo_estado = list(estado)
            novo_estado[i] -= num_retirar
            yield tuple(novo_estado)

def evaluate(estado, jogador):
    if all(fichas == 0 for fichas in estado):
        return 1 if not jogador else -1

def minimax(estado, jogador):
    valor = get_dp(jogador, estado)
    if valor is not None:
        return valor

    if all(fichas == 0 for fichas in estado):
        return save_dp(jogador, estado, 1 if not jogador else -1)

    novos_estados = possible_new_states(estado)
    if jogador:
        valores = [minimax(novo_estado, False) for novo_estado in novos_estados]
        return save_dp(jogador, estado, max(valores))
    else:
        valores = [minimax(novo_estado, True) for novo_estado in novos_estados]
        return save_dp(jogador, estado, min(valores))

def best_move(estado, jogador):
    melhores_jogadas = []
    melhor_valor = float("-inf") if jogador else float("inf")
    
    for novo_estado in possible_new_states(estado):
        valor = minimax(novo_estado, not jogador)
        if (jogador and valor > melhor_valor) or (not jogador and valor < melhor_valor):
            melhor_valor = valor
            melhores_jogadas = [novo_estado]
        elif valor == melhor_valor:
            melhores_jogadas.append(novo_estado)

    return melhores_jogadas[0]
