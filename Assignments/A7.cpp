#include <iostream>
#include <bits/stdc++.h>
#include <cmath> 
using namespace std;

typedef struct node
{    
    int key; 
    struct node *left; 
    struct node *right; 
} BSTNode;

BSTNode *newNode(int item){
 
    BSTNode *temp =  (BSTNode *)malloc(sizeof(BSTNode)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
}

BSTNode* BSTins(BSTNode* node, int key){
 
    if (node == NULL) return newNode(key); 
  
    if (key < node->key) 
        node->left  = BSTins(node->left, key); 
    else if (key > node->key) 
        node->right = BSTins(node->right, key);    
  
    return node; 
}

void printInorder(BSTNode* node){
    
    if (node == NULL) return; 
    printInorder(node->left); 
    cout << node->key << " "; 
    printInorder(node->right); 
} 
  
void printPreorder(BSTNode* node){
 
    if (node == NULL) return; 
    cout << node->key << " "; 
    printPreorder(node->left);  
    printPreorder(node->right); 
}

void BSTprn(BSTNode* node){

	cout << "+++ BST constructed from input array" << endl;
	cout << "Preorder : ";
	printPreorder(node);
	cout << "\nInorder : ";
	printInorder(node);
	cout << endl;
}

BSTNode* BSTcons(vector<int> &A, int n){
	
	BSTNode *root = NULL;
	for(int i=0; i<n; ++i){
		root = BSTins(root, A[i]);
	}

	return root;
}

void BSTfree(BSTNode* node){
 
    if (node == NULL) return; 

    BSTfree(node->left); 
    BSTfree(node->right);  
    free(node); 
}  

int BSTsame(BSTNode* T1, BSTNode* T2){

    if (T1==NULL && T2==NULL) return 1; 

    if (T1!=NULL && T2!=NULL){
     
        return
        ( 
            T1->key == T2->key && 
            BSTsame(T1->left, T2->left) && 
            BSTsame(T1->right, T2->right) 
        ); 
    } 
      
    return 0; 
}

int fact(int n){

    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
}

int nCr(int n, int r){
 
    return fact(n)/(fact(r)*fact(n - r)); 
}

int countSetBits(unsigned int n){
 
    int count = 0; 
    while (n) { 
        count += n & 1; 
        n >>= 1; 
    } 
    return count; 
}   

int countseq(vector<int> A, int n){
	
	if(n<=2) return 1;
	
	int a0 = A[0];
	int L=0, R=0;
	for(int i=1; i<n; ++i){
		if(A[i]<a0) L++;
		else R++;
	}
	
	vector<int> left(L);
	vector<int> right(R);

	int l_count=0, r_count=0;

	for(int i=1; i<n; ++i){
		
		if(A[i]<a0){

			left[l_count] = A[i];
			l_count++;
		}
		else{
			right[r_count] = A[i];
			r_count++;
		}
	}

	int count = countseq(left, L)*countseq(right, R)*nCr(L+R, L);

	return count;

}

int* decToBinary(int t, int size){ 
    // array to store binary number 
    int binaryNum[32];
    int* binary = (int *)malloc(size*sizeof(int));
    for(int i=0; i<size; ++i) binary[i]=0; 
  
    // counter for binary array 
    int i = 0; 
    while (t > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = t % 2; 
        t = t / 2; 
        i++; 
    } 
  
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        binary[j] = binaryNum[j];

    return binary; 
}

void merge_LR(vector<vector<int> > &seq, vector<int> &AL, vector<int> &AR, int n){

	for(int t=0; t < pow(2, n-1); ++t){

		int* B = decToBinary(t, n-1);

        if(countSetBits(t) == AR.size()){
        
            vector<int> vec(n);
            vec[0] = AL[0];
            int li = 1, ri = 0;
            for(int i=0; i<n-1; i++)
            {
                if(B[i] == 0)
                    vec[i+1] = AL[li++];
                else
                    vec[i+1] = AR[ri++];
            }
            for(int i=0; i<n; i++)
                cout<<vec[i]<<" ";
            cout<<endl;
            seq.push_back(vec);
        }
    }
}

vector<vector<int> > findallseq(vector<int> A, int n){

    if(n<=2){
    
        vector<vector<int> > seq;
        seq.push_back(A);
        return seq;
    }

    vector<vector<int> > seq;
	vector<int> AL;
    vector<int> AR;
    
    for(int i=1; i<n; i++){
    	if(A[i]<A[0]) AL.push_back(A[i]);
        else AR.push_back(A[i]);
    }
    
    vector<vector<int> > left_seq = findallseq(AL, AL.size());
    vector<vector<int> > right_seq = findallseq(AR, AR.size());
    
    for(int i=0; i<left_seq.size(); i++){
    	for(int j=0; j<right_seq.size(); j++){
        
            vector<int> left = left_seq[i];
            left.insert(left.begin(), A[0]);
            vector<int> right = right_seq[j];
            merge_LR(seq, left, right, n);
        }
    }
    
    return seq;
}

void checkall(BSTNode *T, vector<vector<int> > &seq, int n){

	int flag=1;
	for(int i=0; i<seq.size(); ++i){
		BSTNode* T_ = BSTcons(seq[i], n);
		if(!BSTsame(T, T_)) flag=0;
	}
	if(flag) cout << "\nAll trees match" << endl;
}

int main(){
	int n;
	cin >> n;
	vector<int> A(n);
	for(int i=0; i<n; i++){
		cin >> A[i];
	}
	cout << "+++ Sequence count" << endl;
	cout << "+++ All sequences" << endl;
	vector<vector<int> > seq = findallseq(A, n);
	cout << "Total number of sequences = " << countseq(A, n) << endl;
	BSTNode *T = BSTcons(A, n);
	BSTprn(T);
	checkall(T, seq, n);
}