#include <stdio.h>
#include <stdlib.h>
 
#define MAX 100005
 
typedef long long ll;
 
typedef struct tree
{
int data;
int size, height;
struct tree *right, *left;
} tree;
 
int max(int a, int b);
int size(tree *root);
tree *insert(int data, int pos, tree *root);
int height(tree *root);
tree *initialise(int data);
int balancing(tree *root);
tree *rightRotate(tree *root);
tree *leftRotate(tree *root);
 
 
 
tree *leftmostOf(tree *node)
{
tree *current = node;
 
while (current->left != NULL)
current = current->left;
 
return current;
}
 
tree *delete(int pos, tree *root)
{
if (root == NULL)
return root;
 
int root_pos = (root->left ? root->left->size : 0);
if (root_pos > pos)
root->left = delete(pos, root->left);
else if (root_pos < pos)
root->right = delete(pos - root_pos - 1, root->right);
else
{
if ((root->left == NULL) || (root->right == NULL))
{
tree *temp = root->left ? root->left : root->right;
 
if (temp == NULL)
{
temp = root;
root = NULL;
}
else
*root = *temp;
}
else
{
tree *leftmost = leftmostOf(root->right);
 
root->data = leftmost->data;
 
root->right = delete(0, root->right);
}
}
 
if (root == NULL)
return root;
 
root->size = 1 + size(root->left) + size(root->right);
root->height = 1 + max(height(root->right), height(root->left));
 
int balance = balancing(root); // height(left) - height(right)
 
 if (balance < -1) // right overload
{
if (balancing(root->right) >= 1) // right left case
{
root->right = rightRotate(root->right);
}
root = leftRotate(root);
}
else if (balance > 1) // left overload
{
if (balancing(root->left) <= -1) // left right case
{
root->left = leftRotate(root->left);
}
root = rightRotate(root);
}
return root;
}
 
void query(int pos, tree *root)
{
int root_pos = (root->left ? root->left->size : 0);
if (root_pos == pos)
{
printf("%d\n", root->data);
return;
}
else if (root_pos > pos)
query(pos, root->left);
else
query(pos - root_pos - 1, root->right);
}
 
void print(tree *root)
{
if (root == NULL)
return;
print(root->left);
// printf("%d,%d,%d left:%d  right:%d\n", root->data, root->size, root->height, (root->left ? root->left->data : 0), (root->right ? root->right->data : 0));
printf("%d ", root->data, root->size);
print(root->right);
return;
}
 
int main()
{
int n, q, value;
tree *root;
root = NULL;
scanf("%d %d", &n, &q);
 
for (int i = 0; i < n; i++)
{
scanf("%d", &value);
root = insert(value, i, root);
}
int Q;
while(Q<q) 
{
    Q++;
int type, k;
scanf("%d %d", &type, &k);
if (type==1){
scanf("%d", &value);
root = insert(value, k - 1, root);
n++;
}
if(type==2){
root = delete(k - 1, root);
n--;
}
if(type==3){
query(k - 1, root);
 
}
// print(root);
// printf("\n");
// fflush(stdout);
}
}
 
 
int max(int a, int b)
{
return a > b ? a : b;
}
 
int size(tree *root)
{
return root ? root->size : 0;
}
 
int height(tree *root)
{
return root ? root->height : 0;
}
 
int balancing(tree *root)
{
if (root == NULL)
return 0;
return height(root->left) - height(root->right);
}
 
tree *rightRotate(tree *root)
{
tree *x = root->left;
tree *T2 = x->right;
 
x->right = root;
// x->parent = root->parent;
 
// root->parent = x;
 
root->left = T2;
// if (T2)
// T2->parent = root;
 
root->height = max(height(root->left), height(root->right)) + 1;
x->height = max(height(x->left), height(x->right)) + 1;
 
root->size = 1 + size(root->left) + size(root->right);
x->size = 1 + size(x->left) + size(x->right);
 
return x;
}
 
tree *leftRotate(tree *root)
{
tree *y = root->right;
tree *T2 = y->left;
 
y->left = root;
// y->parent = root->parent;
 
// root->parent = y;
 
root->right = T2;
// if (T2)
// T2->parent = root;
 
root->height = max(height(root->left), height(root->right)) + 1;
y->height = max(height(y->left), height(y->right)) + 1;
 
root->size = 1 + size(root->left) + size(root->right);
y->size = 1 + size(y->left) + size(y->right);
 
return y;
}
 
tree *initialise(int data)
{
tree *newTree = (tree*) malloc(sizeof(tree));
newTree->data = data;
newTree->right = newTree->left = NULL;
newTree->size = 1;
newTree->height = 1;
return newTree;
}
 
tree *insert(int data, int pos, tree *root)
{
if (!root)
{
return initialise(data);
}
 
int root_pos = size(root->left);
 
if (root_pos >= pos)
{
root->left = insert(data, pos, root->left);
// root->left->parent = root;
}
else
{
root->right = insert(data, pos - root_pos - 1, root->right);
// root->right->parent = root;
}
root->size = 1 + size(root->left) + size(root->right);
root->height = 1 + max(height(root->right), height(root->left));
 
int balance = balancing(root); // height(left) - height(right)
 
if (balance > 1) // left overload
{
if (balancing(root->left) <= -1) // left right case
{
root->left = leftRotate(root->left);
}
root = rightRotate(root);
}
else if (balance < -1) // right overload
{
if (balancing(root->right) >= 1) // right left case
{
root->right = rightRotate(root->right);
}
root = leftRotate(root);
}
 
return root;
} 