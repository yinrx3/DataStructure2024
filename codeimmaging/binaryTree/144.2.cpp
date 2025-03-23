//144前序遍历
//非递归，使用栈的方法
//144前序遍历
//guanzhenyang做法
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root){
        stack<TreeNode*> s;
        vector<int> result;
        while(root!=nullptr||!s.empty()){
            if(root!=nullptr){
                result.push_back(root->val);
                s.push(root);
                root=root->left;
            }
            else if(!s.empty()){
                TreeNode* temp=s.top();
                root=temp->right;
                s.pop();
            }
        } 
        return result;
    }
};