///metropolis-converters.h -- Converters for data types in Metropolis

#ifndef _METRO_METROPOLIS_CONVERTERS_H_
#define _METRO_METROPOLIS_CONVERTERS_H_

#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <boost/python/borrowed.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/lvalue_from_pytype.hpp>
#include <boost/python/module.hpp>
#include <gmtl/Point.h>
#include <cassert>
#include <iostream>

using namespace boost::python;

namespace metro
{
	/**
	 * This is the gmtl::Point2i to python converter.  It will convert a
	 * gmtl::Point2i to python.
	 */
	struct point2i_to_tuple
	{
		static PyObject* convert(gmtl::Point2i const& p)
		{
			PyObject* result = PyTuple_New(2);
			for (int i = 0; i < 2; i++)
			{
				PyTuple_SetItem(result, i, PyInt_FromLong(p[i]));
			}
			return result;
		}
	};

	template <unsigned int SIZE>
	struct tuple_to_pointi
	{
		static gmtl::Point<int, SIZE>& execute(PyObject& src)
		{
			//assert(NULL != src);
			//std::cout << src << std::endl;
			assert(PyTuple_Check(&src));
			assert(SIZE == PyTuple_Size(&src));
			boost::shared_ptr< gmtl::Point<int, SIZE> > point( new gmtl::Point<int, SIZE>());
			for (unsigned int i = 0; i < SIZE; ++i)
			{
				long value = PyInt_AsLong(PyTuple_GET_ITEM(&src, i));
				(*point)[i] = value;
			}
			return *point;
		}
	};
}
#endif
