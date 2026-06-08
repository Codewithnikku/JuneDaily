function TreeNode(val, left, right) {
    this.val = val === undefined ? 0 : val;
    this.left = left === undefined ? null : left;
    this.right = right === undefined ? null : right;
}

var createBinaryTree = function(descriptions) {
    const nodes = new Map();
    const children = new Set();

    for (const [parent, child, isLeft] of descriptions) {
        if (!nodes.has(parent)) {
            nodes.set(parent, new TreeNode(parent));
        }
        if (!nodes.has(child)) {
            nodes.set(child, new TreeNode(child));
        }

        if (isLeft) {
            nodes.get(parent).left = nodes.get(child);
        } else {
            nodes.get(parent).right = nodes.get(child);
        }

        children.add(child);
    }

    for (const [parent] of descriptions) {
        if (!children.has(parent)) {
            return nodes.get(parent);
        }
    }

    return null;
};

const descriptions = [
    [20, 15, 1],
    [20, 17, 0],
    [15, 10, 1]
];

const root = createBinaryTree(descriptions);

console.log(root.val);        
console.log(root.left.val);   
console.log(root.right.val);  
console.log(root.left.left.val); 