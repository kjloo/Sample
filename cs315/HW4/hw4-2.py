#Kaleb Loo

import random

class DuplicateValue(Exception) : pass

def insert(tree, value):
    if not search(tree, value):
        if len(tree) == 0:
            tree.append(value)
            tree.append([])
            tree.append([])
        else:
            if value < tree[0]:
                insert(tree[1], value)
            else:
                insert(tree[2], value)
    else:
        raise DuplicateValue
    
            

def search(tree, value):
    if len(tree) == 0:
        return False
    elif tree[0] == value:
        return True
    else:
        if value < tree[0]:
            return search(tree[1], value)
        else:
            return search(tree[2], value)

def preorder(tree):
    if len(tree) != 0:
        yield (tree[0])
        for node in preorder(tree[1]):
            yield node
        for node in preorder(tree[2]):
            yield node

#1
tree = []
count = 0
while count < 10:
    value = random.randrange(1,51)
    try:
        insert(tree, value)
    except DuplicateValue:
        print("Value already exists in tree")
    else:
        count += 1

#2
print(tree)

#3
dict = {True: "YES", False: "NO"}
for num in range(1,10):
    print("%d: %s" % (num, dict[search(tree, num)]))

#4
for node in preorder(tree):
    print(node)

#5
list = [num for num in preorder(tree)]
print(list)
