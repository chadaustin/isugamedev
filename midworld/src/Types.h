/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_TYPES_H
#define MW_TYPES_H

namespace mw {

#ifdef _MSC_VER

  typedef          __int64 i64;
  typedef unsigned __int64 u64;

#else

  typedef          long long i64;
  typedef unsigned long long u64;


#endif

}

#endif
