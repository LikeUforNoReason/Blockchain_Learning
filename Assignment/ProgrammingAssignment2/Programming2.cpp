#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
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

void createTree (TreeNode* root, int n) {
	if (!root) return;
	queue<TreeNode*> *q = new queue<TreeNode*>;
	q->push(root);
	int cnt = 1;
	while (!q->empty()) {
		TreeNode *node = new TreeNode;
		node = q->front(); q->pop();
		if (node -> left == NULL) {
			TreeNode *l = new TreeNode;
			l -> val = (2 * node -> val) + 1;
			node -> left = l;
			q->push(l);
			++cnt;
			if (cnt == n)
				break;
		}
		if (node -> right == NULL) {
			TreeNode *r = new TreeNode;
			r -> val = (2 * node -> val) + 2;
			node -> right = r;
			q->push(r);
			++cnt;
			if (cnt == n)
				break;
		}
	}
}

/*void levelOrder(TreeNode *root) {
	queue<TreeNode*> *Q = new queue<TreeNode*>;
	Q->push(root);
	while (!Q->empty()) {
		TreeNode *p = Q->front(); Q->pop();
		cout << p -> val << " ";
		if (p -> left != NULL)
			Q->push(p -> left);
		if (p -> right != NULL)
			Q->push(p -> right);
	}
 
}*/


int main(int argc, char const *argv[])
{
	//cout << "Please enter the total number of nodes in the checkpoint tree." << endl;
	int n = 2047;
	TreeNode *root = new TreeNode;
	root -> val = 0;
	createTree (root, n);
	//levelOrder(root);
	int arr[] = {500, 100, 300, 250, 150, 500, 600, 350, 200, 150};
	vector<int> lIDs, rIDs;
	int links[11] = {0};
	int k = sizeof(arr)/sizeof(arr[0]);
	srand((unsigned) time(NULL));
	for (int i = 0; i < 10; ++i) {
		int lDeposits = 0, rDeposits = 0;
		cout << "Round " << i + 1 << ": the IDs of the validators who finalized this checkpoint is ";
		for (int j = 0; j < k; ++j) {
			if ((rand()%10) <= 4) {
				lDeposits += arr[j];
				lIDs.push_back(j);
			}else {
				rDeposits += arr[j];
				rIDs.push_back(j);
			}
		}
		if (lDeposits > rDeposits) {
			links[i + 1] = root -> left -> val;
			root = root -> left;
			for (int h = 0; h < lIDs.size(); ++h)
			{
				cout << lIDs[h] << " ";
			}
			lIDs.clear(); rIDs.clear();
			cout << "The total deposits is: " << lDeposits << endl;
		}else {
			links[i + 1] = root -> right -> val;
			root = root -> right;
			for (int g = 0; g < rIDs.size(); ++g)
			{
				cout << rIDs[g] << " ";
			}
			lIDs.clear(); rIDs.clear();
			cout << "The total deposits is: " << rDeposits << endl;
		}
	}
	cout << "The blockchain is ";
	for (int a = 0; a < 11; ++a) {
		cout << links[a] << " -> ";
	}

	return 0;
}

