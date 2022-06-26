//
// Created by John Nappa on 6/4/22.
//

#ifndef CONTAINERS_TREEITERATOR_HPP
#define CONTAINERS_TREEITERATOR_HPP


#include "Node.hpp"

template <class T>
class TreeIterator{
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator_traits<T*>::value_type 	value_type;
	typedef typename ft::iterator_traits<T*>::reference		reference;
	typedef typename ft::iterator_traits<T*>::pointer 		pointer;
	typedef typename ft::iterator_traits<T*>::difference_type difference_type;

	typedef ft::Node<typename std::remove_const<value_type>::type>* 	node_pointer;

private:
	node_pointer node;

	node_pointer min_tree(node_pointer x){
		while (x->_left != nullptr && !x->_left->is_nil) {
			x = x->_left;
		}
		return x;
	}

	node_pointer max_tree(node_pointer x){
		while (x->_right != nullptr && !x->_right->is_nil)
			x = x->_right;
		return x;
	}


public:

	TreeIterator(){

	}

//	TreeIterator(void *node): node(static_cast<node_pointer>(node)){}

	TreeIterator(void *node): node(static_cast<node_pointer>(node)){}

	pointer operator->() const {
		return node->_value;
	}

	reference operator*() const{
		return *(node->_value);
	}

	TreeIterator & operator=(const TreeIterator<typename std::remove_const<value_type>::type> & other){
		this->node = other.node_p();
		return *this;
	}

	TreeIterator(const TreeIterator<T> & other){
		this->node = other.node;
	}

	TreeIterator& operator++(){
		if (node->_right && !node->_right->is_nil)
			node = min_tree(node->_right);
		else {
			node_pointer n = node->_parent;

			while (n != NULL && node == n->_right) {
				node = n;
				n = n->_parent;
			}
			node = n;
		}
		return *this;
	}


	TreeIterator& operator--(){
		if (node->_left && !node->_left->is_nil)
			node = max_tree(node->_left);
		else {
			node_pointer n = node->_parent;
			while (n != NULL && node == n->_left) {
				node = n;
				n = n->_parent;
			}
			node = n;
		}
		return *this;
	}

	TreeIterator operator--(int){
		TreeIterator temp = *this;
		if (node->_left && !node->_left->is_nil)
			node = max_tree(node->_left);
		else {
			node_pointer n = node->_parent;
			while (n != NULL && node == n->_left) {
				node = n;
				n = n->_parent;
			}
			node = n;
		}
		return temp;
	}


	TreeIterator operator++(int) {
		TreeIterator temp = *this;
		if (!node->_right->is_nil) {
			node = min_tree(node->_right);
		}
		else {
			node_pointer y = node->_parent;
			while (y != NULL && node == y->_right) {
				node = y;
				y = y->_parent;
			}
			node = y;
		}

		return temp;
	}

	node_pointer node_p() const{
		return node;
	}

};

template <typename A, typename B>
bool operator==(const TreeIterator<A>& lhs, const TreeIterator<B>& rhs){
	return lhs.node_p() == rhs.node_p();
}

template <typename A, typename B>
bool operator!=(const TreeIterator<A>& lhs, const TreeIterator<B>& rhs){
	return lhs.node_p() != rhs.node_p();
}

#endif //CONTAINERS_TREEITERATOR_HPP
