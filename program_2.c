
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key, height;
    struct Node *left, *right;
};

int height(struct Node *n) {
    return (n == NULL) ? 0 : n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int balance(struct Node *n) {
    return (n == NULL) ? 0 :
           height(n->left) - height(n->right);
}

struct Node *createNode(int key) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    n->key = key;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

/* Right Rotation */
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left),
                        height(y->right));
    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

/* Left Rotation */
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left),
                        height(x->right));
    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

/* Insertion */
struct Node *insert(struct Node *root, int key) {
    int b;

    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    b = balance(root);

    /* LL Case */
    if (b > 1 && key < root->left->key)
        return rightRotate(root);

    /* RR Case */
    if (b < -1 && key > root->right->key)
        return leftRotate(root);

    /* LR Case */
    if (b > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL Case */
    if (b < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* Find Minimum Node */
struct Node *minValueNode(struct Node *n) {
    while (n->left != NULL)
        n = n->left;

    return n;
}

/* Deletion */
struct Node *deleteNode(struct Node *root, int key) {
    int b;
    struct Node *temp;

    if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        /* Node with zero or one child */
        if (root->left == NULL || root->right == NULL) {
            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            free(root);
            return temp;
        }

        /* Node with two children */
        temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    root->height = 1 + max(height(root->left),
                           height(root->right));

    b = balance(root);

    /* LL Case */
    if (b > 1 && balance(root->left) >= 0)
        return rightRotate(root);

    /* LR Case */
    if (b > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RR Case */
    if (b < -1 && balance(root->right) <= 0)
        return leftRotate(root);

    /* RL Case */
    if (b < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* Search */
struct Node *search(struct Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

/* Inorder Traversal */
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

/* Preorder Traversal */
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Main Function */
int main(void) {
    struct Node *root = NULL;
    int choice, key, result;

    while (1) {
        printf("\n--- AVL TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        fflush(stdout);

        result = scanf("%d", &choice);

        if (result != 1) {
            int c;
            printf("Enter a valid number.\n");

            while ((c = getchar()) != '\n' && c != EOF)
                ;

            if (c == EOF)
                break;

            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1)
                    goto invalid_input;

                root = insert(root, key);
                printf("Key inserted.\n");
                break;

            case 2:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1)
                    goto invalid_input;

                if (search(root, key) == NULL) {
                    printf("Key not found.\n");
                } else {
                    root = deleteNode(root, key);
                    printf("Key deleted.\n");
                }
                break;

            case 3:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1)
                    goto invalid_input;

                if (search(root, key) != NULL)
                    printf("Key found.\n");
                else
                    printf("Key not found.\n");
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }

        continue;

        invalid_input:
        {
            int c;
            printf("Invalid input. Enter an integer.\n");

            while ((c = getchar()) != '\n' && c != EOF)
                ;

            if (c == EOF)
                return 0;
        }
    }

    return 0;
}
