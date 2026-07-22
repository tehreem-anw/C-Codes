#include<iostream>
#include<vector>
using namespace std;
vector<int> pairSum(vector<int>& nums, int target){
    vector<int> sum;
    int ans;
    int start = 0;
    int end = nums.size() - 1;
    while(start < end){
        ans = nums[start] + nums[end];
        if (ans > target)
        {
            end--;
        }
        else if(ans < target){
            start++;
        }
        else{
            sum.push_back(start);
            sum.push_back(end);
            return sum;
        }
    }
    return {};
}
int main(){
    vector<int> nums = {2, 7, 11, 15};
    int target = 26;
    vector<int> sum = pairSum(nums, target);
    if(!sum.empty()){
        cout << "Ans: " << sum[0] << ", " << sum[1];
    }
    else{
        cout << "Pair not found." << endl;
    }
    return 0;
}