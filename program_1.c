
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

/* Node for Separate Chaining */
struct Node {
    int key;
    struct Node *next;
};

struct Node *chain[SIZE];

/* -1 means empty, -2 means deleted */
int hashTable[SIZE];

/* Hash function */
int hashFunction(int key) {
    return key % SIZE;
}

/* Separate Chaining: Insert */
void chainInsert(int key) {
    int index = hashFunction(key);

    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->key = key;
    newNode->next = chain[index];
    chain[index] = newNode;

    printf("Key inserted using Separate Chaining.\n");
}

/* Separate Chaining: Search */
void chainSearch(int key) {
    int index = hashFunction(key);
    struct Node *temp = chain[index];

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key found at index %d.\n", index);
            return;
        }
        temp = temp->next;
    }

    printf("Key not found.\n");
}

/* Separate Chaining: Delete */
void chainDelete(int key) {
    int index = hashFunction(key);
    struct Node *temp = chain[index];
    struct Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL)
                chain[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Key deleted successfully.\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Key not found.\n");
}

/* Separate Chaining: Display */
void chainDisplay(void) {
    int i;
    struct Node *temp;

    printf("\nSeparate Chaining Hash Table:\n");

    for (i = 0; i < SIZE; i++) {
        printf("[%d] -> ", i);
        temp = chain[i];

        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

/* Open Addressing: Insert using Linear Probing */
void linearInsert(int key) {
    int index = hashFunction(key);
    int start = index;

    do {
        if (hashTable[index] == -1 ||
            hashTable[index] == -2) {
            hashTable[index] = key;
            printf("Key inserted at index %d.\n", index);
            return;
        }

        index = (index + 1) % SIZE;

    } while (index != start);

    printf("Hash table is full.\n");
}

/* Open Addressing: Search */
void linearSearch(int key) {
    int index = hashFunction(key);
    int start = index;

    do {
        if (hashTable[index] == -1) {
            printf("Key not found.\n");
            return;
        }

        if (hashTable[index] == key) {
            printf("Key found at index %d.\n", index);
            return;
        }

        index = (index + 1) % SIZE;

    } while (index != start);

    printf("Key not found.\n");
}

/* Open Addressing: Delete */
void linearDelete(int key) {
    int index = hashFunction(key);
    int start = index;

    do {
        if (hashTable[index] == -1) {
            printf("Key not found.\n");
            return;
        }

        if (hashTable[index] == key) {
            hashTable[index] = -2;
            printf("Key deleted successfully.\n");
            return;
        }

        index = (index + 1) % SIZE;

    } while (index != start);

    printf("Key not found.\n");
}

/* Open Addressing: Display */
void linearDisplay(void) {
    int i;

    printf("\nLinear Probing Hash Table:\n");

    for (i = 0; i < SIZE; i++) {
        printf("[%d] : ", i);

        if (hashTable[i] == -1)
            printf("EMPTY");
        else if (hashTable[i] == -2)
            printf("DELETED");
        else
            printf("%d", hashTable[i]);

        printf("\n");
    }
}

int main(void) {
    int i, method, choice, key;

    for (i = 0; i < SIZE; i++) {
        chain[i] = NULL;
        hashTable[i] = -1;
    }

    do {
        printf("\n--- HASH TABLE ---\n");
        printf("1. Separate Chaining\n");
        printf("2. Open Addressing (Linear Probing)\n");
        printf("3. Exit\n");
        printf("Choose method: ");
        scanf("%d", &method);

        if (method == 3)
            break;

        if (method != 1 && method != 2) {
            printf("Invalid method.\n");
            continue;
        }

        do {
            printf("\n1. Insert\n");
            printf("2. Search\n");
            printf("3. Delete\n");
            printf("4. Display\n");
            printf("5. Back to main menu\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter key: ");
                    scanf("%d", &key);

                    if (key < 0) {
                        printf("Use non-negative keys.\n");
                        break;
                    }

                    if (method == 1)
                        chainInsert(key);
                    else
                        linearInsert(key);
                    break;

                case 2:
                    printf("Enter key to search: ");
                    scanf("%d", &key);

                    if (key < 0) {
                        printf("Use non-negative keys.\n");
                        break;
                    }

                    if (method == 1)
                        chainSearch(key);
                    else
                        linearSearch(key);
                    break;

                case 3:
                    printf("Enter key to delete: ");
                    scanf("%d", &key);

                    if (key < 0) {
                        printf("Use non-negative keys.\n");
                        break;
                    }

                    if (method == 1)
                        chainDelete(key);
                    else
                        linearDelete(key);
                    break;

                case 4:
                    if (method == 1)
                        chainDisplay();
                    else
                        linearDisplay();
                    break;

                case 5:
                    break;

                default:
                    printf("Invalid choice.\n");
            }

        } while (choice != 5);

    } while (1);

    printf("Program terminated.\n");
    return 0;
}
