#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node{
    int val;
    struct node *left, *right;
    int height;
}Node;

int maxim(int a, int b)
{
    if(a > b)
        return a;
    else return b;
}

int height(Node *current)
{
    if (current == NULL)
        return 0;
    return current->height;
}

int Balance(Node *current)
{
    if (current == NULL)
        return 0;
    return height(current->left) - height(current->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;
 
    y->height = maxim(height(y->left), height(y->right))+1;
    x->height = maxim(height(x->left), height(x->right))+1;
 
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;
 
    x->height = maxim(height(x->left), height(x->right))+1;
    y->height = maxim(height(y->left), height(y->right))+1;
 
    return y;
}

void print(Node* current, int *min, int *ok)
{
    if(current != NULL)
    {
        print(current->left, min, ok);
        printf("%d ", current->val);

        if(current->val < *min)
            *ok = 0;

        *min = current->val;

        print(current->right, min, ok);
    }
}

Node* newNode(int val)
{
    Node* node;

    node = (Node*) malloc(sizeof(Node));

    node->val = val;
    node->right = node->left = NULL;
    node->height = 0;
    return node;
}

Node *AVL(Node* current, int val)
{
    current->height = 1 + maxim(height(current->left),height(current->right));

    int balance;

    balance = Balance(current);

    if (balance > 1 && val < current->left->val)
        return rightRotate(current);
 
    if (balance < -1 && val > current->right->val)
        return leftRotate(current);
 
    if (balance > 1 && val > current->left->val)
    {
        current->left =  leftRotate(current->left);
        return rightRotate(current);
    }
 
    if (balance < -1 && val < current->right->val)
    {
        current->right = rightRotate(current->right);
        return leftRotate(current);
    }

    return current;
}

Node* insert(Node *current, int val)
{
    if(current == NULL)
        return newNode(val);   

    if(val >= current->val)
        current->right = insert(current->right, val);
    else current->left = insert(current->left, val);

    current = AVL(current, val);

    return current;
}

int search(Node *current, int val)
{
    if(current == NULL)
        return 0;
        
    if(val == current->val)
        return 1;

    if(val > current->val)
        return search(current->right, val);
    else return search(current->left, val);
}

Node* maxNode(Node* node)
{
    Node* current = node;
 
    while (current && current->right != NULL)
        current = current->right;
 
    return current;
}

Node* delete(Node *current, int val)
{
    Node *temp;

    if(current == NULL)
        return current;

    if(val < current->val)
        current->left = delete(current->left, val);
    else if(val > current->val)
        current->right = delete(current->right, val);
    else{ 
            if(current->left == NULL)
                {
                    temp = (Node*) malloc(sizeof(Node));
                    temp = current->right;
                    free(current);
                    return temp;
                }
            else if(current->right == NULL)
                {
                    temp = (Node*) malloc(sizeof(Node));
                    temp = current->left;
                    free(current);
                    return temp;
                }

            temp = (Node*) malloc(sizeof(Node));
            
            temp = maxNode(current->left);

            current->val = temp->val;

            current->left = delete(current->left, temp->val);
        }
    
    if(current == NULL)
        return current;

    current = AVL(current, val);

    return current;

}

int main()
{
    FILE *f;
    int n, a, ok = 1, min;
    Node* root;

    root = (Node*) malloc(sizeof(Node));

    f = fopen("input.txt", "rt");

    fscanf(f, "%d", &n);

    fscanf(f, "%d", &a);

    root = newNode(a);

    while(fscanf(f, "%d", &a) != EOF)
        root = insert(root, a);

    min = INT_MIN;

    print(root, &min, &ok);

    if(ok == 1)
        printf("\nArborele este binar de cautare.");

    a = rand()%40;

    if(search(root, a))
        printf("\n%d se afla in arbore.", a);
    else printf("\n%d nu se afla in arbore.", a);

    printf("\n");

    root = delete(root, 7);

    print(root, &min, &ok);

}