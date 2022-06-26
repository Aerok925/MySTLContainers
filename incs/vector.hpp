#ifndef CONTAINERS_VECTOR_H
#define CONTAINERS_VECTOR_H


#include "reverse_iterator.hpp"
#include "utilities.hpp"
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <type_traits>
#include <string>
#include <memory>

namespace ft{
	template <class T, class Alloc = std::allocator <T> >
	class vector{

	public:
//		friend class reverse_iterator<T>;
		template<typename L>
		class RandomAccessIterator{
			friend class vector;
		public:
			typedef typename iterator_traits<L*>::value_type value_type;
			typedef typename iterator_traits<L*>::pointer    pointer;
			typedef typename iterator_traits<L*>::reference  reference;
			typedef typename iterator_traits<L*>::difference_type difference_type;
			typedef pointer 								iterator_type;
			typedef std::random_access_iterator_tag 		iterator_category;
		private:
			pointer _pointer;

		public:
			RandomAccessIterator(): _pointer(){

			};

			RandomAccessIterator(pointer other) : _pointer(other){

			};

			virtual ~RandomAccessIterator(){

			};


			RandomAccessIterator & operator++(){
				_pointer++;
				return (*this);
			}

			RandomAccessIterator  operator++(int){
				RandomAccessIterator tmp = *this;
				++_pointer;
				return tmp;
			}


			RandomAccessIterator & operator--(){
				_pointer--;
				return (*this);
			}

			RandomAccessIterator  operator--(int){
				RandomAccessIterator tmp = *this;
				_pointer--;
				return tmp;
			}

			RandomAccessIterator  operator+(const difference_type & other) const{
				return _pointer + other;
			}

			RandomAccessIterator  operator-(const difference_type & other) const{
				return _pointer - other;
			}

			RandomAccessIterator & operator+=(const difference_type & other){
				_pointer = _pointer + other;
				return (*this);
			}

			RandomAccessIterator & operator-=(const difference_type & other){
				_pointer = _pointer - other;
				return *this;
			}

//			pointer  operator+(const difference_type & other) const{
//				return _pointer + other;
//			}
//
//			pointer  operator-(const difference_type & other) const{
//				return _pointer - other;
//			}
//
//			pointer & operator+=(const difference_type & other){
//				_pointer = _pointer + other;
//				return (*this);
//			}
//
//			pointer & operator-=(const difference_type & other){
//				_pointer = _pointer - other;
//				return *this;
//			}

			pointer operator->() const{
				return _pointer;
			}

			reference operator*()const{
				return *_pointer;
			}

			reference operator[](difference_type i) const{
				return *(_pointer + i);
			}
//			bool operator!=(const RandomAccessIterator& other){
//				return (_pointer != other._pointer);
//			}
//
//			bool operator==(const RandomAccessIterator& other){
//				return (_pointer == other._pointer);
//			}
//			bool operator>(const RandomAccessIterator& other){
//				return _pointer > other._pointer;
//			}
		};

		template<class iter, class iter2>
		friend bool operator==(const RandomAccessIterator<iter>& first, const RandomAccessIterator<iter2>& second){
			return (first._pointer == second._pointer);
		}
		template<class iter, class iter2>
		friend bool operator!=(const RandomAccessIterator<iter>& first, const RandomAccessIterator<iter2>& second){
			return (first._pointer != second._pointer);
		}
		template<class iter, class iter2>
		friend bool operator>(const RandomAccessIterator<iter>& first, const RandomAccessIterator<iter2>& second){
			return (first._pointer > second._pointer);
		}

		template<class iter, class iter2>
		friend bool operator<(const RandomAccessIterator<iter>& first, const RandomAccessIterator<iter2>& second){
			return !(first._pointer > second._pointer);
		}

		typedef Alloc									allocator_type;
		typedef typename Alloc::size_type 				size_type;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::value_type				value_type;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::const_reference			const_reference;

		typedef RandomAccessIterator<value_type> 		iterator;
		typedef RandomAccessIterator<const value_type>  const_iterator;
		typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> 				reverse_iterator;
		// itertors
		template<class iter, class iter2>
		friend difference_type operator-(const RandomAccessIterator<iter>& first, const RandomAccessIterator<iter2>& second){
			return (first._pointer - second._pointer);
		}

		iterator begin(){
			return ((iterator)_arr);
		}

		iterator end(){
			return ((iterator)_last);
		}

		const_iterator cbegin() const{
			return ((const_iterator)_arr);
		}

		const_iterator cend() const{
			return ((const_iterator)_last);
		}

		//reverce iterator
		reverse_iterator rbegin(){
			return ((reverse_iterator)(_last - 1));
		}

		reverse_iterator rend(){
			return ((reverse_iterator)(_arr - 1));
		}

		const_reverse_iterator crbegin() const {
			return ((const_reverse_iterator)(_last - 1));
		}

		const_reverse_iterator crend() const {
			return ((const_reverse_iterator)(_arr - 1));
		}

	private:

		void new_size(size_type count){
			pointer newarr;
			if (count == 0)
				count = 1;
			try{
				newarr = _alloc.allocate(count);
			}
			catch(...){
				throw;
			}
			try{
				std::uninitialized_copy(_arr, _end, newarr);
			}
			catch(...){
				_alloc.deallocate(newarr, count);
				throw;
			}
			for (;_first != _last; _first++){
				_alloc.destroy(_first);
			}
			_last = newarr + this->size();
			_alloc.deallocate(_arr, this->size());
			_arr = newarr;
			_first = _arr;
			_end = _arr + count;
		}

		void vector_shift(iterator pos, size_type count){
			iterator tmp_begin = pos + (count - 1);
			iterator tmp_last = _last + (count - 1);
			try{
				for (; tmp_last != tmp_begin; tmp_last--){
					_alloc.construct(&*tmp_last, *(tmp_last - count));
				}
			}
			catch (...){
				_alloc.deallocate(_arr, this->capacity());
				throw;
			}
			_last = _last + count;
		}


	public:

		// erase 1 arguments (delete one element from vector by iterator)
		iterator erase(const_iterator pos){
			if (this->size() == 0)
				throw std::length_error("vector");
			size_type distance = pos - begin();
			for (size_type i = distance; i < size() - 1; ++i){
				_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(_arr + i + 1));
			}
			_last--;
			_alloc.destroy(_last);
			return iterator(begin() + distance);
		}

		const_iterator erase(const_iterator pos) const{
			if (this->size() == 0)
				throw std::length_error("vector");
			size_type distance = pos - begin();
			for (size_type i = distance; i < size() - 1; ++i){
				_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(_arr + i + 1));
			}
			_last--;
			_alloc.destroy(_last);
			return iterator(begin() + distance);
		}

		iterator erase(iterator pos){
			if (this->size() == 0)
				throw std::length_error("vector");
			size_type distance = pos - begin();
			for (size_type i = distance; i < size() - 1; ++i){
				_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(_arr + i + 1));
			}
			_last--;
			_alloc.destroy(_last);
			return iterator(begin() + distance);
		}
		////////////////////////////////////////////////////////


		//erase 2 arguments (delene n* elements from vectors by iterators)
		iterator erase(iterator first, iterator last){
			if (this->size() == 0)
				throw std::length_error("vector");
			if (first == last)
				return (last);
			size_type distance = first - begin();
			size_type count = last - first;
			for (size_type i = distance; i < size() - count; ++i){
				_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(_arr + i + count));
			}
			_last -= count;
			_alloc.destroy(_last);
			return iterator(begin() + distance);
		}
		////////////////////////////////////////////////////////////////////////////

		void swap(vector &x){
			if (*this == x)
				return;
			std::swap(_arr, x._arr);
			std::swap(_last, x._last);
			std::swap(_first, x._first);
			std::swap(_end, x._end);
			std::swap(_alloc, x._alloc);
		}

//		iterator
		// pull one element in the end
		void push_back(const T& value){
			if (this->size() == this->capacity()){
				try{
					if (_end == nullptr){
						this->new_size(1);
					}
					else
						this->new_size(this->capacity() * (size_type)2);
				}
				catch (...){
					throw;
				}
			}
			try {
				_alloc.construct(_last, value);
			}
			catch (...){
				throw;
			}
			_last++;
		}

		void resize(size_type count, T value = T()){
			if ((int)count < 0){
				throw (std::length_error("vector"));
			}
			if (count < this->size())
			{
//				std::cout<<"test1"<<std::endl;
				pointer tmp = _arr + count;
				for (; tmp < _last; tmp++){
					_alloc.destroy(tmp);
				}
				_last = _arr + count;
			}
			else if (count > this->size()){
				if (count <= this->capacity()){
					try{
						for (; _last != _arr + count; _last++){
							_alloc.construct(_last, value);
						}
					}
					catch (...){
						throw;
					}
				}
				else {
					try {
						this->new_size(this->capacity() * (size_type)2);
					}
					catch (...){
						throw;
					}
					try{
						for (; _last != _arr + count; _last++){
							_alloc.construct(_last, value);
						}
					}
					catch (...){
						throw;
					}

				}
			}
		}

		void clear(){
			for (;_first != _last; _first++){
				_alloc.destroy(_first);
			}
			_first = _arr;
			_last = _arr;
		}

		void pop_back(){
			if (this->size() < (size_type)1){
				return;
			}
			_last--;
			_alloc.destroy(_last);
		}

		//insert all const and iter 2 arguments//
		iterator insert(const_iterator pos, const T& value ){
			difference_type diff;
			diff = pos - this->begin();
			try {
				if (this->capacity() == this->size())
					this->new_size(this->capacity() * (size_type)2);
			}
			catch (...){
				throw;
			}
			try {
				this->vector_shift(_arr + diff, 1);
			}
			catch(...){
				throw;
			}
			try{
				_alloc.construct(_arr + diff, value);
			}
			catch (...){
				for (difference_type i = 0; i < diff; i++){
					_alloc.destroy(_arr + i);
				}
				for (difference_type i = diff; i < this->size(); i++){
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, this->capacity());
				throw;
			}
			return (_arr + diff);
		}

		iterator insert(iterator pos, const T& value ){
			difference_type diff;
			diff = pos - this->begin();
			try {
				if (this->capacity() == this->size())
					this->new_size(this->capacity() * (size_type)2);
			}
			catch (...){
				throw;
			}
			try {
				this->vector_shift(_arr + diff, 1);
			}
			catch(...){
				throw;
			}
			try{
				_alloc.construct(_arr + diff, value);
			}
			catch (...){
				for (difference_type i = 0; i < diff; i++){
					_alloc.destroy(_arr + i);
				}
				for (difference_type i = diff; i < this->size(); i++){
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, this->capacity());
				throw;
			}
			return (_arr + diff);
		}

		const_iterator insert(const_iterator pos, const T& value ) const{
			difference_type diff;
			diff = pos - this->begin();
			try {
				if (this->capacity() == this->size())
					this->new_size(this->capacity() * (size_type)2);
			}
			catch (...){
				throw;
			}
			try {
				this->vector_shift(_arr + diff, 1);
			}
			catch(...){
				throw;
			}
			try{
				_alloc.construct(_arr + diff, value);
			}
			catch (...){
				for (difference_type i = 0; i < diff; i++){
					_alloc.destroy(_arr + i);
				}
				for (difference_type i = diff; i < this->size(); i++){
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, this->capacity());
				throw;
			}
			return (_arr + diff);
		}
		////////////////////////////////////////////////////////////////////////////

		// insert 3 arguments
		void insert(iterator pos, size_type count, const T& value){
			if (count < 0)
				throw std::logic_error("vector");
			difference_type diff;
			diff = pos - this->begin();
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
				this->new_size(this->capacity() * 2);
			}
			this->vector_shift(_arr + diff, count);
			for (size_type i = 0; i < count; i++){
				_alloc.construct((_arr + i + diff), value);
			}
		}

		const_iterator insert(const_iterator pos, size_type count, const T& value) const {
			if (count < 0)
				throw std::logic_error("vector");
			difference_type diff;
			diff = pos - this->begin();
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
					this->new_size(this->capacity() * 2);
			}
			this->vector_shift(_arr + diff, count);
			for (size_type i = 0; i < count; i++){
				_alloc.construct((_arr + i + diff), value);
			}
			return (_arr + diff);
		}

		iterator insert(const_iterator pos, size_type count, const T& value){
			if (count < 0)
				throw std::logic_error("vector");
			difference_type diff;
			diff = pos - this->begin();
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
					this->new_size(this->capacity() * 2);
			}
			this->vector_shift(_arr + diff, count);
			for (size_type i = 0; i < count; i++){
				_alloc.construct((_arr + i + diff), value);
			}
			return (_arr + diff);
		}
		/////////////////////////////////////////////////////////////////////////////

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) {
			difference_type diff;
			diff = pos - this->begin();
			size_type count = last - first;
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
					this->new_size(this->capacity() * 2);
			}
			try {
				this->vector_shift(_arr + diff, count);
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
			try {
				for (size_type i = 0; i < count; i++, first++) {
					_alloc.construct((_arr + i + diff), *first);
				}
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
		}

		template< class InputIt >
		iterator insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) {
			difference_type diff;
			diff = pos - this->begin();
			size_type count = last - first;
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
					this->new_size(this->capacity() * 2);
			}
			try {
				this->vector_shift(_arr + diff, count);
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
			try {
				for (size_type i = 0; i < count; i++, first++) {
					_alloc.construct((_arr + i + diff), *first);
				}
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
			return (_arr + count);
		}

		template< class InputIt >
		const_iterator insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) const {
			difference_type diff;
			diff = pos - this->begin();
			size_type count = last - first;
			if (this->size() + count > this->capacity()){
				if (this->size() + count > this->capacity() * 2)
					this->new_size(this->capacity() + count);
				else
					this->new_size(this->capacity() * 2);
			}
			try {
				this->vector_shift(_arr + diff, count);
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
			try {
				for (size_type i = 0; i < count; i++, first++) {
					_alloc.construct((_arr + i + diff), *first);
				}
			}
			catch (...){
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->capacity());
				_arr = 0;
				_end = 0;
				_last = 0;
				_first = 0;
				throw;
			}
			return (_arr + count);
		}

		template<class InputIter>
		void assign(InputIter first, InputIter second, typename ft::enable_if<!ft::is_integral<InputIter>::value>::type* = 0){
			if (int(second - first) < 0)
				throw std::length_error("vector");
			if ((size_type)(second - first) <= this->capacity()){
				for (; _first < _last; _first++)
					_alloc.destroy(_first);
				try {
					std::uninitialized_copy(first, second, _arr);
				}
				catch (...){
					throw;
				}
				_first = _arr;
				_last = _arr + (second - first);
			}
			else{
				pointer newarr;
				try {
					newarr = _alloc.allocate(second - first);
				}
				catch(...){
					throw;
				}
				try{
					std::uninitialized_copy(first, second, newarr);
				}
				catch (...){
					_alloc.deallocate(newarr, second - first);
					throw;
				}
				for (; _first != _last; _first++)
					_alloc.destroy(_first);
				_alloc.deallocate(_arr, this->size());
				_arr = newarr;
				_first = _arr;
				_end = _arr + (second - first);
				_last = _end;
			}
		}

		void assign(size_type count, const_reference value){
			if ((int)count < 0)
				throw std::length_error("vector");
			if (this->capacity() >= count){
				for (; _first < _last; _first++){
					_alloc.destroy(_first);
				}
				_first = _arr;
				for (size_type i = 0; i < count; i++){
					_alloc.construct(_first + i, value);
				}
				_last = _arr + count;
			}
			else{
				pointer newarr;
				try {
					newarr = _alloc.allocate(count);
				}
				catch (...){
					throw;
				}
				try {
					for (size_type i = 0; i < count; i++){
						_alloc.construct(newarr + i, value);
					}
//					std::uninitialized_copy((size_type)0, count, newarr);
				}
				catch(...){
					_alloc.deallocate(newarr, count);
					throw;
				}
				for (; _first != _last; _first++){
					_alloc.destroy(_first);
				}
				_alloc.deallocate(_arr, this->size());
				_arr = newarr;
				_first = _arr;
				_end = _arr + count;
				_last = _end;
			}
		}

		reference front(){
			return ((reference)*_first);
		}

		reference back(){
			return ((reference)*(_last - 1));
		}

		void reserve(size_type new_cap){
			if (new_cap <= this->size())
				return;
			try{
				new_size(new_cap);
			}
			catch (...){
				throw;
			}
		}

		const_reference front() const {
			return ((const_reference)*_first);
		}

		const_reference back() const {
			return ((const_reference)*(_last - 1));
		}

		reference at(size_type i){
			if (i < 0 || i >= this->size())
				throw std::out_of_range("vector");
			return (reference(_arr[i]));
		}

		//constuct
		explicit vector(const Alloc& alloc = Alloc()) : _alloc(alloc){
			_arr = 0;
			_last = 0;
			_first = 0;
			_end = 0;
		}

		explicit vector(size_type count, const T& value = T(), const Alloc& alloc = Alloc()) : _alloc(alloc){
			if ((int)count < 0){
				throw (std::length_error("vector"));
			}
			try {
				_arr = _alloc.allocate(count);
			}
			catch (std::bad_alloc){
				throw;
			}
			for (size_type i = 0; i < count; i++){
				try{
					_alloc.construct(_arr + i, value);
				}
				catch (...){
					for (size_type j = 0; j < i; i++)
						_alloc.destroy(_arr + j);
					_alloc.deallocate(_arr, count);
					throw;
				}
			}
			_first = _arr;
			_last = _arr + count;
			_end = _arr + count;
		}

		vector(const vector &temp){
			_alloc = temp.get_allocator();
			if (temp._arr){
				try {
					_arr = _alloc.allocate(temp._end - temp._first);
				}
				catch (std::bad_alloc){
					throw;
				}
			}
			else
				_arr = nullptr;
			_end	= _arr + (temp._end - temp._first);
			_first 	= _arr;
			_last 	= _arr + (temp._last - temp._first);
			try {
				std::uninitialized_copy(temp._arr, temp._end, _arr);
			}
			catch (...){
				_alloc.deallocate(_arr, _end - _first);
				throw;
			}
		}

		template<class InputIter>
		vector(InputIter first, InputIter second, const Alloc& alloc = Alloc(), typename ft::enable_if<!ft::is_integral<InputIter>::value>::type* = 0) : _alloc(alloc){

			if (first > second){
				throw std::length_error("vector");
			}
			try {
				_arr = _alloc.allocate(second - first);
			}
			catch (...){
				throw ;
			}
			_first = _arr;
			_last = _arr + (second - first);
			_end = _last;
			try {
				std::uninitialized_copy(first, second, _arr);
			}
			catch (...){
				_alloc.deallocate(_arr, second - first);
			}
			_first = _arr;
		}

		~vector(){
			for (pointer tmp = _first; tmp != _end; tmp++){
				_alloc.destroy(tmp);
			}
			_alloc.deallocate(_arr, _end - _first);
		}

		//copy construct
		vector<T> operator=(vector<T>& second){
			_alloc = second.get_allocator();
			for (; _first != _last; _first++){
				_alloc.destroy(_first);
			}

			_alloc.deallocate(_arr, this->size());
			_arr = _alloc.allocate(second.size());

			std::uninitialized_copy(second.begin(), second.end(), _arr);
			_end = _arr + second.capacity();
			_first = _arr;

			_last = _arr + second.size();

			return (*this);
		}

		allocator_type get_allocator() const{
			return (_alloc);
		}

		// capacity
		bool	empty(){
			return (_arr == _last);
		}

		size_type size() const{
			return ((size_type)(_last - _arr));
		}

		size_type max_size(){
			return (_alloc.max_size());
		}



		size_type capacity() const {
			return ((size_type)(_end - _arr));
		}
		// operators
		reference operator[](size_type i){
			return (_arr[i]);
		}

		const_reference operator[](size_type i) const{
			return (_arr[i]);
		}


	private:
		pointer _arr; // pointer on all arr
		pointer _first; // first element in arr
		pointer	_last;	// last element in arr
		pointer	_end;	// end allocation memory
		Alloc	_alloc;
	};

	template<class temp>
	bool operator==(vector<temp>& first, vector<temp>& second){
		return first.size() == second.size() && ft::equal(first.begin(), first.end(), second.begin());
	}

	template<class temp>
	bool operator!=(vector<temp>& first, vector<temp>& second){
		return !(first == second);
	}

	template<class temp>
	bool operator<(vector<temp>& first, vector<temp>& second){
		return (ft::lexicographical_compare(first.begin(), first.end(), second.begin(), second.end()));
	}

	template<class temp>
	bool operator>(vector<temp>& first, vector<temp>& second){
		return (ft::lexicographical_compare(second.begin(), second.end(), first.begin(), first.end()));
	}

	template<class temp>
	bool operator>=(vector<temp>& first, vector<temp>& second){
		return !(first < second);
	}

	template<class temp>
	bool operator<=(vector<temp>& first, vector<temp>& second){
		return !(first > second);
	}
};

namespace std{
	template <class T, class Alloc>
			void swap(ft::vector<T, Alloc>&lhs, ft::vector<T, Alloc>&rhs){
				lhs.swap(rhs);
			};
}

#endif //CONTAINERS_VECTOR_H
