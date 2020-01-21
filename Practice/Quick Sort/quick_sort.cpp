#include <iostream>
#include <stdio.h>
using namespace std;

void swap(int* a, int* b){

    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high){

    int pivot = arr[high];
    int i = low-1;
    int j=0;
    
    for (j=low; j<high; ++j){

        if (arr[j] < pivot){

            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i+1], &arr[j]);
    return (i+1);
}

void quickSort(int arr[], int low, int high){

    if (low<high){

        int partition_index = partition(arr, low, high);
        quickSort(arr, low, partition_index-1);
        quickSort(arr, partition_index+1, high);
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
  
    quickSort(arr, 0, arr_size - 1); 
  
    cout << "Sorted array is " << endl; 
    printArray(arr, arr_size); 
    
    return 0; 
}