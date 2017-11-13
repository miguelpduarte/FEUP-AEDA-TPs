#include <iostream>
#include <stack>

using namespace std;

template <class T>
class StackExt {
private:
	stack<T> main_stack;
	stack<T> min_stack;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return main_stack.empty();
}

template <class T>
T& StackExt<T>::top() {
	return main_stack.top();
}

template <class T>
void StackExt<T>::pop() {
	//If element is also in min_stack it must be popped so that it is updated
	//== is the same as !(a < b) && !(b < a) or as !(a < b || b < a)
	if(!(min_stack.top() < main_stack.top() || main_stack.top() < min_stack.top()))
		min_stack.pop();

	main_stack.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	//Updating main stack
	main_stack.push(val);
	//Updating auxiliar minimum stack
	//If min stack is empty, insert straight away
	//If new element is smaller than or equal to current minimum, insert into min_stack
	if(min_stack.empty() || val < min_stack.top() || !(val < min_stack.top() || min_stack.top() < val)){
		min_stack.push(val);
	}
}

template <class T>
T& StackExt<T>::findMin() {
	return min_stack.top();
}

/*
void Beach::print(ostream& os){
	os << aksdasod;
}

friend ostream & operator<<(ostream &os, Beach &b){
	b.print(os);
	return os;
}

a->print(cout);
 */