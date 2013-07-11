#!/bin/bash


# --- using: GCC 4 ---


# set constants ----------------------------------------------------------------
COMPILE_OPTIONS="-c -x c -ansi -std=iso9899:199409 -pedantic -O3 -ffast-math -mfpmath=sse -msse -Wall -Wextra -D TESTING"


# compile ----------------------------------------------------------------------
echo
gcc --version
echo "--- compile ---"

gcc $COMPILE_OPTIONS PowFast.c
gcc $COMPILE_OPTIONS PowFast-tester.c


# link -------------------------------------------------------------------------
echo
echo "--- link ---"

gcc -o PowFast-tester_c *.o


rm *.o


echo
echo "--- done ---"


exit
