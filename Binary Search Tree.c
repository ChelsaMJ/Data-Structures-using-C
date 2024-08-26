#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct BinaryTreeNode {
    int key;
    struct BinaryTreeNode *left, *right;
};

// Function to create a new node with a given value
struct BinaryTreeNode* newNodeCreate(int value) {
    struct BinaryTreeNode* temp = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node with a specific value in the tree
struct BinaryTreeNode* insertNode(struct BinaryTreeNode* node, int value) {
    if (node == NULL) {
        return newNodeCreate(value);
    }
    if (value < node->key) {
        node->left = insertNode(node->left, value);
    } else if (value > node->key) {
        node->right = insertNode(node->right, value);
    }
    return node;
}

// Function to search for a node with a specific key in the tree
struct BinaryTreeNode* searchNode(struct BinaryTreeNode* root, int target) {
    if (root == NULL || root->key == target) {
        return root;
    }
    if (root->key < target) {
        return searchNode(root->right, target);
    }
    return searchNode(root->left, target);
}

// Function to perform in-order traversal
void inOrder(struct BinaryTreeNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf(" %d ", root->key);
        inOrder(root->right);
    }
}

// Function to perform pre-order traversal
void preOrder(struct BinaryTreeNode* root) {
    if (root != NULL) {
        printf(" %d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to perform post-order traversal
void postOrder(struct BinaryTreeNode* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf(" %d ", root->key);
    }
}

// Function to find the minimum value node
struct BinaryTreeNode* findMin(struct BinaryTreeNode* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from the tree
struct BinaryTreeNode* deleteNode(struct BinaryTreeNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct BinaryTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BinaryTreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct BinaryTreeNode* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to find the height of the tree
int findHeight(struct BinaryTreeNode* node) {
    if (node == NULL)
        return -1;
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to count the number of nodes in the tree
int countNodes(struct BinaryTreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    struct BinaryTreeNode* root = NULL;
    int choice, value;

    do {
        printf("\n\nBinary Search Tree Operations:\n");
        printf("1. Insert a node\n");
        printf("2. Search for a node\n");
        printf("3. Delete a node\n");
        printf("4. In-order traversal\n");
        printf("5. Pre-order traversal\n");
        printf("6. Post-order traversal\n");
        printf("7. Find minimum value\n");
        printf("8. Find height of the tree\n");
        printf("9. Count the number of nodes\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct BinaryTreeNode* found = searchNode(root, value);
                if (found != NULL) {
                    printf("Node %d found in the tree.\n", value);
                } else {
                    printf("Node %d not found in the tree.\n", value);
                }
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node %d deleted from the tree.\n", value);
                break;
            case 4:
                printf("In-order traversal: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-order traversal: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Post-order traversal: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                struct BinaryTreeNode* minNode = findMin(root);
                if (minNode != NULL) {
                    printf("Minimum value in the tree: %d\n", minNode->key);
                } else {
                    printf("The tree is empty.\n");
                }
                break;
            case 8:
                printf("Height of the tree: %d\n", findHeight(root));
                break;
            case 9:
                printf("Number of nodes in the tree: %d\n", countNodes(root));
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
