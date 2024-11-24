busca_conexo
    Estado <- vetor[0, ... , n-1] de enumerações {não_atingido , atingido}
    // SubGrafo <- []
    SubGrafos <- []
    para v E V
        Estado[v] <- 'não_atingido'
    para u E V
        SubGrafo <- []
        se Estado[u] = 'não_atingido'
            Estado[u] <- 'atingido'
            distancia <- buscaemlargura[Grafo, u]
            para w E distancia
                se distancia[w] != -1
                    SubGrafo.inserir(w)
                    Estado[w] <- 'atingido'
            SubGrafo.correção()
            SubGrafos.inserir(SubGrafo)
    retornar SubGrafos

Kruskel
SubGrafos <- busca_conexo
while SubGrafos != NULO
    SubGrafo <- SubGrafos.pop()
    L <- lista com as arestas de SubGrafo ordenadas por w(peso)
    A <- []
    Rep<-vetor[0, ..., n-1]   de numeros
    Comp<-vetor[0, ..., n-1]  de numeros
    para u E V
        comp[u].primeiro<-novo_noh(u,nulo)
        comp[u].ultimo<-comp[u].primeiro
        comp[u].tam<-1
        rep[u]<-u
    enquanto |A|! = n-1
        {u,v}<-L.remover_primeiro()
        se rep[u]!=rep[v]
            A<- A U {{u,v}} // A.inserir{u,v}
            x<-rep[u]
            y<-rep[v]
            se comp[x].tam < comp[y].tam
                aux<-x;x<-y;y<-aux
            z<-com[y].primeiro
            comp[u].ultimo->proximo<-z
            comp[u].ultimo<-comp[y].ultimo
            comp[x]<-comp[x].tam+com[y].tam
            enquanto z != NULO
                rep[z->elem]<-x
                z<-z->prox
    retorne A
