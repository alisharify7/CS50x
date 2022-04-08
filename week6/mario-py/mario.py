import cs50


# main function
def main():
    # get Height from user
    h = get_int()

    for i in range(h):
        # add spaces. decrementing so subract 1
        for jok in range(h - i - 1):
            print(" ", end="")
    # print hashtags
        for jeb in range(i + 1):
            print("#", end="")
        print("")


def get_int():
    while True:
        x = cs50.get_int("Height: ")
        if x > 0 and x < 9:
            break
    return x


main()

