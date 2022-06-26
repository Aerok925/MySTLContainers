#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include <vector>
#include <stack>
#include "../incs/BlackRedTree.hpp"
#include "../incs/map.hpp"
#include <map>
#include "../incs/set.hpp"

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template <typename T>
void test(ft::vector<T> vector){
//	for (int i = 0; i < 1; ++i)
//	{
//		vector.push_back(i);
//	}
//	std::cout << vector << std::endl;
//	std::cout << vector[15] << std::endl;
	std::cout<<vector.size()<<std::endl;
	std::cout<<vector.capacity()<<std::endl;

	std::vector<int> v;
//	for (int i = 0; i < 1; ++i)
//	{
//		v.push_back(i);
//	}
//	std::cout << v[0] << std::endl;
//	std::cout << v[15] << std::endl;
	std::cout<<v.size()<<std::endl;
	std::cout<<v.capacity()<<std::endl;
}

template <class T>
void print_vector(ft::vector<T>& vec){
	typename ft::vector<T>::iterator it;
	it = vec.begin();
	for (; it != vec.end(); it++){
		std::cout<<*it<<" ";
	}
	std::cout<<std::endl;
}

template <class T>
void print_vector(std::vector<T>& vec){
	typename std::vector<T>::iterator it;
	it = vec.begin();
	for (; it != vec.end(); it++){
		std::cout<<*it<<" ";
	}
	std::cout<<std::endl;
}

template <class T>
void print_size_capacity(std::vector<T>& vec){

	std::cout<<"size - "<<vec.size()<<std::endl;

	std::cout<<"capacity - "<<vec.capacity()<<std::endl;
}

template <class T>
void print_size_capacity(ft::vector<T>& vec){

	std::cout<<"size - "<<vec.size()<<std::endl;

	std::cout<<"capacity - "<<vec.capacity()<<std::endl;
}

typedef struct t_node{
	t_node *left;
	t_node *right;
	t_node *parent;
	int value;
} node;

node *create_node(const int& value){
	node *tmp = new node;
	tmp->left = nullptr;
	tmp->right = nullptr;
	tmp->parent = nullptr;
	tmp->value = value;
	return tmp;
}

void insert(node &){

}

int qwe(long int value, int del){
	if (value % del == 0 )
		return value / del;
	else
		return value * del;
}

template <class T, class V, class C>
void fillMap(ft::map<T, V, C> &mp) {
	mp.insert(ft::make_pair(16, 3));
	mp.insert(ft::make_pair(8, 3));
	mp.insert(ft::make_pair(23, 3));
	mp.insert(ft::make_pair(7, 3));
	mp.insert(ft::make_pair(19, 3));
	mp.insert(ft::make_pair(29, 3));
	mp.insert(ft::make_pair(41, 3));
	mp.insert(ft::make_pair(4, 3));
	mp.insert(ft::make_pair(11, 3));
}

template <class T, class V, class C>
void fillMap(std::map<T, V, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}


int main() {
	ft::set<int> st;
	std::vector<int> v;

	st.insert(5);
	st.insert(3);
	st.insert(7);
	ft::set<int>::reverse_iterator rit = st.rbegin();
	ft::set<int>::reverse_iterator rit2 = st.rend();
	v.push_back(*rit);
	rit++;
	rit2--;
	v.push_back(*rit);
	v.push_back(*rit2);
	rit++;
	v.push_back(*rit == *rit2);
	v.push_back(rit == rit2);
	rit2--;
	v.push_back(*rit);
	v.push_back(*rit2);
	v.push_back(*rit2 > *rit);
	v.push_back(*rit2 < *rit);
	v.push_back(*(--rit));
	v.push_back(*(++rit2));
	v.push_back(*(rit--));
	v.push_back(*(rit2++));
}