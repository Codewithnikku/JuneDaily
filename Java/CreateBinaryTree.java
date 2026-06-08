import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
    }
}

class CBT {
    public TreeNode createBinaryTree(int[][] descriptions) {
        Map<Integer, TreeNode> nodes = new HashMap<>();
        Set<Integer> children = new HashSet<>();

        for (int[] d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            nodes.putIfAbsent(parent, new TreeNode(parent));
            nodes.putIfAbsent(child, new TreeNode(child));

            if (isLeft == 1) {
                nodes.get(parent).left = nodes.get(child);
            } else {
                nodes.get(parent).right = nodes.get(child);
            }

            children.add(child);
        }

        for (int[] d : descriptions) {
            int parent = d[0];
            if (!children.contains(parent)) {
                return nodes.get(parent);
            }
        }

        return null;
    }
}

public class CreateBinaryTree {
    public static void main(String[] args) {
        int[][] descriptions = {
            {20, 15, 1},
            {20, 17, 0},
            {15, 10, 1}
        };

        CBT solution = new CBT();
        TreeNode root = solution.createBinaryTree(descriptions);

        System.out.println("Root: " + root.val);
    }
}