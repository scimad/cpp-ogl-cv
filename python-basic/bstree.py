'''
Module for binary search tree.
Definition of BSTree:
A BSTree must have following three properties:
- Each subtree on the left must be smaller (in a specified sense) than the root node
- Each subtree on the right must be larger (in a specified sense) than the root node
- Each subtree on the left and right must be a BSTree itself.
'''


from tree import Node


class BSNode:
    '''
    Class for Binary Search Tree
    '''
    def __init__(self, key, value=None, left=None, right=None) -> None:
        self.key = key
        self.value = 100 * key
        if value is not None:
            self.value = value
        self.left = left
        self.right = right

    def set_val(self, value):
        '''
        setter function for value
        '''
        self.value = value

    def set_lr(self, left, right):
        '''
        Setter function for left and right nodes
        '''
        self.left = left
        self.right = right

    @classmethod
    def sample_case_1(cls):
        '''
        Factory Function
                        8
                      /   \\
                    3       10
                  /   \       \\
                0       6       14
                      /   \\      \\
                    4       7       17
                                  /
                                15
        '''

        return BSNode(8,
            left=BSNode(3,
                    left=BSNode(0),
                    right=BSNode(6,
                        left=BSNode(4),
                        right=BSNode(7))),
            right=BSNode(10,
                        right=BSNode(14,right=BSNode(17,
                                                    left=BSNode(15)))))



class BS_Algo:
    '''
    class for Algorithms to perform actions of BS Tree
    '''
    def __init__(self) -> None:
        pass

    def search_key(self, bs_tree, key):
        if bs_tree == None:
            print('data not found.')
            return None
        print (f'currently scanning:{bs_tree.key}')
        if key == bs_tree.key:
            print (f'succesfully found. The value for the key {key} is {bs_tree.value}.')
            return bs_tree.value
        elif key < bs_tree.key:
            print('going left.')
            return self.search_key(bs_tree.left, key)
        elif key > bs_tree.key:
            print('going right.')
            return self.search_key(bs_tree.right, key)



class Solution:
    '''
    Our solution
    '''
    def __init__(self) -> None:
        pass

    @staticmethod
    def run_test():
        '''
        Static Method for tester class
        '''
        test_tree = BSNode.sample_case_1()
        bs_algo = BS_Algo()
        bs_algo.search_key(test_tree,6)

if __name__ == '__main__':
    Solution.run_test()
