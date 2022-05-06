import sys
import csv

#
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py CSV_FILE TEXT_FILE")

num_rowwwe = 0
#
database = {}
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        num_rowwwe += 1
        for column, value in row.items():
            database.setdefault(column, []).append(value)

#
with open(sys.argv[2]) as file2:
    dna = file2.read()

match = []
match_b12kp = []

#
for m in range(num_rowwwe-1):
    match.append(m)

#
for key in database.keys():
    conttador = 0
    maxiemo = 0
    #
    if key != 'name':
        #
        for i in range((len(dna)-len(key))):
            if dna[i:(len(key)+i)] == key:
                #
                for kek in range(i, ((len(dna)-len(key))), len(key)):
                    if dna[kek:(len(key)+kek)] == key:
                        conttador += 1
                    else:
                        #
                        if conttador > maxiemo:
                            maxiemo = conttador
                        conttador = 0
                        break

        #
        for sec in range(num_rowwwe-1):
            if int(database[key][sec]) == maxiemo:
                #
                if match.count(sec) > 0:
                    match_b12kp.append(sec)

        #
        if len(match_b12kp) == 0:
            print('No match')
            exit()

        #
        match.clear()
        match = match_b12kp.copy()
        match_b12kp.clear()

print(database["name"][match[0]])