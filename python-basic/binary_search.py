'''
Implement Binary Search on a list data structure
'''


class BSList:
    '''
    This class represents the data structure for binary search.
    Data are self sorted on appending
    '''
    def __init__(self) -> None:
        self.values = []
        # data [0, 1, 2, 2, 10, 11, 17, 30]
        # find 17

    def append_list(self, unsorted_list):
        '''
        Append whole list of elements in BSList
        '''
        for item in unsorted_list:
            self.append(item)

    def append(self, element):
        '''
        Append single element in BSList
        '''
        insert_location = len(self.values)
        for i, item in enumerate(self.values):
            if element <= item:
                insert_location = i
                break
        self.values = self.values[0:insert_location] + [
            element
        ] + self.values[insert_location:]

        return self

    def search(self, needle):
        '''
        Function to search the needle in sorted haystack using binary search
        In the following code: #end = len(self.values)-1 isn't used but #end = len(self.values) is used
        Though the index of list goes from 0 to len(self.values)-1, pos = (start+end)//2 does integer
        division. Say, when the actual len is 5 (i.e. indexes range from 0 to 4), 
        if we use the start = 0 and end = 4, then we will never get the actual index in the loop
        since (3+4)//2 = 3. So, the index never goes to 4. Hence we need to loop from 0 to 5.
        '''
        start = 0
        end = len(self.values)

        pos = (start + end) // 2
        print(f'Total number of elements: {len(self.values)}')
        while needle != self.values[pos]:
            print(
                f'Searching at position pos: {pos} found element {self.values[pos]}. Start = {start}, end = {end}'
            )
            if needle > self.values[pos]:
                start = pos
            elif needle < self.values[pos]:
                end = pos

            new_pos = (start + end) // 2
            if new_pos == pos:
                # print('Element not found in the list.')
                return None
            pos = new_pos
        print(
            f'Searching at position pos: {pos} found element {self.values[pos]}. Start = {start}, end = {end}'
        )
        return pos


class Solution:
    '''
    This class represents the the process to solve the problem.
    '''
    def __init__(self) -> None:
        pass

    @staticmethod
    def run():
        test_list = BSList()
        # test_list.append_list([1,2,4,5])

        # test_list.append_list([12,30,4,5,76,11,41,63,12,7,87,22,53,\
        # 12,52,26,78,23,12,44,55,6,9,22,5,11,3,66,12,56,78,7,24,16,\
        # 35,95,48,12,20,14,36,48,94,97,96,32,45,1,23,20,34,10,65,34,29,86,42])

        test_list.append_list([2, 2, 2, 2, 3])
        print(f'Searching in list: {test_list.values}')
        print(f'Item found at {test_list.search(3)} index.')


if __name__ == '__main__':
    Solution.run()
