#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

int find_num_2_factors(int n){

	int fact_count=0;
	while(n%2==0){
		n/=2;
		fact_count+=1;
	}

	// cout << "\nNum factors = " << fact_count << endl;

	return fact_count;
}

void greedy2(int n){

	int temp;
	int opt1, opt2;
	int fact_opt1, fact_opt2;
	temp = n;
	cout << "\nStart : " << n << endl;
	int num_steps=0;
	while(temp!=1){
		if (temp==3){
			temp-=1;
			cout << "Decrement : " << temp << endl;
		}
		else{

			if(temp%2==0){
				temp/=2;
				cout << "Divide : " << temp << endl;
			} 
			else{
				opt1 = temp-1; opt2 = temp+1;
				fact_opt1 = find_num_2_factors(opt1);
				fact_opt2 = find_num_2_factors(opt2);
				temp = (fact_opt1>fact_opt2) ? opt1 : opt2;
				// cout << temp << opt1 << opt2;
				if(temp==opt1){
					cout << "Decrement : " << temp << endl;
				}
				else cout << "Increment : " << temp << endl;			
			}
		}
		num_steps+=1; 
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

void greedy1(int n){

	int temp;
	temp = n;
	cout << "\nStart : " << n << endl;
	int num_steps=0;
	while(temp!=1){
		if(temp%2==0){
			temp/=2;
			cout << "Divide : " << temp << endl;
		} 
		else{
			temp-=1;
			cout << "Decrement : " << temp << endl;
		}
		num_steps+=1; 
	}
	cout << "--- Number of steps = " << num_steps << endl;

}

void greedy3(int n, int k, int A[]){
	int temp;
	int opt1, opt2;
	int fact_opt1, fact_opt2;
	int *temp_arr = (int *)malloc(k*sizeof(int));
	int max_ele;
	int last_occ;
	int ele_A;
	temp = n;
	cout << "\nStart : " << n << endl;
	int num_steps=0;
	while(temp!=1){
		if(temp%2==0){
			temp/=2;
			cout << "Divide : " << temp << endl;
		} 
		else{
			max_ele = -99999;
			for(int i=0;i<k;++i){
				if ((temp+A[i])>0) temp_arr[i] = find_num_2_factors(temp + A[i]);
				else temp_arr[i]=0;
				// cout << temp_arr[i] << " ";
			}
			for(int i=0;i<k;++i){
				if (temp_arr[i]>max_ele){
					max_ele = temp_arr[i];
					last_occ = i;
					ele_A = A[i];
					// cout << "\n Max : " << max_ele << " " << ele_A << endl; 
				}
				if (temp_arr[i]==max_ele){
					if(A[i]<A[last_occ]){
						last_occ=i;
						ele_A=A[i];
					}
				}
			}
			temp+=ele_A;
			cout << "Add " << ele_A << " : " << temp << endl;
			// break;			
		}
		num_steps+=1; 
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

void optimal(int n, int k, int A[]){
	int temp;
	int opt1, opt2;
	int fact_opt1, fact_opt2;
	int *temp_arr = (int *)malloc(k*sizeof(int));
	int max_ele;
	int last_occ;
	int ele_A;
	temp = n;
	cout << "\nStart : " << n << endl;
	int num_steps=0;
	while(temp!=1){
		if(temp%2==0){
			int *temp_arr2 = (int *)malloc((k+1)*sizeof(int));
			int *A2 = (int *)malloc((k+1)*sizeof(int));
			A2[0] = temp;
			for(int i=1;i<=k;i++){
				A2[i] = A[i-1];
			}
			temp_arr2[0] = find_num_2_factors(A2[0]);
			max_ele = -99999;
			for(int i=1;i<k;++i){
				if ((temp+A2[i])>0) temp_arr2[i] = find_num_2_factors(temp + A2[i]);
				else temp_arr2[i]=0;
				// cout << temp_arr[i] << " ";
			}
			for(int i=0;i<k;++i){
				if (temp_arr2[i]>max_ele){
					max_ele = temp_arr2[i];
					last_occ = i;
					ele_A = A2[i];
					// cout << "\n Max : " << max_ele << " " << ele_A << endl; 
				}
				if (temp_arr2[i]==max_ele){
					if(A2[i]<A2[last_occ]){
						last_occ=i;
						ele_A=A2[i];
					}
				}
			}
			if (last_occ!=0){
				temp+=ele_A;
				cout << "Add : " << ele_A << " : " << temp << endl;
				temp/=2;
				cout << "Divide : " << temp << endl;	
				num_steps+=2;
			} 
			else{
				temp/=2;
				cout << "Divide : " << temp << endl;
				num_steps+=1;
			} 
			
		} 
		else{
			max_ele = -99999;
			for(int i=0;i<k;++i){
				if ((temp+A[i])>0) temp_arr[i] = find_num_2_factors(temp + A[i]);
				else temp_arr[i]=0;
				// cout << temp_arr[i] << " ";
			}
			for(int i=0;i<k;++i){
				if (temp_arr[i]>max_ele){
					max_ele = temp_arr[i];
					last_occ = i;
					ele_A = A[i];
					// cout << "\n Max : " << max_ele << " " << ele_A << endl; 
				}
				if (temp_arr[i]==max_ele){
					if(A[i]<A[last_occ]){
						last_occ=i;
						ele_A=A[i];
					}
				}
			}
			temp+=ele_A;
			cout << "Add " << ele_A << " : " << temp << endl;
			// break;
			num_steps+=1;			
		}
		 
	}
	cout << "--- Number of steps = " << num_steps << endl;
}

int main(){
	int n;
	cout << "n = ";
	cin >> n;
	cout << "\n+++ Greedy 1" << endl;
	greedy1(n);
	cout << "\n+++ Greedy 2" << endl;
	greedy2(n);
	int k;
	cout << "k = ";
	cin >> k;
	int *A = (int *)malloc(k*sizeof(int));
	for(int i=0;i<k;i++){
		cin >> A[i];
	}
	cout << "\n";
	for(int i=0;i<k;i++){
		cout << A[i] << " ";
	}
	cout << "\n\n";
	cout << "+++ Greedy 3" << endl;
	greedy3(n, k, A);
	cout << "+++ Optimal" << endl;
	optimal(n, k, A);
	return 0;
}