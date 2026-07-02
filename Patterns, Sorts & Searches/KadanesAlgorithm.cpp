#include<iostream>
using namespace std;
int main(){
    int sz = 7;
    int arr[sz] = {3, -4, 5, 4, -1, 7, -8};
    int maxSum = INT_MIN;
    int currentSum = 0;
    for (int i = 0; i < sz; i++)
    {
        currentSum += arr[i];
        maxSum = max(currentSum, maxSum);
        if (currentSum < 0)
        {
            currentSum = 0;
        }   
    }
    cout << "Max Subarray Sum: " << maxSum;
    return 0 ;
}
