#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*
template <typename T>
using priority_queue = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

int n,q,x,val;
vector<long long> arr;


struct segment_tree {
	segment_tree *left, *right;
	int from, to, value;
	segment_tree(int from, int to)
	: from(from), to(to), left(NULL), right(NULL), value(0) { }
};

segment_tree* build(const vector<long long> &arr, int l, int r) {
	if (l > r) return NULL;
	segment_tree *res = new segment_tree(l, r);
	if (l == r) {
	res->value = arr[l];
	} else {
	int m = (l + r) / 2;
	res->left = build(arr, l, m);
	res->right = build(arr, m + 1, r);
	if (res->left != NULL) res->value += res->left->value;
	if (res->right != NULL) res->value += res->right->value;
	}
	return res;
}

long long query(segment_tree *tree, int l, int r) {
	if (tree == NULL) return 0;
	if (l <= tree->from && tree->to <= r) return tree->value;
	if (tree->to < l) return 0;
	if (r < tree->from) return 0;
	return query(tree->left, l, r) + query(tree->right, l, r);
}

long long  update(segment_tree *tree, int i, int val) {
	if (tree == NULL) return 0;
	if (tree->to < i) return tree->value;
	if (i < tree->from) return tree->value;
	if (tree->from == tree->to && tree->from == i) {
	tree->value = val;
	} else {
	tree->value = update(tree->left, i, val) + update(tree->right, i, val);
	}
	return tree->value;
}

int main(){

	cin >> n >> q;
	ordered_set<int>  s;
	priority_queue<int> p;
	arr.resize(n);
	struct segment_tree *st = build(arr, 0, n-1);
	int cnt = 0;
	
	while(q--){
		cin >> x >> val;	
		arr[x-1]+= val;
		s.insert(-arr[x-1]);
		p.priority_queue(arr[x-1]);
		
		cout << p.order_of_key(arr[x-1]) << " " << s.order_of_key(-arr[x-1]) << "\n";
		
	}
	
	return 0;
}