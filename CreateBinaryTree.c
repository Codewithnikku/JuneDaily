#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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


int main() {
    int row1[] = {20, 15, 1};
    int row2[] = {20, 17, 0};
    int row3[] = {15, 10, 1};

    int* descriptions[] = {row1, row2, row3};
    int descriptionsColSize[] = {3, 3, 3};

    struct TreeNode* root =
        createBinaryTree(descriptions, 3, descriptionsColSize);

    printf("Root: %d\n", root->val);

    return 0;
}