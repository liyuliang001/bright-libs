#ifndef _BRIGHT_LIB__BST__BST_HPP
#define _BRIGHT_LIB__BST__BST_HPP

#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

namespace bright_lib{

template <class T>
class BstNode{
public:
	T data;
	BstNode *parent, *son[2];
	int64_t count;
	uint32_t rd;

	BstNode() : parent(NULL), count(0) { son[0] = son[1] = NULL; rd = ::rand();}
	BstNode(const T &_data) : data(_data), parent(NULL), count(1) { son[0] = son[1] = NULL; rd = ::rand();}
};

template <class T> 
class Bst{
public:
	BstNode<T> *root, *none;
	
	Bst(){
		none = new BstNode<T>();
		none->son[0] = none->son[1] = none;
		root = none;
	}
	Bst(const Bst &bst); // disable copy constructor
	~Bst(){
		clear(root);
		delete none;
	}

	BstNode<T>* new_node(const T &data){
		BstNode<T>* res = new BstNode<T>(data);
		res->son[0] = res->son[1] = none;
		return res;
	}

	// update metadata of node p (e.g., count)
	void update(BstNode<T> *p){
		p->count = p->son[0]->count + p->son[1]->count + 1;
	}
	// bring son[dir] up
	BstNode<T>* rotate(BstNode<T> *p, int dir){
		BstNode<T>* q = p->son[dir];
		p->son[dir] = q->son[dir^1];
		q->son[dir^1] = p;
		update(p);
		update(q);
		return q;
	}
	BstNode<T>* insert(BstNode<T> *p, const T &data){
		if (p == none)
			return new_node(data);
		int dir = data >= p->data; // 0: left, 1: right
		p->son[dir] = insert(p->son[dir], data);
		if (p->son[dir]->rd < p->rd)
			return rotate(p, dir);
		update(p);
		return p;
	}
	void insert(const T &data){
		root = insert(root, data);
	}

	BstNode<T>* remove(BstNode<T> *p){
		if (p->son[0] == none && p->son[1] == none){
			delete p;
			return none;
		}
		int dir = (p->son[0] == none) || ((p->son[1] != none) && (p->son[0]->rd > p->son[1]->rd));
		p = rotate(p, dir);
		p->son[dir^1] = remove(p->son[dir^1]);
		update(p);
		return p;
	}
	BstNode<T>* remove(BstNode<T> *p, const T &data){
		if (p == none)
			return p;
		if (p->data == data)
			return remove(p);
		int dir = (p->data < data);
		p->son[dir] = remove(p->son[dir], data);
		update(p);
		return p;
	}
	void remove(const T &data){
		root = remove(root, data);
	}

	void clear(BstNode<T> *p){
		if (p == none)
			return;
		clear(p->son[0]);
		clear(p->son[1]);
		delete p;
	}
	void clear(){
		clear(root);
		root = none;
	}

	// get the i-th node, i should be in [0, n-1]
	// think in this way: there should be i nodes less than the returned one
	BstNode<T>* get_i_th_node(BstNode<T> *p, int64_t i){
		if (p == none)
			return none;
		int64_t l_cnt = p->son[0]->count;
		if (l_cnt == i)
			return p;
		if (l_cnt > i)
			return get_i_th_node(p->son[0], i);
		return get_i_th_node(p->son[1], i - l_cnt - 1);
	}
	BstNode<T>* get_i_th_node(int64_t i){
		return get_i_th_node(root, i);
	}
	T get_i_th_data(int64_t i){
		return get_i_th_node(i)->data;
	}

	int64_t count(){
		return root->count;
	}
	// return the number of data < x in p
	int64_t count_smaller(BstNode<T> *p, const T &x){
		if (p == none)
			return 0;
		if (p->data >= x)
			return count_smaller(p->son[0], x);
		return p->son[0]->count + 1 + count_smaller(p->son[1], x);
	}
	// return the number of data < x
	int64_t count_smaller(const T &x){
		return count_smaller(root, x);
	}
	// return the number of data > x in p
	int64_t count_greater(BstNode<T> *p, const T &x){
		if (p == none)
			return 0;
		if (p->data <= x)
			return count_greater(p->son[1], x);
		return p->son[1]->count + 1 + count_greater(p->son[0], x);
	}
	// return the number of data > x
	int64_t count_greater(const T &x){
		return count_greater(root, x);
	}
	int64_t count_no_smaller(const T &x){
		return root->count - count_smaller(x);
	}
	int64_t count_no_greater(const T &x){
		return root->count - count_greater(x);
	}

	bool check(BstNode<T> *p){
		if (p == none)
			return true;
		if (!check(p->son[0]) || !check(p->son[1]))
			return false;
		if (p->son[0] != none && (p->data < p->son[0]->data || p->rd > p->son[0]->rd))
			return false;
		if (p->son[1] != none && (p->data > p->son[1]->data || p->rd > p->son[1]->rd))
			return false;
		if (p->count != p->son[0]->count + p->son[1]->count + 1)
			return false;
		return true;
	}
	bool check(){
		return check(root);
	}

	void traverse(BstNode<T> *p, void (*func)(const T &data)){
		if (p == none)
			return;
		traverse(p->son[0], func);
		func(p->data);
		traverse(p->son[1], func);
	}
	void traverse(void (*func)(const T &data)){
		traverse(root, func);
	}
};

} /* bright_lib */

#endif /* _BRIGHT_LIB__BST__BST_HPP */
