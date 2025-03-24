def canconverttoint(s):
    try:
        int(s)
        return True
    except ValueError:
        return False


while True:
    x = input("Height: ")
    if canconverttoint(x) and int(x) > 0 and int(x) <= 8:
        x = int(x)
        for i in range(x):
            print(" "*(x-i-1)+"#"*(i+1), "", "#"*(i+1))
        exit()
