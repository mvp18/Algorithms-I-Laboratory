#include <iostream>
#include <string>
using namespace std;

int method_0(int arr[], int n){
	int index_a, index_b, index_c;
	int a, b, c;
	int flag=0;
	
	for(int a=1; a<=n; a++){
		for(int b=a+1; b<=n; b++){
			for(int c=b+1; c<=n; c++){
				for(int z=0; z<n; z++){
					if (arr[z]==c) index_c=z;
					else if (arr[z]==a)	index_a=z;
					else if (arr[z]==b) index_b=z;
				}
				if ((index_c<index_a) && (index_a<index_b)){
					flag=1;
					break;
				}				
			}
		}
	}

	return flag;
}

int method_1(int arr[], int n){
	int index_a, index_b, index_c;
	int a, b, c;
	int flag=0;
	
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			for(int k=j+1; k<n; k++){
				c=arr[i]; a=arr[j]; b=arr[k];
				if ((a<b)&&(b<c)){
					flag=1;
					break;
				}
			}
		}
	}
	
	return flag;
}

int method_2(int arr[], int n){
	int flag_dec=0;
	
	for(int i=0; i<n; i++){
		int c=arr[i];
		int prev=c;
		for(int j=i+1; j<n; j++){
			if(arr[j]<c){
				if (arr[j]>prev){
				flag_dec=1;
				break;
				}
				else prev=arr[j];
			}
		}
	}

	return flag_dec;

}

string produce_string(int flag){

	if (flag==0) return "Algolicious";
	else return "Unalgolicious";
}

int main(){
	int n;
	cout << "n = ";
	cin >> n;
	int arr[n];
	for (int i=0; i<n; i++){
		cin >> arr[i];
	}
	cout << "+++ Sequence: ";
	for(int i=0; i<sizeof(arr)/sizeof(int); i++){
		cout << arr[i] << " ";
	}
	int flag_0 = method_0(arr, n);
	int flag_1 = method_1(arr, n);
	int flag_2 = method_2(arr, n);
	cout << "\nMethod 0:" << produce_string(flag_0)<<endl;
	cout << "Method 1:" << produce_string(flag_1)<<endl;
	cout << "Method 2:" << produce_string(flag_2)<<endl;
	return 0;
}