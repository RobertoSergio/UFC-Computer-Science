Kruskel
    L <- lista com as arestas de G ordenadas por w(peso)
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
            comp[x].ultimo->proximo<-z
            comp[x].ultimo<-comp[y].ultimo
            comp[x]<-comp[x].tam+com[y].tam
            enquanto z != NULO
                rep[z->elem]<-x
                z<-z->prox
    retorne A

Kruskel
    L <- lista com as arestas de G ordenadas por w(peso)
    A <- []
    criar_comp_conexas()
    enquanto |A|!=|V|-1
        {u,v}<-L.remover_primeiro()
        se rep[u]!=rep[v]
            A<- A U {{u,v}}
            unir(u,v)
retorne A

criar_comp_conexa
    Rep<-vetor[0, ..., n-1]  
    Comp<-vetor[0, ..., n-1]  
    para u E V
        comp[u].primeiro<-novo_noh(u,nulo)
        comp[u].ultimo<-comp[u].primeiro
        comp[u].tam<-1