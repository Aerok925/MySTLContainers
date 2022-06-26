//
// Created by John Nappa on 6/7/22.
//

#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP
namespace ft{
	template<class T1, class T2> struct pair {
		typedef T1 firstType;
		typedef T2 secondType;

		firstType first;
		secondType second;

		pair() : first(), second(){}
		template <class F, class S>
		pair(const pair<F, S> &copy):first(copy.first), second(copy.second){}
		pair(const pair & copy) : first(copy.first), second(copy.second){}
		pair(const firstType &a, const secondType &b):first(a), second(b){}
		pair & operator=(const pair & right){
			first = right.first;
			second = right.second;
			return (*this);
		}
	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2>&lhs, const pair<T1, T2>& rhs){
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
		return lhs.first < rhs.first  || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
		return rhs < lhs;
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2>&lhs, const pair<T1, T2>& rhs){
		return !(lhs < rhs);
	}

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 lhs, T2 rhs){
		return pair<T1, T2>(lhs, rhs);
	}

}
#endif //CONTAINERS_PAIR_HPP
