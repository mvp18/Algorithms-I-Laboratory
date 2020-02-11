#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define MIN_COST -1e256

double find_profit(int m, double s, double t, double p){
	double profit = (1-pow(p,m))*s + pow(p, m)*t;
	// cout << profit;
	return profit;
}

void optimalbuy1(int n,int C, int c[], double s[], double t[], double p[]){
	double T[n][C+1];
	int M[n][C+1];
	int i,j;
	int m0;
	int m;
	double max_profit;
	double curr_profit;
	int best_mi;
	
	for(j=0; j<c[0];++j){
		T[0][j]=MIN_COST;
		M[0][j]=0;
	}
	
	for(j=c[0];j<C+1;++j){
		m0=int(j/c[0]);
		T[0][j]=find_profit(m0, s[0], t[0], p[0]);
		M[0][j]=m0;
	}
	
	for(i=1; i<n; ++i){
		for(j=0; j<c[i]; ++j){
			T[i][j]=MIN_COST;
			M[i][j]=0;
		}
	}
	
	for(i=1; i<n; ++i){
		for(j=c[i]; j<C+1; ++j){
			max_profit = MIN_COST;
			for(m=1; m<int(j/c[i]); ++m){
				
				if(j-m*c[i]<0) continue;
				
				curr_profit = T[i-1][j-m*c[i]] + find_profit(m, s[i], t[i], p[i]);
				if(curr_profit>max_profit){
					max_profit=curr_profit;
					best_mi=m;
				}

			M[i][j] = best_mi;
			T[i][j] = max_profit;
			
			}
		}
	}


	// for(i=0; i<n; ++i){
	// 	for(j=c[i]; j<C+1; ++j){
	// 		cout << M[i][j] << " ";
	// 	}
	// 	cout << endl;
	// 	cout << "----------------------------" << endl;
	// }

	int total_buying_cost=0;
	
	int rem_capital=C;
	int num_copies=0;
	
	for(i=n-1; i>=0; i--){
		cout << "Machine " << i << ": ";
		if(i==n-1) {
			num_copies=M[i][C];
		}
		else{
			rem_capital-=num_copies*c[i+1];
			// cout << "Rem capital " << rem_capital << endl;
			num_copies=M[i][rem_capital];
		}
		cout << num_copies << " copies, cost = " << c[i]*num_copies << endl;
		total_buying_cost += c[i]*num_copies;
	}
	cout << "--- Total buying cost = " << total_buying_cost << endl;

	cout << "--- Expected total profit = " << T[n-1][C] << endl;

}
void optimalbuy2(int n,int C, int c[], double s[], double t[], double r[], double p[], double q[]){
	double T[n][C+1];
	int M[n][C+1];
	int R[n];
	int i,j;
	int m0;
	int m;
	int r_counter;
	int repair_flag=0;
	double max_profit_r;
	double max_profit_nr;
	double curr_profit;
	int best_mi_r;
	int best_mi_nr;
	
	for(j=0; j<c[0];++j){
		T[0][j]=MIN_COST;
		M[0][j]=0;
	}
	
	for(j=c[0];j<C+1;++j){
		m0=int(j/c[0]);
		T[0][j]=find_profit(m0, s[0], t[0], p[0]);
		M[0][j]=m0;
	}
	
	for(i=1; i<n; ++i){
		for(j=0; j<c[i]; ++j){
			T[i][j]=MIN_COST;
			M[i][j]=0;
		}
	}
	
	for(i=1; i<n; ++i){
		for(j=c[i]; j<C+1; ++j){
			for(r_counter=0; r_counter<2;++r_counter){
				if(r_counter==0){
					max_profit_nr = MIN_COST;
					for(m=1; m<int(j/c[i]); ++m){
						
						if(j-m*c[i]<0) continue;
						
						curr_profit = T[i-1][j-m*c[i]] + find_profit(m, s[i], t[i], p[i]);
						if(curr_profit>max_profit_nr){
							max_profit_nr=curr_profit;
							best_mi_nr=m;
						}
					
					}
				}
				else{
					max_profit_r = MIN_COST;
					for(m=1; m<int(j/c[i]); ++m){
						
						if(j-m*c[i]<0) continue;
						
						curr_profit = T[i-1][j-m*c[i]] + find_profit(m, s[i], t[i], q[i]) - m*r[i];
						if(curr_profit>max_profit_r){
							max_profit_r=curr_profit;
							best_mi_r=m;
						}
					
					}	
				}
			}
			
			if(max_profit_nr>max_profit_r){
				M[i][j] = best_mi_nr;
				T[i][j] = max_profit_nr;
				repair_flag = 0;
			}
			else{
				M[i][j] = best_mi_r;
				T[i][j] = max_profit_r;
				repair_flag = 1;	
			}		
			
		}
		
		if(repair_flag) R[i]=1;
		else R[i]=0;
	}


	// for(i=0; i<n; ++i){
	// 	for(j=c[i]; j<C+1; ++j){
	// 		cout << M[i][j] << " ";
	// 	}
	// 	cout << endl;
	// 	cout << "----------------------------" << endl;
	// }

	int total_buying_cost=0;
	
	int rem_capital=C;
	int num_copies=0;
	
	for(i=n-1; i>=0; i--){
		cout << "Machine " << i << ": ";
		if(i==n-1) {
			num_copies=M[i][C];
		}
		else{
			rem_capital-=num_copies*c[i+1];
			// cout << "Rem capital " << rem_capital << endl;
			num_copies=M[i][rem_capital];
		}
		cout << num_copies << " copies, cost = " << c[i]*num_copies;
		total_buying_cost += c[i]*num_copies;
		if(R[i]==0) cout << "[Maintenance not needed]" << endl;
		else cout << "[Maintenance needed]" << endl;
	}
	cout << "--- Total buying cost = " << total_buying_cost << endl;

	cout << "--- Expected total profit = " << T[n-1][C] << endl;
}

int main(){
	
	// int C=2532;
	// int c[] = {41, 55, 51, 38, 83, 91, 43, 96, 98, 46, 95, 23, 89, 29, 52, 92};
	// double s[] = {98, 70, 50, 61, 94, 84, 91, 81, 81, 70, 82, 51, 97, 76, 95, 55};
	// double t[] = {10, 35, 12, 13, 36, 11, 25, 30, 39, 27, 17, 25, 19, 26, 14, 28};
	// double r[] = {5, 4, 5, 4, 3, 1, 3, 2, 2, 2, 5, 2, 4, 4, 1, 5};
	// double p[] = {0.9588481828, 0.6090085574, 0.9949199038, 0.5982189628, 
	// 			  0.8812402696, 0.5552817465, 0.7384469380, 0.6776996251, 
	// 			  0.8359002484, 0.8605754214, 0.7293403466, 0.7806705960,
	// 			  0.6731179239, 0.7149133080, 0.8381089516, 0.8136845610};
	// double q[] = {0.7686569828, 0.0610634239, 0.0545880344, 0.2801836246,
	// 			  0.8605711086, 0.3952110880, 0.2891662559,	0.3816935232,
	// 			  0.7402798372, 0.6947915922, 0.2011213947, 0.3774181376,
	// 			  0.5810420500, 0.0518749737, 0.8351910188, 0.3619142445};
	int C=3786;
	int c[] = {89, 61, 56, 86, 98, 84, 84, 94, 44, 83, 48, 40, 97, 94, 61, 70};
	double s[] = {65, 98, 74, 72, 68, 56, 77, 53, 90, 58, 57, 77, 89, 67, 59, 60};
	double t[] = {29, 18, 35, 11, 27, 22, 14, 36, 31, 24, 19, 11, 36, 30, 37, 30};
	double r[] = {5, 3, 3, 2, 3, 2, 1, 5, 5, 4, 5, 1, 1, 5, 1, 4};
	double p[] = {0.9677234022, 0.7029225953, 0.5956791426, 0.6206195374, 
				  0.6086358503, 0.8966557267, 0.8145519378, 0.5190614029, 
				  0.9906660006, 0.9170714719, 0.8970835644, 0.8764973501, 
				  0.7268638824, 0.9760647509, 0.6654729823, 0.7703263684};
	double q[] = {0.3540109271, 0.2268331615, 0.3009378525, 0.2915592198, 
				  0.3732578074, 0.5413447555, 0.5102089647, 0.4965962773, 
		          0.2930110220, 0.3343770039, 0.2340338334, 0.4770201073, 
				  0.4889666956, 0.4227880384, 0.6052897018, 0.4169863393};
	int n=sizeof(c)/sizeof(c[0]);
	cout << "+++	Part 1: Best buying option" << endl;
	optimalbuy1(n, C, c, s, t, p);
	cout << "\n\n";
	cout << "+++	Part 2: Best buying option" << endl;
	optimalbuy2(n, C, c, s, t, r, p, q); 
	return 0;
}