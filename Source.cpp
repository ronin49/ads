#include <iostream>
#include "Header.h"

int main() {
	vector<vector<int>> d = {
		{0,1,0},
		{1,0,4},
		{0,4,0}
	};
	Cluster<int> root = tree(d);
	printTree(root);
	return 0;
}