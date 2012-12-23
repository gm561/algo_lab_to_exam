from random import randint

NUM_TEST_CASES = 1000
MAX_NUM_FLOORS = 100000
MAX_INT = pow(2,31) - 1

rows = []

for i in range(0, NUM_TEST_CASES) :
    floors = randint(1, MAX_NUM_FLOORS)
    rows.append([floors])
    for i in range(0, floors) :
        weight = randint(0, MAX_INT)
        capacity = randint(weight, MAX_INT)
        cost = randint(0, MAX_INT)
        rows.append([weight, capacity, cost])

print NUM_TEST_CASES
for row in rows :
    to_print = ""
    for item in row :
        to_print += " "
        to_print += " " + str(item)
    print to_print

