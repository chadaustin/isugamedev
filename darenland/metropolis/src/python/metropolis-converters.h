///metropolis-converters.h -- Converters for data types in Metropolis

#ifndef _METRO_METROPOLIS_CONVERTERS_H_
#define _METRO_METROPOLIS_CONVERTERS_H_

#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>
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
	namespace bp = boost::python;
	/**
	 * This will convert a gmtl::Point*i to a Python tuple.
	 */
	template <unsigned SIZE>
	struct pointi_to_tuple
	{
		static PyObject* convert(gmtl::Point<int, SIZE> const& p)
		{
			PyObject* result = PyTuple_New(2);
			for (int i = 0; i < SIZE; i++)
			{
				PyTuple_SetItem(result, i, PyInt_FromLong(p[i]));
			}
			return result;
		}
	};

	/**
	 * This takes a Python tuple and converts it to a gmtl::Point
	 */
	template <typename DATA_TYPE, unsigned SIZE>
	struct tuple_to_point
	{
		static gmtl::Point<DATA_TYPE, SIZE>& execute(object& src)
		{
			bp::tuple& t = bp::extract<bp::tuple&>(src);
			//assert(t.check());
			boost::shared_ptr< gmtl::Point<DATA_TYPE, SIZE> > point( new gmtl::Point<DATA_TYPE, SIZE>());
			for (unsigned int i = 0; i < SIZE; ++i)
			{
				(*point)[i] = t[i];
			}
			return *point;
		}
	};
	
	template <typename DATA_TYPE, unsigned SIZE>
	struct tuple_to_vec
	{
		static gmtl::Vec<DATA_TYPE, SIZE>& execute(object& src)
		{
			tuple& t = extract<tuple&>(src);
			//assert(t.check());
			boost::shared_ptr< gmtl::Vec<DATA_TYPE, SIZE> > point( new gmtl::Vec<DATA_TYPE, SIZE>());
			for (unsigned int i = 0; i < SIZE; ++i)
			{
				(*point)[i] = t[i];
			}
			return *point;
		}
	};
}
#endif
