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
        return Node(
            'M', Node('A', Node('D', Node('H', Node('A', Node('V', None))))))


class Traversal:
    '''
    Class that implements the algorithms in Singly linked list
    '''
    def __init__(self) -> None:
        pass

    def traverse(self, linked_list):
        if linked_list is None:
            return

        print(linked_list.data)
        self.traverse(linked_list.next_node)

    def search(self, linked_list, data):
        if linked_list.data == data:
            print('Data found.')
            return data

        return self.search(linked_list.next_node, data)


class Solution:
    '''
    Class to test our code
    '''
    def __init__(self) -> None:
        pass

    @staticmethod
    def test_code():
        sample_linked_list = SinglyLinkedList.sample_linked_list_1()
        trav = Traversal()
        # trav.traverse(sample_linked_list)
        trav.search(sample_linked_list, 'H')


if __name__ == '__main__':
    Solution.test_code()
