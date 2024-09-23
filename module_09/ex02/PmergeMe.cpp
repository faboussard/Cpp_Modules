#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <limits>
#include <vector>
#include <algorithm>
#include "PmergeMe.hpp"

/*============================================================================*/
/*       Constructors 			   	                                        */
/*============================================================================*/

PmergeMe::PmergeMe() : _vector(), _s(), _pend(), _deq(), _straggler(0), _sortedPairs()
{}

PmergeMe::PmergeMe(int argc, char **argv) : _straggler(0), _sortedPairs()
{
	if (argc < 3)
	{
		std::cerr << "usage: ./PmergeMe int1 int2 ... " << std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i < argc; i++)
	{
		char *end;
		errno = 0;
		unsigned long value = std::strtoul(argv[i], &end, 10);
		if (end == argv[i] || *end != '\0' || errno == ERANGE)
		{
			std::cerr << "Invalid argument: " << argv[i] << std::endl;
			exit(EXIT_FAILURE);
		}
		if (value > std::numeric_limits<unsigned int>::max())
		{
			std::cerr << "value out of range"  << argv[i] << std::endl;
			exit(EXIT_FAILURE);
		}

		unsigned int unsignedValue = static_cast<unsigned int>(value);
		_vector.push_back(unsignedValue);
		_deq.push_back(unsignedValue);
	}
}

PmergeMe::PmergeMe(const PmergeMe &rhs) : _vector(rhs._vector), _s(rhs._s),
										  _pend(rhs._pend), _deq(rhs._deq), _straggler(rhs._straggler), _sortedPairs(rhs._sortedPairs)
{}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this != &rhs)
	{
		_vector = rhs._vector;
		_deq = rhs._deq;
		_straggler = rhs._straggler;
		_sortedPairs = rhs._sortedPairs;
		_s = rhs._s;
		_pend = rhs._pend;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

/*============================================================================*/
/*       Getter Functions                                                    */
/*============================================================================*/

const vector &PmergeMe::getMyVector() const
{
	return _vector;
}

const deque &PmergeMe::getMyDeque() const
{
	return _deq;
}

unsigned int PmergeMe::getMyStraggler() const
{
	return _straggler;
}

const sortedPairs &PmergeMe::getSortedPairs() const {
	return _sortedPairs;
}

vector &PmergeMe::getMyVector() {
	return _vector;
}

deque &PmergeMe::getMyDeque() {
	return _deq;
}

unsigned int PmergeMe::getMyStraggler() {
	return _straggler;
}

sortedPairs &PmergeMe::getSortedPairs() {
	return _sortedPairs;
}

/*============================================================================*/
/*       Member Functions                                                    */
/*============================================================================*/

void PmergeMe::createStraggler()
{
	if (getMyVector().size() % 2 != 0)
	{
		_straggler = _vector.back();
		_vector.pop_back();
	}
}

void PmergeMe::makeSortedPairs()
{
	size_t size = _vector.size();

	for (size_t i = 0; i < size; i += 2)
	{
		if (i + 1 < size)
		{
			if (_vector[i] < _vector[i + 1])
				_sortedPairs.push_back(std::make_pair(_vector[i], _vector[i + 1]));
			else
				_sortedPairs.push_back(std::make_pair(_vector[i + 1], _vector[i]));
		}
	}
	// TO DELETE
	std::cout << "Sorted pairs:" << std::endl;
	for (size_t j = 0; j < _sortedPairs.size(); ++j) {
		std::cout << "(" << _sortedPairs[j].first << ", " << _sortedPairs[j].second << ")" << std::endl;
	}
}

void PmergeMe::largestValues()
{
	for (size_t i = 0; i < _sortedPairs.size(); ++i)
	{
		_s.push_back(_sortedPairs[i].second);
	}
}

void PmergeMe::smallestValues()
{
	for (size_t i = 0; i < _sortedPairs.size(); ++i)
	{
		_pend.push_back(_sortedPairs[i].first);
	}
}

vector PmergeMe::generateJacobsthal() {
	vector jacobsthal;
	jacobsthal.push_back(0); // Start with J(0) = 0 (not used)
	jacobsthal.push_back(1); // J(1) = 1

	for (unsigned int i = 2; i < _s.size(); ++i) {
		unsigned int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		jacobsthal.push_back(next);
	}

	return jacobsthal;
}

// Function to insert elements using binary search
void PmergeMe::insertUsingBinarySearch(std::vector<unsigned int>& S, unsigned int element) {
	std::vector<unsigned int>::iterator it = std::lower_bound(S.begin(), S.end(), element);
	S.insert(it, element);
}

void PmergeMe::insertAndMerge() {
	// Generate Jacobsthal numbers based on the size of _s
	vector jacobsthal = generateJacobsthal();

	// Insert the first element (paired with the smallest in _s) into _pend
	if (!_s.empty()) {
		insertUsingBinarySearch(_pend, _s[0]);
	}

	// Insert the remaining elements based on Jacobsthal numbers
	for (size_t i = 1; i < _s.size(); ++i) {
		insertUsingBinarySearch(_pend, _s[i]);
	}

	_vector = _pend;

	// Output the sorted array 'pend' TO DELETE
	std::cout << "Sorted array after insertions:" << std::endl;
	for (size_t j = 0; j < _pend.size(); ++j) {
		std::cout << _pend[j] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::insertStraggler()
{
	if (_straggler != 0)
	{
		vector::iterator it = std::lower_bound(_vector.begin(), _vector.end(), _straggler);
		_vector.insert(it, _straggler);
	}
}

void PmergeMe::sortVector()
{
	createStraggler();
	makeSortedPairs();
	largestValues();
	smallestValues();
	insertAndMerge();
	insertStraggler();
}

/*============================================================================*/
/*       Class overload                                                       */
/*============================================================================*/

std::ostream &operator<<(std::ostream &os, const PmergeMe &pmergeMe)
{
	os << pmergeMe.getMyVector() << std::endl;
//	os << pmergeMe.getMyDeque() << std::endl;

	return os;
}

std::ostream &operator<<(std::ostream &os, const vector &vec)
{
	for (vector::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		os << *it << " ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const deque &deque)
{
	for (deque::const_iterator it = deque.begin(); it != deque.end(); it++)
	{
		os << *it << " ";
	}
	return os;
}
