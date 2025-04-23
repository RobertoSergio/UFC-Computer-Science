goto main
wb 0

r ww 2
a ww 0
total ww 1
c ww 1
d ww 2
contador ww 1
zera ww 0
teste ww 2

main  add x, total
          sub x, contador
          jz x, final
          mov x, zera
          sub x, zera
          add x, d
          mov x, teste
          sub x, teste
          add x, r
          add x, c
	      mov x, r
	      goto isPrimo

isPrimo resto x, teste
             jz x, main
             mov x, zera
             sub x, zera
             add x, teste
	         add x, c
	         mov x, teste
	         sub x, teste
             add x, r
             sub x, teste
	         jz x, addConte
             mov x, zera
             sub x, zera
             add x, r
             goto isPrimo
addConte add x, contador
	       add x, c
	       mov x, contador
	       sub x, contador
           goto main

final halt