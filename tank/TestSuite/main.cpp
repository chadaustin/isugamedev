#include <CppUnit/framework/TestSuite.h>
#include <CppUnit/textui/TestRunner.h>
#include <TestCases/Math/QuatSelfTest.h>

// type "runner noninteractive" to run tests...
int main (int ac, char **av)
{
    TestRunner runner;

   //------------------------------------
   //  noninteractive
   //------------------------------------
   // create non-interactive test suite
   TestSuite* noninteractive_suite = new TestSuite( "NonInteractive" );

   // add tests to the noninteractive suite
   noninteractive_suite->addTest( tankTest::QuatSelfTest::suite() );
   
   // Add the test suite to the runner
   runner.addTest( "noninteractive", noninteractive_suite );

   // create test suite #2
   TestSuite* interactive_suite = new TestSuite("Interactive");

   // add tests to the interactive suite
   //interactive_suite->addTest( ThreadTest::suite() );

   // Add the test suite to the runner
   runner.addTest( "interactive", interactive_suite );

   // run all test suites
   runner.run( ac, av );


   return 0;
}
