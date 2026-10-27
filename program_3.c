
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

/* Create a new node */
struct TrieNode *createNode(void) {
    struct TrieNode *node = malloc(sizeof(struct TrieNode));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    node->isEndOfWord = 0;
    return node;
}

/* Insert a word */
void insert(struct TrieNode *root, char word[]) {
    struct TrieNode *p = root;
    int i, index;

    for (i = 0; word[i] != '\0'; i++) {
        index = word[i] - 'a';

        if (p->children[index] == NULL)
            p->children[index] = createNode();

        p = p->children[index];
    }

    p->isEndOfWord = 1;
    printf("Word inserted\n");
}

/* Search for a complete word */
int search(struct TrieNode *root, char word[]) {
    struct TrieNode *p = root;
    int i, index;

    for (i = 0; word[i] != '\0'; i++) {
        index = word[i] - 'a';

        if (p->children[index] == NULL)
            return 0;

        p = p->children[index];
    }

    return p->isEndOfWord;
}

/* Display all words */
void displayWords(struct TrieNode *root,
                  char word[], int depth) {
    int i;

    if (root->isEndOfWord) {
        word[depth] = '\0';
        printf("%s\n", word);
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            word[depth] = 'a' + i;
            displayWords(root->children[i], word, depth + 1);
        }
    }
}

/* Autocomplete */
void autocomplete(struct TrieNode *root, char prefix[]) {
    struct TrieNode *p = root;
    char word[100];
    int i, index;

    for (i = 0; prefix[i] != '\0'; i++) {
        index = prefix[i] - 'a';

        if (p->children[index] == NULL) {
            printf("No words found\n");
            return;
        }

        p = p->children[index];
    }

    strcpy(word, prefix);
    printf("Words with prefix %s:\n", prefix);
    displayWords(p, word, strlen(prefix));
}

/* Main function */
int main(void) {
    struct TrieNode *root = createNode();
    char word[100];
    int choice, i, valid;

    do {
        printf("\n1.Insert\n2.Search\n3.Display all words\n");
        printf("4.Autocomplete\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Enter word or prefix: ");
            scanf("%99s", word);

            valid = 1;
            for (i = 0; word[i] != '\0'; i++) {
                word[i] = tolower((unsigned char)word[i]);

                if (word[i] < 'a' || word[i] > 'z')
                    valid = 0;
            }

            if (!valid) {
                printf("Use English letters a-z only\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                insert(root, word);
                break;

            case 2:
                if (search(root, word))
                    printf("Word found\n");
                else
                    printf("Word not found\n");
                break;

            case 3: {
                char buffer[100];
                displayWords(root, buffer, 0);
                break;
            }

            case 4:
                autocomplete(root, word);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);

    return 0;
}
