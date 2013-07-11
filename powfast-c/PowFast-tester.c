/*------------------------------------------------------------------------------

   HXA7241 General library.
   Harrison Ainsworth / HXA7241 : 2004-2011

   http://www.hxa.name/

------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <stdio.h>

#include "PowFast.h"




/*- constants ----------------------------------------------------------------*/

static const char BANNER_MESSAGE[] =
   "\n  PowFast tester  :  HXA7241\n"
   "  http://www.hxa.name/articles/content/"
   "fast-pow-adjustable_hxa7241_2007.html\n\n";
static const char NOT_IMPLEMENTED[] = "!!! not implemented";
static const char EXCEPTION[]       = "*** execution failed";


extern int test_PowFast
(
   FILE* pOut,
   int   isVerbose,
   int   seed
);




/*/ entry point //////////////////////////////////////////////////////////////*/

int main
(
   void
)
{
   int isOk = 0;

   printf( BANNER_MESSAGE );

   isOk = test_PowFast( stdout, 1, 0 );

   switch( isOk )
   {
      case -1:   printf( "\n%s\n", NOT_IMPLEMENTED );   break;
      case -2:   printf( "\n%s\n", EXCEPTION );         break;
   }

   fflush( stdout );

   return (1 == isOk) ? EXIT_SUCCESS : EXIT_FAILURE;
}
