/*
 * \file queue.h
 * \brief Queue utils
 *
 * \author boussole
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stack/stack_wrapper.h>

namespace conq_queue
{

/**
 * \interface QueueInterface
 * \brief Interface of queue is used in tasks
 * \tparam T Type of queue units
 */
template <typename T>
class QueueInterface
{
public:
	/**
	 * \brief Constructor of object
	 */
	QueueInterface() { }

	/**
	 * \brief Destructor of object
	 */
	virtual ~QueueInterface() {}

	/**
	 * \brief Read first value from queue
	 * \tparam T Type of value
	 * \return Value
	 */
	virtual T & top() const = 0;

	/**
	 * \brief Put value to queue
	 * \param[in] v Value
	 * \tparam T Type of value
	 */
	virtual void enqueue(const T & v) = 0;

	/**
	 * \brief Remove value from queue
	 * \return Value
	 */
	virtual void dequeue() = 0;

	/**
	 * \brief Check queue for empty
	 * \return Result of check
	 */
	virtual bool is_empty() const = 0;

	/**
	 * \brief Minimal value (for task test only)
	 */
	virtual const T & min() const = 0;
};

/**
 * \class QueueThroughStackImpl queue.h "queue/queue.h"
 */
template <typename T>
class QueueThroughStackImpl : public QueueInterface<T>
{
public:
	/**
	 * \brief Constructor of object
	 */
	QueueThroughStackImpl() { std :: cout << __PRETTY_FUNCTION__ << std :: endl; }

	/**
	 * \brief Destructor of object
	 */
	~QueueThroughStackImpl() {}

	/**
	 * \brief Read first value from queue
	 * \tparam T Type of value
	 * \return Value
	 */
	T & top() const {
		assert(!is_empty());
		return _s.top();
	}

	/**
	 * \brief Put value to queue
	 * \param[in] v Value
	 * \tparam T Type of value
	 */
	void enqueue(const T & v) {
		put_bottom(v);
	}

	/**
	 * \brief Remove value from queue
	 * \return Value
	 */
	void dequeue() {
		_s.pop();
	}

	/**
	 * \brief Check queue for empty
	 * \return Result of check
	 */
	bool is_empty() const {
		return _s.is_empty();
	}

	/**
	 * \brief Minimal value (for task test only)
	 */
	const T & min() const
	{
		static const T stub = T();
//#warning "Not implemented"
		return stub;
	}

private:
	mutable conq_stack :: SimpleStack<T> _s;

	/**
	 * \brief Put element to bottom
	 */
	void put_bottom(const T & v) {
		if (!_s.is_empty()) {
			T top = _s.top();
			_s.pop();
			put_bottom(v);
			_s.push(top);
		} else {
			_s.push(v);
		}
	}
};

/**
 * \class QueueThrow2Stacks queue.h "queue/queue.h"
 */
template <typename T>
class QueueThrough2StacksImpl : public QueueInterface<T>
{
public:
	/**
	 * \brief Constructor of object
	 */
	QueueThrough2StacksImpl() { std :: cout << __PRETTY_FUNCTION__ << std :: endl; }

	/**
	 * \brief Destructor of object
	 */
	virtual ~QueueThrough2StacksImpl() {}

	/**
	 * \brief Read first value from queue
	 * \tparam T Type of value
	 * \return Value
	 */
	T & top() const {
		assert(!is_empty());

		refactoring();

		return _out.top().first;
	}

	/**
	 * \brief Put value to queue
	 * \param[in] v Value
	 * \tparam T Type of value
	 */
	void enqueue(const T & v) {
		T * min = _in.is_empty() ? nullptr : _in.top().second;
		_in.push(std :: pair<T, T*>(v, min));
		if (!min) {
			_in.top().second = &_in.top().first;
		} else {
			_in.top().second = const_cast<T*>(&std :: min(*min, _in.top().first));
		}
	}

	/**
	 * \brief Remove value from queue
	 * \return Value
	 */
	void dequeue() {
		assert(!is_empty());

		refactoring();

		_out.pop();
	}

	/**
	 * \brief Check queue for empty
	 * \return Result of check
	 */
	bool is_empty() const {
		return _in.is_empty() && _out.is_empty();
	}

	/**
	 * \brief Minimal value (for task test only)
	 */
	const T & min() const {
		static const T stub = T();

		if (!_in.is_empty() && !_out.is_empty())
			return std :: min(*_in.top().second, *_out.top().second);
		else if (!_in.is_empty())
			return *_in.top().second;
		else if (!_out.is_empty())
			return *_out.top().second;

		return stub;
	}

private:
	/**
	 * \brief Fill out OUT stack if it is possible
	 */
	void refactoring() const {
		if (_out.is_empty()) {
			while (!_in.is_empty()) {
				T * min = _out.is_empty() ? nullptr : _out.top().second;
				_out.push(_in.top());
				_in.pop();
				if (!min)
					_out.top().second = &_out.top().first;
				else
					_out.top().second = const_cast<T*>(&std :: min(*min, _out.top().first));
			}
		}
	}

	mutable conq_stack :: SimpleStack<std :: pair<T, T*> > _in;
	mutable conq_stack :: SimpleStack<std :: pair<T, T*> > _out;
};

template <typename T>
class QueueThroughStdQueue
{
public:
	/**
	 * \brief Constructor of object
	 */
	QueueThroughStdQueue() { std :: cout << __PRETTY_FUNCTION__ << std :: endl; }

	/**
	 * \brief Destructor of object
	 */
	virtual ~QueueThroughStdQueue() {}

	/**
	 * \brief Read first value from queue
	 * \tparam T Type of value
	 * \return Value
	 */
	T & top() const {
		return _q.front();
	}

	/**
	 * \brief Put value to queue
	 * \param[in] v Value
	 * \tparam T Type of value
	 */
	void enqueue(const T & v) {
		_q.push(v);
	}

	/**
	 * \brief Remove value from queue
	 * \return Value
	 */
	void dequeue() {
		assert(!is_empty());
		_q.pop();
	}

	/**
	 * \brief Check queue for empty
	 * \return Result of check
	 */
	bool is_empty() const {
		return _q.empty();
	}

private:
	mutable std :: queue<T> _q;
};

template <typename T, template <typename> class Impl/*, ThreadStrategy*/>
class Queue : public Impl<T>
{
public:

	/**
	 * \brief Contructor of object
	 */
	Queue() {}

	/**
	 * \brief Destructor of object
	 */
	~Queue() {}
};

} /* namespace conq_queue */

#endif /* QUEUE_H_ */
