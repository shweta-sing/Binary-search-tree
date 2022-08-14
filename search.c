#include<stdio.h>
#include <malloc.h>

typedef struct tree
{
    int data;//stores data
    int count;//stores frequency of data
    struct tree *left;
    struct tree *right;
} tree;//Structure to create tree
tree *root = NULL;



//Function signatures
void insert_node(int num);
int search(tree *root, int num);
void print_path(tree *node);




//Function to insert node in tree
void insert_node(int num)
{
    tree *current, *previous;
    tree *node = (tree*) malloc(sizeof (tree));
    node->left = NULL;
    node->right = NULL;
    node->data = num;
    node->count = 1;

    if(root==NULL)
        root = node;
    else
    {
         current = root;
         while(current!=NULL)
         {
             previous = current;
             if(num > current->data)
                 current = current->right;
             else
             {
                 if(num < current->data)
                     current = current->left;
                 else
                 {
                     current->count++;
                     break;
                 }
             }
         }
        if(num > previous->data)
            previous->right = node;
        else {
            if (num < previous->data)
                previous->left = node;
        }
    }
}


//Function to search an element
int search(tree *root, int num)
{
    tree *current;
    if(root==NULL)
        return 0;
    else
    {
        current = root;
        while(current!=NULL)
        {
            if(num> current->data)
                current = current ->right;
            else
            {
                if(num< current->data)
                    current = current->left;
                else
                {
                    if(num==current->data)
                        break;
                }
            }
        }
        if(current==NULL)
            return -1;
        else
        {
            print_path(current);//Helper function to print path to element, if element is present in tree
            return 1;
        }
    }
}

//Helper function to print path to element, if element is present in tree
void print_path(tree *node)
{
    tree *current;
    if(node==root)
        printf("\n%d found in tree.\n%d is root of the tree.\n", node->data, node->data);
    else
    {
        current = root;
        printf("\n%d found in tree.\nThe path to element is: \n", node->data);
        while(1)
        {
            if(current->data==node->data)
            {
                printf("%d", current->data);
                break;
            }
            else
            {
                printf("%d -> ", current->data);
                if(node->data > current->data)
                    current= current->right;
                else
                    current = current -> left;
            }
        }
    }
}


//Driver function
int main()
{
    int num, ch=0, output = 0;
    while (ch!=3)
    {
        printf("\n\n\n1.Insert in tree\t2.Search an element\t3.EXIT");
        printf("\nEnter choice from the above options: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: printf("\nEnter number: ");
                scanf("%d", &num);
                insert_node(num);
                break;
            case 2:
                if(root==NULL)
                    printf("\nThe tree is not created. Enter some elements before performing this operation");
                else
                {
                    printf("\nEnter number to be searched: ");
                    scanf("%d", &num);
                    output = search(root, num);
                    if(output == -1)
                        printf("\n%d is not present in the given tree.", num);
                }
                break;
            case 3: printf("\nExited successfully!");
                break;
            default: printf("\nEnter correct choice.");
        }
    }
}