#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <bright_lib/skewheap/skewheap.hpp>

using namespace std;
using namespace bright_lib;

int main(){
	srand(time(0));
	vector<SkewHeapNode<int>*> v;
	SkewHeap<int> h;
	for (int i = 0; i < 100; i++){
		int x = rand() % 100;
		auto node = h.insert(x);
		if (x < 60 and x >= 50)
			v.push_back(node);
	}
#if 1
	for (int i = 0; i < (int)v.size(); i++){
		printf("remove %d\n", v[i]->data);
		h.remove(v[i]);
	}
#endif
	while (not h.empty()){
		printf("%d\n", h.pop());
	}
}
