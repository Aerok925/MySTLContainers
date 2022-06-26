//
// Created by John Nappa on 6/4/22.
//

#ifndef CONTAINERS_NODE_HPP
#define CONTAINERS_NODE_HPP

#include <stack>
#include "memory"

namespace ft{
	template <class Value>
	struct Node{
	public:
		explicit Node(Value *value = 0){
			_value = value;
			_parent = nullptr;
			_left = nullptr;
			_right = nullptr;
			is_black = false;
			is_nil = false;
		}
		Node(const Node& other){
			this->_value = other._value;
			this->_parent = other._parent;
			this->_left = other._left;
			this->_right = other._right;
			this->is_black = other.is_black;
			this->is_nil = other.is_nil;
		};

		Node & operator=(const Node & other){
			this->_value = other._value;
			this->_parent = other._parent;
			this->_left = other._left;
			this->_right = other._right;
			this->is_black = other.is_black;
			this->is_nil = other.is_nil;
			return *this;
		}

		Value *_value;
		Node *_parent;
		Node *_left;
		Node *_right;
		bool is_black;
		bool is_nil;
		virtual ~Node(){}


	};

//	template <class T>
//	std::ostream &operator<<(std::ostream &cout, ft::Node<T> * x){
//		cout<<*x->_value;
//		return cout;
//	}



//	template < class Value>
//	bool  operator==( ft::Node <Value>& x,  ft::Node<Value>& y){
//		return x._value == y._value;
//	}
}

#endif //CONTAINERS_NODE_HPP
