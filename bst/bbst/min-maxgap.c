#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
    int min;
    int max;
    int mingap;
};
 
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
    node->min = key;
    node->max = key;
    node->mingap = 1000000;
    return(node);
}

//utility function to get min
int min(int a,int b)
{
    return a<b? a:b;
}

//a utility function to update mingap
struct Node* updateMingap(struct Node* node)
{
    if(node->left && node->right) 
    {
        int num1 = min(node->left->mingap, node->right->mingap);
        int num2 = min(node->key - node->left->max, node->right->min - node->key);
        node->mingap = min(num1, num2);
    }
    else if(node->left)
        node->mingap = min(node->left->mingap, node->key - node->left->max);
    
    else if(node->right )
        node->mingap = min(node->right->mingap, node->right->min - node->key);

    else node->mingap = 10000000;
}


//a utility function to update max
struct Node* updateMax(struct Node* node)
{
    if(node->left && node->right) 
    {
        int num = max(node->left->max, node->right->max);
        node->max = max(node->key, num);
    }
    else if(node->left) node->max = max(node->left->max, node->key);
    else if(node->right )node->max = max(node->right->max, node->key);
    else node->max = node->key;
}

//a utility function to update min
struct Node* updateMin(struct Node* node)
{
    if(node->left && node->right) 
    {
        int num = min(node->left->min, node->right->min);
        node->min = min(num, node->key);
    }
    else if(node->left) node->min = min(node->left->min, node->key);
    else if(node->right )node->min = min(node->right->min, node->key);
    else node->min = node->key;
}
 
// A utility function to right rotate subtree rooted with y
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

    //update 
    x = updateMin(x);
    y = updateMin(y);
    x = updateMax(x);
    y = updateMax(y);
    x = updateMingap(x);
    y = updateMingap(y);
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
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

    //update 
    x = updateMin(x);
    y = updateMin(y);
    x = updateMax(x);
    y = updateMax(y);
    x = updateMingap(x);
    y = updateMingap(y);
 
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
    
    //update
    node = updateMax(node);
    node = updateMin(node);
    node = updateMingap(node);
 
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

    //update 
    root = updateMax(root);
    root = updateMin(root);
    root = updateMingap(root);
 
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

int mingap(struct Node* root)
{
    return root->mingap;
}

int maxgap(struct Node* root)
{
    return root->max - root->min;
}

int rangeMingap(struct Node* root, int l, int u)
{
    if(root==0) return 10000000;
    if(root->left==0 && root->right==0) return root->mingap;
    if(root->key <= l) 
    {
        if(root->right && root->key==l) return min(root->right->min-root->key, rangeMingap(root->right,root->key,u));
        else return rangeMingap(root->right,root->key,u);
    }
    if(root->key >= u) {
        if(root->left && root->key==u) return min(root->key - root->left->max, rangeMingap(root->left,l,root->key));
        else return rangeMingap(root->left,l,root->key);
    }
    int num1 = 10000000, num2 = 10000000;
    if(root->left && root->right)
    {
           if(root->left->key >= l && root->right->key <= u)
            num1 = min(root->key - root->left->key, root->right->key - root->key);
    }
    else if(root->left)
    {
        if(root->left->key >= l)
            num1 = root->key - root->left->key;
    }
    else{
        if(root->right->key <= u)
            num1 = root->right->key - root->key;
    }
    num2 = min(rangeMingap(root->right, root->key, u),rangeMingap(root->left,l,root->key));
    return min(num1,num2);
}

int rangeMaxgap(struct Node* root, int l, int u)
{
    int num1,num2;
    struct Node* node = root;
    if(node->key==l) num1 = l;
    if(node->key>l)
    {
        if(node->left)
        {
            while(node->left->key>l)
            {
                node = node->left;
                if(node->left==0) break;
            }
            if(node->left)
            {
                if(node->left->key==l) num1 = node->left->key;
                else num1 = node->key;
            }
            else num1 = node->key;
        }
        else num1 = node->key;
    }
    if(node->key<l)
    {
        if(node->right)
        {
            while(node->key<l)
            {
                node = node->right;
                if(node->right==0) break;
            }
            if(node->left)
            {
                while(node->left->key>l) 
                {
                    node = node->left;
                    if(node->left==0) break;
                }
            }
            if(node->left)
                if(node->left->key==l) num1 = node->left->key;
            else num1 = node->key;
        }
        else return 0;
    }
    printf("l = %d\n",num1);
    if(root->key>u)
    {
        if(root->left)
        {
            while(root->key>u)
            {
                root = root->left;
                if(root->left==0) break;
            }
            if(root->right)
            {
                while(root->right->key<u) 
                {
                    root = root->right;
                    if(root->right==0) break;
                }
            }
            if(root->right)
                if(root->right->key==u) num2 = root->right->key;
            else num2 = root->key;
        }
        else return 0;
    }
    if(root->key<u)
    {
        if(root->right)
        {
            while(root->right->key<u)
            {
                root = root->right;
                if(root->right==0) break;
            }
            if(root->right)
            {
                if(root->right->key==u) num2 = root->right->key;
                else num2 = root->key;
            }
            else num2 = root->key;
        }
        else num2 = root->key;
    }
    printf("u = %d\n",num2);
    return num2 - num1;
}

int inorder(struct Node* root)
{
    if(root!=0)
    {
        inorder(root->left);
        printf("%d ",root->mingap);
        inorder(root->right);
    }
    return 0;
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
    int l,u;
    printf("enter l and u\n");
    scanf("%d %d",&l,&u);
    inorder(root);
    printf("\n");
    printf("maxgap between %d and %d = %d\n",l,u,rangeMaxgap(root,l,u));
    printf("maxgap = %d mingap = %d\n",maxgap(root), mingap(root));
    return 0;
}