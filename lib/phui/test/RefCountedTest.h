#ifndef REFCOUNTED_TEST_H
#define REFCOUNTED_TEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <phui/RefCounted.h>

#ifdef NDEBUG
#  error NDEBUG must not be when building the RefCountedTest.
#endif

class RefCountedTest : public CppUnit::TestCase
{
   CPPUNIT_TEST_SUITE( RefCountedTest );
   CPPUNIT_TEST( testConstructor );
   CPPUNIT_TEST( testRef );
   CPPUNIT_TEST_SUITE_END();

public:
   /// Test constructor initialization.
   void testConstructor();

   /// Make sure ref/unref work.
   void testRef();
};

#endif
