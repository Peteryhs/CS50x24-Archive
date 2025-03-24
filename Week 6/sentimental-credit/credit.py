def canconverttoint(s):
    try:
        int(s)
        return True
    except ValueError:
        return False


card = input("Number: ")

if canconverttoint(card):

    num_list = [int(num_list) for num_list in str(card)]

    length = len(num_list)
    sum = 0

    odd_sum = 0

    even_sum = 0

    counter = 0
    for i in range(length):
        c = (length - 1 - i)

        if counter % 2 != 0:
            counter += 1
            value = num_list[c] * 2
            digit_value = [int(digit_value) for digit_value in str(value)]
            if value >= 10:
                firstdigit, seconddigit = digit_value
                odd_sum = odd_sum + firstdigit + seconddigit

            else:

                odd_sum = odd_sum + value
        else:
            counter += 1
            even_sum = even_sum + num_list[c]

    sum = even_sum + odd_sum

    if sum % 10 == 0:

        if (num_list[0] == 3 and (num_list[1] == 4 or num_list[1] == 7)) and length == 15:
            print("AMEX")
        elif num_list[0] == 5 and num_list[1] in [1, 2, 3, 4, 5] and length == 16:
            print("MASTERCARD")
        elif num_list[0] == 4 and (length == 13 or length == 16):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
