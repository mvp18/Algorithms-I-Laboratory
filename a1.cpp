#include <iostream>
#include <cmath> 
#include <iomanip>
#include <bits/stdc++.h> 
using namespace std;

double hirec (int n);
double lorec (int n);

double hirec (int n){

	if (n==0) return 1;
	else return (2*hirec(n-1)+lorec(n-1));
}

double lorec (int n){

	if (n==0) return 0;
	else return (hirec(n-1)+lorec(n-1));
}

double* hilorec(int n){  
  
    if (n==0){

    	double* arr = new double[2];
		arr[0] = 1;
    	arr[1] = 0;
    	
    	return arr;
    }
    else{
    	double* arr_1 = new double[2];
    	arr_1 = hilorec(n-1);
    	double h_n = 2*arr_1[0] + arr_1[1];
    	double l_n = arr_1[0] + arr_1[1];
    	double* arr_2 = new double[2];
    	arr_2[0] = h_n;
    	arr_2[1] = l_n;

    	return arr_2;
    }
    
}

double* hiloformula(int n){  
  
    if (n==0){

    	double* arr = new double[2];
		arr[0] = 1;
    	arr[1] = 0;
    	
    	return arr;
    }
    else{
    	double* arr_1 = new double[2];    	
    	arr_1[0] = ((5+sqrt(5))/10)*(pow((3-sqrt(5))/2, n+1)) + ((5-sqrt(5))/10)*(pow((3+sqrt(5))/2, n+1));
    	arr_1[1] = ((-5-3*sqrt(5))/10)*(pow((3-sqrt(5))/2, n+1)) + ((-5+3*sqrt(5))/10)*(pow((3+sqrt(5))/2, n+1)); 

    	return arr_1;
    }
    
}  

int main(){
	int n;
	cin >> n;
	double* arr_1 = hilorec(n);
	double* arr_2 = hiloformula(n); 
	cout << "\n+++ Method 0\n    hi(" << n << ") = " << std::scientific << hirec(n) << ", lo(" << n << ") = " << std::scientific << lorec(n) << endl;
	cout << "\n+++ Method 1\n    hi(" << n << ") = " << std::scientific << arr_1[0] << ", lo(" << n << ") = " << std::scientific << arr_1[1] << endl;
	cout << "\n+++ Method 2\n    hi(" << n << ") = " << std::scientific << arr_2[0] << ", lo(" << n << ") = " << std::scientific << arr_2[1] << endl;
	
	return 0;
}