// func added by bscott

#ifndef SMART_PTR_DYNCAST_ADDON_TO_BOOST_
#define SMART_PTR_DYNCAST_ADDON_TO_BOOST_


namespace boost
{

//  we need the ability to do downcasting for polymorphic objects whose pointers
//  are being shared. This code was pulled off the boost mailing list. See
//  http://groups.yahoo.com/group/boost/message/12019
template<typename T, typename U>
inline shared_ptr<T>& sp_dynamic_cast( const shared_ptr<U>& a )
{
   if ( dynamic_cast<T *>(a.get()) ) {
      return *( shared_ptr<T>* )&a;
   }
   return shared_ptr<T>(0);
}

}

#endif
