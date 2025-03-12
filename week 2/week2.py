# t = [['' for _ in range(10)] for _ in range(10)]
# m = input()
# n = len(m)
# r, c = 0, 0
# for i in range(n):
#     if i == '|':
#         t[r][r + 1] = 'E'
#         t[r + 1][r + 2] = m[i - 1]
#         t[r + 2][r + 5] = 'E'
#         t[r][r + 3] = 'E'
#         t[r + 4][r + 5] = 'E'
#         t[r + 3][r + 4] = m[i + 1]
#         r += 5
#     elif i == '*':
#         t[r - 1][r] = 'E'
#         t[r][r + 1] = 'E'
#         t[r][r + 3] = 'E'
#         t[r + 1][r + 2] = m[i - 1]
#         t[r + 2][r + 1] = 'E'
#         t[r + 2][r + 3] = 'E'
#         r += 3
#     elif i == '+':
#         t[r][r + 1] = m[i - 1]
#         t[r + 1][r] = 'E'
#         r += 1
#     else:
#         if c == 0:
#             if m[i].isalpha() and m[i + 1].isalpha():
#                 t[r][r + 1] = m[i]
#                 t[r + 1][r + 2] = m[i + 1]
#                 r = r + 2
#                 c = 1
#             c = 1
#         elif c == 2:
#             if m[i + 1].isalpha():
#                 t[r][r + 1] = m[i + 1]
#                 r = r + 1
#                 c = 2
#         else:
#             if m[i + 1].isalpha():
#                 t[r][r + 1] = m[i + 1]
#                 r = r + 1
#                 c = 3
# for i in range(r + 1):
#     print(i, end=" ")
# for i in range(r + 1):
#     for j in range(c + 1):
#         print(t[i][j], end=" ")
#     print()


# print(f"Start state: 0, End state: {i-1}")
def regex_to_nfa(regex):
    # Initialize transition table with empty strings
    t = [['' for _ in range(20)] for _ in range(20)]
    n = len(regex)
    r = 0  # Current state

    i = 0
    while i < n:
        if regex[i] == '|':
            # Handle OR operation
            t[0][1] = 'E'
            t[1][2] = regex[i - 1]
            t[2][5] = 'E'
            t[0][3] = 'E'
            t[3][4] = regex[i + 1]
            t[4][5] = 'E'
            r = 5  # Set r to 5 for OR operation
            i += 2

        elif regex[i] == '*':
            # Handle Kleene closure
            t[r - 1][r] = 'E'
            t[r][r + 1] = 'E'
            t[r][r + 3] = 'E'
            t[r + 1][r + 2] = regex[i - 1]
            t[r + 2][r + 1] = 'E'
            t[r + 2][r + 3] = 'E'
            r += 3
            i += 1

        elif regex[i] == '+':
            # Handle one or more occurrences
            t[r][r + 1] = regex[i - 1]
            t[r + 1][r] = 'E'
            r += 1
            i += 1

        else:
            # Handle regular characters
            if i + 1 < n and regex[i + 1] not in '|*+':
                t[r][r + 1] = regex[i]
                t[r + 1][r + 2] = regex[i + 1]
                r += 2
                i += 2
            else:
                t[r][r + 1] = regex[i]
                r += 1
                i += 1

    # Print the transition table
    print("\nTransition Table:")
    print("   ", end="")
    for i in range(r + 1):
        print(f"{i:3}", end="")
    print()

    for i in range(r + 1):
        print(f"{i:2} ", end="")
        for j in range(r + 1):
            if t[i][j]:
                print(f"{t[i][j]:3}", end="")
            else:
                print(" _ ", end="")
        print()

    print(f"\nStart state: 0")
    print(f"End state: {r}")


# Test the function
regex = input("Enter regex: ")
regex_to_nfa(regex)
