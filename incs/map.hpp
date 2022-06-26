//
// Created by John Nappa on 6/4/22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "BlackRedTree.hpp"

namespace ft{
	template < class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, Value> > >
	class map{


	public:
		typedef Key key_type;
		typedef Value mapped_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare	key_compare;
		typedef	Alloc	allocator_type;
		typedef ft::pair<const Key, Value>	value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Alloc::pointer	pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef typename RedBlackTree<value_type>::iterator 	iterator;
		typedef typename RedBlackTree<value_type>::reverse_iterator reverse_iterator;
		typedef typename RedBlackTree<value_type>::const_iterator 	const_iterator;
		typedef typename RedBlackTree<value_type>::const_reverse_iterator const_reverse_iterator;


	private:

		class pair_compare {
			key_compare _compare;

		public:
			pair_compare(const key_compare & compare) : _compare(compare) {}

			bool operator()(const value_type & x, const value_type & y) const{
				return (_compare(x.first, y.first));
			}
		};
		typedef pair_compare value_compare;
		typedef RedBlackTree<value_type, value_compare , allocator_type> tree_type;
		allocator_type _alloc;
		Compare _comp;
		tree_type tree;

	public:

//		explicit map(const allocator_type& alloc):
//				_alloc(alloc), _comp(key_compare()), tree(tree_type(_comp, alloc))  {
//		}

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_alloc(alloc), tree(tree_type(comp, alloc)), _comp(comp) {}

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()):
				_alloc(alloc), tree(first, last, comp, _alloc), _comp(comp) {}


		//insert and erase
		ft::pair<iterator, bool> insert(const value_type& value){
			return tree.insert(value);
		}

		template<class InputIt>
		ft::pair<iterator, bool> insert(typename enable_if< !is_integral<InputIt>::value, InputIt >::type first, InputIt last){
			ft::pair<iterator, bool> ret;
			for (; first != last; first++){
				ret = tree.insert(*first);
			}
			return ret;
		}

		iterator insert(iterator hint, const value_type& value ){
			return tree.insert(hint, value);
		}

		void erase(iterator pos){
			tree.erase(pos);
		}

		void erase(iterator first, iterator last){
			tree.erase(first, last);
		}

		size_type erase(const Key& key){
			return tree.erase(ft::make_pair(key, mapped_type()));
		}
		//////////////////////////////

		//			FIND  			//

		iterator find(const Key &key){
			return tree.find(ft::make_pair(key, mapped_type()));
		}

		//////////////////////////////

		iterator begin(){
			return (tree.begin());
		}

		iterator end() {
			return (tree.end());
		}

		const_iterator end() const {
			return (tree.end());
		}

		const iterator begin() const{
			return (tree.begin());
		}

		reverse_iterator rbegin(){
			return(tree.rbegin());
		}

		reverse_iterator rend(){
			return(tree.rend());
		}


		//capacity
		size_type empty(){
			return tree.empty();
		}

		size_type size(){
			return tree.size();
		}

		size_type max_size() const{
			return tree.max_size();
		}

		size_type count(const Key& key) const{
			return (tree.count(ft::make_pair(key, mapped_type())));
		}

		allocator_type get_allocator() const{
			return tree.get_allocator();
		}

		mapped_type& at(const Key& key){
			return (tree.found(make_pair(key, mapped_type()))->_value->second);
		}

		mapped_type& at(const Key& key) const {
			return (tree.found(make_pair(key, mapped_type()))->_value->second);
		}

		mapped_type& operator[](const Key& key){
			return (this->insert(ft::make_pair(key, mapped_type())).first)->second;
		}

		tree_type& get_tree(){
			return	tree;
		}

		void swap(map &other){
			std::swap(this->_comp, other._comp);
			std::swap(this->_alloc, other._alloc);
			tree.swap(other.tree);
		}

		void clear(){
			tree.clear();
		}

		iterator lower_bound(const Key& key){
			return tree.lower_bound(ft::make_pair(key, mapped_type()));
		}

		iterator upper_bound(const Key& key){
			return tree.upper_bound(ft::make_pair(key, mapped_type()));
		}

		pair<iterator, iterator> equal_range(const key_type & key){
			return (tree.equal_range(make_pair(key, mapped_type())));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type & key) const{
			return (tree.equal_range(make_pair(key, mapped_type())));
		}

		key_compare key_comp() const {
			return _comp;
		}

	};
	template <class Key, class Value, class Compare, class Alloc>
	bool operator<(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return (first.get_tree() < second.get_tree());
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return (first.get_tree() > second.get_tree());
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>=(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return !(first < second);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<=(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return !(first > second);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator==(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return (first.get_tree() == second.get_tree());
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator!=(map<Key, Value, Compare, Alloc>& first, map<Key, Value, Compare, Alloc>& second){
		return !(first == second);
	}
}

namespace std{
	template <class Key, class Value, class Compare, class Alloc>
	void swap(const ft::map<Key, Value, Compare, Alloc>&left, const ft::map<Key, Value, Compare, Alloc>&right){
		left.swap(right);
	};
}

#endif //CONTAINERS_MAP_HPP
