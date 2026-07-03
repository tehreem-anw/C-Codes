#include<iostream>
using namespace std;
int main(){
    int arr[7] = {6, 7, 4, 8, 9, 5, 2};
    int target = 8;
    for (int i = 0; i < 7; i++)
    {
        if (arr[i] == target)
        {
            cout << "Target " << target << " found at index: " << i << endl;
            return 0;
        }
    }
    return -1;
}