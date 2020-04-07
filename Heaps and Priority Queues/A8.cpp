#include <iostream>
#include <bits/stdc++.h>
#include <cmath> 
using namespace std;

typedef struct multi_heap
{
	int node_cap;
	int num_keys;
	int num_nodes;
	vector<vector<int> > nodes;
} heap;

heap* initheap(int p, int n_max){

	heap *H = (heap *)malloc(sizeof(heap));
	H->node_cap = p;
	H->num_keys = 0;
	H->num_nodes = 0;
	return H;
}

void insert(heap* H, int x){

	// int last_node_index;
	
	if(H->num_keys < H->node_cap*H->num_nodes){
		// last_node_index = H->num_nodes%H->node_cap;
		H->nodes[H->num_nodes-1].push_back(x);
	}
	else{
		vector<int> vec(1, x);
		H->nodes.push_back(vec);
		H->num_nodes++;
	}
	
	H->num_keys++;
	
	int i, p;
	i=H->num_nodes-1;
	
	while(1){
		
		if (i==0) return;
		
		p = (i-1)/2;
		int i_max=-99999, p_min=99999;
		
		for(int j=0; j<H->nodes[i].size(); ++j)
			if(H->nodes[i][j]>i_max) i_max = H->nodes[i][j];
		
		for(int k=0; k<H->nodes[p].size(); ++k)
			if(H->nodes[p][k]<p_min) p_min = H->nodes[p][k];
		
		if(p_min >= i_max) return;
		
		vector<int> B;
		for(int j=0; j<H->nodes[i].size(); ++j) B.push_back(H->nodes[i][j]);
		for(int k=0; k<H->nodes[p].size(); ++k) B.push_back(H->nodes[p][k]);
		sort(B.begin(), B.end(), greater<int>());

		H->nodes[i].clear();
		H->nodes[p].clear();

		for(int j=0; j<B.size(); ++j){

			if(j<=H->node_cap-1) H->nodes[p].push_back(B[j]);
			else H->nodes[i].push_back(B[j]);
		}
		i=p;
	}
}

void prnheap(heap* H){

	cout << "\n";

	for(int i=0; i<H->num_nodes; ++i){
		cout << "[ ";
		for(int j=0; j<H->nodes[i].size(); ++j)
			cout << H->nodes[i][j] << " ";
		cout << " ] " << endl;
	}
}

int findmax(heap* H, int *max_index){

	if (H->nodes[0].size()==0){

		cout << "Heap has been completely emptied." << endl;
		return -1;
	}

	int max_ele = -99999;
	
	for(int i=0; i<H->nodes[0].size(); ++i){
		// cout << "\n------------" <<endl;
		if(H->nodes[0][i] > max_ele){

			max_ele = H->nodes[0][i];
			*max_index = i;
		}
	}

	return max_ele;
}

void heapify(heap* H, int index){

	int l, r, l_max, r_max, i_min, child_ind;

	while(1){

		l = 2*index+1; r = 2*index+2;
		
		if(l >= H->num_nodes) return;

		l_max = -99999; r_max = -99999; i_min = 99999;

		for(int i=0; i<H->nodes[index].size(); ++i)
			if(H->nodes[index][i] < i_min) i_min = H->nodes[index][i];

		for(int j=0; j<H->nodes[l].size(); ++j)
			if(H->nodes[l][j] > l_max) l_max = H->nodes[l][j];
		
		for(int k=0; k<H->nodes[r].size(); ++k)
			if(H->nodes[r][k] > r_max) r_max = H->nodes[r][k];

		if ((i_min >= l_max) && (i_min >= r_max)) return;

		child_ind = ((r==H->num_nodes) || (i_min < l_max)) ? l : r;

		vector<int> B;
		for(int j=0; j<H->nodes[index].size(); ++j) B.push_back(H->nodes[index][j]);
		for(int k=0; k<H->nodes[child_ind].size(); ++k) B.push_back(H->nodes[child_ind][k]);
		
		sort(B.begin(), B.end(), greater<int>());

		H->nodes[index].clear();
		H->nodes[child_ind].clear();

		for(int j=0; j<B.size(); ++j){

			if(j<=H->node_cap-1) H->nodes[index].push_back(B[j]);
			else H->nodes[child_ind].push_back(B[j]);
		}

		index = child_ind;
	}	
}

void delmax(heap* H){

	if (H->nodes[0].size()==0) return;

	// H->nodes[0].erase(std::remove(H->nodes[0].begin(), H->nodes[0].end(), findmax(H)), H->nodes[0].end());

	int max_ele, max_index;

	max_ele = findmax(H, &max_index);

	H->nodes[0].erase(H->nodes[0].begin()+max_index);

	// prnheap(H);
	
	if (H->num_nodes==1) return;

	int ele_moved = H->nodes[H->num_nodes-1][0];
	H->nodes[0].push_back(ele_moved);
	
	// H->nodes[H->num_nodes-1].erase(std::remove(H->nodes[H->num_nodes-1].begin(), H->nodes[H->num_nodes-1].end(), ele_moved), H->nodes[H->num_nodes-1].end());

	H->nodes[H->num_nodes-1].erase(H->nodes[H->num_nodes-1].begin());

	// prnheap(H);
	
	if (H->nodes[H->num_nodes-1].size()==0) H->num_nodes--;
	
	H->num_keys--;
	
	heapify(H, 0);
}

int main(){

	int n, p;
	cin >> p >> n;
	int *A = (int *)malloc(n*sizeof(int));
	for(int i=0; i<n; ++i){
		cin >> A[i];
	}

	heap *H = initheap(p, n);
	for(int i=0; i<n; ++i){
		insert(H, A[i]);
	}

	cout << "\n+++ " << n << " Insertions made" << endl;
	prnheap(H);
	
	int max_index;

	for(int i=n-1; i>=0; --i){
		
		A[i] = findmax(H, &max_index);
		delmax(H);
	}

	cout << "\n+++ " << n << " Deletions made" << endl;
	cout << "\nInput array sorted" << endl;

	for(int i=0; i<n; ++i) cout << A[i] << " ";

	cout << "\n\n";

	return 0;
}