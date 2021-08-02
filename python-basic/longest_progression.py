import itertools

def palindrome(text):
    if text == text[::-1]:
        return True
    else:
        return False


T = int(input())
n_ks = []
input_strings = []
for i in range(T):
    n_ks.append(input().split(' '))
    s = input()
    input_strings.append(s)

for test_case in range(T):
    n = int(n_ks[test_case][0])
    k = int(n_ks[test_case][1])
    s = input_strings[test_case]

    all_chars = []
    for i in range(97,97+k):
        all_chars.append(chr(i))

    
    # all_perm = 
    # # all_perm = list(map(lambda x:''.join(x),all_perm))
    # for 

    poss = 0
    for item in itertools.product(all_chars,repeat=n):
        if ''.join(item) < s and palindrome(''.join(item)):
            poss += 1

    print (f'Case #{test_case+1}: {poss}')