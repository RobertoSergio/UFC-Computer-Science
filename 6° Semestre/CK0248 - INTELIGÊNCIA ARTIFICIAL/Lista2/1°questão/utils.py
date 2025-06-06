dp = {}

def get_dp(jogador, estado):
    return dp.get(f"{jogador},{estado}")

def save_dp(jogador, estado, valor):
    dp[f"{jogador},{estado}"] = valor
    return valor

def minimax(estado, jogador):
    valor = get_dp(jogador, estado)
    if valor is not None:
        return valor
    if estado == 0:
        return save_dp(jogador, estado, 1 if jogador else -1)
    novos_estados = [estado - jogada for jogada in (1, 2, 3) if jogada <= estado]
    if jogador:  
        valores = [minimax(novo_estado, False) for novo_estado in novos_estados]
        return save_dp(jogador, estado, max(valores))
    else:  
        valores = [minimax(novo_estado, True) for novo_estado in novos_estados]
        return save_dp(jogador, estado, min(valores))
