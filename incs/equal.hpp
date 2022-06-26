//
// Created by John Nappa on 5/28/22.
//

#ifndef CONTAINERS_EQUAL_HPP
#define CONTAINERS_EQUAL_HPP

namespace ft{

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ){
		for (; first1 != last1; first1++, first2++){
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

}

#endif //CONTAINERS_EQUAL_HPP
