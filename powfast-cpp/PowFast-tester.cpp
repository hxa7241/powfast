/*------------------------------------------------------------------------------

   HXA7241 General library.
   Harrison Ainsworth / HXA7241 : 2004-2011

   http://www.hxa.name/

------------------------------------------------------------------------------*/


#include <cstdlib>
#include <exception>
#include <iostream>

#include "PowFast.hpp"




// constants -------------------------------------------------------------------
namespace
{

const char BANNER_MESSAGE[] =
   "\n  PowFast tester  :  HXA7241\n"
   "  http://www.hxa.name/articles/content/"
   "fast-pow-adjustable_hxa7241_2007.html\n\n";
const char EXCEPTION_PREFIX[]   = "*** execution failed:  ";
const char EXCEPTION_ABSTRACT[] = "no annotation for cause";

}


bool test_PowFast
(
   std::ostream* pOut,
   bool          isVerbose,
   int           seed
);




/// entry point ////////////////////////////////////////////////////////////////
int main
(
   int   ,//argc,
   char* []//argv[]
)
{
   int returnValue = EXIT_FAILURE;

   // catch everything
   try
   {
      std::cout << BANNER_MESSAGE;

      const bool isOk = test_PowFast( &std::cout, true, 0 );

      returnValue = isOk ? EXIT_SUCCESS : EXIT_FAILURE;
   }
   // print exception message
   catch( const std::exception& e )
   {
      std::cout << '\n' << EXCEPTION_PREFIX << e.what() << '\n';
   }
   catch( const char*const pExceptionString )
   {
      std::cout << '\n' << EXCEPTION_PREFIX << pExceptionString << '\n';
   }
   catch( ... )
   {
      std::cout << '\n' << EXCEPTION_PREFIX << EXCEPTION_ABSTRACT << '\n';
   }

   try
   {
      std::cout.flush();
   }
   catch( ... )
   {
      // suppress exceptions
   }

   return returnValue;
}
