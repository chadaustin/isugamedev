/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_LOCKABLE_H
#define THREAD_LOCKABLE_H


namespace thread {

   class Lockable {
   public:
      virtual ~Lockable() { }

      virtual void lock() = 0;
      virtual void unlock() = 0;
   };

} // namespace thread


#endif // THREAD_LOCKABLE_H
