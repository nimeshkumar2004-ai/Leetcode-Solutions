class Solution {
public:
    bool check(vector<int>& nums) {
        int n= nums.size();
        int i = n-1;
        while(i >0 && nums[i-1] <= nums[i]){
            i--;
        }
        if(i == 0 )return true;
        for(int j = i ; j <(i+n)-1;j++){
            if(nums[j%n] > nums[(j+1)%n]){
                return false;
            }
        }
        return true;
    }
};