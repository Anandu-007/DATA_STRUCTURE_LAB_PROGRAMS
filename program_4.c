
#include <stdio.h>
#include <stdlib.h>

#define M 4
#define MAX 3

struct BTreeNode {
    int keys[MAX];
    struct BTreeNode *child[M];
    int n;
    int leaf;
};

struct BTreeNode *root = NULL;

/* Create a new node */
struct BTreeNode *createNode(int leaf) {
    struct BTreeNode *p;
    int i;

    p = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));

    if (p == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    p->n = 0;
    p->leaf = leaf;

    for (i = 0; i < M; i++)
        p->child[i] = NULL;

    return p;
}

/* Search for a key */
int search(struct BTreeNode *p, int key) {
    int i;

    if (p == NULL)
        return 0;

    i = 0;

    while (i < p->n && key > p->keys[i])
        i++;

    if (i < p->n && key == p->keys[i])
        return 1;

    if (p->leaf)
        return 0;

    return search(p->child[i], key);
}

/* Split a full child */
void splitChild(struct BTreeNode *p, int i) {
    struct BTreeNode *y;
    struct BTreeNode *z;
    int middle;
    int j;

    y = p->child[i];
    z = createNode(y->leaf);

    z->n = 1;
    z->keys[0] = y->keys[2];

    if (!y->leaf) {
        z->child[0] = y->child[2];
        z->child[1] = y->child[3];
    }

    middle = y->keys[1];
    y->n = 1;

    for (j = p->n; j >= i + 1; j--)
        p->child[j + 1] = p->child[j];

    p->child[i + 1] = z;

    for (j = p->n - 1; j >= i; j--)
        p->keys[j + 1] = p->keys[j];

    p->keys[i] = middle;
    p->n++;
}

/* Insert into a non-full node */
void insertNonFull(struct BTreeNode *p, int key) {
    int i;

    i = p->n - 1;

    if (p->leaf) {
        while (i >= 0 && key < p->keys[i]) {
            p->keys[i + 1] = p->keys[i];
            i--;
        }

        p->keys[i + 1] = key;
        p->n++;
    } else {
        while (i >= 0 && key < p->keys[i])
            i--;

        i++;

        if (p->child[i]->n == MAX) {
            splitChild(p, i);

            if (key > p->keys[i])
                i++;
            else if (key == p->keys[i])
                return;
        }

        insertNonFull(p->child[i], key);
    }
}

/* Insert a key */
void insert(int key) {
    struct BTreeNode *s;

    if (search(root, key)) {
        printf("Duplicate key\n");
        return;
    }

    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    if (root->n == MAX) {
        s = createNode(0);
        s->child[0] = root;

        splitChild(s, 0);
        root = s;
    }

    insertNonFull(root, key);
}

/* Inorder traversal */
void traverse(struct BTreeNode *p) {
    int i;

    if (p == NULL)
        return;

    for (i = 0; i < p->n; i++) {
        if (!p->leaf)
            traverse(p->child[i]);

        printf("%d ", p->keys[i]);
    }

    if (!p->leaf)
        traverse(p->child[i]);
}

/* Main function */
int main(void) {
    int choice, key;

    do {
        printf("\n1. Insert\n");
        printf("2. Traverse\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1) {
                    printf("Invalid input\n");
                    return 1;
                }

                insert(key);
                break;

            case 2:
                printf("B-Tree traversal: ");
                traverse(root);
                printf("\n");
                break;

            case 3:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1) {
                    printf("Invalid input\n");
                    return 1;
                }

                if (search(root, key))
                    printf("Key found\n");
                else
                    printf("Key not found\n");
                break;

            case 4:
                printf("Program terminated\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
