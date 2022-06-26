//
// Created by John Nappa on 5/26/22.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "utilities.hpp"

namespace ft{
	template <class Iterator>
	class reverse_iterator {
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
	private:
		iterator_type base_iterator;
	public:
		reverse_iterator() : base_iterator(){

		};

		explicit reverse_iterator(iterator_type it) : base_iterator(it){

		};

		template <class Iterator1>
		reverse_iterator(const reverse_iterator<Iterator1>& reverse_it){
			base_iterator = reverse_it.base_iterator;
		};

		template <class Iterator1>
		reverse_iterator& operator=(const reverse_iterator<Iterator1>& reverse_it){
			base_iterator = reverse_it.base_iterator;
			return (*this);
		};

		iterator_type base() const {
			return (this->base_iterator);
		};

		reference operator*() const{
			return (*base_iterator);
		};

		pointer operator->() const{
			return &(operator*());
		};

		reverse_iterator operator++(int){
			reverse_iterator tmp = *this;
			base_iterator--;
			return tmp;
		}
		reverse_iterator operator--(int){
			reverse_iterator tmp = *this;
			base_iterator++;
			return tmp;
		}
		reverse_iterator operator++(){
			base_iterator--;
			return *this;
		}
		reverse_iterator operator--(){
			base_iterator++;
			return *this;
		}
		reverse_iterator operator+(reverse_iterator::difference_type i){
			return (reverse_iterator(base_iterator - i));
		}

		reverse_iterator operator-(reverse_iterator::difference_type i){
			return (reverse_iterator(base_iterator + i));
		}

//		template <class iter>
//		bool operator==( const reverse_iterator<iter>& second){
//			return (*this == *second);
//		}

		template <class iter>
		friend bool operator==(const reverse_iterator<iter>& first, const reverse_iterator<iter>& second){
			return (*first == *second);
		}

		template <class iter>
		friend bool operator!=(const reverse_iterator<iter>& first, const reverse_iterator<iter>& second){
			return (*first != *second);
		}

		template <class iter>
		typename reverse_iterator<iter>::difference_type operator-(const reverse_iterator<iter>& second){
			return (this->base_iterator - second.base());
		}

		template <class iter>
		typename reverse_iterator<iter>::difference_type operator+( const reverse_iterator<iter>& second){
			return (second.base() + this->base());
		}

		template <class iter>
		bool operator>(const reverse_iterator<iter>& second){
			return (*this < *second);
		}

		template <class iter>
		bool operator<(const reverse_iterator<iter>& second){
			return (*this > *second);
		}
	};


}


#endif //CONTAINERS_REVERSE_ITERATOR_HPP
