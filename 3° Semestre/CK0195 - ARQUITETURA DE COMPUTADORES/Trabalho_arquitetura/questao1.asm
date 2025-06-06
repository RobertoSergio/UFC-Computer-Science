goto main
wb 0

r ww 1
a ww 0
b ww 2020
c ww 1
d ww 4
e ww 0

main add x, b
          resto x, d
          jz x, final
          mov x, e
          sub x, e
          goto final2

final2 add x, a
            mov x, r
            sub x, r
            goto final
final halt