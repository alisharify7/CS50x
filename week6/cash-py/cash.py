import cs50


def main():
    inpuT = input_fun()
    money = round(inpuT * 100)
    number = 0

    # cheak for 25 cent
    while money >= 25:
        money -= 25
        number = number + 1

    # cheak for 10 cent
    while money >= 10:
        money -= 10
        number = number + 1

    # cheak for 5 cent
    while money >= 5:
        money -= 5
        number = number + 1

    # cheak for 1 cent
    while money >= 1:
        money -= 1
        number = number + 1

    # print out put
    print(number)


def input_fun():
    while True:
        x = cs50.get_float("Change owed: ")
        if x > 0:
            break
    return x


main()
