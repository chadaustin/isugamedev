/* 
This class is a store class for MyObject pointers.  
*/
#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

#include "MyObject.h"

struct ObjectList
{
	MyObject* Object;
	ObjectList* next;
};

#endif

#ifndef __MYOBJECTSTORE_H__
#define __MYOBJECTSTORE_H__

#include "MyObject.h"

class MyObjectStore
{
public:
	
	//MyObjectStore()
	//Pre: None
	//Post: a new MyObjectStore is created
	MyObjectStore();

	~MyObjectStore();
	
	//Insert()
	//Pre: A new MyObject has been created on heap
	//Post: Inserts given object pointer
	int Insert(MyObject* the_object);

	//Remove()
	//Pre: None
	//Post: if given object is in store removes it and 
	//		returns true, otherwise returns false
	bool Remove(MyObject* the_object);

	//Index()
	//Pre: None
	//Post: If object in store returns location index
	//		otherwise returns -1
	int Index(MyObject* the_object);

	//GetbyIndex()
	//Pre: None
	//Post: If index is associated with object returns 
	//		pointer to that object otherwise false
	MyObject* GetbyIndex(int index);

	//ResetCursor()
	//Pre: None
	//Post: Resets cursor to head of store
	bool ResetCursor();

	//GetObject()
	//Pre: None
	//Post: Returns object pointer cursor is current pointing at
	//		and moves cursor to next object.  If cursor off end
	//		return null
	void GetCurrentObject(MyObject*& theObject);

	//GetNumObjects()
	//Pre: None
	//Post: Returns number of pointers currently in store.
	int GetNumObjects();

private:

	ObjectList* head,*tail;
	int ObjectCount;
	ObjectList* current;

	bool Find(MyObject* the_object, ObjectList* previous, int& index);
};
#endif