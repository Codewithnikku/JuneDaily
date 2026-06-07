#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class CreateBinaryTree {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        for (auto& d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (!nodes.count(parent)) nodes[parent] = new TreeNode(parent);
            if (!nodes.count(child)) nodes[child] = new TreeNode(child);

            if (isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];

            children.insert(child);
        }

        for (auto& d : descriptions) {
            int parent = d[0];
            if (!children.count(parent))
                return nodes[parent];
        }

        return nullptr;
    }
};

int main() {
    vector<vector<int>> descriptions = {
        {20, 15, 1},
        {20, 17, 0},
        {15, 10, 1}
    };

    CreateBinaryTree obj;
    TreeNode* root = obj.createBinaryTree(descriptions);

    cout << root->val << endl;

    return 0;
}