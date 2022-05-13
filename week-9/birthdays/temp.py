from cs50 import SQL




db = SQL('sqlite:///birthdays.db')




temp = db.execute('SELECT name,day,month from birthdays')

names = []
# for each in temp:
#     names.append((
#     each[0],
#     str(each[1]) + '/' + str(each[2]),
#     ))


for name in temp:
    n = name['name']
    d = name['day']
    m = name['month']
    names.append((
        n , str(m) + '/' + str(d),
    ))

print(names)