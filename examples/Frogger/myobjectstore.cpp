#include "MyObjectStore.h"
#include "MyObject.h"
#include <stdlib.h>

MyObjectStore::MyObjectStore()
{
	///////////////////////////////
	//Lets initialize all variables
	///////////////////////////////
	head = NULL;
	tail = NULL;
	ObjectCount = 0;
	current = NULL;
}

MyObjectStore::~MyObjectStore()
{
	ObjectList* cursor, *thenext;

	cursor = head;

	while (cursor != NULL)
	{
		thenext = cursor->next;
		delete cursor;
		cursor = thenext;
	}
}
	
int MyObjectStore::Insert(MyObject* the_object)
{
	ObjectList* temp = NULL;
	int i;

	if (!(Find(the_object, temp, i)))
	{
		/////////////////////////////////////
		// if no items in list create one and
		// set head and tail pointers to it
		/////////////////////////////////////
		if (head == NULL)
		{
			head = new ObjectList;
			head->next = NULL;
			head->Object = the_object;
			tail = head;
		}
		//////////////////////////////
		// Just add new one to end
		//////////////////////////////
		else
		{
			tail->next = new ObjectList;
			tail = tail->next;
			tail->next = NULL;
			tail->Object = the_object;
		}
		///////////////////////////////////////
		// Be sure to keep track of ObjectCount
		///////////////////////////////////////
		ObjectCount++;
	}
	return ObjectCount;
}
	
bool MyObjectStore::Remove(MyObject* the_object)
{
	ObjectList* Previous = NULL, *cursor = NULL;
	int index;

	if (Find(the_object, Previous, index))
	{
		//////////////////////////////////////////
		//if Previous equals NULL we know that we
		//are removing the head 
		//////////////////////////////////////////
		if (Previous == NULL)
		{
			/////////////////////////////////////
			//if head equals tail we are removing
			//last item from list
			/////////////////////////////////////
			if (head == tail)
			{
				delete head;
				head = NULL;
				tail = NULL;
			}
			//////////////////////////////////////////
			//there is at least one more item in list
			//////////////////////////////////////////
			else
			{
				cursor = head;
				head = head->next;
				delete cursor;
			}
		}
		//////////////////////////////////////////////
		//we are removing some other item besides head
		//////////////////////////////////////////////
		else
		{
			//if we remove tail update it
			if(Previous->next->next == NULL)
				tail = Previous;
			cursor = Previous->next;
			Previous->next = Previous->next->next;
			delete cursor;
		}
		ObjectCount--;
		return true;
	}
return false;
}

bool MyObjectStore::Find(MyObject* the_object, ObjectList* previous, int& index)
{
	ObjectList* prev = NULL;
	ObjectList* cursor;
	int i = 0;
	index = i;
	cursor = head;
		
	//////////////////////////////////////////////////////////
	//If we don't find item and break out of loop return false
	//////////////////////////////////////////////////////////
	while (cursor != NULL)
	{	
		//////////////////////////////////////////////////////
		//We found the object return true and previous pointer
		//////////////////////////////////////////////////////
		if (cursor->Object == the_object)
		{
			previous = prev;
			return true;
		}
		//////////////////////
		//Lets keep on looking
		//////////////////////
		else
		{
			prev = cursor;
			cursor = cursor->next;
			i++;
			index = i;
		}
	}
	return false;
}
	
int MyObjectStore::Index(MyObject* the_object)
{   
	/////////////////////////////////////
	//This function is very easy just let
	//Find do all the work
	/////////////////////////////////////
	ObjectList* temp = NULL;
	int index;
	if (!(Find(the_object, temp, index)))
		index = -1;
	return index;
}

MyObject* MyObjectStore::GetbyIndex(int index)
{
	ObjectList* cursor;
	int i = 0;
	cursor = head;

	////////////////////////////////////////////////
	//If we get to end of list before we reach index
	//return NULL
	////////////////////////////////////////////////
	while (cursor != NULL)
	{
		if (i != index)
			cursor = cursor->next;
		else
			return cursor->Object;
	}

	return NULL;
}

bool MyObjectStore::ResetCursor()
{
	if (head != NULL)
	{
		current = head;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}


void MyObjectStore::GetCurrentObject(MyObject*& theObject)
{
	MyObject* temp = NULL;

	///////////////////////////////////
	//If we are off the end return NULL
	///////////////////////////////////
	if (current != NULL)
	{
		temp = current->Object;
		current = current->next;
	}
	theObject = temp;
}

int MyObjectStore::GetNumObjects()
{
	return ObjectCount;
}