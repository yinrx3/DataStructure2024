//102二叉树的层序遍历
#include <iostream>
#include <vector>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        queue<TreeNode*> que;
        if(root==nullptr)
            return result;
        if(root!=nullptr)
            que.push(root);
        while(!que.empty()){
            int size=que.size();
            //这里必须使用固定值，因为在程序运行过程中，size会不断改变
            vector<int> vec;
            for(int i=0;i<size;++i){
                TreeNode* node=que.front();
                que.pop();
                vec.push_back(node->val);
                if(node->left!=nullptr)
                    que.push(node->left);
                if(node->right!=nullptr)
                    que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }
};