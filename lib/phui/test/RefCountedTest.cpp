#include "RefCountedTest.h"
using namespace phui;

CPPUNIT_TEST_SUITE_REGISTRATION( RefCountedTest );

void
RefCountedTest::testConstructor()
{
   // Constructor should init ref count to zero
   RefCounted obj;
   CPPUNIT_ASSERT(obj.getRefCount() == 0);
}

void
RefCountedTest::testRef()
{
   /**
    * This specialized RefCounted object takes a pointer to a boolean upon
    * construction that it will set to true when it is destroyed.
    */
   class MyObj : public RefCounted
   {
   public:
      MyObj(bool* destroyed)
         : mDestroyed(destroyed)
      {}

      ~MyObj()
      {
         *mDestroyed = true;
      }
   private:
      bool* mDestroyed;
   };

   // init our destroyed boolean
   bool destroyed = false;

   //ref should always increment the ref count
   MyObj *obj = new MyObj(&destroyed);
   obj->ref();
   CPPUNIT_ASSERT(obj->getRefCount() == 1);
   obj->ref();
   CPPUNIT_ASSERT(obj->getRefCount() == 2);
   obj->ref();
   CPPUNIT_ASSERT(obj->getRefCount() == 3);

   //unref sohuld always decrement the ref count
   obj->unref();
   CPPUNIT_ASSERT(obj->getRefCount() == 2);
   obj->unref();
   CPPUNIT_ASSERT(obj->getRefCount() == 1);

   //last unref should delete the object
   //XXX how the hell do i test for this??
   obj->unref();
   CPPUNIT_ASSERT(destroyed == true);
}
