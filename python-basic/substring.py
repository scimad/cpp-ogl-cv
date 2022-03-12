T = int(input())
l_s = []
for i in range(T):
    l = int(input())
    s = input()
    l_s.append([l, s])

for i in range(T):
    string = l_s[i][1]
    string_result = [1] * l_s[i][0]
    for j in range(1, l_s[i][0]):
        if ord(string[j:j+1]) > ord(string[j-1:j]):
            string_result[j] = string_result[j-1]+1
    
    print_string = str(string_result)[1:-1].replace(',', '')
    print (f'Case #{i+1}: {print_string}')