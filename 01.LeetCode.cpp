// LeetCode 31. Next Permutation; https://leetcode.com/problems/next-permutation/
// Solution: https://www.youtube.com/watch?v=umhrBhdLkaY

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int idx1 = -1;
        for (int i = nums.size()-2; i >= 0; i--) {
            if (nums[i] < nums[i+1]) {
                idx1 = i;
                break;
            }
        }

        if (idx1 == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        int idx2 = -1;
        for (int i = nums.size()-1; i >= 0; i--) {
            if (nums[i] > nums[idx1]) {
                swap(nums[i], nums[idx1]);
                break;
            }
        }

        reverse(nums.begin()+idx1+1, nums.end());
    }
};
