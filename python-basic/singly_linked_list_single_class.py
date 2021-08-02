'''
Module that implements and tests singly linked list
'''


class Node:
    '''
    Class that represents a Node for a linked list
    '''
    def __init__(self, data=None, next_node=None) -> None:
        self.data = data
        self.next_node = next_node


class SinglyLinkedList:
    '''
    Class to implement singly linked list data structure
    '''
    def __init__(self, head) -> None:
        self.head = head

    @classmethod
    def sample_linked_list_1(cls):
        next_node = Node('A', Node('D', Node('H', Node('A', Node('V', None)))))
        return cls(Node('M', next_node))

    def traverse(self):
        trav = self.head
        while trav is not None:
            print (trav.data)
            trav = trav.next_node
    
    def search(self, key):
        trav = self.head
        index = 0
        while trav != None:
            if trav.data == key:
                return index
            index += 1
            trav = trav.next_node
            


# class SLLAlgorithms:
#     '''
#     Class that implements the algorithms in Singly linked list
#     '''
#     def __init__(self) -> None:
#         pass

#     def traverse(self, linked_list):
#         '''
#         Function to traverse linked list
#         '''
#         if linked_list is None:
#             return

#         print(linked_list.data)
#         self.traverse(linked_list.next_node)

#     def search(self, linked_list, data):
#         '''
#         Function to search an element on linked list
#         '''
#         if linked_list.data == data:
#             print('Data found.')
#             return 0

#         return 1 + self.search(linked_list.next_node, data)
    
    


class Solution:
    '''
    Class to test our code
    '''
    def __init__(self) -> None:
        pass

    @staticmethod
    def test_code():
        sample_linked_list = SinglyLinkedList.sample_linked_list_1()
        # algo = SLLAlgorithms()
        # algo.traverse(sample_linked_list)
        # found_index = algo.search(sample_linked_list, 'H')
        # print(f'Data found at index: {found_index}')

        sample_linked_list.traverse()
        result = sample_linked_list.search('V')
        print (f'Given data found at index: {result}')


if __name__ == '__main__':
    Solution.test_code()
