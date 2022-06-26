//
// Created by John Nappa on 5/30/22.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft{
	template <class T, class Container = ft::vector<T> >
	class stack{
	public:
		typedef typename 	Container::value_type  			value_type ;
		typedef typename 	Container::reference  			reference;
		typedef typename 	Container::const_reference  	const_reference;
		typedef typename 	Container::size_type  			size_type;
		typedef 			Container  						container_type;
	protected:
		Container c;
	public:

		stack(stack & other) : c(other.c){

		}

		explicit stack( const Container& cont = Container()) : c(cont){}

		stack &operator=(stack &other){
			c = other.c;
			return *this;
		}
		size_type empty(){
			return c.empty();
		}
		size_type size(){
			return c.size();
		}

		reference top(){
			return c.back();
		}

		void push(value_type & value){
			c.push_back(value);
		}

		void push(const value_type & value){
			c.push_back(value);
		}

		void pop(){
			c.pop_back();
		}

		template <class A, class B>
		friend bool operator==(stack<A, B>& first,  stack<A, B>& second){
			return first.c == second.c;
		}

		template <class A, class B>
		friend bool operator!=(stack<A, B>& first,  stack<A, B>& second){
			return first.c != second.c;
		}

		template <class A, class B>
		friend bool operator>=(stack<A, B>& first,  stack<A, B>& second){
			return first.c >= second.c;
		}

		template <class A, class B>
		friend bool operator<=(stack<A, B>& first,  stack<A, B>& second){
			return first.c <= second.c;
		}

		template <class A, class B>
		friend bool operator>(stack<A, B>& first,  stack<A, B>& second){
			return first.c > second.c;
		}

		template <class A, class B>
		friend bool operator<(stack<A, B>& first,  stack<A, B>& second){
			return first.c < second.c;
		}
	};

}

#endif //CONTAINERS_STACK_HPP
