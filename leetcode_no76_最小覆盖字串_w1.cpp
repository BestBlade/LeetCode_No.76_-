/* ------------------------------------------------------------------|
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

 

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
示例 2：

输入：s = "a", t = "a"
输出："a"
 

提示：

1 <= s.length, t.length <= 105
s 和 t 由英文字母组成
 

进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-window-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	滑动窗口法
*
*	执行用时：412 ms, 在所有 C++ 提交中击败了6.45%的用户
*	内存消耗：8 MB, 在所有 C++ 提交中击败了42.74%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool check(unordered_map<char, int> &temp,unordered_map<char,int> &ans) {
    for (const auto& iter : temp) {
        if (ans[iter.first] < iter.second) {
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t) {
    unordered_map<char, int> temp;
    unordered_map<char, int> ans;
    for (const char &c : t) {
        temp[c]++;
    }

    int left = 0;
    int right = 0;
    int resleft = -1;
    int resright = -1;
    int reslen = INT_MAX;

    while (right <= s.size()) {
        if (temp[s[right]]) {
            ans[s[right]]++;
        }
        while (check(temp, ans) && left <= right) {
            if (right - left + 1 < reslen) {
                resleft = left;
                reslen = right - left + 1;
            }
            if (temp[s[left]]) {
                ans[s[left]]--;
            }
            left++;
        }
        right++;
    }

    return resleft == -1 ? string() : s.substr(resleft, reslen);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string res = minWindow(s, t);
}