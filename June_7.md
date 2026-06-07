# 2196. Create Binary Tree From Descriptions

## Intuition

The problem provides a list of descriptions where each description has the format:

```text
[parent, child, isLeft]
```

This means:

- `parent` is the value of the parent node.
- `child` is the value of the child node.
- `isLeft = 1` means the child is attached to the left side of the parent.
- `isLeft = 0` means the child is attached to the right side of the parent.

For example:

```text
[20, 15, 1]
```

means:

```text
    20
   /
 15
```

The main challenge is determining the root of the tree because the descriptions only provide relationships and do not explicitly tell us which node is the root.

A key observation is:

> Every node except the root appears as a child exactly once.

Therefore:

- If we store all child nodes in a set,
- The only node that never appears in the child set must be the root.

This observation allows us to build the tree and find the root efficiently.

---

## Approach

### Step 1: Create a Hash Map for Nodes

We need a way to quickly access any node by its value.

Use a hash map:

```text
value -> TreeNode
```

Example:

```text
20 -> Node(20)
15 -> Node(15)
17 -> Node(17)
10 -> Node(10)
```

Whenever we encounter a value for the first time, we create its node and store it in the map.

---

### Step 2: Track Every Child Node

Create a hash set:

```text
children
```

Every time a node appears as a child, insert it into this set.

Example:

```text
Descriptions:

[20,15,1]
[20,17,0]
[15,10,1]

Children Set:

{15,17,10}
```

---

### Step 3: Build Parent-Child Connections

For every description:

```text
[parent, child, isLeft]
```

Perform the following:

1. Create parent node if it doesn't exist.
2. Create child node if it doesn't exist.
3. Connect child to parent.
4. Store child in the children set.

Example:

```text
[20,15,1]
```

creates:

```text
20
|
15
```

Since `isLeft = 1`:

```text
    20
   /
 15
```

Now process:

```text
[20,17,0]
```

```text
    20
   /  \
 15   17
```

Now process:

```text
[15,10,1]
```

```text
       20
      /  \
    15   17
   /
 10
```

The tree is fully constructed.

---

### Step 4: Find the Root

Now we know:

```text
Children = {15,17,10}
```

Check every parent value.

```text
20 -> Not in children set ✓
15 -> In children set
17 -> In children set
10 -> In children set
```

Therefore:

```text
Root = 20
```

Return node `20`.

---

## Dry Run

### Input

```text
descriptions = [
    [20,15,1],
    [20,17,0],
    [15,10,1]
]
```

### Iteration 1

```text
Parent = 20
Child = 15
isLeft = 1
```

Tree:

```text
20
/
15
```

Children:

```text
{15}
```

---

### Iteration 2

```text
Parent = 20
Child = 17
isLeft = 0
```

Tree:

```text
    20
   /  \
 15   17
```

Children:

```text
{15,17}
```

---

### Iteration 3

```text
Parent = 15
Child = 10
isLeft = 1
```

Tree:

```text
       20
      /  \
    15   17
   /
 10
```

Children:

```text
{15,17,10}
```

---

### Root Search

```text
20 -> Not a child
```

Return:

```text
20
```

---

## Correctness Proof

We prove that the algorithm always returns the correct root.

### Lemma 1

Every non-root node appears as a child exactly once.

This follows directly from the definition of a tree because every node except the root has exactly one parent.

### Lemma 2

The root node never appears as a child.

The root has no parent, so it cannot appear as a child in any description.

### Lemma 3

Every non-root node is inserted into the child set.

Whenever a description is processed, its child value is inserted into the child set.

Thus all non-root nodes belong to the child set.

### Conclusion

The only node that never appears in the child set is the root.

Therefore the algorithm always returns the correct root node.

---

## Complexity Analysis

Let:

```text
n = descriptions.length
```

### Time Complexity

Building nodes and connections:

```text
O(n)
```

Finding the root:

```text
O(n)
```

Total:

```text
O(n)
```

---

### Space Complexity

Hash Map:

```text
O(n)
```

Hash Set:

```text
O(n)
```

Total:

```text
O(n)
```

```cpp []
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        for(auto& d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if(!nodes.count(parent))
                nodes[parent] = new TreeNode(parent);

            if(!nodes.count(child))
                nodes[child] = new TreeNode(child);

            if(isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];

            children.insert(child);
        }

        for(auto& d : descriptions) {
            int parent = d[0];

            if(!children.count(parent))
                return nodes[parent];
        }

        return nullptr;
    }
};
```

```java []
class Solution {
    public TreeNode createBinaryTree(int[][] descriptions) {
        Map<Integer, TreeNode> nodes = new HashMap<>();
        Set<Integer> children = new HashSet<>();

        for(int[] d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            nodes.putIfAbsent(parent, new TreeNode(parent));
            nodes.putIfAbsent(child, new TreeNode(child));

            if(isLeft == 1)
                nodes.get(parent).left = nodes.get(child);
            else
                nodes.get(parent).right = nodes.get(child);

            children.add(child);
        }

        for(int[] d : descriptions) {
            int parent = d[0];

            if(!children.contains(parent))
                return nodes.get(parent);
        }

        return null;
    }
}
```

```python []
class Solution(object):
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
```

```javascript []
var createBinaryTree = function (descriptions) {
  const nodes = new Map();
  const children = new Set();

  for (const [parent, child, isLeft] of descriptions) {
    if (!nodes.has(parent)) nodes.set(parent, new TreeNode(parent));

    if (!nodes.has(child)) nodes.set(child, new TreeNode(child));

    if (isLeft) nodes.get(parent).left = nodes.get(child);
    else nodes.get(parent).right = nodes.get(child);

    children.add(child);
  }

  for (const [parent] of descriptions) {
    if (!children.has(parent)) return nodes.get(parent);
  }

  return null;
};
```

---

# C

> **Note:** This implementation follows the same idea but uses linear searches for node lookup. Its worst-case complexity is **O(n²)** and may result in **TLE** on large LeetCode test cases. A hash-table-based implementation is required for an optimal **O(n)** solution in C.

```c
typedef struct {
    int key;
    struct TreeNode* node;
} NodeMap;

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
    NodeMap map[20000];
    int mapSize = 0;

    int children[20000];
    int childSize = 0;

    for (int i = 0; i < descriptionsSize; i++) {
        int parent = descriptions[i][0];
        int child = descriptions[i][1];
        int isLeft = descriptions[i][2];

        struct TreeNode *parentNode = NULL, *childNode = NULL;

        for (int j = 0; j < mapSize; j++) {
            if (map[j].key == parent) {
                parentNode = map[j].node;
                break;
            }
        }

        if (parentNode == NULL) {
            parentNode = createNode(parent);
            map[mapSize].key = parent;
            map[mapSize].node = parentNode;
            mapSize++;
        }

        for (int j = 0; j < mapSize; j++) {
            if (map[j].key == child) {
                childNode = map[j].node;
                break;
            }
        }

        if (childNode == NULL) {
            childNode = createNode(child);
            map[mapSize].key = child;
            map[mapSize].node = childNode;
            mapSize++;
        }

        if (isLeft)
            parentNode->left = childNode;
        else
            parentNode->right = childNode;

        children[childSize++] = child;
    }

    for (int i = 0; i < descriptionsSize; i++) {
        int parent = descriptions[i][0];
        int isChild = 0;

        for (int j = 0; j < childSize; j++) {
            if (children[j] == parent) {
                isChild = 1;
                break;
            }
        }

        if (!isChild) {
            for (int j = 0; j < mapSize; j++) {
                if (map[j].key == parent)
                    return map[j].node;
            }
        }
    }

    return NULL;
}
```
