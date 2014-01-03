Project Euler Solutions
=======================

This is just a collection of Project Euler solutions. The code is written in several languages: Python,
Cython, Sage, C, and C++. I started solving these a few years ago and am just now getting around to placing
them on Github.

In most cases, I have several solutions - either multiple solutions in one language (to show
differences in complexity/timings) or solutions in multiple languages. The Python is made efficient
where possible. The Cython can come in one of a couple of flavors: It is either compiled and executed
directly inside the Sage Notebook environment, or it has been written as a Python module through a .pyx
file (which is compiled to C and then compiled by gcc and imported into Python). In the latter case, the
Cython can either wrap existing C/C++ code and libraries or it can simply declare its own code.

Some of the problems are done in Sage and the Sage Notebook, other than what has been done in Cython
through the Sage Notebook. This is because Sage already has some capabilities that make some of the
problems very fast to solve.

When the code is written in C or C++, I'll provide either a compilation/linkage script/command or, in
more special situations, provide a makefile and/or other instructions. Some of the problems require
special libraries (e.g., OpenMP, GMP, etc.) and that will be made clear in the solution description in
a separate file.
