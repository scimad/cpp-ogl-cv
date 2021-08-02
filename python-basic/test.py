
def palindrome(text):
    if text == text[::-1]:
        print("palindrome")
        return True
    else:
        print('not palindrome')
        return False


print (palindrome('aabbxaa'))