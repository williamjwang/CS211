#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* insert(Node* first, int number)
{
    if (first == NULL)
    {
        first = (Node*)malloc(sizeof(Node));
        first->val = number;
        first->left = NULL;
        first->right = NULL;
        printf("inserted\n");
        return first;
    }
    else if (number == first->val)
    {
        printf("not inserted\n");
        return first;
    }
    if (number < first->val) first->left = insert(first->left, number);
    else first->right = insert(first->right, number);
    return first;
}

Node* delete (Node* first, int number)
{
    if (first == NULL)
    {
        printf("absent\n");
        return first;
    }
    if (number == first->val)
    {
        if (first->left == NULL)
        {
            Node *temp = first->right;
            free(first);
            first = temp;
            printf("deleted\n");
            return first;
        }
        else if (first->right == NULL)
        {
            Node *temp = first->left;
            free(first);
            first = temp;
            printf("deleted\n");
            return first;
        }

        Node *temp = first->right;
        while (temp->left != NULL) temp = temp->left;

        first->val = temp->val;
        first->right = delete(first->right, temp->val);
        return first;
    }
    else if (number < first->val) first->left = delete(first->left, number);
    else if (number > first->val) first->right = delete(first->right, number);
    return first;
}

void search(Node *first, int number)
{

    if (first == NULL)
    {
        printf("absent\n");
        return;
    }
    if (first->val == number)
    {
        printf("present\n");
        return;
    }
    if (number < first->val)
        search(first->left, number);
    else
        search(first->right, number);
}

void printBST(Node *first)
{
    if (first == NULL) return;
    printf("(");
    printBST(first->left);
    printf("%d", first->val);
    printBST(first->right);
    printf(")");
}

void freeBST(Node *first)
{
    if (first == NULL) return;
    freeBST(first->left);
    freeBST(first->right);
    free(first);
}

int main()
{
    Node *first = NULL;
    char code;
    int number;

    char *input = (char *)malloc(sizeof(char));

    while (fgets(input, sizeof(input), stdin))
    {
        if (sscanf(input, " %c %d", &code, &number) == 2)
        {
            if (code == 'i') first = insert(first, number);            
            else if (code == 'd') first = delete (first, number);            
            else if (code == 's') search(first, number);            
        }
        if (sscanf(input, " %c", &code) == 1)
        {
            if (code == 'p')
            {
                printBST(first);
                printf("\n");
            }
        }
    }
    free(input);
    freeBST(first);
    return EXIT_SUCCESS;
}