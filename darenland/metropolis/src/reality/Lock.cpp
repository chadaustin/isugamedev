#include "Lock.h"

namespace metro
{
	Lock::Lock()
	{
		//no one has a static lock
		mStaticLockID = 0;
	}

	Lock::~Lock()
	{
	}

	//if there is any form of lock on the hex, reject this request
	//TODO: should static requests take precedence over the queue?
	Lock::RequestSuccess Lock::requestStaticLock ( EntityID id )
	{
		if(getLockState() == NO_LOCK)
		{
			mStaticLockID = id;
			return FILLED_REQUEST;
		}
		else
		{
			return REJECTED_REQUEST;
		}
	}

	//if an entity is passing through a hex, but intends to leave it, a temporary
	//lock request is queued with the hex. Returns filled, queued, or rejected
	//request success value. A tempLock request may fail if the wait is too long.
	Lock::RequestSuccess Lock::requestTempLock   ( EntityID id )
	{
		std::vector< std::pair< EntityID, bool > >::iterator itr;
		for( itr = mTempLockQueue.begin(); itr != mTempLockQueue.end(); ++itr )
		{
			//if the id was found in the queue already
			if( itr->first == id )
			{
				//refresh the request
			 	itr->second=true;

				//if at the top of the queue, the request is as good as filled
				if( itr == mTempLockQueue.begin() )
				{
					return FILLED_REQUEST;
				}
				else
				{
					return QUEUED_REQUEST;
				}
			}
		}
		//the id was not found, add it to the end
		mTempLockQueue.push_back( std::pair< EntityID, bool >(id,true) );
	}

	//what lock state is the hex in?
	Lock::LockState Lock::getLockState()const
	{
		//static lock takes state precedence over the queue for sure
		if( mStaticLockID != 0 )
		{
			return STATIC_LOCK;
		}

		if( mTempLockQueue.size() > 0 )
		{
			return TEMP_LOCK;
		}

		return NO_LOCK;
	}

	//how long is the wait for a temp lock?
	unsigned int Lock::getTempQueueLengh()const
	{
		return mTempLockQueue.size();
	}

	//go through the queue and delete things that are old
	//anything new should be made old
	void Lock::clearOld()
	{
		std::vector< std::pair< EntityID, bool > >::iterator itr;
		for( itr = mTempLockQueue.begin(); itr != mTempLockQueue.end(); )
		{
			//if the request is fresh, mark it for deletion
			if( itr->second )
			{
				itr->second=false;
				++itr;
				continue;
			}
			//delete old requests right away
			else
			{
				mTempLockQueue.erase(itr);
				//don't increment itr, erase does that anyway
				continue;
			}
		}
	}
}

