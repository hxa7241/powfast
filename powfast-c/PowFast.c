/*------------------------------------------------------------------------------

   HXA7241 General library.
   Harrison Ainsworth / HXA7241 : 2004-2011

   http://www.hxa.name/

------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <math.h>

#include "PowFast.h"




#if __STDC_VERSION__ < 199901L
#define inline
#endif




/*- implementation -----------------------------------------------------------*/

/**
 * Following the bit-twiddling idea in:
 *
 * 'A Fast, Compact Approximation of the Exponential Function'
 * Technical Report IDSIA-07-98
 * Nicol N. Schraudolph;
 * IDSIA,
 * 1998-06-24.
 *
 * [Rewritten for floats by HXA7241, 2007.]
 *
 * and the adjustable-lookup idea in:
 *
 * 'Revisiting a basic function on current CPUs: A fast logarithm implementation
 * with adjustable accuracy'
 * Technical Report ICSI TR-07-002;
 * Oriol Vinyals, Gerald Friedland, Nikki Mirghafori;
 * ICSI,
 * 2007-06-21.
 *
 * [Improved (doubled accuracy) and rewritten by HXA7241, 2007.]
 */


static const float _2p23 = 8388608.0f;


/**
 * Initialize powFast lookup table.
 *
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
static void powFastSetTable
(
   unsigned int* const pTable,
   const unsigned int  precision
)
{
   /* step along table elements and x-axis positions */
   float zeroToOne = 1.0f / ((float)(1 << precision) * 2.0f);
   int   i;
   for( i = 0;  i < (1 << precision);  ++i )
   {
      /* make y-axis value for table element */
      const float f = ((float)pow( 2.0f, zeroToOne ) - 1.0f) * _2p23;
      pTable[i] = (unsigned int)( f < _2p23 ? f : (_2p23 - 1.0f) );

      zeroToOne += 1.0f / (float)(1 << precision);
   }
}


/**
 * Get pow (fast!).
 *
 * @val        power to raise radix to
 * @ilog2      one over log, to required radix, of two
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
inline
static float powFastLookup
(
   const float         val,
   const float         ilog2,
   unsigned int* const pTable,
   const unsigned int  precision
)
{
   /* build float bits */
   const int i = (int)( (val * (_2p23 * ilog2)) + (127.0f * _2p23) );

   /* replace mantissa with lookup */
   const int it = (i & 0xFF800000) | pTable[(i & 0x7FFFFF) >> (23 - precision)];

   /* convert bits to float */
   union { int i; float f; } pun;
   return pun.i = it,  pun.f;
}


typedef struct {
   unsigned int  precision_m;
   unsigned int* pTable_m;
} PowFast;




/*- basic object services ----------------------------------------------------*/

void* powFastCreate
(
   unsigned int precision
)
{
   PowFast* pPowFast = 0;

   precision = (precision <= 18u) ? precision : 18u;

   pPowFast = (PowFast*)malloc( sizeof(PowFast) + ((1 << precision) *
      sizeof(*(pPowFast->pTable_m))) );
   if( pPowFast )
   {
      pPowFast->precision_m = precision;
      pPowFast->pTable_m   = (unsigned int*)((char*)pPowFast + sizeof(PowFast));

      powFastSetTable( pPowFast->pTable_m, pPowFast->precision_m );
   }

   /*PowFast* pPowFast = (PowFast*)malloc( sizeof(PowFast) );
   if( pPowFast )
   {
      pPowFast->precision_m = (precision <= 18u) ? precision : 18u;
      pPowFast->pTable_m    = (unsigned int*)malloc( (1 << precision) *
         sizeof(*(pPowFast->pTable_m)) );

      if( pPowFast->pTable_m )
      {
         powFastSetTable( pPowFast->pTable_m, pPowFast->precision_m );
      }
      else
      {
         free( pPowFast );
         pPowFast = 0;
      }
   }*/

   return pPowFast;
}


int powFastFree
(
   const void* powFast
)
{
   PowFast* ppf = (PowFast*)powFast;

   /*free( ppf->pTable_m );*/
   free( ppf );

   return 1;
}




/*- queries ------------------------------------------------------------------*/

float powFast2
(
   const void* powFast,
   float       f
)
{
   const PowFast* ppf = (const PowFast*)powFast;

   return powFastLookup( f, 1.0f, ppf->pTable_m, ppf->precision_m );
}


float powFastE
(
   const void* powFast,
   float       f
)
{
   const PowFast* ppf = (const PowFast*)powFast;

   return powFastLookup( f, 1.44269504088896f, ppf->pTable_m, ppf->precision_m);
}


float powFast10
(
   const void* powFast,
   float       f
)
{
   const PowFast* ppf = (const PowFast*)powFast;

   return powFastLookup( f, 3.32192809488736f, ppf->pTable_m, ppf->precision_m);
}


float powFast
(
   const void* powFast,
   float       logr,
   float       f
)
{
   const PowFast* ppf = (const PowFast*)powFast;

   return powFastLookup( f, (logr * 1.44269504088896f),
      ppf->pTable_m, ppf->precision_m );
}


unsigned int powFastPrecision
(
   const void* powFast
)
{
   const PowFast* ppf = (const PowFast*)powFast;

   return ppf->precision_m;
}








/*- test ---------------------------------------------------------------------*/
#ifdef TESTING


#include <float.h>
#include <stdio.h>


typedef  unsigned int  udword;
typedef  int           dword;


int test_PowFast
(
   FILE* pOut,
   dword isVerbose,
   dword seed
);


/**
 * rand [0,1) (may be coarsely quantized).
 */
static float randFloat( void )
{
   return (float)((udword)rand()) / (float)((udword)RAND_MAX + 1);
}


/**
 * @return  1 for success, 0 for fail, -2 for exception
 */
int test_PowFast
(
   FILE* pOut,
   dword isVerbose,
   dword seed
)
{
   int         isOk       = 1;
   const void* powFastAdj = powFastCreate( 11 );

   if( pOut ) fprintf( pOut, "[ test_PowFast ]\n\n" );


   srand( (unsigned int)(seed) );

   if( powFastAdj )
   {
      const dword J_COUNT = 1000;

      const dword E_START = -86;
      const dword E_END   = +88;
      float sumDifE = 0.0f;
      float maxDifE = (float)FLT_MIN;

      const dword T_START = -36;
      const dword T_END   = +38;
      float sumDifT = 0.0f;
      float maxDifT = (float)FLT_MIN;

      dword i = 0;

      for( i = E_START;  i < E_END;  ++i )
      {
         int j;
         for( j = 0;  j < J_COUNT;  ++j )
         {
            const float number = (float)i + randFloat();

            const float pe    = (float)pow( 2.71828182845905f, number );
            const float pef   = powFastE( powFastAdj, number );
            const float peDif = (float)fabs( pef - pe ) / pe;
            sumDifE += peDif;
            maxDifE = (maxDifE >= peDif) ? maxDifE : peDif;

            if( (0 == j) && pOut && isVerbose )
            {
               fprintf( pOut, "%+10f  E %e %e\n", number, pef, peDif );
            }
         }
      }
      if( pOut && isVerbose ) fprintf( pOut, "\n" );

      for( i = T_START;  i < T_END;  ++i )
      {
         int j;
         for( j = 0;  j < J_COUNT;  ++j )
         {
            const float number = (float)i + randFloat();

            const float pt    = (float)pow( 10.0f, number );
            const float ptf   = powFast10( powFastAdj, number );
            const float ptDif = (float)fabs( ptf - pt ) / pt;
            sumDifT += ptDif;
            maxDifT = (maxDifT >= ptDif) ? maxDifT : ptDif;

            if( (0 == j) && pOut && isVerbose )
            {
               fprintf( pOut, "%+10f  T %e %e\n", number, ptf, ptDif );
            }
         }
      }
      if( pOut && isVerbose ) fprintf( pOut, "\n" );

      {
         const float meanDifE = sumDifE / ((float)(E_END - E_START) *
            (float)J_COUNT);
         const float meanDifT = sumDifT / ((float)(T_END - T_START) *
            (float)J_COUNT);

         if( pOut && isVerbose )
         {
            fprintf( pOut, "precision: %u\n", powFastPrecision( powFastAdj ) );
            fprintf( pOut, "mean diff,  E: %e  10: %e\n", meanDifE, meanDifT );
            fprintf( pOut, "max  diff,  E: %e  10: %e\n", maxDifE, maxDifT );
            fprintf( pOut, "\n" );
         }

         isOk = (meanDifE < 0.0001f) & (meanDifT < 0.0001f) &
            (maxDifE < 0.0002f) & (maxDifT < 0.0002f);
      }

      if( pOut ) fprintf( pOut, "adjustable : %s\n\n",
         (isOk ? "--- succeeded" : "*** failed") );

      powFastFree( powFastAdj );
   }
   else
   {
      isOk = -2;
   }


   if( pOut ) fprintf( pOut, "%s completed \n\n",
      ((1 == isOk) ? "--- successfully" : "*** failurefully") );

   if( pOut ) fflush( pOut );


   return isOk;
}


#endif/*TESTING*/
