zmqTest
==============================

## Target ## 

Make usage of the `zmqpp` C++ library in `Golang` with `cgo`

## Attempt Process ##

1. Installed the `zmqpp` library and create a simple C++ project for test in [zmqTest/zmqC++](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2B).

2. After the simple success test, I tried to import zmqpp` functions in **Golang**. That is the [zmqTest/zmqGoC++](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqGoC%2B%2B) at the very beginning.

3. After times of failure, I decided to try whether the C++ functions written in the `extern C` wrapper could work well outside that `extern C`. So I created two kinds of **C++ wrapper class** and tested how they cooperated with a **C++ main function**.
    1. In [zmqTest/zmqC++WithWrapper/WithClass](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2BWithWrapper/WithClass), I create a wrapper that encapsulated all variables and functions in a **C++ class**. But then I find such format may be hard to be imported into `Golang`, so I switch to the next option.
    2. In [zmqTest/zmqC++WithWrapper/WithoutClass](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2BWithWrapper/WithoutClass), I just used a seperated `.cpp` to store all functions. Because we need to hold the socket open during the whole process, I used a global variable `zmqpp::socket my_socket` to store the socket we were using. But that caused a bunch of problems.

4. Because the C++ functions can not work properly. I change my mind to think that whether a successful cooperation of `cgo` and `libzmq` C library will give me some inspiration. So I quickly read about `libzmq` and imported it into a **Golang** project in [zmqTest/zmqGoC](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2BWithWrapper). However, though the code can be compiled, it does not work properly. It also shows that it would be challenged to use a **C/C++ class** as the wrapper class in [zmqTest/zmqC++WithWrapper/WithClass](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2BWithWrapper/WithClass) in `Golang`.

5. I modified [zmqTest/zmqGoC++](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqGoC%2B%2B) while I was learning from [zmqTest/zmqC++WithWrapper](https://github.com/lyudmilalala/zmqTest/tree/dev/zmqC%2B%2BWithWrapper). Unfortunately I still could not make it compiled.

Detailed compiling and running outcomes are recorded in the `ErrorTracker.md` file in each directory.

## Main Difficulties ##

#### Storage of C/C++ Objects ####

In our case, we need to hold a `socket` open for a while to send messages back and forward. I am confusing about the convertion between `void*` in C and `unsafe.Pointer` in Go. I do not know how could I ensure that they are pointing to the exact same object. I am also confusing about how can I call the function of a `C/C++ object` from an `unsafe.Pointer` in `Golang`. Additionally, for the C++ projects, though I have tried my best to construct the `socket`, the fact that it does not work shows me that there are some traps that I have not noticed before.

#### Compiling Configuration ####

When I was compiling, `g++` gives a lot of errors related to `lack of -std=c++11` even when I already included it in the `CXXFLAGS`, which make me confused. Also, I have to include the static library `libzmq.a` or `libzmqpp.a` manually to the command line if I want the C++ programs to be successfully compiled. I think that is wired, but do not know where to change the settings. Also, because the compiler cannot search in the `CFLAGS` recursively, so I need to add `/usr/include/c++/8/x86_64-redhat-linux/` in `CFLAGS` to make the program use basic `C++` inbuild headers. It took me a lot of time of find those dependencies.
