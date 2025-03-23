//94中序遍历
//非递归调用
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
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        stack<TreeNode*> s;
        while(root!=nullptr||!s.empty()){
            if(root!=nullptr){
                s.push(root);
                root=root->left;
            }
            else if(!s.empty()){
                root=s.top();
                s.pop();
                result.push_back(root->val);
                root=root->right;
            }
        }
        return result;
    }
};