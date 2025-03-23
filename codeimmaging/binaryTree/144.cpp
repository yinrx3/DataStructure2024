//144前序遍历
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
    void traversal(TreeNode* cur,vector<int> &vec){
        if(cur==nullptr) return;//注意递归的结束位置
        vec.push_back(cur->val);
        traversal(cur->left,vec);
        traversal(cur->right,vec);
        //这里因为是前序遍历，先遍历左子树，再遍历根节点，再遍历右子树
        //根左右
    }
    vector<int> preorderTraversal(TreeNode* root){
        vector<int> result;
        traversal(root,result);
        return result;
    }
};