

Fast-Pow-Adjustable code
======================================================================


Harrison Ainsworth / HXA7241 : 2004-2011.
http://wwww.hxa.name/articles/

2011-07-09
2007-11-21




Contents
--------

* Description
* Acknowledgements
* License




Description
-----------

This code accompanies the article 'Fast pow() With Adjustable Accuracy' at
<http://www.hxa.name/articles/content/fast-pow-adjustable_hxa7241_2007.html>

The main module, in the PowFast.* files, has an interface with two parts:
 * create and free a PowFast instance of particular precision
 * query an instance for pow calculations
Look at the header for usage details. The implementation includes a test
function.

The tester module, in the PowFast-tester file, just calls the test function in
the main PowFast module. (And outputs 200+ lines of numbers.)

Run a build script, for VC-2005 on Windows, or GCC-4 on Linux (and similar),
to build the test program.

The code assumes a 32 bit int. For 64 bit builds, adjustments might be needed
to specify that explicitly.




Acknowledgements
----------------

* 'A Fast, Compact Approximation of the Exponential Function'  
  Technical Report IDSIA-07-98;  
  Nicol N. Schraudolph;  
  IDSIA,  
  1998-06-24.
* 'Revisiting a basic function on current CPUs: A fast logarithm implementation
  with adjustable accuracy'  
  Technical Report ICSI TR-07-002;  
  Oriol Vinyals, Gerald Friedland, Nikki Mirghafori;  
  ICSI,  
  2007-06-21.




License
-------

Harrison Ainsworth / HXA7241 : 2004-2011.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* The name of the author may not be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
