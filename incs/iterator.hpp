//
// Created by John Nappa on 5/24/22.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

#include <stdio.h>
#include <ostream>
#include <iostream>
#include <type_traits>

namespace ft{
	template <class Iterator>
	class iterator_traits{
	public:
		typedef typename Iterator::difference_type  	difference_type;
		typedef typename Iterator::value_type       	value_type;
		typedef typename Iterator::pointer          	pointer;
		typedef typename Iterator::reference        	reference;
		typedef typename Iterator::iterator_category    iterator_category;
	};

	template <class T>
	class iterator_traits<T*>{
	public:
		typedef ptrdiff_t 						difference_type;
		typedef T              					value_type;
		typedef value_type*             		pointer;
		typedef value_type&             		reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t 						difference_type;
		typedef T 								value_type;
		typedef value_type* 					pointer;
		typedef value_type&				  		reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
};



#endif //CONTAINERS_ITERATOR_HPP
