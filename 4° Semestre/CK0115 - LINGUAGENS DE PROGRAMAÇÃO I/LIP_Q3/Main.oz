%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402

declare [Circuitos] = {Module.link ['./Circuitos.oz']}

%Subtrator
A= 1|0|1|0|0|_
B= 1|1|0|1|0|_
Tin=1|_ S Tout in

{Subtrator5bits A B Tin S Tout}
{Browse inp(A B Tin)#sum(S Tout)}

%E primo 5 bits
declare
X=0|1|0|1|_ P in
{Circuitos.eprimo X P}
{Browse inp(X)#primo(P)}

%Sequencia de 1's em 7bits
declare
X=1|1|0|0|_ E in
{Circuitos.sequencia_de_1 X E}
{Browse E}