#Kaleb Loo

def countPairs(filename):
    inFile = open(filename)
    dict = {}
    for line in inFile:
        for i in range(0, len(line) - 1):
            pair = line[i] + line[i + 1]
            pair = pair.lower()
            if pair.isalpha():
                if pair in dict:
                    dict[pair] = dict[pair] + 1
                else:
                    dict[pair] = 1
    return dict

def getTopFivePairs(pairDict):
    list = []
    length = 5
    max = 0
    count = 0
    for pair in pairDict:
        if pairDict[pair] > max:
            max = pairDict[pair]
    while count < length and count < len(pairDict):
        tmp = []
        for pair in pairDict:
            if pairDict[pair] == max:
                tmp.append((pair, pairDict[pair]))
                count = count + 1
            tmp.sort()
        for item in tmp:
            list.append(item)
        max = max - 1;
    return list

def createFollowsDict(pairDict, letter):
    dict = {}
    for num in range(ord('a'), ord('z') + 1):
        dict[chr(num)] = 0
    for pair in pairDict:
        if pair[0] == letter:
            dict[pair[1]] = pairDict[pair]
    return dict

def combineDict(dict1, dict2):
    dict = {}
    for pair in dict1:
        dict[pair] = dict1[pair]
    for pair in dict2:
        if pair in dict:
            dict[pair] = dict[pair] + dict2[pair]
        else:
            dict[pair] = dict2[pair]
    return dict

#Driver
#1
dict1 = countPairs("text1.txt")
#2
dict2 = countPairs("text2.txt")
#3
list1 = getTopFivePairs(dict1)
#4
print(list1)
#5
list2 = getTopFivePairs(dict2)
#6
print(list2)
#7
for vowel in "aeiou":
#a
    print(vowel)
#b
    dict = createFollowsDict(dict1, vowel)
#c
    list = [dict[chr(letter)] for letter in range(ord('a'), ord('z') + 1)]
#d
    print(list)
#8
for vowel in "aeiou":
#a                                                                              
    print(vowel)
#b                                                                              
    dict = createFollowsDict(dict2, vowel)
#c                                                                              
    list = [dict[chr(letter)] for letter in range(ord('a'), ord('z') + 1)]
#d                                                                              
    print(list)
#9
dict3 = combineDict(dict1, dict2)
#10
print(dict3)
