#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define MINUSINFINITY -1000000000

struct node 
{ 
    int data; 
    struct node *left; 
    struct node *right; 
};

struct node* rrotate(struct node* u){
   
   struct node* v, *w;

   v = u->left;
   if (v == NULL) return u;
   
   w = v->right;
   v->right = u;
   u->left = w;
   
   return v;
}

// void swap_child(struct node* u){

// 	int temp = u->left;
// 	u->left = u->right;
// 	u->right = temp;
// }

struct node* lrotate(struct node* u){

   struct node* v, *w;

   v = u->left;
   if (v == NULL) return u;
   
   w = v->left;
   v->left = u;
   u->right = w;
   
   return v;
}

// struct node* makeskew(struct node* T){

// 	struct node* p;
// 	p = T;
// 	while (T->right) {
// 		while (T->right->left) T->right = rrotate(T->right);
//     	T = T->right;
//    }

//    return T;
// }

void makeskew(struct node* T, struct node* dummy){

	if(T == NULL || (T->left == NULL && T->right == NULL))
        return;

    if(T->left==NULL)
        makeskew(T->right,T);
    
    while(T->left){

        T = rrotate(T);
        if(dummy != NULL){

            dummy->right = T;
            dummy = T;
        }
    }
    makeskew(T->right, T);
}

struct node* readtree(int n){

	if(n <= 0)
    	return NULL;
    int key, n1, n2;
    
    cin >> key >> n1 >> n2;
        
    struct node* T = (struct node *)malloc(sizeof(struct node));
    T->data = key;
    
    if(n == 1){

    	T->left = NULL;
        T->right = NULL;
        return T;
    }
    
    T->left = readtree(n1);
    T->right = readtree(n2);
    
    return T;
}  

void printInorder(struct node* node){
    
    if (node == NULL) 
        return; 
    printInorder(node->left); 
    cout << node->data << " "; 
    printInorder(node->right); 
} 
  
void printPreorder(struct node* node){
 
    if (node == NULL) 
        return; 
    cout << node->data << " "; 
    printPreorder(node->left);  
    printPreorder(node->right); 
}

int main(){

	int n;
	cout << "n = ";
	cin >> n;
	// int *pre = (int *)malloc(n*sizeof(int));
	// int *lnodes = (int *)malloc(n*sizeof(int));
	// int *rnodes = (int *)malloc(n*sizeof(int));
	// for(int i=0; i<n; ++i){
		// cin >> pre[i];
		// cin >> lnodes[i];
		// cin >> rnodes[i];
	// }
	struct node *root = readtree(n);
	cout << "+++ Initial tree" << endl;
	cout << "--- Preorder Listing" << endl;
	printPreorder(root);
	cout << "\n--- Inorder Listing" << endl;
	printInorder(root);
	// struct node *skew_tree = makeskew(root);
	makeskew(root, root);
	cout << "\n+++ Tree made skew" << endl;
	cout << "--- Preorder Listing" << endl;
	// printPreorder(skew_tree);
	printPreorder(root);
	cout << "\n--- Inorder Listing" << endl;
	// printInorder(skew_tree);
	printInorder(root); 
	return 0;
}