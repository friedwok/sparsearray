class BinaryTree:
    _height = 0

    def __init__(self, value=None):
        self.left = None
        self.right = None
        self.value = value

    def find(self, value):
        if self.value == value:
            return True
        elif self.value > value and self.left:
            return self.left.find(value)
        elif self.value < value and self.right:
            return self.right.find(value)
        else:
            print("Node with value {} not found".format(value))
            return False

    def remove(self, value):
        if self.find(value):
            self._remove(value)

    # does not work if you delete the root
    def _remove(self, value, parent=None, side=None):
        if not self.left and not self.right and value != self.value:
            return
        if value > self.value:
            self.right._remove(value, parent=self, side='right')
        elif value < self.value:
            self.left._remove(value, parent=self, side='left')
        elif value == self.value:
            if not self.left and not self.right:
                if side == 'right':
                    parent.right = None
                elif side == 'left':
                    parent.left = None
            elif self.left and not self.right:
                if side == 'left':
                    parent.left = self.left
                elif side == 'right':
                    parent.right = self.left
            elif self.right and not self.left:
                if side == 'right':
                    parent.right = self.right
                elif side == 'left':
                    parent.left = self.right
            else:
                if not self.right.left:
                    if side == 'right':
                        parent.right = self.right
                    elif side == 'left':
                        parent.left = self.right
                    self.right.left = self.left
                else:
                    m = self.right.left
                    while m.left:
                        m = m.left
                    if side == 'right':
                        parent.right = m
                    elif side == 'left':
                        parent.left = m
                    m.left = self.left
                    m.right = self.right

    def insert_value(self, value):
        if not self.value:
            self.value = value
        if value > self.value:
            if self.right:
                self.right.insert_value(value)
            else:
                obj = BinaryTree(value)
                self.right = obj
        elif value < self.value:
            if self.left:
                self.left.insert_value(value)
            else:
                obj = BinaryTree(value)
                self.left = obj
        else:
            print("This value has already exists")

    def insert_values(self, *args):
        for value in args:
            self.insert_value(value)

    # method which set the height of main tree(class) and returns its value
    def get_height(self, height_tmp=0):
        if not self.left and not self.right:
            if height_tmp > BinaryTree._height:
                BinaryTree._height = height_tmp
        if self.left:
            self.left.get_height(height_tmp+1)
            height_tmp -= 1
        if self.right:
            self.right.get_height(height_tmp+1)
            height_tmp -= 1

        return BinaryTree._height

    def print_tree(self):
        if self.value:
            print(self.value, end=' ')
        if self.left:
            self.left.print_tree()
        if self.right:
            self.right.print_tree()


b = BinaryTree(5)
b.insert_values(2, 8, 3, 1, 9, 7, 6, 5)
print("height:", b.get_height())
b.find(6)
b.find(9)
b.find(9.6)
b.insert_value(9)
b.print_tree()
b.remove(6)
print()
b.print_tree()
print(b.remove(6))
list_of_values = []
tree = BinaryTree()
