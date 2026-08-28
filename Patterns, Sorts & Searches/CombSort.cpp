#include<iostream>
using namespace std;
void combSort(int arr[], int n){
  int gap = n;
  float shrink = 1.3;
  bool swapped = true;
  while(gap != 1 || swapped == true){
    gap = (gap/shrink < 1.0) ? 1 : gap/shrink;
    swapped = false;
    for(int i = 0; i < n; i++){
      if(arr[i] > arr[i + gap]){
        swap(arr[i], arr[i + gap];
        swapped = true;
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
