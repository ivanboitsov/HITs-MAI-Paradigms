#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
	string value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(string value) : value(value), left(nullptr), right(nullptr) {}
};
vector<string> pushingBack(vector<string> inputResult, string element) {
	vector<string> cloneResult = inputResult;
	cloneResult.push_back(element);
	return cloneResult;
}
vector<string> input(vector<string> result = vector<string>()) {
	vector<string> localResult = result;
	string a;
	return (cin >> a) ? input(pushingBack(localResult, a)) : localResult;
}
queue<TreeNode*> queueCopy(queue<TreeNode*>& queueArgument) {
	queue<TreeNode*> newQueue(queueArgument);
	return newQueue;
}
TreeNode* addRoot(TreeNode* tree, TreeNode* root) {
	TreeNode* local_root = tree;
	(local_root->left == nullptr) ? local_root->left = root : local_root->right = root;
	return local_root;
}
TreeNode* sortedListToBST(const vector<string>& nums, int left, int right) {
	return (left > right) ? new TreeNode("null") : (left != right) ? addRoot(addRoot(new TreeNode(nums[(right + left + ((right + left) % 2)) / 2]), sortedListToBST(nums, left, (right + left + ((right + left) % 2)) / 2 - 1)), sortedListToBST(nums, (right + left + ((right + left) % 2)) / 2 + 1, right)) : new TreeNode(nums[(right + left + ((right + left) % 2)) / 2]);
}
TreeNode* sortedListToBST(const vector<string>& nums) {
	return sortedListToBST(nums, 0, nums.size() - 1);
}
void levelOrderPrintHelper(queue<TreeNode*>& queueArgument) {
	if (queueArgument.empty()) return;
	const TreeNode* temp = queueArgument.front();
	cout << temp->value << " ";
	queue<TreeNode*> newQueue = queueCopy(queueArgument);
	newQueue.pop();
	(temp->left != NULL) ? newQueue.push(temp->left), (temp->right != NULL) ? newQueue.push(temp->right) : void() : (temp->right != NULL) ? newQueue.push(temp->right) : void();
	levelOrderPrintHelper(newQueue);

}
void levelOrderPrint(TreeNode* root) {
	if (root == NULL) return;
	queue<TreeNode*> queue;
	queue.push(root);
	levelOrderPrintHelper(queue);
}
int main() {
	vector<string> nums = input();
	TreeNode* root = sortedListToBST(nums);
	levelOrderPrint(root);
	return 0;
}