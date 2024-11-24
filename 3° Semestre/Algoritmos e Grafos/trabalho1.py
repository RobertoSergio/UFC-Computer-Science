def N(u, E):
  k = []
  for v in E:
    if u in v:
      if u == v[0]:
        k.append(v[1])
      else:
        k.append(v[0])
  return k


def comp(E, o):
  comp = []
  comp.append(o)
  F = []
  F.append(o)
  while len(F) != 0:
    u = F.pop(0)
    for v in N(u, E):
      if v not in comp:
        comp.append(v)
        F.append(v)
  comp.sort()
  return comp


var = input("")
var = input("")
n = int(input("").split("=")[1])
var = input("")
V = []
k = 0
while n != k:
  k = k + 1
  V.append(k)
var = input("")
E = []
while var != "":
  k = []
  k.append(int(var.split()[0]))
  k.append(int(var.split()[1]))
  E.append(k)
  try:
    var = input("")
  except EOFError as e:
    if e:
      break

G = [comp(E, V[0])]
while len(V) != 0:
  for p in G:
    for q in p:
      if q in V:
        V.remove(q)
  if len(V) != 0:
    G.append(comp(E, V[0]))
for k in G:
  output = str(k[0])
  for j in range(len(k) - 1):
    output = output + " " + str(k[j + 1])
  print(output)

[[1,3,6], [2,4,5], [7, 8, 9, 10]]