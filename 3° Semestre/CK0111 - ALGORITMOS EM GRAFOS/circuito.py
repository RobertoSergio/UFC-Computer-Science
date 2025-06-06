def tem_circuito(G):
    Estado = vetor [0 , ... , n-1] # de enumerações {nao_atingido,no_caminho, finalizado}
    circuito <- []
    para v ∈ V
        Estado[v] <- ['não_atingido']
    for v ∈ V:
        if Estado[v] = 'não_atingido'
            if encontrou_circuito(G, Estado, v, ciclo):
                return circuito
    return []

def encontrou_circuito(G, Estado, u , ciclo ):
    Estado[u] <- 'no_caminho_atual'
    circuito.inserir(u)
    para v ∈ N+(G, u):
        if Estado[v] = 'no_caminho_atual':
            circuito.inserir(v)
            return true
        if Estado[v] = 'não_atingido'
            if encontrou_circuito(G, Estado, v , ciclo):
                return True
    
    Estado[u] <- 'finalizado'
    circuito.remover(u)
    return False

def N(G, v)
    vizinhos <- []
    para aresta ∈ G:
        se aresta[0] = v
            vizinhos.inserir(aresta[1])
    return vizinhos

#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
              
estado <- vetor[0... n-1]{n_atingido,caminho_atual, finalizado}
P<-pilha vazia
para u em V:
    estado[u]=n_atingido

para u em V:
    se estado[u]=n_atingido:
        P.empilha(u)
        estado[u]<- caminho atual
        Enquanto pilha != vazia:
            a <- P.desempilha()
            para v ∈ N⁺(a):
                se estado[v] = caminho_atual:
                    retorne verdadeiro
                se estado[v] = n_atingido:
                    P.empilha(v)
                    estado[v]<-caminho_atual
            estado[a]<-finalizado
retorne falso

#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
#--------------------------------------------------------------------------------------#
estado <- vetor[0... n-1]{n_atingido,caminho_atual, finalizado}
P<-pilha vazia
para u em V:
    estado[u]=n_atingido

para u em V:
    se estado[u]=n_atingido:
        P.empilha(u)
        estado[u]<- caminho atual
        Enquanto pilha != vazia:
            a <- P.desempilha()
            para v ∈ N⁺(a):
                se estado[v] = caminho_atual:
                    retorne verdadeiro
                se estado[v] = n_atingido:
                    P.empilha(v)
                    estado[v]<-caminho_atual
            estado[a]<-finalizado
retorne falso