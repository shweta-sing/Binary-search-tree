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

typedef struct tree_list
{
    tree *left;
    tree *right;
    struct tree_list *next;
} list;//structure to create list that would hold nodes for level order traversal
list *start = NULL;



//Function to insert node in tree
int insert_node(int num)
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

//Function to insert values in the list for level order traversal
void push_list(tree *l, tree *r)
{
    list *temp;
    list *node = (list*) malloc(sizeof (list));
    node -> next = NULL;
    node ->left =l;
    node->right = r;
    if(start==NULL)
        start = node;
    else
    {
        if(start->next==NULL)
            start ->next = node;
        else
        {
            temp = start;
            while(temp->next!=NULL)
                temp = temp->next;
            temp->next = node;
        }
    }
}

//Function for level order traversal
int level_traversal(tree *root)
{
    tree *temp = NULL,  *head=NULL;
    list *current=NULL;
    if(root==NULL)
        return -1;
    else
    {
        if(start==NULL)
        {
            temp = root;
            printf("\n%d(%d)",temp->data, temp->count); //If you don't wish to print frequency of the elements, remove the field 'count' from program
            if(temp->left!=NULL&&temp->right!=NULL)
                push_list(temp, temp);
            else
            {
                if(temp->left!=NULL&&temp->right==NULL)
                    push_list(temp, NULL);
                else
                {
                    if(temp->left==NULL&&temp->right!=NULL)
                        push_list(NULL, temp);
                }
            }
        }

        if(root->left!=NULL||root->right!=NULL) {
            current = start;
            while (current != NULL) {
                if (current->left != NULL) {
                    head = current->left->left;
                    printf("\t%d(%d)", head->data,
                           head->count); //If you don't wish to print frequency of the elements, remove the field 'count' from program
                    if (head->left != NULL && head->right != NULL)
                        push_list(head, head);
                    else {
                        if (head->left != NULL && head->right == NULL)
                            push_list(head, NULL);
                        else {
                            if (head->left == NULL && head->right != NULL)
                                push_list(NULL, head);
                        }
                    }
                }
                if (current->right != NULL) {
                    head = current->right->right;
                    printf("\t%d(%d)", head->data,
                           head->count); //If you don't wish to print frequency of the elements, remove the field 'count' from program
                    if (head->left != NULL && head->right != NULL)
                        push_list(head, head);
                    else {
                        if (head->left != NULL && head->right == NULL)
                            push_list(head, NULL);
                        else {
                            if (head->left == NULL && head->right != NULL)
                                push_list(NULL, head);
                        }
                    }
                }
                current = current->next;
            }
            //Deletion of temporary list created using push_list()
            current = start;
            while (current != NULL) {
                current = current->next;
                free(start);
                start = current;
            }
        }
    }
}



//Driver function
int main()
{
    int num, ch=0;
    while (ch!=3)
    {
        printf("\n\n\n1.Insert in tree\t2.Level order traversal\t3.EXIT");
        printf("\nEnter choice: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: printf("\nEnter number: ");
                scanf("%d", &num);
                insert_node(num);
                break;
            case 2:
                printf("\nThe tree is printed in the format :element(frequency)");
                //If you don't wish to print frequency of the elements, remove the field 'count' from program
                level_traversal(root);
                break;
            case 3: printf("\nExited successfully!");
                break;
            default: printf("\nEnter correct choice.");
        }
    }
}