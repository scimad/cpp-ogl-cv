'''
Module that implements and tests Doubly linked list
'''


class Node:
    '''
    Class that represents a Node for a linked list
    '''
    def __init__(self, data=None, next_node=None, prev_node=None) -> None:
        self.data = data
        self.next_node = next_node
        self.previous_node = prev_node



class DoublyLinkedList:
    '''
    Class to implement Doubly linked list data structure
    '''
    def __init__(self, *args) -> None:
        for i, node in enumerate(args[1:-1]):
            node.previous_node = args[i-1]
            node.next_node = args[i+1]
        
        self.head = args[0]
        self.tail = args[-1]
        # args[0].previous_node = None
        # args[-1].next_node = None

    @classmethod
    def sample_linked_list_1(cls):
        return cls(Node('M'),Node('A'), Node('D'), Node('H'), Node('A'), Node('V'))

    def traverse_forward(self):
        trav = self.head
        while trav is not None:
            print (trav.data)
            trav = trav.next_node

    def traverse_backward(self):
        trav = self.tail
        while trav is not None:
            print (trav.data)
            trav = trav.previous_node
    
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
#     Class that implements the algorithms in Doubly linked list
#     '''
#     def __init__(self) -> None:
#         pass

#     def traverse_forward(self, linked_list):
#         '''
#         Function to traverse linked list
#         '''
#         if linked_list is None:
#             return

#         print(linked_list.data)
#         self.traverse_forward(linked_list.next_node)

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
        sample_linked_list = DoublyLinkedList.sample_linked_list_1()
        # algo = SLLAlgorithms()
        # algo.traverse_forward(sample_linked_list)
        # found_index = algo.search(sample_linked_list, 'H')
        # print(f'Data found at index: {found_index}')

        sample_linked_list.traverse_forward()
        # sample_linked_list.traverse_backward()
        # result = sample_linked_list.search('V')
        # print (f'Given data found at index: {result}')


if __name__ == '__main__':
    Solution.test_code()
