T = int(input())
n_s = []
input_strings = []


def getn_from_k_g(K,G):
    det = ((2*K-1)**2+8*G)**0.5
    r1 = (-(2*K+1) + det)/2
    # r2 = (-(2*K+1) - det)/2
    return r1

for i in range(T):
    n_s.append(int(input()))

for test_case in range(T):
    G = n_s[test_case]

    max_K = G
    count = 0
    for K in range(1, G+1):
        possible_n = getn_from_k_g(K,G)
        if possible_n%1 == 0:
            count+=1

    print (f'Case #{test_case+1}: {count}')