
// C program to demonstrate insert operation in binary search tree
#include<stdio.h>
#include<stdlib.h>
  
struct node
{
    int key;
    struct node *left, *right;
};
  
// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
  
// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
  
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);   
 
    /* return the (unchanged) node pointer */
    return node;
}
  
// Driver Program to test above functions
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
  
    // print inoder traversal of the BST
    inorder(root);
  
    return 0;
}


















// #include<stdio.h>
// #include<stdlib.h>
// #define N 10000

// typedef struct node{
//     struct node* parent;
//     struct node* leftChild;
//     struct node* rightChild;
//     int data;
// } node;

// int add(node** root, int num)
// {
//     if((*root)==0) 
//     {
//         // (*root)->parent = 0;
//         // (*root)->leftChild = 0;
//         // (*root)->rightChild = 0;

//         (*root)->data = num;
//         printf("root initialised\n");
//         return 0;
//     }
//     node* node = (struct node*) malloc(sizeof(struct node));
//     node = *root;
//     while(node!=0)
//     {
//         if(num<node->data) 
//         {
//             if(node->leftChild != 0)
//                 node = node->leftChild;
//             else{
//                 struct node* leftChild = (struct node*)malloc(sizeof(struct node));
//                 node->leftChild = leftChild;
//                 node->leftChild->parent = node;
//                 node->leftChild->data = num;
//                 node->leftChild->rightChild = 0;
//                 node->leftChild->leftChild = 0;
//                 return 0;
//             }
//         }
//         else 
//         {
//             if(node->rightChild != 0)
//                 node = node->rightChild;
//             else{
//                 struct node* rightChild = (struct node*)malloc(sizeof(struct node));
//                 node->rightChild = rightChild;
//                 node->rightChild->parent = node;
//                 node->rightChild->data = num;
//                 node->rightChild->rightChild = 0;
//                 node->rightChild->leftChild = 0;
//                 return 0;        
//             }
//         }
//     }
// }


// int main()
// {
//     node* root = (struct node*)malloc(sizeof(struct node));
//     root = 0;
//     add(&root, 7);
//     add(&root, 3);
//     add(&root, 4);
//     return 0;
// }