//
// Created by John Nappa on 5/28/22.
//

#ifndef CONTAINERS_ENABLE_IF_HPP
#define CONTAINERS_ENABLE_IF_HPP



namespace ft{

	template<bool A, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

}


#endif //CONTAINERS_ENABLE_IF_HPP
