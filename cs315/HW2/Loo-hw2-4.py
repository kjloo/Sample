#Kaleb Loo

filename = raw_input("Enter DFA Filename: ")
inFile = open(filename)
alphabet = inFile.readline().rstrip()
alphabet = alphabet.replace(" ", "")
n = len(alphabet)
DFA = {}
state = 0
for line in inFile:
    line = line.replace(" ", "")
    DFA[state] = [line[0], {alphabet[i]:line[i+1] for i in range(0,n)}]
    state = state + 1
inFile.close()

dict = {'+':"ACCEPTED", '-':"REJECTED"}
filename = raw_input("Enter Test Filename: ")
inFile = open(filename)
for line in inFile:
    state = 0
    n = len(line)
    for i in range(0,n-1):
        state = int(DFA[state][1][line[i]])
    print("String: %s Final state: %d %s" % 
          (line.rstrip(), state, dict[DFA[state][0]]))
inFile.close()
