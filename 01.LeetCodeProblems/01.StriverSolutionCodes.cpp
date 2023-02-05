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

// 8. Merge Intervals

class Solution {
    static bool compare(vector<int>a, vector<int> b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] < b[0];
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;

        sort(intervals.begin(), intervals.end(), compare);

        int currStart = intervals[0][0];
        int currStop = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {
            if (currStop < intervals[i][0]) {
                ans.push_back({currStart, currStop});

                currStart = intervals[i][0];
                currStop = intervals[i][1];
            }
            else if (currStop < intervals[i][1]) {
                currStop = intervals[i][1];
            }
        }
        ans.push_back({currStart, currStop});

        return ans;
    }
};
