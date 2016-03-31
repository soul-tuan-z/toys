#include <vector>
#include <functional>

using namespace std;

/*
 *   Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
 *   
 *   For example,
 *   Given the following matrix:
 *   [ [1,2,3],
 *     [4,5,6],
 *     [7,8,9] ]
 *   return [1,2,3,6,9,8,7,4,5]
 *
 */

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        if (matrix.size() == 0) {
            return ret;
        }
        vector<function<bool(int&, int&)>> func;
        int left = -1, right = matrix[0].size(), up = -1, down = matrix.size();
        func.push_back(bind(&Solution::goRight, this, ref(ret), ref(matrix), ref(right), ref(up), placeholders::_1, placeholders::_2));
        func.push_back(bind(&Solution::goDown, this, ref(ret), ref(matrix), ref(down), ref(right), placeholders::_1, placeholders::_2));
        func.push_back(bind(&Solution::goLeft, this, ref(ret), ref(matrix), ref(left), ref(down), placeholders::_1, placeholders::_2));
        func.push_back(bind(&Solution::goUp, this, ref(ret), ref(matrix), ref(up), ref(left), placeholders::_1, placeholders::_2));
        int nextStatus[4] = {1, 2, 3, 0};
        int status = 0;
        int row = 0, col = -1;
        while (ret.size() != matrix.size() * matrix[0].size()) {
            if (!func[status](row, col)) {
                status = nextStatus[status];
            }
        }
        return ret;
    }

    bool goLeft(vector<int>& ret, vector<vector<int>>& matrix, int& left, int& down, int& row, int& col) {
        if (col - 1 >left) {
            col -= 1;
            if (col - 1 == left) {
                --down;
            }
            ret.push_back(matrix[row][col]);
            return true;
        }
        return false;
    }
    bool goRight(vector<int>& ret, vector<vector<int>>& matrix, int& right, int& up, int& row, int& col) {
        if (col + 1 < right) {
            col += 1;
            if (col + 1 == right) {
                ++up;
            }
            ret.push_back(matrix[row][col]);
            return true;
        }
        return false;
    }
    bool goUp(vector<int>& ret, vector<vector<int>>& matrix, int &up, int &left, int& row, int& col) {
        if (row - 1 > up) {
            row -= 1;
            if (row - 1 == up) {
                ++left;
            }
            ret.push_back(matrix[row][col]);
            return true;
        }
        return false;
    }
    bool goDown(vector<int>& ret, vector<vector<int>>& matrix, int &down, int &right, int& row, int& col) {
        if (row + 1 < down) {
            row += 1;
            if (row + 1 == down) {
                --right;
            }
            ret.push_back(matrix[row][col]);
            return true;
        }
        return false;
    }
};
