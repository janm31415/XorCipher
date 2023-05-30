# XorCipher

The [XOR cipher](https://en.wikipedia.org/wiki/XOR_cipher) is a relatively simple encryption algorithm.


The file `xorcipher.h` contains everything you need to run the XOR cipher algorithm in your own C or C++ code. The way this file can be integrated in your own code is similar to how the popular [stb header only files](https://github.com/nothings/stb) are used. You have to select one single C or C++ file in your source code where you add the following two lines at the top:

    #define XORCIPHER_IMPLEMENTATION
    #include "xorcipher.h"
    
and you're good to go.


Next to the header only `xorcipher.h` file there is a utility program and some test code delivered with this repository. If you want to build these, you can simply use `CMAKE` on any platform.
