#ifndef REFOBJTEST_H_INCLUDED
#define REFOBJTEST_H_INCLUDED

#include <iostream>

#include <TestCase.h>
#include <TestSuite.h>
#include <TestCaller.h>

#include "RefObj.h"

/*****************************************************************
 tests out the functionality expected of RefObj
*******************************************************************/

namespace tankTest
{

class RefObjTest : public TestCase
{
public:
   typedef safe_ptr<RefObj> objptr;

public:
   RefObjTest ( const std::string &name ) : TestCase (name)
   {
   }


   virtual ~RefObjTest()
   {
   }

   //: Constructor initialization OK
   void constructorTest()
   {
      //Constructor should init refcount to zero
      RefObj *obj = new RefObj();
      assertTest( obj->getRefCount() == 0 );
      delete obj;
   }

   //: Make sure ref/unref work
   void refTest()
   {
      //ref should always increment the ref count
      RefObj *obj = new RefObj();
      obj->ref();
      assertTest( obj->getRefCount() == 1 );
      obj->ref();
      assertTest( obj->getRefCount() == 2 );
      obj->ref();
      assertTest( obj->getRefCount() == 3 );

      //unref sohuld always decrement the ref count
      obj->unref();
      assertTest( obj->getRefCount() == 2 );
      obj->unref();
      assertTest( obj->getRefCount() == 1 );
      
      //last unref should delete the object
      //XXX how the hell do i test for this??
      obj->unref();
   }

   //: Safe ptr constructor / assignment works OK
   void safePtrAssignmentTest()
   {
      //default constructor inits to null
      objptr nullptr;
      assertTest( nullptr == NULL );

      //constructor w/ arg should ref the arg
      objptr p1( new RefObj() );
      assertTest( p1.get() != NULL );
      assertTest( p1.get()->getRefCount() == 1 );

      //additional ptr to p1 should inc ref count
      objptr *ptr = new objptr( p1 );
      assertTest( (*ptr)->getRefCount() == 2 );
      assertTest( (*ptr) == p1.get() );

      //destruction of second ptr to p1 should decrement the ref count
      delete ptr;
      ptr = NULL;
      assertTest( p1.get()->getRefCount() == 1 );

      //assignment operators
      objptr p2 = p1;
      assertTest( p2.get()->getRefCount() == 2 );
      assertTest( p1.get() == p2.get() );
      p2 = new RefObj();
      assertTest( p2.get()->getRefCount() == 1 );
      assertTest( p2.get()->getRefCount() == 1 );
      assertTest( p1.get() != p2.get() );
      
      //assignment to NULL
      objptr p3 = p1;
      assertTest( p3.get()->getRefCount() == 2 );
      assertTest( p3.get() == p1.get() );
      p3 = NULL;
      assertTest( p1.get()->getRefCount() == 1 );
      assertTest( p3.get() == NULL );
   }

   void safePtrCastTest()
   {
      objptr p1 = new RefObj();
      // non-const cast
      RefObj* obj = p1;
      assertTest( obj == p1.get() );
      obj = NULL;

      // const cast
      const RefObj* cobj = p1;
      assertTest( cobj = p1.get() );
      cobj = NULL;
   }

   void safePtrOperatorsTest()
   {
      //address-of operator
      objptr p1;
      assertTest( (*(&p1)) == 0 );
      p1 = new RefObj();
      assertTest( (*(&p1)) != 0 );

      //dereferencing
      RefObj &obj = *p1;
      assertTest( obj.getRefCount() == 1 );

      //member access operator
      assertTest( p1->getRefCount() == 1 );
   }

   typedef TestCaller<RefObjTest> Caller;
   static Test* suite()
   {
      TestSuite *test_suite = new TestSuite ("RefObjTest");

      test_suite->addTest( new Caller("constructor test", constructorTest) );
      test_suite->addTest( new Caller("ref test", refTest) );
      test_suite->addTest( new Caller("safe pointer assignment test", safePtrAssignmentTest) );
      test_suite->addTest( new Caller("safe pointer cast test", safePtrCastTest) );
      test_suite->addTest( new Caller("safe pointer overloaded operators", safePtrOperatorsTest) );

      return test_suite;
   }
};

}

#endif // ! REFOBJTEST_H_INCLUDED
