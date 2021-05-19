'''
Example of basic function decorator
'''

def join_msg(func):

    def new_add(a,b):
        '''
        This should take as many arguments as the function to be decorated
        '''
        return "The result is " + str(func(a,b))

    return new_add

################ Syntax A ################
@join_msg
def add(a,b):
    return a+b

################ Syntax B ################
def sub(a,b):
    return a-b

sub = join_msg(sub)

if __name__ == '__main__':
    print (add(10,5))
    print (sub(15,5))
