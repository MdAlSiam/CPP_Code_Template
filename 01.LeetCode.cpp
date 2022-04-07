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

// First Missing Positive | MEX: Minimum Excluded | LeetCode 41

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size(); 
        // MEX will be 1 to n+1
        // 1, if 1 is missing, n+1, if all number from 1 to n is present
        // Here, as the array size is n, all number from 1 to n will appear only once 
        // So the numbers in the array in range [1, n] will be considered, others will be discarded
        // Make all the out of range [1, n] values 1
        // But before making them 1, think that, 1 might be the MEX, which will loose after adding 1
        // So check if MEX is 1 at the very beginning

        bool isMEXOne = true;
        for (int num : nums) {
            if (num == 1) isMEXOne = false;
        }

        if (isMEXOne) {
            return 1;
        }

        // Now make all the numbers out of [1,n] equal to 1
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 1 and nums[i] <= n) {
                // No need to change
            }
            else {
                nums[i] = 1;
            }
        }

        for (int num : nums) {
            // Make the number at index equal to an existing number negative
            // index-1 will be modified as we have array index 0 to n-1
            if (nums[abs(num)-1] > 0) {
                // Checked if still positive
                // already negative means already exisiting element for this index, hence got negated
                nums[abs(num)-1] *= -1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] >= 1) {
                // At this index, the number did not negated, hence no existing number equal to index
                return i+1;
            }
        }

        return n+1;
    }
};
