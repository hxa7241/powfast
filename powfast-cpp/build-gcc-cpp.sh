#!/bin/bash


# --- using: GCC 4 ---


# set constants ----------------------------------------------------------------
COMPILE_OPTIONS="-c -x c++ -ansi -std=c++98 -pedantic -fno-gnu-keywords -fno-enforce-eh-specs -fno-rtti -O3 -ffast-math -mfpmath=sse -msse -Wall -Wextra -D TESTING"


# compile ----------------------------------------------------------------------
echo
g++ --version
echo "--- compile ---"

g++ $COMPILE_OPTIONS PowFast.cpp
g++ $COMPILE_OPTIONS PowFast-tester.cpp


# link -------------------------------------------------------------------------
echo
echo "--- link ---"

g++ -o PowFast-tester_cpp *.o


rm *.o


echo
echo "--- done ---"


exit
