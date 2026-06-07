class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class CreateBinaryTree:
    def createBinaryTree(self, descriptions):
        nodes = {}
        children = set()

        for parent, child, isLeft in descriptions:
            if parent not in nodes:
                nodes[parent] = TreeNode(parent)
            if child not in nodes:
                nodes[child] = TreeNode(child)

            if isLeft:
                nodes[parent].left = nodes[child]
            else:
                nodes[parent].right = nodes[child]

            children.add(child)

        for parent, _, _ in descriptions:
            if parent not in children:
                return nodes[parent]

        return None


def preorder(root):
    if not root:
        return
    print(root.val, end=" ")
    preorder(root.left)
    preorder(root.right)


descriptions = [
    [20, 15, 1],
    [20, 17, 0],
    [15, 10, 1]
]

CreateBinaryTree = CreateBinaryTree()
root = CreateBinaryTree.createBinaryTree(descriptions)

print("Root:", root.val)
print("Preorder Traversal:", end=" ")
preorder(root)
print()