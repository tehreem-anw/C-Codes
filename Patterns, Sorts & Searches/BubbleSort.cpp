#include<iostream>
using namespace std;

void bubbleSort(int arr[], int n){
    for(int i = 0; i < n; i++){
        int isSwap = false;
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                isSwap = true;
            }
        }
    }
}

int main(){
    int arr[7] = {4, 2, 1, 8, 9, 6, 7};
    int n = 7;
    bubbleSort(arr, n);
    cout << "{";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << "}" << endl;
    return 0;
}
