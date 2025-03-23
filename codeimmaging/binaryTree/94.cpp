//94中序遍历
#include <iostream>
#include <vector>
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
    void traversal(TreeNode* cur,vector<int>& vec){
        if(cur==nullptr) return;
        traversal(cur->left,vec);
        vec.push_back(cur->val);
        traversal(cur->right,vec);//左根右
    }
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        traversal(root,result);
        return result;
    }
};