////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// Copyright (c) 2004 by Peter Kuemmel
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

#ifndef FACTORYGEN_H
#define FACTORYGEN_H

#include "Functor.h"
#include "Factory.h"
#include "Typelist.h"

namespace Loki
{

////////////////////////////////////////////////////////////////////////////////
// class template FunctorImpl
// Specialization for up to 15 parameters
////////////////////////////////////////////////////////////////////////////////

   struct FactoryImplBase{
       typedef EmptyType Parm1;
       typedef EmptyType Parm2;
       typedef EmptyType Parm3;
       typedef EmptyType Parm4;
       typedef EmptyType Parm5;
       typedef EmptyType Parm6;
       typedef EmptyType Parm7;
       typedef EmptyType Parm8;
       typedef EmptyType Parm9;
       typedef EmptyType Parm10;
       typedef EmptyType Parm11;
       typedef EmptyType Parm12;
       typedef EmptyType Parm13;
       typedef EmptyType Parm14;
       typedef EmptyType Parm15;
   };

   template <typename AP, typename Id, typename TList >
   struct FactoryImpl;

   template<typename AP, typename Id>
   struct FactoryImpl<AP, Id, NullType>
       : public FactoryImplBase{
       virtual AP* CreateObject(const Id & id ) = 0;
   };

   template <typename AP, typename Id, typename P1 >
   struct FactoryImpl<AP,Id, TYPELIST_1( P1 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       virtual AP* CreateObject(const Id& id, Parm1 ) = 0;
   };

   template<typename AP, typename Id, typename P1,typename P2 >
   struct FactoryImpl<AP, Id, TYPELIST_2( P1,P2 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2 ) = 0;
   };

   template<typename AP, typename Id, typename P1,typename P2,typename P3 >
   struct FactoryImpl<AP, Id, TYPELIST_3( P1,P2,P3 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       virtual AP* CreateObject(const Id& id, Parm1, Parm2, Parm3 ) = 0;
   };

   template<typename AP, typename Id, typename P1,typename P2,typename P3,typename P4 >
   struct FactoryImpl<AP, Id, TYPELIST_4( P1,P2,P3,P4 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4 ) = 0;
   };

   template<typename AP, typename Id,
               typename P1,typename P2,typename P3,typename P4,typename P5 >
   struct FactoryImpl<AP, Id, TYPELIST_5( P1,P2,P3,P4,P5 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5 ) = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6>
   struct FactoryImpl<AP, Id, TYPELIST_6(P1,P2,P3,P4,P5,P6 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6 )
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7>
   struct FactoryImpl<AP, Id, TYPELIST_7(P1,P2,P3,P4,P5,P6,P7 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7 )
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8>
   struct FactoryImpl<AP, Id, TYPELIST_8(P1,P2,P3,P4,P5,P6,P7,P8 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9>
   struct FactoryImpl<AP, Id, TYPELIST_9(P1,P2,P3,P4,P5,P6,P7,P8,P9 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10>
   struct FactoryImpl<AP, Id, TYPELIST_10(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9,Parm10)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10,
               typename P11>
   struct FactoryImpl<AP, Id, TYPELIST_11(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       typedef typename TypeTraits<P11>::ParameterType Parm11;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9,Parm10,
                                              Parm11)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10,
               typename P11,typename P12>
   struct FactoryImpl<AP, Id, TYPELIST_12(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       typedef typename TypeTraits<P11>::ParameterType Parm11;
       typedef typename TypeTraits<P12>::ParameterType Parm12;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9,Parm10,
                                              Parm11,Parm12)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10,
               typename P11,typename P12,typename P13>
   struct FactoryImpl<AP, Id, TYPELIST_13(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       typedef typename TypeTraits<P11>::ParameterType Parm11;
       typedef typename TypeTraits<P12>::ParameterType Parm12;
       typedef typename TypeTraits<P13>::ParameterType Parm13;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9,Parm10,
                                              Parm11,Parm12,Parm13)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10,
               typename P11,typename P12,typename P13,typename P14>
   struct FactoryImpl<AP, Id, TYPELIST_14(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       typedef typename TypeTraits<P11>::ParameterType Parm11;
       typedef typename TypeTraits<P12>::ParameterType Parm12;
       typedef typename TypeTraits<P13>::ParameterType Parm13;
       typedef typename TypeTraits<P14>::ParameterType Parm14;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm8,Parm10,
                                              Parm11,Parm12,Parm13,Parm14)
                                              = 0;
   };

   template<typename AP, typename Id,
               typename  P1,typename  P2,typename  P3,typename  P4,typename  P5,
               typename  P6,typename  P7,typename  P8,typename  P9,typename P10,
               typename P11,typename P12,typename P13,typename P14,typename P15 >
   struct FactoryImpl<AP, Id, TYPELIST_15( P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15 )>
       : public FactoryImplBase{
       typedef typename TypeTraits<P1>::ParameterType Parm1;
       typedef typename TypeTraits<P2>::ParameterType Parm2;
       typedef typename TypeTraits<P3>::ParameterType Parm3;
       typedef typename TypeTraits<P4>::ParameterType Parm4;
       typedef typename TypeTraits<P5>::ParameterType Parm5;
       typedef typename TypeTraits<P6>::ParameterType Parm6;
       typedef typename TypeTraits<P7>::ParameterType Parm7;
       typedef typename TypeTraits<P8>::ParameterType Parm8;
       typedef typename TypeTraits<P9>::ParameterType Parm9;
       typedef typename TypeTraits<P10>::ParameterType Parm10;
       typedef typename TypeTraits<P11>::ParameterType Parm11;
       typedef typename TypeTraits<P12>::ParameterType Parm12;
       typedef typename TypeTraits<P13>::ParameterType Parm13;
       typedef typename TypeTraits<P14>::ParameterType Parm14;
       typedef typename TypeTraits<P15>::ParameterType Parm15;
       virtual AP* CreateObject(const Id& id, Parm1,Parm2,Parm3,Parm4,Parm5,
                                              Parm6,Parm7,Parm8,Parm9,Parm10,
                                              Parm11,Parm12,Parm13,Parm14,Parm15 )
                                              = 0;
   };

////////////////////////////////////////////////////////////////////////////////
// class template FactoryGen
// Implements a generic object factory
////////////////////////////////////////////////////////////////////////////////

   template
   <
       class AbstractProduct,
       typename IdentifierType,
       typename CreatorParmTList = NullType,
       template<typename, class> class FactoryErrorPolicy = DefaultFactoryError
   >
   class FactoryGen : public FactoryErrorPolicy<IdentifierType, AbstractProduct>
   {
   public:
       typedef Functor<AbstractProduct*, CreatorParmTList> ProductCreator;
       typedef FactoryImpl< AbstractProduct, IdentifierType, CreatorParmTList > Impl;
       typedef typename Impl::Parm1 Parm1;
       typedef typename Impl::Parm2 Parm2;
       typedef typename Impl::Parm3 Parm3;
       typedef typename Impl::Parm4 Parm4;
       typedef typename Impl::Parm5 Parm5;
       typedef typename Impl::Parm6 Parm6;
       typedef typename Impl::Parm7 Parm7;
       typedef typename Impl::Parm8 Parm8;
       typedef typename Impl::Parm9 Parm9;
       typedef typename Impl::Parm10 Parm10;
       typedef typename Impl::Parm11 Parm11;
       typedef typename Impl::Parm12 Parm12;
       typedef typename Impl::Parm13 Parm13;
       typedef typename Impl::Parm14 Parm14;
       typedef typename Impl::Parm15 Parm15;

       bool Register(const IdentifierType& id, ProductCreator creator)
       {
           return associations_.insert(
           typename IdToProductMap::value_type(id, creator)).second;
       }

       template <class PtrObj, typename CreaFn>
       bool Register(const IdentifierType& id, const PtrObj& p, CreaFn fn)
       {
           ProductCreator creator( p, fn );
           return associations_.insert(typename IdToProductMap::value_type(id, creator)).second;
       }

       bool Unregister(const IdentifierType& id)
       {
           return associations_.erase(id) == 1;
       }

       AbstractProduct* CreateObject(const IdentifierType& id){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
           Parm1 p1){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
           Parm1 p1,Parm2 p2){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1 p1,Parm2 p2, Parm3 p3){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1 p1,Parm2 p2, Parm3 p3,Parm4 p4){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1 p1,Parm2 p2, Parm3 p3,Parm4 p4,Parm5 p5){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9 );
           return this->OnUnknownType(id);
       }
       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10,
               Parm11 p11 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10,
               Parm11 p11,Parm12 p12 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10,
               Parm11 p11,Parm12 p12, Parm13 p13 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10,
               Parm11 p11,Parm12 p12, Parm13 p13,Parm14 p14 ){
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14 );
           return this->OnUnknownType(id);
       }

       AbstractProduct* CreateObject(const IdentifierType& id,
               Parm1  p1 ,Parm2  p2 , Parm3  p3 ,Parm4  p4 ,Parm5  p5 ,
               Parm6  p6 ,Parm7  p7 , Parm8  p8 ,Parm9  p9 ,Parm10 p10,
               Parm11 p11,Parm12 p12, Parm13 p13,Parm14 p14,Parm15 p15 )
       {
           typename IdToProductMap::iterator i = associations_.find(id);
           if (i != associations_.end())
               return (i->second)( p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15 );
           return this->OnUnknownType(id);
       }

   private:
       typedef AssocVector<IdentifierType, ProductCreator> IdToProductMap;
       IdToProductMap associations_;
   };

} //namspace Loki

/*
Using FactoryGen:

#include "FactoryGen.h"

using Loki::FactoryGen;
using Loki::SingletonHolder;

////////////////////////////////////////////
// Object to create: Product
// Constructor with 0 and 2 arguments
////////////////////////////////////////////

class AbstractProduct{};

class Product : public AbstractProduct{
public:
   Product(){}
   Product( int, int ){}
};

///////////////////////////////////////////////////////////
// Factory for creation a Product object without parameters
///////////////////////////////////////////////////////////

typedef SingletonHolder
<
   FactoryGen< AbstractProduct, int >
>
PFactoryNull;

/////////////////////////////////////////////////////////////
// Factory for creation a Product object with 2 parameters
/////////////////////////////////////////////////////////////

typedef SingletonHolder
<
   FactoryGen< AbstractProduct, int, TYPELIST_2( int, int ) >
>
PFactoryGen;

////////////////////////////////////////////////////
// Creator functions, different names and overloaded
////////////////////////////////////////////////////

Product* createProductOver()               { return new Product;     }
Product* createProductOver( int a, int b ) { return new Product( a, b ); }
Product* createProductNull()               { return new Product;     }
Product* createProductParm( int a, int b ) { return new Product( a, b ); }

///////////////////////////////////////////////////
// Creator functions are polymorphic member functions
///////////////////////////////////////////////////

class AbstractCreator{
public:
   virtual AbstractProduct* create() = 0;
   virtual AbstractProduct* createParm( int, int ) = 0;
};
class Creator : public AbstractCreator{
public:
   Creator(){};
   AbstractProduct* create()                   {return new Product;       }
   AbstractProduct* createParm( int a, int b ) {return new Product( a,b );}
};

///////////////////////////////////////////////////////////
// Creator functions are member functions of a template class
///////////////////////////////////////////////////////////

template< class T>
class CreatorT{
public:
   CreatorT(){};
   T* create()                   {return new T;       }
   T* createParm( int a, int b ) {return new T( a,b );}
};

///////////////////////////////////////
// Register creator functions
// No additional typdefs are necessary!
//////////////////////////////////////

AbstractCreator* c = new Creator;
CreatorT<Product> cT;

bool const ok1 = PFactoryNull::Instance().Register( 1, createProductNull );
bool const ok2 = PFactoryNull::Instance().Register( 2, (Product*(*)()) createProductOver );
bool const ok3 = PFactoryNull::Instance().Register( 3, c, &AbstractCreator::create );
bool const ok4 = PFactoryNull::Instance().Register( 4, &cT, &CreatorT<Product>::create );

bool const ok5 = PFactoryGen::Instance().Register( 1, createProductParm );
bool const ok6 = PFactoryGen::Instance().Register( 2, (Product*(*)(int,int))createProductOver );
bool const ok7 = PFactoryGen::Instance().Register( 3, c, &AbstractCreator::createParm );
bool const ok8 = PFactoryGen::Instance().Register( 4, &cT, &CreatorT<Product>::createParm );

void testFactory(){

   AbstractProduct* pNull  = PFactoryNull::Instance().CreateObject( 1 );
   AbstractProduct* pOver  = PFactoryNull::Instance().CreateObject( 2 );
   AbstractProduct* pClass = PFactoryNull::Instance().CreateObject( 3 );
   AbstractProduct* pT     = PFactoryNull::Instance().CreateObject( 4 );

   AbstractProduct* pP      = PFactoryGen::Instance().CreateObject( 1, 64,64 );
   AbstractProduct* pPOver  = PFactoryGen::Instance().CreateObject( 2, 64,64 );
   AbstractProduct* pPClass = PFactoryGen::Instance().CreateObject( 3, 64,64 );
   AbstractProduct* pPT     = PFactoryGen::Instance().CreateObject( 4, 64,64 );
}
*/

#endif
