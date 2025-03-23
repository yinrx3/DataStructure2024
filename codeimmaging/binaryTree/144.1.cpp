//144前序遍历
//非递归，使用栈的方法
//144前序遍历
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
        //这里要保证出栈的顺序是  中 左 右
        //先将根节点入栈，然后将右孩子入栈，最后左孩子入栈
        stack<TreeNode*> st;
        vector<int> result;
        if(root==nullptr){return result;}
        st.push(root);
        while(!st.empty()){
            TreeNode* node=st.top();
            st.pop();
            result.push_back(node->val);
            if(node->right){st.push(node->right);}
            if(node->left){st.push(node->left);}//这里必须先放置右孩子
        }
        return result;
    }
};