import cs50

def main():

    sents = 0
    letters = 0
    word = 0

    s = cs50.get_string("Text: ")
    letters = len(s)

    for i in s:
        if i in [".", "?", "!"]:
            sents = sents + 1

    for i in s:
        if i == " ":
            word = word + 1

    sun = sents + word
    letters = letters - sun
    word = word + 1

    L = (letters / word) * 100
    S = (sents / word) * 100

    index = (0.0588 * L - 0.296 * S - 15.8)
    indexx = index

    if indexx < 1:
        print("Before Grade 1")

    elif indexx > 16:
        print("Grade 16+")
    else:
        print("Grade ", indexx)

main()

