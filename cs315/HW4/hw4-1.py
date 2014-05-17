#Kaleb Loo

def genLetters(string):
    for letter in string:
        if letter.isalpha():
            yield letter.lower()

#1
string = raw_input("Enter a string: ")

#2
letterTable = {}
for letter in genLetters(string):
    if letter in letterTable:
        letterTable[letter] += 1
    else:
        letterTable[letter] = 1

#3
genPairs = ((key, letterTable[key]) for key in sorted(letterTable))

#4
for pair in genPairs:
    print(pair)
