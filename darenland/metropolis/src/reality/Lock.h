#ifndef _METRO_LOCK_H_
#define _METRO_LOCK_H_

#include "Includes.h"
#include "EntityID.h"

namespace metro
{
	class Lock
	{
	public:
		enum LockState
		{
			TEMP_LOCK,
			STATIC_LOCK,
			NO_LOCK
		};

		enum RequestSuccess
		{
			FILLED_REQUEST,
			QUEUED_REQUEST,
			REJECTED_REQUEST
		};

		//bitwise state for the passability of all the edges on the hex
		char edgeState;

		Lock();
		~Lock();

		//if an entity wishes to enter and remain in a hex, it requests a static lock
		//on that hex. A success value of 'filled' or 'rejected' is returned.
		RequestSuccess requestStaticLock ( EntityID id );

		//if an entity is passing through a hex, but intends to leave it, a temporary
		//lock request is queued with the hex. Returns filled, queued, or rejected
		//request success value. A tempLock request may fail if the wait is too long.
		RequestSuccess requestTempLock   ( EntityID id );

		//what lock state is the hex in?
		LockState getLockState()const;

		//how long is the wait for a temp lock?
		unsigned int getTempQueueLengh()const;

		//clears old items from the temp lock queue
		void clearOld();

	private:
		//who has the static lock?
		EntityID mStaticLockID;

		//temp lock request queue: < who? , is request fresh? >
		std::vector< std::pair< EntityID, bool > > mTempLockQueue;
		//not a queue because queues suck and I want random access.
	};
}

#endif
