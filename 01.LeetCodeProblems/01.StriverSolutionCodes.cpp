// Striver's SDE sheet solution codes

// 6. Sort Colors

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size()-1;

        int mid = 0;
        while (lo <= hi) {
            if (nums[mid] == 0) {
                swap(nums[mid], nums[lo]);
                lo++;
                mid++;
            }
            else if (nums[mid] == 1) {
                mid++;
            } 
            else if (nums[mid] == 2) {
                swap(nums[mid], nums[hi]);
                hi--;
            }
        }
    }
};

// 7. Rotate Image

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        int ro = 0;
        int col = 0;

        while (ro < n and col < n) {
            int currRo = ro;
            int currCol = col;

            while (currRo < n and currCol < n) {
                swap(matrix[ro][currCol], matrix[currRo][col]);
                currRo++;
                currCol++;
            }

            ro++;
            col++;
        }

        for (int i = 0; i < matrix.size(); i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

// 
