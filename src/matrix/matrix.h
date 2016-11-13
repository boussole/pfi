/**
 * \file    matrix.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <common/common.h>

namespace conq_matrix {

enum class RotationAngle { _90, _180, _270 };

typedef boost::geometry::model::d2::point_xy<int> point_xy;
typedef boost::geometry::model::d2::point_xy<float> fpoint_xy;


/************************************************************
                   Forward declaration
*************************************************************/
template <typename T, typename Function>
void forEachElementInSubMatrix(const boost :: numeric :: ublas :: matrix<T> & m,
                               size_t startRow, size_t rowSz,
                               size_t startCol, size_t colSz, Function fn);

static inline
void averagePoint(const point_xy & p1, const point_xy & p2, point_xy & aver);

/************************************************************
 * \class SubMatrixCoord Position and length inside original matrix
 ***********************************************************/
class SubMatrix {
public:
	SubMatrix() {
		reset();
	}

	template <typename T>
	void print(const boost :: numeric :: ublas :: matrix<T> & m) {
		std :: cout << "submatrix = [" << _rLen << ", " << _cLen << "], start point = [" << _row << ", " << _col << "].\n";
		size_t col_num = 0;
		forEachElementInSubMatrix(m, _row, _rLen, _col, _cLen, boost :: bind<void>([](size_t & colNum, size_t colLen, T element)->void {
			if (++colNum == colLen) {
				std :: cout << element << std :: endl;
				colNum = 0;
			}
			else
				std :: cout << element << "\t";
		}, col_num, _cLen, _1));
	}

	bool isValid() {
		return (_row >= 0);
	}

	void set(size_t row, size_t rowLen, size_t col, size_t colLen) {
		_row = row; _col = col; _rLen = rowLen; _cLen = colLen;
	}

	void reset() {
		_row = -1; _col = -1; _rLen = -1; _cLen = -1;
	}
private:
	size_t _row;
	size_t _col;
	size_t _rLen;
	size_t _cLen;
};

/************************************************************
 * \class Coord Description of submatrix
 ************************************************************/
class Coord {
public:
	Coord() {
		_first.x(-1);
		_first.y(-1);
		_last.x(-1);
		_last.y(-1);
	}

	Coord(int leftRow, int leftCol, int rightRow, int rightCol) {
		_first.x(leftRow);
		_first.y(leftCol);
		_last.x(rightRow);
		_last.y(rightCol);
	}

	Coord(const Coord & rhs) {
		_first = rhs._first;
		_last = rhs._last;
	}

	void buildQuad(const Coord & rhs) {
		int offset = std :: min(rhs._last.x() - rhs._first.x(), rhs._last.y() - rhs._first.y());
		_first = rhs._first;
		_last.x(_first.x() + offset);
		_last.y(_first.y() + offset);
	}

	void average(point_xy & aver) {
		averagePoint(_first, _last, aver);
	}

	void setFirst(const point_xy & val) {
		_first = val;
	}

	void setLast(const point_xy & val) {
		_last = val;
	}

	const point_xy & first() const {
		return _first;
	}

	const point_xy & last() const {
		return _last;
	}

	void saveFirst(point_xy & val) const {
		val = _first;
	}

	void saveLast(point_xy & val) const {
		val = _last;
	}

	template <typename T>
	bool inBound(const boost :: numeric :: ublas :: matrix<T> & m) const {
		return (_first.x() >= 0) && (_first.y() >= 0) &&
		       (static_cast<size_t>(_first.x()) < m.size1()) && (static_cast<size_t>(_first.y()) < m.size2()) &&
			   (_last.x() >= 0) && (_last.y() >= 0) &&
			   (static_cast<size_t>(_last.x()) < m.size1()) && (static_cast<size_t>(_last.y()) < m.size2());
	}

	bool isValid() const {
		return (_first.x() <= _last.x()) && (_first.y() <= _last.y());
	}

private:
	point_xy _first;
	point_xy _last;
};

/************************************************************
 * \brief Element access using point_xy
 ************************************************************/
template <typename T>
T & element_xy(boost :: numeric :: ublas :: matrix<T> & m, const point_xy & p)
{
	return m(static_cast<size_t>(p.x()), static_cast<size_t>(p.y()));
}

/************************************************************
 * \brief Average point
 ************************************************************/
static inline
void averagePoint(const point_xy & p1, const point_xy & p2, point_xy & aver)
{
	aver.x((p1.x() + p2.x()) / 2);
	aver.y((p1.y() + p2.y()) / 2);
}

/************************************************************
 * \brief Matrix comparison
 ************************************************************/
template <typename T>
static inline
bool operator==(const boost :: numeric :: ublas :: matrix<T> & left, const boost :: numeric :: ublas :: matrix<T> & right)
{
	BOOST_ASSERT((left.size1() == right.size1()) && (left.size2() == right.size2()));

	for (std :: size_t i = 0; i < left.size1(); i++)
		for (std :: size_t j = 0; j < left.size2(); j++) {
			if (left(i, j) != right(i, j)) {
				return false;
			}
		}

	return true;
}


/************************************************************
 * \brief Missing operator == for point_xy
 ************************************************************/
static inline
bool operator==(const point_xy & left, const point_xy & right)
{
	return (left.x() == right.x()) && (left.y() == right.y());
}

/************************************************************
 * \brief Missing operator != for point_xy
 ************************************************************/
static inline
bool operator!=(const point_xy & left, const point_xy & right)
{
	return !(left == right);
}

/************************************************************
 * \brief Missing operator = for point_xy
 ************************************************************/
template <typename T, typename P>
boost::geometry::model::d2::point_xy<T> & copyPointXY(boost::geometry::model::d2::point_xy<T> & dst, const boost::geometry::model::d2::point_xy<P> & src)
{
	dst.x(src.x());
	dst.y(src.y());

	return dst;
}

/************************************************************
 * \brief Fill out matrix order values
 ************************************************************/
template <typename T>
void fillOutStub(boost :: numeric :: ublas :: matrix<T> & m)
{
	int stub_val = 1;
	for (std :: size_t i = 0; i < m.size1(); i++) {
		for (std :: size_t j = 0; j < m.size2(); j++) {
			m(i, j) = stub_val++;
		}
	}
}

/************************************************************
 * \brief Fill out matrix random values
 ************************************************************/
template <typename T>
void fillOutRand(boost :: numeric :: ublas :: matrix<T> & m, int max)
{
	srand(time(NULL));

	for (std :: size_t i = 0; i < m.size1(); i++) {
		for (std :: size_t j = 0; j < m.size2(); j++) {
			m(i, j) = (rand() - (RAND_MAX / 2)) % max;
		}
	}
}

/************************************************************
 * \brief Print matrix in math view
 ************************************************************/
template <typename T>
void print(boost :: numeric :: ublas :: matrix<T> & m)
{
	for (std :: size_t i = 0; i < m.size1(); i++) {
		for (std :: size_t j = 0; j < m.size2(); j++) {
			std :: cout << m(i, j) << "\t";
		}
		std :: cout << std :: endl;
	}
}

/************************************************************
 * \brief Sort matrix by rows and cols
 ************************************************************/
template <typename T>
void sortRowAndCol(boost :: numeric :: ublas :: matrix<T> & m)
{
	/** by rows */
	for (std :: size_t i = 0; i < m.size1(); i++) {
		std :: size_t j = 0;
		bool xchg = false;
		while (j < m.size2()) {
			for (std :: size_t new_j = j + 1; new_j < m.size2(); new_j++) {
				if (m(i, new_j) < (m(i, j))) {
					std :: swap(m(i, new_j), (m(i, j)));
					xchg = true;
					break;
				}
			}

			xchg ? (xchg = false) : (j++);
		}
	}

	/** by cols */
	for (std :: size_t j = 0; j < m.size2(); j++) {
		std :: size_t i = 0;
		bool xchg = false;
		while (i < m.size1()) {
			for (std :: size_t new_i = i + 1; new_i < m.size1(); new_i++) {
				if (m(new_i, j) < (m(i, j))) {
					std :: swap(m(new_i, j), (m(i, j)));
					xchg = true;
					break;
				}
			}

			xchg ? (xchg = false) : (i++);
		}
	}
}

/************************************************************
 * \brief   #238: Find number in matrix which has been sorted by
 *                rows and cols
 *
 * \return  Value has been found => true, value hasn't been found => false
 * \warning Not optimal, can be faster
 ************************************************************/
template <typename T>
bool findValueInHVSortMatrix(boost :: numeric :: ublas :: matrix<T> & m, const T & value, point_xy & pos)
{
	int compare_num = 0;
	for (std :: size_t i = 0; (i < m.size1()) && (m(i, 0) <= value); i++) {
		/** skip row which doesn't contain value */
		if (m(i, m.size2() - 1) < value) continue;
		for (std :: size_t j = 0; (j < m.size2()) && (m(i, j) <= value); j++) {
			compare_num++;
			if (m(i, j) == value) {
				pos.x(i); pos.y(j);
				std :: cout << "compare num = " << compare_num << std :: endl;
				return true;
			}
		}
	}

	std :: cout << "compare num = " << compare_num << std :: endl;

	return false;
}

/************************************************************
 * \brief Matrix edge rotation to 90, hard code alrorithm
 ************************************************************/
template <typename T>
void rotateEdge_90(boost :: numeric :: ublas :: matrix<T> & m, int edge)
{
	point_xy up(edge, edge);
	point_xy right(edge, m.size1() - edge - 1);
	point_xy bottom(m.size1() - edge - 1, m.size2() - edge - 1);
	point_xy left(m.size2() - edge - 1, edge);

	for (int steps = m.size2() - edge - 1; up.y() < steps; up.y(up.y() + 1)) {
		std :: swap(m(up.x(), up.y()), m(right.x(), right.y()));
		right.x(right.x() + 1);
		std :: swap(m(bottom.x(), bottom.y()), m(up.x(), up.y()));
		bottom.y(bottom.y() - 1);
		std :: swap(m(left.x(), left.y()), m(up.x(), up.y()));
		left.x(left.x() - 1);
	}
}

/************************************************************
 * \brief #40
 * \details Matrix rotation to 90 degrees, hard code algorithm
 ************************************************************/
template <typename T>
void rotate_90(boost :: numeric :: ublas :: matrix<T> & m)
{
	BOOST_ASSERT(m.size1() == m.size2());

	/** for half matrix only */
	for (std :: size_t edge = 0; edge < m.size1() / 2; edge++) {
		rotateEdge_90(m, edge);
	}
}

/************************************************************
 * brief #40
 * \details Matrix rotation to 90 | 180 | 270 degrees using affinis transformation.
 ***********************************************************/
template <typename T>
void rotate_f(boost :: numeric :: ublas :: matrix<T> & m, RotationAngle angle)
{
	BOOST_ASSERT(m.size1() == m.size2());

	int cos_fi = 0, sin_fi = 0;

	switch (angle) {
	case RotationAngle :: _90: cos_fi = 0; sin_fi = -1; break; /** -90 == 270 */
	case RotationAngle :: _180: cos_fi = -1; sin_fi = 0; break;
	case RotationAngle :: _270: cos_fi = 1; sin_fi = 0; break; /** 270 == -90 */
	}

	float offset = (float)(m.size1() - 1) / 2;

	auto move_fn = [&](point_xy & p, fpoint_xy & fp) -> fpoint_xy& {
		fp.x(p.x() - offset);
		fp.y(p.y() - offset);
		return fp;
	};

	auto rotate_fn = [&](fpoint_xy & fp) -> fpoint_xy& {
		fpoint_xy tmp(fp.x() * cos_fi - fp.y() * sin_fi, fp.x() * sin_fi + fp.y() * cos_fi);
		return copyPointXY(fp, tmp);
	};

	auto move_back_fn = [&](fpoint_xy & fp, point_xy & p) -> point_xy& {
		p.x(fp.x() + offset);
		p.y(fp.y() + offset);
		return p;
	};

	for (std :: size_t x = 0; x < m.size1() / 2; x++)
	for (std :: size_t y = x; y < m.size2() - x - 1; y++) {
		point_xy xy(x, y), next_xy(x, y);
		fpoint_xy tmp;
		do {
			move_back_fn(rotate_fn(move_fn(next_xy, tmp)), next_xy);
			std :: swap(m(next_xy.x(), next_xy.y()), m(xy.x(), xy.y()));
		} while(xy != next_xy);
	}
}

/***********************************************************
 * brief #40
 * \details Matrix rotation to 90 | 180 | 270 degrees using affinis transformation.
 * This version has difference from rotate_f, it doesn't use float variables.
 * Instead of them it uses scale transformation
 ***********************************************************/
template <typename T>
void rotate(boost :: numeric :: ublas :: matrix<T> & m, RotationAngle angle)
{
	BOOST_ASSERT(m.size1() == m.size2());

	int cos_fi = 0, sin_fi = 0;

	switch (angle) {
	case RotationAngle :: _90: cos_fi = 0; sin_fi = -1; break; /** -90 == 270 */
	case RotationAngle :: _180: cos_fi = -1; sin_fi = 0; break;
	case RotationAngle :: _270: cos_fi = 1; sin_fi = 0; break; /** 270 == -90 */
	}

	int offset = (m.size1() - 1) / 2;
	int scale = 1;

	if (((m.size1() - 1) % 2)) {
		scale++;
		offset = (m.size1() - 1) * scale / 2;
	}

	auto move_fn = [&](point_xy & p, point_xy & fp) -> point_xy& {
		fp.x(p.x() * scale - offset);
		fp.y(p.y() * scale - offset);
		return fp;
	};

	auto rotate_fn = [&](point_xy & fp) -> point_xy& {
		point_xy tmp(fp.x() * cos_fi - fp.y() * sin_fi, fp.x() * sin_fi + fp.y() * cos_fi);
		return copyPointXY(fp, tmp);
	};

	auto move_back_fn = [&](point_xy & fp, point_xy & p) -> point_xy& {
		p.x((fp.x() + offset) / scale);
		p.y((fp.y() + offset) / scale);
		return p;
	};

	for (std :: size_t x = 0; x < m.size1() / 2; x++)
	for (std :: size_t y = x; y < m.size2() - x - 1; y++) {
		point_xy xy(x, y), next_xy(x, y);
		point_xy tmp;
		do {
			move_back_fn(rotate_fn(move_fn(next_xy, tmp)), next_xy);
			std :: swap(m(next_xy.x(), next_xy.y()), m(xy.x(), xy.y()));
		} while(xy != next_xy);
	}
}

/************************************************************
 * \brief Pass throw sub matrix edge
 *
 * \param [in]  m   Quad matrix
 * \param [in]  sub Submatrix number of quad matrix
 * \param [out] fn  Callback for each element
 ************************************************************/
template <typename T, typename Function>
void forEachSubMatrixEdgeElement(boost :: numeric :: ublas :: matrix<T> & m, size_t sub, Function fn)
{
	BOOST_ASSERT(m.size1() == m.size2());

	const int start = sub, finish = m.size1() - sub;

	if (finish <= 0) return;

	/* through up row */
	for (int row = start, col = start; col < finish; col++) {
		fn(m(row, col));
	}

	/* through right col */
	for (int row = start + 1, col = finish - 1; row < finish; row++) {
		fn(m(row, col));
	}

	/* through down row */
	for (int row = finish - 1, col = finish - 2; col >= start; col--) {
		fn(m(row, col));
	}

	/* through left col */
	for (int row = finish - 2, col = start; row > start; row--) {
		fn(m(row, col));
	}
}

/************************************************************
 * \brief       Find submatrix edge in quad matrix with the largest sum
 * \param [out] largestSum - Largest sum of submatrix edge
 * \return      Index of edge
 ***********************************************************/
template <typename T>
int findSubMatrixEdgeWithLargestSum(boost :: numeric :: ublas :: matrix<T> & m, int & largestSum)
{
	BOOST_ASSERT(m.size1() == m.size2());

	if (m.size1() == 0) return -1;

	int sub_matrix = 0;
	largestSum = 0;
	forEachSubMatrixEdgeElement(m, 0, boost :: bind<void>([](int & sum, int element)->void {
		sum += element;
	}, boost :: ref(largestSum), _1));

	int sub_sum = 0;
	for (std :: size_t sub = 1; sub < m.size1() / 2; sub++, sub_sum = 0) {
		forEachSubMatrixEdgeElement(m, 0, boost :: bind<void>([](int & sum, int element)->void {
			sum += element;
		}, boost :: ref(sub_sum), _1));

		if (sub_sum > largestSum) {
			largestSum = sub_sum;
			sub_matrix = static_cast<int>(sub);
		}
	}

	return sub_matrix;
}

/************************************************************
 * \brief     Pass through each element of submatrix
 * \param [in] m        - Matrix
 * \param [in] startRow - Start row position of submatrix in original matrix
 * \param [in] rowSz    - Size of rows in submatrix
 * \param [in] startCol - Start col position of submatrix in original matrix
 * \param [in] colSz    - Size of cols in submatrix
 * \param [in] fn       - Callback for each matrix element
 ************************************************************/
template <typename T, typename Function>
void forEachElementInSubMatrix(const boost :: numeric :: ublas :: matrix<T> & m,
                               size_t startRow, size_t rowSz,
                               size_t startCol, size_t colSz, Function fn)
{
	size_t rowMax = startRow + rowSz, colMax = startCol + colSz;

	BOOST_ASSERT((startCol < m.size1()) && (startRow < m.size2()));
	BOOST_ASSERT((rowMax <= m.size1()) && (colMax <= m.size2()));

	for (size_t row = startRow; row < rowMax; row++)
		for (size_t col = startCol; col < colMax; col++)
			fn(m(row, col));
}

/************************************************************
 * \brief       Find submatrix in quad matrix with the largest sum
 * \param [out] sm - Coords of submatrix
 * \return      largestSum
 ***********************************************************/
template <typename T>
int findSubMatrixWithLargestSum(boost :: numeric :: ublas :: matrix<T> & m, SubMatrix & sm)
{
	BOOST_ASSERT(m.size1() == m.size2());

	if (m.size1() == 0) return std :: numeric_limits<int> :: min();

	int largest_sum = std :: numeric_limits<int> :: min();

	sm.reset();

	// for each point of matrix
	for (std :: size_t row = 0; row < m.size1(); row++)
		for (std :: size_t col = 0; col < m.size2(); col++) {
			/* for each matrix in point */
			std :: size_t row_max = m.size1() - row, col_max = m.size2() - col;
			for (std :: size_t row_len = 1; row_len <= row_max; row_len++)
				for (std :: size_t col_len = 1; col_len <= col_max; col_len++) {
					int sum = 0;
					forEachElementInSubMatrix(m, row, row_len, col, col_len,
							boost :: bind<void>([](int & sum, int element) {
								sum += element;
							}, boost :: ref(sum), _1));
					if (sum >= largest_sum) {
						largest_sum = sum;
						sm.set(row, row_len, col, col_len);
					}
				}
		}

	return largest_sum;
}

/*************************************************************
 * kthSmallest
 *************************************************************/
template <typename T>
T & findKthSmallestInHVSortMatrix(boost :: numeric :: ublas :: matrix<T> & m, std :: size_t kTh)
{
	--kTh;//< specific task
	assert(kTh > 0 && kTh < m.size1() * m.size2());

	std :: vector<std :: pair<T *, std :: size_t> > next_min;
	for (std :: size_t row = 0; row < m.size1(); ++row)
		next_min.push_back(std :: make_pair(&m(row, 0), 0));

	std :: function<bool(std :: pair<T *, std :: size_t> &, std :: pair<T *, std :: size_t> &)> cmp =
		[](std :: pair<T *, std :: size_t> & lhs, std :: pair<T *, std :: size_t> & rhs)->bool {
			return *lhs.first > *rhs.first;
		}
	;

	std::make_heap(next_min.begin(), next_min.end(), cmp);

	for (std :: size_t k = 0; k < kTh; ++k) {
		T * ptr = next_min.front().first;
		std :: size_t next = next_min.front().second + 1;
		std::pop_heap(next_min.begin(), next_min.end(), cmp); next_min.pop_back();

		if (next < m.size2()) {
			next_min.push_back(std :: make_pair(++ptr, next));
			std :: push_heap(next_min.begin(), next_min.end(), cmp);
		}
	}

	return *next_min.front().first;
}

namespace book {
/************************************************************
 * \brief  #238: Find number in matrix which has been sorted by
 *               rows and cols
 *
 * \return Value has been found => true, value hasn't been found => false
 ************************************************************/
template <typename T>
bool findValueInHVSortMatrix(boost :: numeric :: ublas :: matrix<T> & m, const T & value, point_xy & pos)
{
	int compare_num = 0;
	std :: size_t i = 0;
	int j = m.size2() - 1;
	while ((i < m.size1()) && (j >= 0)) {
		compare_num++;
		if (m(i, j) == value) {
			pos.x(i);
			pos.y(j);
			std :: cout << "compare num = " << compare_num << std :: endl;
			return true;
		}

		(m(i, j) > value) ? j-- : i++;
	}

	std :: cout << "compare num = " << compare_num << std :: endl;

	return false;
}

/*************************************************************
 * \brief  #238: Find number in matrix which has been sorted by
 *               rows and cols, using bisection method
 *
 * \return Value has been found => true, value hasn't been found => false
 *************************************************************/
class findValueInHVSortMatrixBin
{
public:
	template <typename T>
	static bool doIt(boost :: numeric :: ublas :: matrix<T> & m, const T & value, point_xy & pos)
	{
		BOOST_ASSERT(m.size1() && m.size2());

		Coord sub(0, 0, m.size1() - 1, m.size2() - 1);

		return doIt(m, value, sub, pos);
	}

private:
	template <typename T>
	static bool doIt(boost :: numeric :: ublas :: matrix<T> & m, const T & value, const Coord & sub, point_xy & pos)
	{
		if (!sub.inBound(m))
			return false;

		if (element_xy(m, sub.first()) == value) {
			sub.saveFirst(pos);
			return true;
		}
		else if (!sub.isValid()) {
			return false;
		}

		Coord coord;
		coord.buildQuad(sub);

		while (coord.isValid()) {
			point_xy avr;
			coord.average(avr);
			if (element_xy(m, avr) < value) {
				avr.x(avr.x() + 1);
				avr.y(avr.y() + 1);
				coord.setFirst(avr);
			}
			else {
				avr.x(avr.x() - 1);
				avr.y(avr.y() - 1);
				coord.setLast(avr);
			}
		}

		return split(m, value, sub, coord.first(), pos);
	}

	template <typename T>
	static bool split(boost :: numeric :: ublas :: matrix<T> & m,
	                  const T & value, const Coord & sub,
	                  const point_xy & avg, point_xy & pos)
	{
		Coord bottom_left(avg.x(), sub.first().y(), sub.last().x(), avg.y() - 1);
		Coord up_right(sub.first().x(), avg.y(), avg.x() - 1, sub.last().y());

		return doIt(m, value, bottom_left, pos) || doIt(m, value, up_right, pos);
	}
};

} /** namespace book */

/*************************************************************
 * \brief  #63: Find celebrety if it exists
 *
 * \return Celebrety index or -1 if it doesn't exist
 *************************************************************/
int findCelebrety(boost :: numeric :: ublas :: matrix<int> & m, int peopleNum);

} /* namespace conq_matrix */

#endif /* MATRIX_H_ */
