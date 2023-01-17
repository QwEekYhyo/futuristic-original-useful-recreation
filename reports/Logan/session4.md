# Session 4 report

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; So my program used to work fine but I was
using the c++ standard library because I am used to it and it provides very
useful classes like array that I was using for the game's grid (a 6x7 matrix).
Little did I know, arduino does not support the c++ standard library, it has
its own libraries. Being unable to use the class `std::array` (among others)
I decided to create my own array class using basic c++ and pointers and
I replaced everything with my own arrays. Thanks to this change the code now
runs on arduino (tested and approved during this session).

Here is a ![link to the pull request](https://github.com/QwEekYhyo/futuristic-original-useful-recreation/pull/1).
