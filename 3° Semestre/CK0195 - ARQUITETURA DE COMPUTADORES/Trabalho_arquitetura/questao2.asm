goto main
wb 0

r ww 1
a ww 0
b ww 4
c ww 1

main add x, b
         jz x, final
         sub x, b
 roda add x, b
         mov x, a
         sub x, c
         mov x, b
         sub x, b
         add x, r
         mult x, a
         mov x, r
         sub x, r
         add x, b
         jz x, final
         sub x, b
   goto roda

final halt