#ifndef REFPTR_TEST_H
#define REFPTR_TEST_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <phui/RefCounted.h>
#include <phui/RefPtr.h>

class RefPtrTest : public CppUnit::TestCase
{
   CPPUNIT_TEST_SUITE( RefPtrTest );
   CPPUNIT_TEST( testConstructor );
   CPPUNIT_TEST( testCopyConstructor );
   CPPUNIT_TEST( testDestructor );
   CPPUNIT_TEST( testGet );
   CPPUNIT_TEST( testAssignmentPtr );
   CPPUNIT_TEST( testAssignmentRefPtr );
   CPPUNIT_TEST( testDereference );
   CPPUNIT_TEST( testMemberAccess );
   CPPUNIT_TEST( testCastBool );
   CPPUNIT_TEST( testEquality );
   CPPUNIT_TEST( testEqualityPtr );
   CPPUNIT_TEST_SUITE_END();

public:
   void testConstructor();
   void testCopyConstructor();
   void testDestructor();
   void testGet();
   void testAssignmentPtr();
   void testAssignmentRefPtr();
   void testDereference();
   void testMemberAccess();
   void testCastBool();
   void testEquality();
   void testEqualityPtr();
};

#endif
