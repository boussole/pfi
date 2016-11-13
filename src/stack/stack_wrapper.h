/**
 * \file    stack_emulation.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef STACK_WRAPPER_H_
#define STACK_WRAPPER_H_

#include <common/common.h>

/**
 * @namespace conq_stack
 * @brief Group stack structures, classes and functions
 */
namespace conq_stack {

/**
 * limit operations: pop, push, top, is_empty
 */
template <typename T>
class SimpleStack : private std :: stack<T>
{
public:
	SimpleStack() {}
	virtual ~SimpleStack() {}
	void push(const T & val) { std :: stack<T> :: push(val); }
	void pop() { std :: stack<T> :: pop(); }
	bool is_empty() const { return std :: stack<T> :: empty(); }
	T & top() { return std :: stack<T> :: top(); }
	const T & top() const { return std :: stack<T> :: top(); }
	void revert();
	void revertUsingStackSz(); /** second method, using stack size */

protected:
	bool revert(T & childTop, int level, const int maxLevel);
	/** used by second revert method */
	void revertLevel(int steps, int dstSteps);
	void change(int steps, T & value);

private:
};

template <typename T>
void SimpleStack<T> :: revert()
{
	if (is_empty()) { return; }

	T child_top;

	int max_level = 0;

	while (revert(child_top, 0, max_level)) {
		push(child_top);
		max_level++;
	}

	push(child_top); /** for last iteration */
}

template <typename T>
bool SimpleStack<T> :: revert(T & childTop, int level, const int maxLevel)
{
	bool retval = true;

	T current = top(); // save current

	pop();

	T child_top;

	if (!is_empty()) {
		retval = revert(child_top, level + 1, maxLevel);
	}
	else {
		childTop = current;
		return (maxLevel < level);
	}

	if (level >= maxLevel) {
		push(current);
		childTop = child_top;
	}
	else {
		/** don't change this part of stack */
		push(child_top);
		childTop = current;
	}

	return retval;
}

template <typename T>
void SimpleStack<T> :: revertUsingStackSz()
{
	int steps = std :: stack<T> :: size() / 2;
	for (int i = 0; i < steps; i++) {
		int change_pos = std :: stack<T> :: size() - i - 1;
		revertLevel(i, change_pos - i);
	}
}

template <typename T>
void SimpleStack<T> :: revertLevel(int steps, int dstSteps)
{
	T value = top();

	pop();

	if (!steps) {
		change(dstSteps - 1, value);
	}
	else {
		revertLevel(steps - 1, dstSteps);
	}

	push(value);
}

template <typename T>
void SimpleStack<T> :: change(int steps, T & value)
{
	T v = top();
	pop();

	if (!steps) {
		push(value);
		value = v;
	}
	else {
		change(steps - 1, value);
		push(v);
	}
}

} /* namespace conq_stack */

#endif /* STACK_WRAPPER_ */
