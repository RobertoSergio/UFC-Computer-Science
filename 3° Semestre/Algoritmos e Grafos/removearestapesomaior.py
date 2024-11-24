tem_circuito(G)
    Estado = (0 , ... , n-1) # de enumerações {nao_atingido,no_caminho, finalizado}
    circuito <-[]
    para v E V
    Estado[v] <- ['não_atingido']
    para v E V:
        se Estado[v] = 'não_atingido':
            se encontrou_circuito(G, Estado, v, ciclo):
                return circuito
    return []

encontrou_circuito(G, Estado, u , ciclo )
    Estado[u] <- 'no_caminho_atual'
    circuito.inserir(u)
    para v E N(G, u):
        se Estado[v] = 'no_caminho_atual':
            circuito.inserir(v)
                return true
          se Estado[v] = 'não_atingido':
              se encontrou_circuito(G, Estado, v , circuito):
                  return True

    Estado[u] <- 'finalizado'
    circuito.remover(u)
    return False

N(G, v)
    vizinhos <- []
    para aresta E G:
        se aresta[0] = v:
          vizinhos.inserir(aresta[1])
    return vizinhos

tamanho(ciclo)
    tam <- 0
        para i E circuito
            tam<- tam+1
    retorne tam

remove_aresta(G)
    while circuito <- tem_circuito(G)
        aresta_max <- (null,null)
        peso_max <- -1
        para i E tamanho(circuito)-1
            u <-circuito[i]
            v <-circuito[i+1]
            para aresta E G
                se aresta[0] = u e aresta[1] = v e aresta[2] > peso_max
                    peso_max = aresta[2]
                    aresta_max <- (u , v)
        G.remove(aresta)
    retorne G

#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#

def tem_ciclo(G):
    Estado = (0 , ... , n-1) # de enumerações {nao_atingido,no_caminho, finalizado}
    ciclo <-[]
    para v E V
    Estado[v] <- ['não_atingido']
    for v E V:
        if Estado[v] = 'não_atingido':
            if encontrou_ciclo(G, Estado, v, ciclo , None ):
                return ciclo
    return []

def encontrou_ciclo(G, Estado, u , ciclo, pai ):
    Estado[u] <- 'no_caminho_atual'
    ciclo.inserir(u)
    para v E N(E, u , pai ):
        if Estado[v] = 'no_caminho_atual':
            ciclo.inserir(v)
            return true
        if Estado[v] = 'não_atingido':
            if encontrou_ciclo(G, Estado, v , ciclo, u):
                return True
    
    Estado[u] <- 'finalizado'
    ciclo.remover(u)
    return False

def N(E, o, pai):
  L = []
    for k in E:
      if o in k and not(pai in k):
        if o == k[0]:
          L.append(k[1])
        else:
          L.append(k[0])

remove_aresta(G)
    while ciclo <- tem_circuito(G)
        aresta_max <- -1
        peso_max <- -1
        para i E tamanho(ciclo)-1)
            u <-ciclo[i]
            v <-ciclo[i+1]
            para aresta E G
                se aresta[0] = u e aresta[1] = v e aresta[2] > peso_max
                    max_peso = aresta[2]
                    aresta_max <- (u , v)
        G.remove(aresta_max)
    retorne G