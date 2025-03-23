//N叉树的层序遍历
//广度优先搜索
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> que;
        vector<vector<int>> result;
        if(root==nullptr){return result;}
        if(root!=nullptr){que.push(root);}
        while(!que.empty()){
            vector<int> vec;
            int size=que.size();
            for(int i=0;i<size;++i){
                Node* cur=que.front();
                vec.push_back(cur->val);
                que.pop();
                for(int j=0;j<cur->children.size();++j){
                    if(cur->children[j]!=nullptr)
                        que.push(cur->children[j]);
                }
            }
            result.push_back(vec);
        }
        return result;
    }
};