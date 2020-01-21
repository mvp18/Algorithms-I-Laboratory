#include <iostream>
#include <stdio.h>
using namespace std;

void merge(int arr[], int l, int m, int r){

    int s1 = m-l+1;
    int s2 = r-m;
    int temp1[s1], temp2[s2];

    int i, j, k;
    
    for (i=0; i<s1; ++i){
        temp1[i] = arr[l+i];
    }
    
    for (j=0; j<s2; ++j){

        temp2[j] = arr[m+1+j];
    }
    
    i=0; j=0; k=l;
    
    while ((i<s1)&&(j<s2)){

        if(temp1[i] <= temp2[j]){

            arr[k] = temp1[i];
            i++;
        }
        else{

            arr[k] = temp2[j];
            j++;
        }
        k++;
    }

    while (i<s1){

        arr[k]=temp1[i];
        i++;
        k++;
    }

    while (j<s2){

        arr[k]=temp2[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r){

    if (l<r){

        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        cout << A[i] << " ";
    cout << endl;  
} 
  
int main() 
{ 
    int arr[] = {12, 11, 13, 5, 6, 7}; 
    int arr_size = sizeof(arr)/sizeof(arr[0]); 
  
    cout << "Given array is " << endl; 
    printArray(arr, arr_size); 
  
    mergeSort(arr, 0, arr_size - 1); 
  
    cout << "Sorted array is " << endl; 
    printArray(arr, arr_size); 
    
    return 0; 
} 