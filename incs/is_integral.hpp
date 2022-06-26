//
// Created by John Nappa on 5/27/22.
//

#ifndef CONTAINERS_IS_INTEGRAL_HPP
#define CONTAINERS_IS_INTEGRAL_HPP

namespace ft{
	template <class T, T Value>
	struct integral_constant{
		static const T value = Value;
		typedef T		value_type;
		bool	operator()() const { return value; };
		operator value_type() {return value;}
	};
struct true_type: public ft::integral_constant<bool, true>{};
struct false_type: public ft::integral_constant<bool, false>{};


	template <class _Tp> struct is_integral                     : public false_type {};
	template <>          struct is_integral<bool>               : public true_type {};
	template <>          struct is_integral<char>               : public true_type {};
	template <>          struct is_integral<signed char>        : public true_type {};
	template <>          struct is_integral<unsigned char>      : public true_type {};
	template <>          struct is_integral<wchar_t>            : public true_type {};
	template <>          struct is_integral<char16_t>           : public true_type {};
	template <>          struct is_integral<char32_t>           : public true_type {};
	template <>          struct is_integral<short>              : public true_type {};
	template <>          struct is_integral<unsigned short>     : public true_type {};
	template <>          struct is_integral<int>                : public true_type {};
	template <>          struct is_integral<unsigned int>       : public true_type {};
	template <>          struct is_integral<long>               : public true_type {};
	template <>          struct is_integral<unsigned long>      : public true_type {};
	template <>          struct is_integral<long long>          : public true_type {};
	template <>          struct is_integral<unsigned long long> : public true_type {};
	template <>          struct is_integral<__int128_t>         : public true_type {};
	template <>          struct is_integral<__uint128_t>        : public true_type {};

//	template < >
//	struct is_integral<int>
//	{
//		Type true_false;
//	};



//	template <>
//	struct is_integral<int>: public ft::integral_base<int, true>{};
}


#endif //CONTAINERS_IS_INTEGRAL_HPP
