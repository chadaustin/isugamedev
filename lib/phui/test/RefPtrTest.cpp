#include "RefPtrTest.h"
using namespace phui;

CPPUNIT_TEST_SUITE_REGISTRATION( RefPtrTest );

void
RefPtrTest::testConstructor()
{
   // Constructor should init to null
   RefPtr<RefCounted> p1;
   CPPUNIT_ASSERT(p1.get() == 0);

   // Constructor should ref the object
   RefCounted* obj = new RefCounted();
   RefPtr<RefCounted> p2(obj);
   CPPUNIT_ASSERT(p2.get() == obj);
   CPPUNIT_ASSERT(p2.get()->getRefCount() == 1);
}

void
RefPtrTest::testCopyConstructor()
{
   // Copy null
   RefPtr<RefCounted> nullptr;
   RefPtr<RefCounted> p1(nullptr);
   CPPUNIT_ASSERT(p1.get() == 0);

   // Copy value
   RefPtr<RefCounted> p2(new RefCounted());
   RefPtr<RefCounted> p3(p2);
   CPPUNIT_ASSERT(p3.get() == p2.get());
   CPPUNIT_ASSERT(p3.get()->getRefCount() == 2);
}

void
RefPtrTest::testDestructor()
{
   RefPtr<RefCounted> p1(new RefCounted());

   // Create the second RefPtr in another scope so it will get destroyed now now
   {
      RefPtr<RefCounted> p2(p1);
      CPPUNIT_ASSERT(p2.get()->getRefCount() == 2);
   }
   CPPUNIT_ASSERT(p1.get()->getRefCount() == 1);
}

void
RefPtrTest::testGet()
{
   // non-const get
   RefCounted* obj = new RefCounted();
   RefPtr<RefCounted> p1(obj);
   CPPUNIT_ASSERT(p1.get() == obj);

   // const get
   const RefPtr<RefCounted> p2(obj);
   CPPUNIT_ASSERT(p2.get() == obj);
}

void
RefPtrTest::testAssignmentPtr()
{
   // Assignment to null
   RefPtr<RefCounted> p1 = 0;
   CPPUNIT_ASSERT(p1.get() == 0);

   // Assignment to a value
   RefCounted* obj = new RefCounted(); // don't delete, p2 will do it for us
   RefPtr<RefCounted> p2;
   p2 = obj;
   CPPUNIT_ASSERT(p2.get() == obj);
}

void
RefPtrTest::testAssignmentRefPtr()
{
   // Assignment to null
   RefPtr<RefCounted> nullptr;
   RefPtr<RefCounted> p1 = nullptr;
   CPPUNIT_ASSERT(p1.get() == 0);

   // Assignment to a value
   RefPtr<RefCounted> p2(new RefCounted());
   RefPtr<RefCounted> p3(p2);
   CPPUNIT_ASSERT(p3.get() == p2.get());
}

class MyObj : public RefCounted
{
public:
   MyObj()
      : value(0xDEADBEEF)
   {}

   int value;
};

void
RefPtrTest::testDereference()
{
   RefPtr<MyObj> p1(new MyObj());
   MyObj& obj = *p1;
   CPPUNIT_ASSERT(p1.get()->getRefCount() == 1);
   CPPUNIT_ASSERT(obj.value == (int)0xDEADBEEF);
}

void
RefPtrTest::testMemberAccess()
{
   RefPtr<RefCounted> p1(new RefCounted());
   CPPUNIT_ASSERT(p1->getRefCount() == 1);
}

void
RefPtrTest::testCastBool()
{
   // null
   RefPtr<RefCounted> nullptr;
   CPPUNIT_ASSERT((bool)nullptr == false);

   // non-null
   RefPtr<RefCounted> p1(new RefCounted());
   CPPUNIT_ASSERT((bool)p1 == true);
}

void
RefPtrTest::testEquality()
{
   RefPtr<RefCounted> nullptr;
   RefCounted *obj1 = new RefCounted();
   RefCounted *obj2 = new RefCounted();
   RefPtr<RefCounted> p1(obj1);
   RefPtr<RefCounted> p2(obj2);

   // null to null
   CPPUNIT_ASSERT(nullptr == 0);
   CPPUNIT_ASSERT(! (nullptr != 0));
   CPPUNIT_ASSERT(0 == nullptr);
   CPPUNIT_ASSERT(! (0 != nullptr));

   // value to null
   CPPUNIT_ASSERT(! (p1 == 0));
   CPPUNIT_ASSERT(p1 != 0);
   CPPUNIT_ASSERT(! (obj1 == nullptr));
   CPPUNIT_ASSERT(obj1 != nullptr);

   // null to value
   CPPUNIT_ASSERT(! (nullptr == obj1));
   CPPUNIT_ASSERT(nullptr != obj1);
   CPPUNIT_ASSERT(! (0 == p1));
   CPPUNIT_ASSERT(0 != p1);

   // value to value
   CPPUNIT_ASSERT(p1 == obj1);
   CPPUNIT_ASSERT(! (p1 != obj1));
   CPPUNIT_ASSERT(obj1 == obj1);
   CPPUNIT_ASSERT(! (obj1 != obj1));

   CPPUNIT_ASSERT(p2 == obj2);
   CPPUNIT_ASSERT(!(p2 != obj2));
   CPPUNIT_ASSERT(obj2 == p2);
   CPPUNIT_ASSERT(!(obj2 != p2));

   CPPUNIT_ASSERT(p1 != obj2);
   CPPUNIT_ASSERT(! (p1 == obj2));
   CPPUNIT_ASSERT(obj1 != p2);
   CPPUNIT_ASSERT(! (obj1 == p2));

   CPPUNIT_ASSERT(p2 != obj1);
   CPPUNIT_ASSERT(! (p2 == obj1));
   CPPUNIT_ASSERT(obj2 != p1);
   CPPUNIT_ASSERT(! (obj2 == p1));
}

void
RefPtrTest::testEqualityPtr()
{
   RefPtr<RefCounted> nullptr;
   RefPtr<RefCounted> p1(new RefCounted());
   RefPtr<RefCounted> p2(new RefCounted());

   // null to null
   CPPUNIT_ASSERT(nullptr == nullptr);
   CPPUNIT_ASSERT(! (nullptr != nullptr));

   // value to null
   CPPUNIT_ASSERT(! (p1 == nullptr));
   CPPUNIT_ASSERT(p1 != nullptr);

   // null to value
   CPPUNIT_ASSERT(! (nullptr == p1));
   CPPUNIT_ASSERT(nullptr != p1);

   // value to value
   CPPUNIT_ASSERT(p1 == p1);
   CPPUNIT_ASSERT(! (p1 != p1));

   CPPUNIT_ASSERT(p2 == p2);
   CPPUNIT_ASSERT(!(p2 != p2));

   CPPUNIT_ASSERT(p1 != p2);
   CPPUNIT_ASSERT(! (p1 == p2));

   CPPUNIT_ASSERT(p2 != p1);
   CPPUNIT_ASSERT(! (p2 == p1));
}
