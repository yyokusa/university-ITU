import datetime 
from datetime import date 
import calendar 

def findDay(date): 
	day, month, year = (int(i) for i in date)	 
	born = datetime.date(year, month, day) 
	return born.strftime("%A") 

# Driver program 
i_date = input("enter date: d/m/y: ")
date = i_date.split(' ')
date2 = date[:]
final_year = int(input("final year: "))
var_range = final_year - int(date[2])
count = 0
value = int(date2[2]) + 1
date2[2] = str(value)
for i in range(var_range):
    if findDay(date) == findDay(date2):
        count += 1
        print(f"match {count} {i}: {findDay(date)}") 
    value = int(date2[2]) + 1
    date2[2] = str(value)
print(count, "matches total") 
print("initil date was ", findDay(date)) 
print("date2: ", date2) 
