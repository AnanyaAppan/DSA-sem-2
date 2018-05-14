
// C program to demonstrate insert operation in binary search tree
#include<stdio.h>
#include<stdlib.h>
  
struct node
{
    int key;
    struct node *left, *right, *parent;
};
  
// A utility function to create a new BST node
struct node *newNode(int item, struct node* parent)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->parent = parent;
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
struct node* insert(struct node* node, int key ,struct node* parent)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key, parent);
 
    /* Otherwise, recur down the tree */
    if (key <= node->key)
        node->left  = insert(node->left, key , node);
    else if (key > node->key)
        node->right = insert(node->right, key, node);   
 
    /* return the (unchanged) node pointer */
    return node;
}

struct node* IOP(struct node* node)
{
    struct node* lc = node->left;
    while(lc->right!=0) lc = lc->right;
    return lc;
}

struct node* IOS(struct node* node)
{
    struct node* rc = node->right;
    while(rc->left!=0) rc = rc->left;
    return rc;
}

struct node* search(struct node* node, int num)
{
    if(node==0) return 0;
    if(node->key==num) return node;
    if(node->key>num) return search(node->left, num);
    return search(node->right, num);
}

int delete(struct node* root, int num)
{
    struct node* node = search(root, num);
    if(node==0) return 0;
    if(node->right==0 && node->left==0) 
    {
        free(node);
        return 0;
    }
    if(node->left!=0 && node->right==0)
    {
        struct node* lc = node->left;
        lc->parent = node->parent;
        node->parent->left = node->left;
        free(node);
        return 0;
    }
    if(node->left==0 && node->right!=0)
    {
        struct node* rc = node->right;
        rc->parent = node->parent;
        node->parent->right = node->right;
        free(node);
        return 0;
    } 
    struct node* inOrderPredecessor = IOP(node);
    node->key = inOrderPredecessor->key;
    free(inOrderPredecessor);
    return 0;
}


  
// Driver Program to test above functions
// int main()
// {
//     /* Let us create following BST
//               50
//            /     \
//           30      70
//          /  \    /  \
//        20   40  60   80 */
//     struct node *root = NULL;
//     root = insert(root,50,0);
//     insert(root, 30,0);
//     insert(root, 20,0);
//     insert(root, 40,0);
//     insert(root, 70,0);
//     insert(root, 60,0);
//     insert(root, 80,0);
  
//     // print inorder traversal of the BST
//     inorder(root);
//     printf("IOP of root = %d\n",IOP(root)->key);
//     printf("IOS of root = %d\n",IOS(root)->key);
//     delete(root, 90);
//     inorder(root);
//     return 0;
// }