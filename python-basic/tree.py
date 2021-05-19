'''
Implements Tree data structure and few algorithms
'''

class Node:
    '''
    This code is for class Node
    '''
    def __init__(self, name=None) -> None:
        self.name = name
        self.left = None
        self.right = None
        self.visited = False

    def set_lr(self, left, right):
        '''
        Setter function for binary tree
        '''
        self.left = left
        self.right = right

    @classmethod
    def sample_case1(cls):
        '''
        Factory function for following tree
                       A
                     /   \\
                    /      \\
                  B         C
                /   \\    /   \\
              D       E  F     G
            /   \\
          H       I
        '''
        t_h = Node('H')
        t_i = Node('I')
        t_d = Node('D')
        t_d.set_lr(t_h,t_i)

        t_e = Node('E')
        t_b = Node('B')
        t_b.set_lr(t_d,t_e)

        t_f = Node('F')
        t_g = Node('G')

        t_c = Node('C')
        t_c.set_lr(t_f,t_g)

        t_a = Node('A')
        t_a.set_lr(t_b, t_c)

        return t_a

    @classmethod
    def sample_case2(cls):
        '''
        Factory function to produce the following tree
                1
              /   \\
            2       3
          /   \\
        4       5
        '''
        t_4 = Node(4)
        t_5 = Node(5)
        t_2 = Node(2)
        t_2.set_lr(t_4, t_5)
        t_3 = Node(3)
        t_1 = Node(1)
        t_1.set_lr(t_2, t_3)

        return t_1


def start_end(traverse_func):
    '''
    decorator
    '''

    def wrapper(self, tree):
        '''
        One can use *args, **kwargs and expand the arguments
        but for now, it's okay to use self and tree
        '''
        print (f'Starting: {traverse_func.__name__}.')
        traverse_func(self, tree)
        print (f'Ending: {traverse_func.__name__}.')

    return wrapper

class Traversal:
    '''
    Traversal class:
    There are different traversal functions defined in this class.
    One should pass a Node object in the traversal functions.
    '''
    def __init__(self) -> None:
        pass

    def pre_order(self, tree):
        '''
        Function for preorder traversal of tree
        <Root, Left, Right>
        '''

        if tree is None:
            return
        print(tree.name)
        # tree.name += " visited"
        tree.visited = True
        self.pre_order(tree.left)
        self.pre_order(tree.right)

    def in_order(self, tree):
        '''
        Function for inorder traversal of tree
        <Left, Root, Right>
        '''

        if tree is None:
            return
        self.in_order(tree.left)
        print(tree.name)
        # tree.name += " visited"
        tree.visited = True
        self.in_order(tree.right)

    def post_order(self, tree):
        '''
        Function for postorder traversal of tree
        <Left, Right, Root>
        '''

        if tree is None:
            return
        self.post_order(tree.left)
        self.post_order(tree.right)
        print(tree.name)
        # tree.name += " visited"
        tree.visited = True

    @start_end
    def bfs(self, tree):
        '''
        Function for bfs traversal of tree
        '''
        queue = [tree]
        while len(queue)>0:
            current = queue.pop(0)
            if current is not None:
                print (current.name)
                queue.append(current.left)
                queue.append(current.right)

class TestCode:
    '''
    Driver code for the solution
    '''
    def __init__(self) -> None:
        pass

    @staticmethod
    def run_test():
        '''
        Static funciton to run test.
        '''
        traversal = Traversal()

        t_a = Node.sample_case1()
        t_1 = Node.sample_case2()

        # traversal.in_order(t_a)
        # print ('----')
        # traversal.post_order(t_a)
        # print ('----')
        # traversal.pre_order(t_a)
        # print ('----')
        traversal.bfs(t_a)
        print ('----')

        # traversal.in_order(t_1)
        # print ('----')
        # traversal.pre_order(t_1)
        # print ('----')
        # traversal.post_order(t_1)
        # print ('----')
        traversal.bfs(t_1)
        print ('----')

if __name__ == '__main__':
    test_code = TestCode()
    test_code.run_test()
