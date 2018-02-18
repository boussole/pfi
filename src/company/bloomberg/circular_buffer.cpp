#include <stdexcept>
#include <iostream>
#include <memory>

// https://en.wikipedia.org/wiki/Circular_buffer
// https://www.embedded.com/electronics-blogs/embedded-round-table/4419407/The-ring-buffer
/* NOTE: not memory optimized */
template <typename T>
class CircularBuffer {
	CircularBuffer() : _mem(nullptr), _head(nullptr), _tail(nullptr), _capacity(0), _size(0) {}
public:
	CircularBuffer(size_t capacity) :
		_mem(nullptr), _head(nullptr), _tail(nullptr), _first(nullptr), _last(nullptr),
		_capacity(capacity), _size(0)
	{
		if (_capacity == 0)
			throw std::invalid_argument(__PRETTY_FUNCTION__);

		_mem = new T*[_capacity]();
		_head = _mem;
		_tail = _mem + _capacity;
		_first = _last = _head;
	}

	~CircularBuffer()
	{
		while (_head != _tail) {
			if (*_head)
				delete *_head;
			++_head;
		}

		delete []_mem;
	}

	void push_front(T &&rhs)
	{
		decrement(_first);
		if (*_first)
			delete *_first;
		*_first = new T(rhs);

		if (!full())
			++_size;
		else
			_last = _first;
	}

	void push_back(T &&rhs)
	{
		if (*_last)
			delete *_last;

		*_last = new T(rhs);
		increment(_last);

		if (!full())
			++_size;
		else
			_first = _last;
	}

	void pop_front()
	{
		if (empty())
			return;

		if (*_first) {
			delete *_first;
			*_first = nullptr;
		}

		increment(_first);
		--_size;

		if (empty())
			_first = _last = _head;
	}

	void pop_back()
	{
		if (empty())
			return;

		decrement(_last);
		if (_last) {
			delete *_last;
			*_last = nullptr;
		}

		--_size;

		if (empty())
			_first = _last = _head;
	}

	bool full()
	{
		return _size == _capacity;
	}

	bool empty()
	{
		return _size == 0;
	}

	T &operator[](size_t index)
	{
		if (index >= _size)
			throw std::out_of_range(__PRETTY_FUNCTION__);

		T *pos = *add(_first, index);

		return *pos;
	}

	/* debug only */
	void debug_internals()
	{
#ifdef _CIRCULAR_BUFFER_DEBUG
		for (size_t i = 0; i < _capacity; ++i) {
			if (_mem[i] == nullptr) {
				std::cout << "(" << _mem + i << ") nullptr" << " | ";
			} else {
				std::cout << "(" << _mem[i] << ") " << *_mem[i] << " | ";
			}
		}
		std::cout << std::endl;
		if (*_first)
			std::cout << "first (" << *_first << ") = " << *(*_first) << std::endl;
		else
			std::cout << "first (" << *_first << ") = nullptr" << std::endl;

		if (*_last)
			std::cout << "last (" << *_last << ") = " << *(*_last) << std::endl;
		else
			std::cout << "last (" << *_last << ") = nullptr" << std::endl;
#endif
	}

private:
	void increment(T **&p) const
	{
		if (++p == _tail)
			p = _head;
	}

	void decrement(T **&p) const
	{
		if (p == _head)
			p = _last;
		--p;
	}

	T** add(T **p, size_t index) const
	{
		T **pos = p + index;
		if (pos >= _tail) {
			pos = _head + (pos - _tail);
		}

		return pos;
	}

	T **_mem, **_head, **_tail, **_first, **_last;
	size_t _capacity, _size;
};


/* using the same test example from boost::circular_buffer page
 * http://www.boost.org/doc/libs/1_39_0/libs/circular_buffer/doc/circular_buffer.html
 */
int main(int /*argc*/, char* /*argv*/[]) {

	// Create a circular buffer with a capacity for 3 integers.
	CircularBuffer<int> cb(3);

	cb.debug_internals();

	// Insert some elements into the buffer.
	cb.push_back(1);
	cb.push_back(2);
	cb.push_back(3);
	cb.debug_internals();

	int a = cb[0];  // a == 1
	int b = cb[1];  // b == 2
	int c = cb[2];  // c == 3
	std::cout << a << " " << b << " " << c << std::endl;

	// The buffer is full now, pushing subsequent
	// elements will overwrite the front-most elements.

	cb.push_back(4);  // Overwrite 1 with 4.
	cb.push_back(5);  // Overwrite 2 with 5.
	cb.debug_internals();

	// The buffer now contains 3, 4 and 5.

	a = cb[0];  // a == 3
	b = cb[1];  // b == 4
	c = cb[2];  // c == 5
	std::cout << a << " " << b << " " << c << std::endl;

	// Elements can be popped from either the front or the back.

	cb.pop_back();  // 5 is removed.
	cb.debug_internals();
	cb.pop_front(); // 3 is removed.
	cb.debug_internals();

	int d = cb[0];  // d == 4
	std::cout << d << std::endl;

	return 0;
}


