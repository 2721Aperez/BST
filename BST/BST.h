#pragma once
#include "tNode.h"
using namespace std;

class BST
{
public:
	BST();
	~BST();
	tNode* insert(tNode* root, int data);
	int depth(tNode* root);
	int countNodes(tNode* root);
	int secondLargest(tNode* root);//Problem 36
	bool verifyBST(tNode* root);//p89
	void levelOrderTrav(tNode* root);
	void inorder(tNode* root);
	void preorder(tNode* root);
	void postorder(tNode* root);
	bool isSymmetric(tNode* root);
	tNode* reconstructTree(char in[], char pre[], int inStrt, int inEnd);
	int countLeaves(tNode* root);
	int DeepestNode(tNode* root);
	tNode* invertTree(tNode* root);
	int largestBST(tNode* root);
	int maxSumPath(tNode* root);
	void printPath(tNode* root);
	tNode* LCA(tNode* root, int A, int B);
	int evaluate(tNode* root);
	bool isSubTree(tNode* root, tNode* rootA);
	int minSum(tNode* root);
	void twoSum(tNode* root, int target, map<int, int>& store);
	tNode* inorderSuccessor(tNode* root, tNode* n);
	int findMinPath(tNode* root);
	bool isBalanced(tNode* root);
};

//BFS is level order traversal
//DFS is the normal BST traversal
