#ifndef REFOBJ_H_INCLUDED
#define REFOBJ_H_INCLUDED

#include <stdlib.h> //for NULL
#include <assert.h>

//: A reference counted object that will delete itself when it determines that
//  it is no longer being used anywhere in the application.
class RefObj
{
public:
   //: Initializes the reference count to zero.
   RefObj()
      : mRefCount(0)
   {
   }

#ifndef NDEBUG
   //: When debugging is enabled, assert that there are no references to the
   //  object that's being destroyed.
   virtual ~RefObj()
   {
      assert(mRefCount == 0 &&
             "Destroying an object that still has references");
   }
#endif

   //: Notifies this object that the calling object has a reference to this
   //  object and is using it. The reference count is incremented. Note that all
   //  calls to ref() must be later followed with a call to unref().
   void ref()
   {
      mRefCount++;
   }

   //: Notifies this object that the calling object has released its reference
   //  to this object and no longer needs it. The reference count is
   //  decremented. If the count reaches zero, this object is automagically
   //  deleted.
   void unref()
   {
      assert(mRefCount > 0 && "tried to unref an object with no references");
      if (--mRefCount == 0) {
         delete this;
      }
   }

private:
   int mRefCount;
};

//: A smart/safe pointer that automatically handles reference counting for you.
template <class obj_t>
class safe_ptr
{
public:
   //: Creates a smart pointer pointing to the given object. Defaults to
   //  pointing to NULL if no object is given.
   safe_ptr(obj_t *ptr = NULL)
      : mPtr(ptr)
   {
      if (mPtr) {
         mPtr->ref();
      }
   }

   //: Creates a copy of the given smart pointer
   safe_ptr(const safe_ptr<obj_t>& ptr)
      : mPtr(ptr.mPtr)
   {
      if (mPtr) {
         mPtr->ref();
      }
   }

   //: Destructor that releases its reference to the object it points to.
   ~safe_ptr()
   {
      if (mPtr) {
         mPtr->unref();
      }
   }

   //: Points this pointer to a new object (possibly NULL)
   safe_ptr& operator=(obj_t *ptr)
   {
      if (mPtr) {
         mPtr->unref();
      }
      mPtr = ptr;
      if (mPtr) {
         mPtr->ref();
      }
      return *this;
   }

   //: Points this pointer to a new smart pointer (possibly NULL)
   safe_ptr& operator=(const safe_ptr &ptr)
   {
      return *this = ptr.mPtr;
   }

   //: Dereferencing the smart pointer is equivalent to dereferencing the normal
   //  pointer of the object we have stored.
   obj_t& operator*() const
   {
      return *mPtr;
   }

   //: The member access operator is overloaded to act in a transparent manner
   //  to allow access to the members of the real object.
   obj_t* operator->() const
   {
      return mPtr;
   }

   //: Allow correct determination of the address of the pointer. Since this is
   //  a pointer to the internal pointer, TAKE CARE NOT TO MODIFY THE RETURNED
   //  VALUE.
   obj_t** operator&()
   {
      return &mPtr;
   }

   //: Transparently allow conversion to the object type.
   operator obj_t*() const
   {
      return mPtr;
   }

   //: Transparently allow conversion to the const object type.
   operator const obj_t*() const
   {
      return mPtr;
   }

   //: Allow the smart pointer to be used in boolean tests for NULL.
   operator bool() const
   {
      return mPtr != NULL;
   }
   
private:
   obj_t *mPtr;
};

#endif // ! REFOBJ_H_INCLUDED
