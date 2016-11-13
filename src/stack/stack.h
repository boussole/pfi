/*
 * \file stack.h Stack definition and tools
 * \author boussole
 */
#ifndef STACK_H_
#define STACK_H_

#include <queue/queue.h>

namespace conq_stack
{

template <typename T>
class StackInterface
{
public:
	StackInterface() {}

	virtual ~StackInterface() {}

	/**
	 * \brief Read first value from stack
	 * \tparam T Type of value
	 * \return Value
	 */
	virtual T & top() const = 0;

	/**
	 * \brief Put value to stack
	 * \param[in] v Value
	 * \tparam T Type of value
	 */
	virtual void push(const T & v) = 0;

	/**
	 * \brief Remove value from stack
	 * \return Value
	 */
	virtual void pop() = 0;

	/**
	 * \brief Check stack for empty
	 * \return Result of check
	 */
	virtual bool is_empty() const = 0;
};

/**
 * \class StackThrough2QueuesImpl
 * \brief  Implementation of stack using 2 queues
 */
template <typename T>
class StackThrough2QueuesImpl : public StackInterface<T>
{
public:
	StackThrough2QueuesImpl() : _activeQ(0) {}

	virtual ~StackThrough2QueuesImpl() {}

	virtual T & top() const {
		assert(!is_empty());
		return _q[_activeQ].top();
	}

	virtual void push(const T & v) {
		_q[!_activeQ].enqueue(v);
		refactoring();
	}

	virtual void pop() {
		_q[_activeQ].dequeue();
	}

	virtual bool is_empty() const {
		return _q[_activeQ].is_empty();
	}

protected:
	void refactoring() const {
		while (!_q[_activeQ].is_empty()) {
			_q[!_activeQ].enqueue(_q[_activeQ].top());
			_q[_activeQ].dequeue();
		}

		_activeQ = (_activeQ + 1) % 2;
	}

private:
	mutable conq_queue :: Queue<T, conq_queue :: QueueThroughStdQueue> _q[2];
	mutable int _activeQ;
};

template <typename T, template <typename> class Impl>
class Stack : public Impl<T>
{
public:
	Stack() {}
	~Stack() {}
};

} /* namespace conq_stack */

#endif /* STACK_H_ */
