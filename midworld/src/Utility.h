/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_UTILITY_H
#define MW_UTILITY_H


namespace mw
{

   inline bool isPowerOfTwo(int i)
   {
      return (i & (i - 1)) == 0;
   }

}


#endif
