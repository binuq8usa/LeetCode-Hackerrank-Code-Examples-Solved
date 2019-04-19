#include <vector>
#include <stack>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
};
*/


// recursion
vector<int> preorderTraversalR(TreeNode* root){
	vector<int> result;
	if(root != NULL){
		result.push_back(root->val);
		vector<int> r_l = preorderTraversal(root->left);
		vector<int> r_r = preorderTraversal(root->right);
		for(auto &item : r_l)
			result.push_back(item);
		for(auto &item : r_r)
			result.push_back(item);
	}
	return result;
}


// iterative
vector<int> preorderTraversalI(TreeNode* root){
	vector<int> result;
	stack<TreeNode*> st;
	if(root == NULL)
		return result;
	else
		st.push(root);

	while(!st.empty()){
		TreeNode* curr_node = st.top();
		st.pop();
		result.push_back(curr_node->val);
		if(curr_node->right != NULL) st.push(curr_node->right);
		if(curr_node->left != NULL) st.push(curr_node->left);
	}
	return result;
}
