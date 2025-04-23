goto main
wb 0

r ww 0
a ww 1
b ww 16
c ww 1
d ww 2


main add x, b
         jz x, final
         sub x, b
  raiz add x, b
         sub x, a
         mov x, b
         sub x, b
         add x, a
         add x, d
         mov x, a
         sub x, a
         add x, r
         add x, c
         mov x, r
         sub x, r
         add x, b
        jz x, final
        sub x, b
   goto raiz

final halt