import unittest
from binarytree.binarytree import BinaryTree
from random import randint


class TestTree(unittest.TestCase):
    def setUp(self):
        self.binarytree = BinaryTree()
        self.list_of_values = []
        for i in range(100):
            val = randint(1, 100)
            self.binarytree.insert_value(val)
            if val not in self.list_of_values:
                self.list_of_values.append(val)

    def test_insert(self):
        for val in self.list_of_values:
            self.assertEqual(True, self.binarytree.find(val))

    '''
    def test_remove(self):
         while self.list_of_values:
             if len(self.list_of_values) > 1:
                 index = randint(0, len(self.list_of_values)-1)
             else:
                 index = 0
             self.assertEqual(None, self.binarytree.remove(self.list_of_values[index]))
             self.list_of_values.remove(self.list_of_values[index])
    '''
