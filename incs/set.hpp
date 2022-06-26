//
// Created by John Nappa on 6/10/22.
//

#ifndef CONTAINERS_SET_HPP
#define CONTAINERS_SET_HPP

#include "BlackRedTree.hpp"

namespace ft{
	template <class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
	class set{
	public:
		typedef	Value 														key_type;
		typedef	Value 														value_type;
		typedef std::size_t 												size_type;
		typedef std::ptrdiff_t 												difference_type;
		typedef	Compare														key_compare;
		typedef Compare 													value_compare;
		typedef Alloc 														allocator_type;
		typedef value_type&													reference;
		typedef typename Alloc::pointer										pointer;
		typedef typename Alloc::const_pointer								const_pointer;
		typedef RedBlackTree<value_type, value_compare, allocator_type> 	tree_type;
		typedef typename tree_type::iterator								iterator;
		typedef typename tree_type::const_iterator 							const_iterator;
		typedef typename tree_type::reverse_iterator						reverse_iterator;
		typedef typename tree_type::const_reverse_iterator 					const_reverse_iterator;
	private:
		allocator_type _allocator;
		tree_type _tree;
		value_compare  _comp;

	public:
		explicit set(const value_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_allocator(alloc), _tree(tree_type(comp, alloc)), _comp(comp) {}

		template< class InputIt >
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()):
		_allocator(alloc), _tree(first, last, comp, _allocator), _comp(comp) {}

		set& operator=(const set& other){
			this->_tree = other._tree;
			this->_allocator = other._allocator;
			this->_comp = other._comp;
			return *this;
		}

		size_type size() const{
			return _tree.size();
		}

		bool empty() const{
			return _tree.empty();
		}

		size_type max_size(){
			return _allocator.max_size();
		}

		allocator_type get_allocator() const{
			return _allocator;
		}

		void clear(){
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type& value){
			return _tree.insert(value);
		}

		template<class InputIt>
		ft::pair<iterator, bool> insert(typename enable_if< !is_integral<InputIt>::value, InputIt >::type first, InputIt last){
			ft::pair<iterator, bool> ret;
			for (; first != last; first++){
				ret = _tree.insert(*first);
			}
			return ret;
		}

		iterator insert(iterator hint, const value_type& value ){
			return _tree.insert(hint, value);
		}

		void erase(iterator pos){
			_tree.erase(pos);
		}

		void erase(iterator first, iterator last){
			_tree.erase(first, last);
		}

		size_type erase(const key_type & key){
			return _tree.erase(key);
		}

		iterator begin() {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator begin() const {
			return _tree.begin();
		}

		const_iterator end() const {
			return _tree.end();
		}

		reverse_iterator rbegin(){
			return _tree.rbegin();
		}

		reverse_iterator rend(){
			return _tree.rend();
		}

//		const_reverse_iterator rbegin() const {
//			return _tree.rbegin();
//		}
//
//		const_reverse_iterator rend() const {
//			return _tree.rend();
//		}


		size_type count(const key_type& key ){
			return _tree.count(key);
		}

		iterator find(const key_type& key){
			return _tree.find(key);
		}

		iterator lower_bound(const key_type & key){
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const key_type& key){
			return _tree.upper_bound(key);
		}

		pair<iterator, iterator> equal_range(const key_type & key){
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type & key) const{
			return _tree.equal_range(key);
		}

		key_compare key_comp() const {
			return _comp;
		}

		void swap(set & other){
			std::swap(this->_allocator, other._allocator);
			std::swap(this->_comp, other._comp);
			_tree.swap(other._tree);
		}

		tree_type& get_tree(){
			return _tree;
		}

	};

	template <class Value, class Compare, class Alloc>
	bool operator<(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return (first.get_tree() < second.get_tree());
	}

	template <class Value, class Compare, class Alloc>
	bool operator>(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return (first.get_tree() > second.get_tree());
	}

	template <class Value, class Compare, class Alloc>
	bool operator>=(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return !(first < second);
	}

	template <class Value, class Compare, class Alloc>
	bool operator<=(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return !(first > second);
	}

	template <class Value, class Compare, class Alloc>
	bool operator==(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return (first.get_tree() == second.get_tree());
	}

	template <class Value, class Compare, class Alloc>
	bool operator!=(set<Value, Compare, Alloc>& first, set<Value, Compare, Alloc>& second){
		return !(first == second);
	}

}

namespace std{
	template <class Value, class Compare, class Alloc>
	void swap(const ft::set<Value, Compare, Alloc>&left, const ft::set<Value, Compare, Alloc>&right){
		left.swap(right);
	};
}

#endif //CONTAINERS_SET_HPP
