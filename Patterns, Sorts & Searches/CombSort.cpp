#include<iostream>
using namespace std;
void combSort(int arr[], int n){
  int gap = n;
  float shrink = 1.3;
  bool swapped = true;
  while(gap != 1 || swapped == true){
    gap = (gap/shrink < 1.0) ? 1 : gap/shrink;
    swapped = false;
  }
}
