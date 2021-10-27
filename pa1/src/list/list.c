#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int val;
    struct Node* next;
} Node;

Node* insert(Node* first, int number)
{
    if (first == NULL)
    {
        first = (Node*)malloc(sizeof(Node));
        first->val = number;
        first->next = NULL;
        return first;
    }
    if (number < first->val)
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->val = number;
        temp->next = first;
        first = temp;
        return first;
    }
    Node* ptr = first;
    while(ptr->next != NULL && number > ptr->next->val)
    {
        ptr = ptr->next;
    }
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->val = number;
    temp->next = ptr->next;
    ptr->next = temp;
    return first;
}

Node* delete(Node* first, int number)
{
    if (first == NULL) return first;
    if (first->val == number)
    {
        Node* temp = first;
        first = first->next;
        free(temp);
        return first;
    }
    Node* curr = first->next;
    Node* prev = first;
    while (curr != NULL)
    {
        if (curr->val == number)
        {
            prev->next = curr->next;
            free(curr);
            return first;
        }
        prev = curr;
        curr = curr->next;
    }
    return first;
}

int main()
{
    Node* first = NULL;
    int numNodes = 0;
    char code = 'd';
    int number;

    while(scanf(" %c %d", &code, &number) == 2)
    {
        if (code == 'i')
        {
            Node* ptr = first;
            int checkExists = 0;
            while (ptr!= NULL)
            {
                if (number == ptr->val)
                {
                    checkExists = 1;
                    break;
                }
                ptr = ptr->next;
            }
            if (checkExists == 0)
            {
                first = insert(first, number);
                numNodes = numNodes + 1;
            }
        }
        else if (code == 'd')
        {
            Node* ptr = first;
            int checkExists = 0;
            while (ptr!= NULL)
            {
                if (number == ptr->val)
                {
                    checkExists = 1;
                    break;
                }
                ptr = ptr->next;
            }
            if (checkExists == 1)
            {
                first = delete(first, number);
                numNodes = numNodes - 1;
            }
        }

        //Print the number of nodes and the linked list itself
        printf("%d :", numNodes);
        Node* ptr = first;
        while (ptr != NULL)
        {
            printf(" %d", ptr->val);            
            ptr = ptr->next;
        }
        printf("\n");
    }
    while (first != NULL)
    {
        Node* temp = first;
        first = first->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}