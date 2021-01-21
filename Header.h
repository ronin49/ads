#pragma once
#include <vector>
using namespace std;
template<class LOL>
class Cluster {
public:
	const Cluster* father, * lchild, * rchild;
	vector<LOL> points;
	Cluster(int i) {
		lchild = rchild = father = 0;
		points.push_back(i);
	}
	Cluster(const Cluster& l, const Cluster& r) {
		lchild = new Cluster(l);
		rchild = new Cluster(r);
		father = 0;
		for (int i : l.points)
			points.push_back(i);
		for (int i : r.points)
			points.push_back(i);
	}
};
template<class LOL>
LOL f(Cluster<LOL> a, Cluster<LOL> b, vector<vector<LOL>> d) {
	LOL min = d[a.points[0]][b.points[0]];
	for(int i = 0; i < a.points.size(); i++)
		for (int j = 1; j < b.points.size(); j++) {
			LOL tmp = d[a.points[i]][b.points[j]];
			if (tmp < min) min = tmp;
		}
	return min;
}


template<class LOL>
void join(vector<Cluster<LOL>>& clusters, vector<vector<LOL>>& d) {
	int i = 0, j = 1;
	LOL min = f(clusters[0], clusters[1],d);
	for(int k = 0; k < clusters.size(); k++)
		for (int z = k + 1; z < clusters.size(); z++) {
			LOL l = f(clusters[k], clusters[z],d);
			if (l < min) {
				min = l;
				i = k;
				j = z;
			}
		}
	Cluster<LOL> father(clusters[i], clusters[j]);
	clusters.erase(clusters.begin() + j);
	clusters.erase(clusters.begin() + i);
	clusters.insert(clusters.begin() + i, father);
}
template<class LOL>
Cluster<LOL> tree(vector<vector<LOL>> d) {
	vector<Cluster<LOL>> clusters;
	for (int i = 0; i < d.size(); i++) {
		clusters.push_back(Cluster<LOL>(i));
	}
	while (clusters.size() > 1)
		join(clusters,d);
	return clusters[0];
}

template<class LOL>
void printTree(const Cluster<LOL> & leaf, int level = 0) {
	for (int i = 0; i < level; i++)
		cout << '\t';
	cout << '{' << leaf.points[0];
	for (int i = 1; i < leaf.points.size(); i++)
		cout << ',' << leaf.points[i];
	cout << '}' << endl;
	if(leaf.lchild)
		printTree(*leaf.lchild, level + 1);
	if (leaf.rchild)
		printTree(*leaf.rchild, level + 1);
}