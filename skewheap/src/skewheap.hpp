#ifndef SKEWHEAP_HPP
#define SKEWHEAP_HPP
#include <vector>
#include <utility>
#include <string>

namespace bright_lib{

template <class T>
class SkewHeapNode{
public:
	T data;
	SkewHeapNode *parent, *son[2];

	SkewHeapNode() : parent(NULL) {son[0] = son[1] = NULL;}
	SkewHeapNode(T &a) : data(a), parent(NULL) {son[0] = son[1] = NULL;}
};

template <class T> 
class SkewHeap{
public:
	SkewHeapNode<T> *root;
	size_t n;

	SkewHeap(): n(0) { root = new SkewHeapNode<T>();}

	SkewHeapNode<T>* merge(SkewHeapNode<T> *a, SkewHeapNode<T> *b){
		if (a == NULL) return b;
		if (b == NULL) return a;
		if (b->data < a->data){
			SkewHeapNode<T> *tmp = a; a = b; b = tmp;
		}
		SkewHeapNode<T> *tmp = merge(a->son[1], b);
		tmp->parent = a;
		a->son[1] = a->son[0];
		a->son[0] = tmp;
		return a;
	}
	SkewHeapNode<T> *insert(T &a){
		SkewHeapNode<T> *node = new SkewHeapNode<T>(a);
		n++;
		root->son[0] = merge(root->son[0], node);
		root->son[0]->parent = root;
		return node;
	}
	void remove(SkewHeapNode<T> *node){
		SkewHeapNode<T> *parent = node->parent;
		int idx = (parent->son[1] == node); // which son of the parent is this node 
		parent->son[idx] = merge(node->son[0], node->son[1]);
		if (parent->son[idx] != NULL)
			parent->son[idx]->parent = parent;
		delete node;
		n--;
	}
	bool has(SkewHeapNode<T> *node){
		while (node->parent != NULL)
			node = node->parent;
		return node == root;
	}
	T pop(){
		SkewHeapNode<T> *node = root->son[0];
		T res = node->data;
		root->son[0] = merge(node->son[0], node->son[1]);
		if (root->son[0] != NULL)
			root->son[0]->parent = root;
		delete node;
		n--;
		return res;
	}
	T head(){
		return root->data;
	}
	size_t size(){
		return n;
	}
	bool empty(){
		return n == 0;
	}

	void destruct(SkewHeapNode<T> *node){
		if (node == NULL)
			return;
		destruct(node->son[0]);
		destruct(node->son[1]);
		delete node;
		n--;
	}
	~SkewHeap(){
		destruct(root);
	}

	// for debug
	void check(SkewHeapNode<T> *node){
		if (node == NULL)
			return;
		for (int i = 0; i < 2; i++){
			if (node->son[i] != NULL)
				if (node->son[0]->parent != node)
					printf("error: %d's son[%d]\n", node->data, i);
			check(node->son[i]);
		}
	}
	void check(){
		check(root->son[0]);
	}
	std::pair<std::vector<std::string>, int> to_readable(SkewHeapNode<T> *node){
		std::pair<std::vector<std::string>, int> res;
		if (node == NULL)
			return res;
		auto left = to_readable(node->son[0]), right = to_readable(node->son[1]);
		std::string left_blank, mid_blank, right_blank;
		std::string now;
		if (left.first.size() > 0){
			for (int i = 0; i < left.first[0].size(); i++)
				left_blank += ' ';
		}
		if (right.first.size() > 0){
			for (int i = 0; i < right.first[0].size(); i++)
				right_blank += ' ';
		}
		now = std::to_string(node->data);
		for (int i = 0; i < now.size(); i++)
			mid_blank += ' ';
		now = left_blank + now + right_blank;
		for (int i = left.second; i < left_blank.size(); i++)
			now[i] = (i == left.second) ? '|' : '-';
		for (int i = left_blank.size() + mid_blank.size(); i <= (int)left_blank.size() + (int)mid_blank.size() + right.second; i++)
			now[i] = (i == left_blank.size() + mid_blank.size() + right.second) ? '|' : '-';
		res.second = left_blank.size() + mid_blank.size() / 2;
		res.first.push_back(now);
		for (int i = 0; i < left.first.size() || i < right.first.size(); i++){
			if (i < left.first.size())
				now = left.first[i];
			else 
				now = left_blank;
			now += mid_blank;
			if (i < right.first.size())
				now += right.first[i];
			else
				now += right_blank;
			res.first.push_back(now);
		}
		return res;
	}
	std::string to_readable(){
		auto r = to_readable(root->son[0]);
		std::string res;
		for (int i = 0; i < (int)r.first.size(); i++)
			res += r.first[i] + '\n';
		return res;
	}
};

} /* namespace bright_lib */

#endif /* SKEWHEAP_HPP */
