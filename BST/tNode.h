#pragma once
#include<iostream>
#include<string>

using namespace std;
class tNode
{
public:
	int val;
	string str;
	tNode* left;
	tNode* right;
	tNode(int d) {
		val = d;
		left = nullptr;
		right = nullptr;
	}
};