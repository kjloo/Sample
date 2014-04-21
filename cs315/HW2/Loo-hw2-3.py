#Kaleb Loo
# Homework 2 - problem 3
import re

# Write patterns for regular expressions a-d here

a = re.compile(r"^(([1-9])|(1[0-2])):([0-5]\d) (AM|PM)$")

b = re.compile(r"^(([A-Za-z_]\w*)?(, )?)*$")

c = re.compile(r"(\w+)\s*(<|<=|>|>=)\s*(\w+)")
dict = {'<':'>', '<=':'>=', '>':'<', '>=':'<='}
subStr = lambda x: x.group(3) + " " + dict[x.group(2)] + " " + x.group(1)
  # Place what you want to substitute (used in sub)

# Tests - do not modify

print("----Part a tests that match:")
print(a.search("1:45 PM"))
print(a.search("10:36 AM"))
print(a.search("12:00 PM"))
print(a.search("11:59 AM"))
print(a.search("8:27 AM"))

print("----Part a tests that do not match:")
print(a.search("21:45 PM"))
print(a.search("13:36 AM"))
print(a.search("12:00 XM"))
print(a.search("11:59 AP"))
print(a.search("8:3 AM"))
print(a.search("1:23PM"))
print(a.search("3:62 PM"))

print("----Part b tests that match:")
print(b.search("hello"))
print(b.search("_max3"))
print(b.search("hello, _max3"))
print(b.search("a, b, c, d, e, f"))
print(b.search("_, _a, _b3, get_Max, HELLO"))
print(b.search(""))

print("----Part b tests that do not match:")
print(b.search("hello,"))
print(b.search("hello,_max3"))
print(b.search("a, b, c, d, e, f,"))
print(b.search("aa, bb, cc, dd,  ee, f"))
print(b.search(" aa, bb, cc, dd, ee, f"))
print(b.search("aa, bb, cc, dd, ee, f "))
print(b.search(" "))
print(b.search("a, b, 5ac, fsa"))
print(b.search("6"))

print("----Part c tests:")
print(c.sub(subStr, "a < b"))
print(c.sub(subStr, "a<b"))
print(c.sub(subStr, "a     <    b"))
print(c.sub(subStr, "a <= b"))
print(c.sub(subStr, "aa <= bb"))
print(c.sub(subStr, "Hello! aa < bb Bye!"))
print(c.sub(subStr, "5 <= 15"))
print(c.sub(subStr, "5 <= 15 && 3 < 4"))
print(c.sub(subStr, "5 <= 15, 15 < 4, 23 <= 45"))
print(c.sub(subStr, "Fill in the blank: ____ < 315"))
print(c.sub(subStr, "< No substitutions here! <"))
print(c.sub(subStr, "!<!"))
