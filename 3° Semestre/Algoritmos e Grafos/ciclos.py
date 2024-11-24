def tem_ciclo(G):
    Estado = vetor[0 , ... , n-1] # de enumerações {nao_atingido,no_caminho, finalizado}
    ciclo <-[]
    para v ∈ V
        Estado[v] <- ['não_atingido']
    for v E V:
        if Estado[v] = 'não_atingido':
            if encontrou_ciclo(G, Estado, v, ciclo , None ):
                return ciclo
    return []

def encontrou_ciclo(G, Estado, u , ciclo, pai ):
    Estado[u] <- 'no_caminho_atual'
    ciclo.inserir(u)
    para v ∈ N(E, u , pai ):
        if Estado[v] = 'no_caminho_atual':
            if v=o:
                ciclo.inserir(v)
                return true
        if Estado[v] = 'não_atingido':
            if encontrou_ciclo(G, Estado, v , ciclo, u):
                return True
    
    Estado[u] <- 'finalizado'
    ciclo.remover(u)
    return False

def N(E, v, pai):
  L = []
    for aresta in E:
      if v in aresta and not(pai in aresta):
        if v == aresta[0]:
          L.append(aresta[1])
        else:
          L.append(aresta[0])