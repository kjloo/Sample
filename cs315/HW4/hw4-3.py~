#Kaleb Loo
import datetime


class ImproperList(Exception) : pass
class EmptyList(Exception) : pass
class ImproperDate(Exception) : pass

def isLeapYear(year):
   return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)

def checkDate(date):
    month = date[0]
    day = date[1]
    year = date[2]
    if year < 1800:
        return False

    if month in (1, 3, 5, 7, 8, 10, 12):
        if day > 0 and day <= 31:
            return True
    elif month in (4, 6, 9, 11):
        if day > 0 and day <= 30:
            return True
    elif month == 2:
        if day > 0 and day <= (28 + isLeapYear(year)):
            return True
    return False

def getBestDate(date_list, score_func, low = False):
    if len(date_list) == 0:
        raise EmptyList
    else:
       i = iter(date_list)
       bestDate = i.next()
       if len(bestDate) != 3:
          raise ImproperList
       elif not checkDate(bestDate):
          raise ImproperDate
       else:
          topScore = score_func(bestDate)
          for date in i:
             if len(date) != 3:
                raise ImproperList
             elif not checkDate(date):
                raise ImproperDate
             else:
                score = score_func(date)
                if low:
                   if score < topScore:
                      topScore = score
                      bestDate = date
                else:
                   if score > topScore:
                      topScore = score
                      bestDate = date
    return bestDate
        

def genDateCompare(target):
    def daysAway(date):
       d0 = datetime.date(date[2], date[0], date[1])
       d1 = datetime.date(target[2], target[0], target[1])
       delta = d0 - d1
       return abs(delta.days)
    return daysAway

#1
inFile = open("dates.txt")
tmp = [x.rstrip().split() for x in inFile]
dateList = [(int(x[0]), int(x[1]), int(x[2])) for x in tmp]
inFile.close()

#2
month = input("Enter month: ")
day = input("Enter day: ")
year = input("Enter year: ")
targetDate = (month, day, year)

#3
dateCompare = genDateCompare(targetDate)

#4
bestDate = getBestDate(dateList, dateCompare)

#5
print(bestDate)

#6
def latestDate(date):
    score = date[0] * 100 + date[1]
    return score
result = getBestDate(dateList, latestDate)

#7
print(result)

#8
try:
   print(getBestDate([(1, 2, 3000, 3)], dateCompare))
except ImproperList:
   print("List incorrectly formatted")

try:
   print(getBestDate([], dateCompare))
except EmptyList:
   print("List is empty")

try:
   print(getBestDate([(1, 32, 2000)], dateCompare))
except ImproperDate:
   print("Invalid date")
