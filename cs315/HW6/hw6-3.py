#By: Kaleb Loo
#Homework 6 - problem 3
#5/31/14

import re

inFile = open("memory.txt")
n = int(inFile.readline().rstrip())
dict = {}
mark = []
sweep = []
var = re.compile(r"[A-Za-z_][A-Za-z_0-9]*")

#Make memory map
for line in inFile:
    line = line.rstrip().replace(" ", "").split(",")
    if not line[0] in dict:
        dict[line[0]] = []
    dict[line[0]].append(line[1])

#Mark nodes
stack = []
for key in dict:
    if var.search(key):
        pointer = key
        for node in dict[pointer]:
            if not int(node) in mark:
                stack.append(node)
                mark.append(int(node))
        while stack:
            pointer = stack.pop()
            if pointer in dict:
                for node in dict[pointer]:
                    if not int(node) in mark:
                        stack.append(node)
                        mark.append(int(node))

#Sweep nodes
for num in range(0,n):
    if not num in mark:
        sweep.append(num)

print("Marked nodes: " + (", ".join(str(x) for x in sorted(mark))))
print("Swept nodes: " + (", ".join(str(x) for x in sorted(sweep))))
