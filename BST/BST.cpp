#include "BST.h"
#include<queue>
#include<stack>
#include<vector>
#include<map>

bool isLeaf(tNode* node)
{
	if (!node->left && !node->right) { return true; }

	return false;
}

BST::BST()
{
}


BST::~BST()
{
}

tNode* BST::insert(tNode* root, int data)
{
	if (!root) {
		return new tNode(data);
	}
	else {
		tNode* cur;
		if (data <= root->val) {
			cur = insert(root->left, data);
			root->left = cur;
		}
		else {
			cur = insert(root->right, data);
			root->right = cur;
		}
		return root;
	}
}

int BST::depth(tNode* root)
{
	if (!root) { return 0; }
	int left = depth(root->left) + 1;
	int right = depth(root->right) + 1;
	return (left > right) ? left : right;
}

int BST::countNodes(tNode* root)
{
	if (!root) { return 0; }
	return countNodes(root->left) + countNodes(root->right) + 1;
}


int BST::secondLargest(tNode* root)
{
	if (!root) { return 0; }
	if (isLeaf(root->right)) { return root->val; }
	else { return secondLargest(root->right); }
}


bool verify(tNode* root, tNode* max, tNode* min) //Helper Function
{
	if (!root) { return true; }
	else if (max && !(root->val <= max->val) || min && !(root->val >= min->val)) { return false; }
	else { return verify(root->left, root, nullptr) && verify(root->right, nullptr, root); }
}
bool BST::verifyBST(tNode* root)
{
	return verify(root, nullptr, nullptr);
}

void BST::inorder(tNode* root)
{
	if (!root) { return; }
	inorder(root->left);
	std::cout << root->val << std::endl;
	inorder(root->right);
}

void BST::preorder(tNode* root)
{
	if (!root) { return; }

	std::cout << root->val << std::endl;
	preorder(root->left);
	preorder(root->right);
}

void BST::postorder(tNode* root)
{
	if (!root) { return; }

	postorder(root->left);
	postorder(root->right);
	std::cout << root->val << std::endl;
}

void BST::levelOrderTrav(tNode* root)
{
	std::queue<tNode*> node;

	node.push(root);

	while (!node.empty())
	{
		tNode* current = node.front();
		std::cout << current->val << " ";

		if (current->left) { node.push(current->left); }
		if (current->right) { node.push(current->right); std::cout << std::endl; }

		node.pop();
	}

}

bool checker(tNode* node, tNode* node1)//For symmetric function
{
	if (!node && !node1) { return true; }
	else if (!node || !node1) { return false; }

	if (node->val != node1->val) { return false; }

	return checker(node->left, node1->right) && checker(node->right, node1->left);
}
bool BST::isSymmetric(tNode* root)
{
	if (!root) { return true; }

	return checker(root->left, root->right);
}

int search(char arr[], int strt, int end, char value)
{
	int i;
	for (i = strt; i <= end; i++)
	{
		if (arr[i] == value)
			return i;
	}
}

tNode* BST::reconstructTree(char in[], char pre[], int inStrt, int inEnd)
{
	static int preIndex = 0;

	if (inStrt > inEnd)
		return NULL;

	/* Pick current node from Preorder
	traversal using preIndex
	and increment preIndex */
	tNode* Node = new tNode(pre[preIndex++]);

	/* If this node has no children then return */
	if (inStrt == inEnd)
		return Node;

	/* Else find the index of this node in Inorder traversal */
	int inIndex = search(in, inStrt, inEnd, Node->val);

	/* Using index in Inorder traversal, construct left and
	right subtress */
	Node->left = reconstructTree(in, pre, inStrt, inIndex - 1);
	Node->right = reconstructTree(in, pre, inIndex + 1, inEnd);

	return Node;
}

int BST::countLeaves(tNode* root)
{
	if (!root) { return 0; }
	if (!root->left && !root->right) { return 1; }
	return countLeaves(root->left) + countLeaves(root->right);
}

int BST::DeepestNode(tNode* root)
{
	std::queue<tNode*>node;
	int last_node = 0;
	node.push(root);

	while (!node.empty())
	{
		tNode* current = node.front();
		last_node = current->val;
		//std::cout << current->val << " ";

		if (current->left) { node.push(current->left); }
		if (current->right) { node.push(current->right); std::cout << std::endl; }

		node.pop();
	}
	return last_node;
}

tNode* BST::invertTree(tNode* root)
{
	if (!root) { return nullptr; }

	tNode* right = invertTree(root->right);
	tNode* left = invertTree(root->left);
	root->left = right;
	root->right = left;

	return root;
}
int largestBSThelper(tNode* node, int* min_ref, int* max_ref, int* max_size_ref, bool* is_bst_ref)
{
	if (node == NULL)
	{
		*is_bst_ref = 1; // An empty tree is BST  
		return 0; // Size of the BST is 0  
	}

	int min = INT_MAX;

	bool left_flag = false;

	bool right_flag = false;

	int ls, rs;

	*max_ref = INT_MIN;
	ls = largestBSThelper(node->left, min_ref, max_ref,
		max_size_ref, is_bst_ref);
	if (*is_bst_ref == 1 && node->val > * max_ref)
		left_flag = true;

	min = *min_ref;

	*min_ref = INT_MAX;
	rs = largestBSThelper(node->right, min_ref,
		max_ref, max_size_ref, is_bst_ref);
	if (*is_bst_ref == 1 && node->val < *min_ref)
		right_flag = true;


	if (min < *min_ref)
		*min_ref = min;
	if (node->val < *min_ref)
		*min_ref = node->val;
	if (node->val > * max_ref)
		*max_ref = node->val;


	if (left_flag && right_flag)
	{
		if (ls + rs + 1 > * max_size_ref)
			*max_size_ref = ls + rs + 1;
		return ls + rs + 1;
	}
	else
	{

		*is_bst_ref = 0;
		return 0;
	}
}
int BST::largestBST(tNode* root)
{
	int min = INT_MAX;
	int max = INT_MIN;
	int max_size = 0;
	bool flag = 0;

	largestBSThelper(root, &min, &max, &max_size, &flag);

	return max_size;
}
int max(int a, int b)
{
	return (a >= b) ? a : b;
}
int maxPathHelp(tNode* root, int& res)
{
	// Base cases 
	if (root == NULL) return 0;
	if (!root->left && !root->right) return root->val;

	// Find maximum sum in left and right subtree. Also 
	// find maximum root to leaf sums in left and right 
	// subtrees and store them in ls and rs 
	int ls = maxPathHelp(root->left, res);
	int rs = maxPathHelp(root->right, res);


	// If both left and right children exist 
	if (root->left && root->right)
	{
		// Update result if needed 
		res = max(res, ls + rs + root->val);

		// Return maxium possible value for root being 
		// on one side 
		return max(ls, rs) + root->val;
	}

	// If any of the two children is empty, return 
	// root sum for root being on one side 
	return (!root->left) ? rs + root->val :
		ls + root->val;
}
int BST::maxSumPath(tNode* root)
{
	int res = INT_MIN;
	maxPathHelp(root, res);
	return res;
}


/* 2
  / \
 1   4
	/ \
   3   5
*/
void pathBuilder(vector<string>& res, tNode* root, string pre)
{
	if (!root) { return; }
	if (!root->left && !root->right)
	{
		res.push_back(pre + to_string(root->val)); return;
	}
	pathBuilder(res, root->left, pre + to_string(root->val) + "->");
	pathBuilder(res, root->right, pre + to_string(root->val) + "->");
}
void BST::printPath(tNode* root)
{
	vector<string>paths;
	pathBuilder(paths, root, "");
	for (auto path : paths) { cout << path << endl; }
}


tNode* BST::LCA(tNode* root, int A, int B)
{
	if (!root) { return nullptr; }


	if (root->val == A || root->val == B) { return root; }


	tNode* left_lca = LCA(root->left, A, B);
	tNode* right_lca = LCA(root->right, A, B);


	if (left_lca && right_lca) { return root; }

	return (left_lca != NULL) ? left_lca : right_lca;
}


int BST::evaluate(tNode* root)
{
	if (root->str == "+") { return evaluate(root->left) + evaluate(root->right); }
	else if (root->str == "-") { return evaluate(root->left) - evaluate(root->right); }
	else if (root->str == "*") { return evaluate(root->left) * evaluate(root->right); }
	else if (root->str == "/") { return evaluate(root->left) / evaluate(root->right); }
	return root->val;
}
bool areIdentical(tNode* root1, tNode* root2)
{
	if (!root1 && !root2) { return true; }
	if (!root1 || !root2) { return false; }

	return (root1->val == root2->val && areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right));
}
bool BST::isSubTree(tNode* root, tNode* rootA)
{
	if (!root) { return false; }
	if (!rootA) { return false; }

	if (areIdentical(root, rootA)) { return true; }


	return isSubTree(root->left, rootA) || isSubTree(root->right, rootA);
}

int BST::minSum(tNode* root)
{
	queue<tNode*>nodes;
	nodes.push(root);
	int res = root->val;

	while (!nodes.empty())
	{
		int sum = 0;
		int count = nodes.size();

		while (count--)
		{
			tNode* temp = nodes.front();
			nodes.pop();

			sum += temp->val;
			if (temp->left) { nodes.push(temp->left); }
			if (temp->right) { nodes.push(temp->right); }


		}
		res = max(sum, res);
	}

	return res;
}


/*
	10
   /   \
 5      15
	   /  \
	 11    15

*/
void BST::twoSum(tNode* root, int target, map<int, int>& store)
{
	if (!root) { return; }

	int x = target - root->val;
	if (store.find(x) != store.end())
	{
		cout << "Sum pairs are: " << x << store.find(root->val)->first << endl;
		return;
	}
	else { store.insert(pair<int, int>(root->val, 0)); }

	twoSum(root->left, target, store);
	twoSum(root->right, target, store);
}
tNode* minValue(tNode* nd) {
	struct tNode* current = nd;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}
tNode* BST::inorderSuccessor(tNode* root, tNode* n)
{
	// step 1 of the above algorithm 
	if (n->right != NULL)
		return minValue(n->right);

	tNode* succ = NULL;

	// Start from root and search for successor down the tree 
	while (root != NULL)
	{
		if (n->val < root->val)
		{
			succ = root;
			root = root->left;
		}
		else if (n->val > root->val)
			root = root->right;
		else
			break;
	}

	return succ;
}
/*This question was asked by Apple.

Given a binary tree, find a minimum path sum from root to a leaf.

For example, the minimum path in this tree is [10, 5, 1, -1], which has sum 15.

  10
 /  \
5    5
 \     \
   2    1
	   /
	 -1
*/
int BST::findMinPath(tNode* root)//This wont solve a BST just a regular tree
{
	if (!root) { return 0; }

	int sum = root->val;
	int left = INT_MAX;
	int right = INT_MAX;

	if (root->right == nullptr && root->left == nullptr) { return sum; }
	else
	{
		if (root->left) { left = findMinPath(root->left); }
		if (root->right) { right = findMinPath(root->right); }

		if (left < right) {
			sum += left;
		}
		else {
			sum += right;
		}
	}

	return sum;
}

bool BST::isBalanced(tNode* root)
{
	return false;
}