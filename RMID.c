#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
int leftsize;
int rightsize;


// function to get the height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
//function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

struct Node* newNode(int key) 
{ 
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// function to right rotate subtree
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
    return x; // Return new root 
}
  
//function to left rotate subtree
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
    return y; 
} 

  
// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
//function for counting the number of nodes
/*  int count(struct Node *n){
  int c=1;
  if(n->left)
    c+=count(n->left);
  if(n->right)
    c+=count(n->right);
  return c;
}
*/
struct Node* insert(struct Node* node, int key) 
{ 
   
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key){ 
        leftsize++;
        node->left  = insert(node->left, key); }
    else if (key > node->key) 
        rightsize++;
        node->right = insert(node->right, key); 
    else 
        return node; 
  
 
    node->height = 1 + max(height(node->left), 
                           height(node->right)); //Height update
 
    int balance = getBalance(node); //Balance factor
  
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

    return node; 
} 
Node * minValueNode(Node* node)  
{  
    Node* current = node;  
    while (current->left != NULL)  
        current = current->left;  
    return current;  
}  
Node* deleteNode(Node* root, int key)  
{   
    if (root == NULL)  
        return root;  
  
    if ( key < root->key ){ 
        leftsize--;
        root->left = deleteNode(root->left, key); } 
    else if( key > root->key ) {
        rightsize--;
        root->right = deleteNode(root->right, key);  }
    else
    {  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else 
            *root = *temp; 
            free(temp);  
        }  
        else
        {   
            Node* temp = minValueNode(root->right);  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    }  
    if (root == NULL)  
    return root;  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  

    int balance = getBalance(root);  
    if (balance > 1 && getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
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
int getpred(struct Node* node){

    struct Node* parent=newNode(0);
    struct Node* current=newNode(0);
    parent=node->left;
    current=parent;
    while (current != NULL) {
            parent = current;
            current = current->right;
        }
        return parent->key;
}
int getsucc(struct Node* node){

    struct Node* parent=newNode(0);
    struct Node* current=newNode(0);
    parent=node->right;
    current=parent;
    while (current != NULL) {
            parent = current;
            current = current->left;
        }
        return parent->key;
}



int main()
{
  int test;
  while(test--){
      int n;
      while (scanf ("%d",&n) != 0) {
          struct Node *root = NULL; 
          leftsize=0;
          rightsize=0;
          int i;
          if(n!=-1){
            root = insert(root, n);  
          }


  }
  }}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /* int t;
    int med;
   scanf("%d",&t);
   while(t--){
       //int number=0;
       bool cond=true;
       while(cond==true){
             struct Node *root = NULL; 
             leftsize=0;
             rightsize=0;
             int i;
             scanf("%d",&i);
             if(i!=-1 && i!=0){
                root = insert(root, i);
               // number=number+1; 
             }
             else if(i==-1){
                int L=count(root->left);
                int R=count(root->right);
                int number=L+R+1;
                int evennodes=number%2==0;
                if(L==R){
                    med=root->key;
                    deleteNode(root,med);
                }
                else if(evennodes==1) //true means 1 and false means 0 
                {
                    if(L==number/2){
                        med=(root->key + getpred(root))/2;
                        deleteNode(root,med);
                    }
                    else if(R==number/2){
                        med=(root->key + getsucc(root))/2;
                        deleteNode(root,med);
                    }
                }
             }

       }
        
  
    