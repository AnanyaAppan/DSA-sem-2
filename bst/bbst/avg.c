#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
    int sum;
    int num;
};
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->sum = node->key;
    return(node);
}

//utility function to update sum
struct Node* updateSum(struct Node* node)
{
    if(node->left && node->right) node->sum = node->left->sum + node->right->sum + node->key;
    else if(node->left) node->sum = node->left->sum + node->key;
    else if(node->right) node->sum = node->right->sum + node->key;
    else node->sum = node->key;
    return node;
}

//a utility function to update num
struct Node* updateNum(struct Node* node)
{
    if(node->left && node->right) node->num = node->left->num + node->right->num + 1;
    else if(node->left) node->num = node->left->num + 1;
    else if(node->right )node->num = node->right->num + 1;
    else node->num = 1;
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    //update sum
    x = updateSum(x);
    y = updateSum(y);

    //update num
    x = updateNum(x);
    y = updateNum(y);
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    //update sum
    x = updateSum(x);
    y = updateSum(y);

    //update num
    x = updateNum(x);
    y = updateNum(y);
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    //update sum and num
    node = updateSum(node);
    node = updateNum(node);
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    //update sum and num
    root = updateSum(root);
    root = updateNum(root);
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

// A utility function to do inorder traversal of BST
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

int prefixSum(struct Node* root, int x)
{
    struct Node* node = root;
    int sum = 0;
    while(node)
    {
        if(node->key == x) 
        {
            if(node->left)return node->left->sum + sum + x;
            else return sum + x;
        }
        else if(node->key > x) node = node->left;
        else 
        {
            if(node->left) sum =  sum + node->key + node->left->sum;
            else sum += node->key;
            node = node->right;
        }
    }
    return sum;
}

int findRank(struct Node* root, int x)
{
    int r = 1;
    struct Node* node = root;
    while(node)
    {
        if(node->key==x) 
        {
            if(node->right!=0)return(node->right->num+r);
            else return r;
        }
        else if(node->key > x)
        {
            r = r + 1 + node->right->num;
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return 0;
}

int num(struct Node* root ,int x, int y)
{
    int num1, num2;
    num1 = x>y?  x:y;
    num2 = x+y-num1;
    return findRank(root, num2) - findRank(root, num1) + 1;
}

int sum(struct Node* root, int x, int y)
{
    int num1, num2;
    num1 = x>y?  x:y;
    num2 = x+y-num1;
    return prefixSum(root, num1) - prefixSum(root, num2-1) ;
}

int avg(struct Node* root, int x, int y)
{
    return sum(root,x,y)/num(root,x,y);
}

int main()
{
    int n;
    printf("enter no of elements\n");
    scanf("%d",&n);
    printf("enter array\n");
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root = 0;
    for(int i=0;i<n;i++)
    {
        int num;
        scanf("%d",&num);
        root = insert(root, num);
    }
    inorder(root);
    printf("enter two numbers\n");
    int x,y;
    scanf("%d %d",&x,&y);
    printf("the avg of nos between them = %d\n",avg(root,x,y));
    return 0;
    return 0;
}