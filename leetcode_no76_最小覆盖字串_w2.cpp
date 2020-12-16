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

/*	单map法
    用哈希表完成，由于匹配数组t可能存在重复值，所以map数值需要是int。
    总体算法模拟音乐音量上下浮动，t 的元素个数就是音量高度，t 以外的其他元素都为 0，
    遍历 s 的过程中，遇到一个音则将其减少一个音量.（* t 数组以外的音量不可能大于 0）
    搜索过程中，指定音量下降计数 cnt 增加，减小到 0 以下不算在内，
    当减少总数等于 t 的总数时，所有数就齐了，计算长度。
    随后进行回退，如果是 t 以外的音，其增加不改变计数 cnt，直到遇到 t 中的音，
    且该值在map中大于0时（区间中 t 的某一个音大于其原始的数量，它map的值可能会小于0），
    回退停止，继续向前搜索，重复 步骤 2。

*
*	执行用时：16 ms, 在所有 C++ 提交中击败了87.26%的用户
*	内存消耗：7.9 MB, 在所有 C++ 提交中击败了54.32%的用户
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

string minWindow(string s, string t) {
    unordered_map<char, int> cnt;
    for (const char& c : t) {
        cnt[c]++;
    }

    int left = 0;
    int reslen = INT_MAX;
    int sum = 0;
    int start = 0;
    for (int i = 0; i < s.size(); i++) {
        if (cnt[s[i]]-- >= 1) {
            sum++;
        }
        while (sum == t.size()) {
            if (cnt[s[left]]++ >= 0) {
                //长度更新放到判断里面来，减少每次循环都要判断更新长度
                if (reslen > i - left + 1) {
                    reslen = i - left + 1;
                    start = left;
                }
                sum--;
            }
            left++;
        }
    }
    return reslen == INT_MAX ? string() : s.substr(start, reslen);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string res = minWindow(s, t);
}