#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

void merge(vector<vector<double> > &arr, int l, int m, int r){

    int s1 = m-l+1;
    int s2 = r-m;
    double temp1[s1][3], temp2[s2][3];

    int i, j, k;
    
    for (i=0; i<s1; ++i){
        temp1[i][0] = arr[l+i][0];
        temp1[i][1] = arr[l+i][1];
        temp1[i][2] = arr[l+i][2];
    }
    
    for (j=0; j<s2; ++j){

        temp2[j][0] = arr[m+1+j][0];
        temp2[j][1] = arr[m+1+j][1];
        temp2[j][2] = arr[m+1+j][2];
    }
    
    i=0; j=0; k=l;
    
    while ((i<s1)&&(j<s2)){

        if(temp1[i][0] <= temp2[j][0]){

            arr[k][0] = temp1[i][0];
            arr[k][1] = temp1[i][1];
            arr[k][2] = temp1[i][2];
            i++;
        }
        else{

            arr[k][0] = temp2[j][0];
            arr[k][1] = temp2[j][1];
            arr[k][2] = temp2[j][2];
            j++;
        }
        k++;
    }

    while (i<s1){

        arr[k][0] = temp1[i][0];
        arr[k][1] = temp1[i][1];
        arr[k][2] = temp1[i][2];
        i++;
        k++;
    }

    while (j<s2){

        arr[k][0]=temp2[j][0];
        arr[k][1]=temp2[j][1];
        arr[k][2]=temp2[j][2];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<double> > &lines, int l, int r){

    if (l<r){

        int m = l+(r-l)/2;
        mergeSort(lines, l, m);
        mergeSort(lines, m+1, r);
        merge(lines, l, m, r);
    }
} 

pair<double, double> find_intersection(double m1, double m2, double c1, double c2){
	double x,y;
	x = (c2-c1)/(m1-m2);
	y = (m1*c2 - m2*c1)/(m1-m2);
	return make_pair(x, y);
}

vector<vector<double> > method1(vector<vector<double> > A){

	double min_slope = 99999;
	int min_index=0;
	for(int i=0; i<A.size(); i++){
		if(A[i][0] < min_slope){
			min_slope=A[i][0];
			min_index=i;	
		} 
	}
	int* visible_arr = new int[A.size()];
	for(int i=0; i<A.size(); ++i){
		visible_arr[i]=0;
	}
	int current_line = min_index;
	visible_arr[min_index] = 1;
	pair<double, double> Q(-99999, 0);
	vector<vector<double> > boundary_pts;
	pair<double, double> curr_int_pt_with_min_x (99999, 0.0);
	
	for(int j=0; j<A.size(); j++){
		if(visible_arr[j]==0){
			for(int i=0; i<A.size(); ++i){
				if ((i!=current_line)&&(visible_arr[i]==0)){
					pair<double, double> curr_int_pt;
					curr_int_pt = find_intersection(A[current_line][0], A[i][0], A[current_line][1], A[i][1]); 
					if ((curr_int_pt.first>Q.first) && (curr_int_pt.first<curr_int_pt_with_min_x.first)){
						curr_int_pt_with_min_x = curr_int_pt;
						min_index=i;
						
					}
				}
				
			}

		current_line = min_index;
		visible_arr[current_line] = 1;
		Q = curr_int_pt_with_min_x;
		boundary_pts[0].push_back(Q.first);
		boundary_pts[1].push_back(Q.second);	
		
		}
				

	}

	return boundary_pts;
}

int main(){

	int n;
	cout << "n = ";
	cin >> n;
	vector<vector<double> > lines(n, vector<double> (3));
	for(int i=0; i<n; i++){
		cin >> lines[i][0] >> lines[i][1];
		lines[i][2]=i;
	}
	cout << "+++ Lines before sorting" << endl;
	for(int i=0; i<n; i++){
		cout << "Line " << lines[i][2] << ": y = " << lines[i][0] << "x + " << lines[i][1] << endl;
	}
	cout << "+++ Method 1" << endl;
	vector<vector<double> > rgn_visibility_pts;
	// rgn_visibility_pts = method1(lines);
	// for(int i=0; i<n; i++){
	// 	cout << ": y = " << rgn_visibility_pts[i][0] << "x + " << rgn_visibility_pts[i][1] << endl;
	// }
	cout << "+++ Lines after sorting" << endl;
	mergeSort(lines, 0, lines.size()-1);
	for(int i=0; i<n; i++){
		cout << "Line " << lines[i][2] << ": y = " << lines[i][0] << "x + " << lines[i][1] << endl;
	}
	return 0;
}