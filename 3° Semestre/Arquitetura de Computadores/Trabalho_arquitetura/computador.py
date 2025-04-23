import memory as mem
import clock as clk
import cpu as cpu
import disco
import sys

disco.read(str(sys.argv[1]))

print(mem.read_word(1))

clk.start([cpu])

print(mem.read_word(1))