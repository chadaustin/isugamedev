///metropolis-converters.h -- Converters for data types in Metropolis

#ifndef _METRO_METROPOLIS_CONVERTERS_H_
#define _METRO_METROPOLIS_CONVERTERS_H_

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <gmtl/Point.h>

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
}
#endif
