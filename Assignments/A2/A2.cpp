#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 

int* bubblesort(int arr[], int size){
	int i,j;
	for (i=size-1;i>0;--i){
		for (j=0; j<i; ++j){
			if (arr[j]>arr[j+1]){
				int t=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=t;
			}
		}
	}

	return arr;
}

void print_sorted_strings(vector<string> &A){

	int* count_arr = (int*) malloc(A.size()*sizeof(int));
	for (int i=0; i<A.size(); i++){
		int count1=0;
		for (int j=0; j<A[i].length(); j++){
			if(A[i][j]=='1') count1+=1;
		count_arr[i]=count1;
		}
	}

	int* count_arr_sorted=bubblesort(count_arr, A.size());

	for (int i=0; i<A.size(); i++){
		for (int j=0; j<A.size(); j++){
			if (count_arr_sorted[i]==A[i].length()) cout << A[i] << endl;
		}
		
	}
}

void push2vec(vector<string> &exp_arr, vector<string> &sub_exp1, vector<string> &sub_exp2, int mode){
    
    string s1, s2;
    for(int i=0; i < sub_exp1.size(); i++){
        s1 = sub_exp1[i];
        for(int j=0; j<sub_exp2.size(); j++){
        	s2 = sub_exp2[j];
            if(mode) exp_arr.push_back(s1 + "+" + s2);
            else exp_arr.push_back("("+s1+")"+"x"+"("+s2+")");
        }
    }
}

vector<string> findallexpr(int n){

    vector<string> exp_arr;
    
    if(n==1){
        exp_arr.push_back("1");
        return exp_arr;
    }
    else{
    	vector<string> sub_exp1, sub_exp2;
	    for(int i=1; i<=n-1; ++i){
	  
	        for(int j=i; j<=n-1; ++j){
	        
	            if(i+j==n){

	                sub_exp1 = findallexpr(i);
	                sub_exp2 = findallexpr(j);
	                push2vec(exp_arr, sub_exp1, sub_exp2, 1);
	            }
	            if(i*j==n){
	            	if (i!=1 && j!=1){
		                sub_exp1 = findallexpr(i);
		                sub_exp2 = findallexpr(j);
		                push2vec(exp_arr, sub_exp1, sub_exp2, 0);
		            }
	            }
	        }
	    }
	return exp_arr;
	}
    
}

void printallexpr(set<string> &A){

	set<string>::iterator it; 
   
    // cout << "\nAfter removing duplicates:\n"; 
    for (it = A.begin(); it != A.end(); ++it) 
        cout << *it << endl; 

	// cout << "Num expressions : " << A.size()<<endl;

	// for (int i=0; i<A.size(); i++){
	// 	cout << A[i] << "\n";
	// } 
        
}

void remove_duplicates_and_print(vector<string> arr){
   
    set<string> s; 

    for (int i = 0; i < arr.size(); i++) {  
        s.insert(arr[i]); 
    }

    printallexpr(s); 
       
}

int main(){

	int n;
	cout << "n = ";
	cin >> n;
	vector<string> vect; 
    vect = findallexpr(n);
    cout << "+++ Before sorting" << endl;
    cout << n << " = " << endl;
    remove_duplicates_and_print(vect);
    print_sorted_strings(vect); 
	return 0;
}