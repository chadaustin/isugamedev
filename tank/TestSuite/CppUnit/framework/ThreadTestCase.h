#ifndef _THREAD_TEST_CASE_H_
#define _THREAD_TEST_CASE_H_

#include <iostream>
#include <string>
#include <TestCase.h>

#include <vpr/Sync/Mutex.h>
#include <vpr/Sync/Guard.h>


class ThreadTestCase : public TestCase 
{
protected:
   struct assertData
   {
      std::string cond_exp;
      long        line_num;
      std::string file_name;
   };


public:
   ThreadTestCase (std::string name)
       : TestCase(name)
   {
      /* Do nothing. */ ;
   }

   virtual ~ThreadTestCase () 
   {
      /* Do nothing. */ ;
   }
   
   void assertThreadImplementation(bool         condition,
                              std::string  conditionExpression = "",
                              long         lineNumber = CPPUNIT_UNKNOWNLINENUMBER,
                              std::string  fileName = CPPUNIT_UNKNOWNFILENAME)
   {
   
   vpr::Guard<vpr::Mutex> assert_guard(mAssertionMutex);

      if(!condition)
      {
         assertData info;
         info.cond_exp = conditionExpression;
         info.line_num = lineNumber;
         info.file_name = fileName;
         mAssertions.push_back(info);
      }
   
   }


   // Reset the assertion info
   void threadAssertReset()
   {   
   vpr::Guard<vpr::Mutex> assert_guard(mAssertionMutex);

      mAssertions.clear();      // Clear the assertions    
   }

   // Check the assertions and throw them if need be
   void checkThreadAssertions()
   {
   vpr::Guard<vpr::Mutex> assert_guard(mAssertionMutex);

      for(unsigned i=0;i<mAssertions.size();i++)
      {
         assertData info = mAssertions[i];
         assertImplementation(false, info.cond_exp, info.line_num, info.file_name);
      }    
   }


protected:
      std::vector<assertData>    mAssertions;      // A list of assertions that have happend
      vpr::Mutex                 mAssertionMutex;  // Mutex to protect the assertion list
};

#ifdef CPPUNIT_SOURCEANNOTATION
#    undef assertTestThread
#    define assertTestThread(condition) (this->assertThreadImplementation ((condition),(#condition),__LINE__, __FILE__))
#else
#    undef assertTestThread
#    define assertTestThread(condition) (this->assertThreadImplementation ((condition),"", __LINE__, __FILE__))
#endif


#endif
