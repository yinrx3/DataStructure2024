//103对称二叉树
#include <iostream>
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
    bool isSymmetric(TreeNode* root){
        queue<TreeNode*> que;
        if(root=nullptr){return true;}
        if(root!=nullptr){que.push(root);}
        while(!que.empty()){
            int size=que.size();
            vector<int> vec;
            for(int i=0;i<size;++i){
                TreeNode* tempN=que.front();
                que.pop();
                vec.push_back(tempN->val);
                if(tempN->left!=nullptr)
                    que.push(tempN->left);
                else{
                    TreeNode* extra1=new TreeNode(1000);
                    que.push(extra1);
                }
                if(tempN->right!=nullptr)
                    que.push(tempN->right);
                else{
                    TreeNode* extra2=new TreeNode(1000);
                    que.push(extra2);
                }
            }
            int vecsize=vec.size();
            if(vecsize%2==1){return false;}
            for(int j=0;j<vecsize/2;++j){
                if(vec[j]!=vec[vecsize-j-1]){return false;}
            }
        }
        return true;
    }
};