
#include <stdio.h>

#define MAX 20

int parent[MAX];
int rank[MAX];

/* MAKE-SET */
void makeSet(int n) {
    int i;

    for (i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

/* FIND with Path Compression */
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

/* UNION by Rank */
void unionSet(int x, int y) {
    int rootX, rootY;

    rootX = find(x);
    rootY = find(y);

    if (rootX == rootY) {
        printf("Already in the same set.\n");
        return;
    }

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    }
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }

    printf("Union completed.\n");
}

/* Display */
void display(int n) {
    int i;

    printf("\nElement\tParent\tRank\n");

    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", i, parent[i], rank[i]);
}

int main(void) {
    int n, choice, x, y;

    printf("Enter number of elements (1-20): ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    makeSet(n);

    while (1) {
        printf("\n--- DISJOINT SET ---\n");
        printf("1. FIND\n");
        printf("2. UNION\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                printf("Enter element (0 to %d): ", n - 1);

                if (scanf("%d", &x) != 1)
                    return 1;

                if (x < 0 || x >= n) {
                    printf("Invalid element.\n");
                    break;
                }

                printf("Representative of %d = %d\n",
                       x, find(x));
                break;

            case 2:
                printf("Enter two elements: ");

                if (scanf("%d %d", &x, &y) != 2)
                    return 1;

                if (x < 0 || x >= n || y < 0 || y >= n) {
                    printf("Invalid elements.\n");
                    break;
                }

                unionSet(x, y);
                break;

            case 3:
                display(n);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
