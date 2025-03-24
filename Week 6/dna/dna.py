import csv
import sys


def main():

    if len(sys.argv) - 1 != 2:
        print("Please enter the correct amount of arguements!")
    else:
        dbname = sys.argv[1]
        filename = sys.argv[2]

        data_list = []
        str_list = []

        with open(dbname, mode='r') as db:
            csv_reader = csv.DictReader(db)
            str_list = (csv_reader.fieldnames)

            for row in csv_reader:
                for key in row:

                    try:
                        row[key] = int(row[key])
                    except ValueError:
                        pass

                data_list.append(row)

        with open(filename, mode='r') as file:
            content = file.read()

        strcount = []
        for i in range(1, len(str_list)):

            strcount.append(longest_match(content, str_list[i]))

    for j in range(len(data_list)):
        match = True

        for k in range(1, len(str_list)):
            if strcount[k-1] != data_list[j][str_list[k]]:
                match = False
                break
        if match:
            print(data_list[j]['name'])
            exit()
    print("No match.")

    # TODO: Read database file into a variable

    # TODO: Read DNA sequence file into a variable

    # TODO: Find longest match of each STR in DNA sequence

    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
