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
