## Exercise: Unit Testing Essentials with CMake and Catch2

This exercise introduces the fundamentals of writing C/C++ unit tests and integrating them with CMake projects.

### Background

Catch2 is a unit testing framework for C/C++ code. Catch2 is a lighter-weight alternative to options like Google Test or Boost Test, and does not require (or support for that matter) integration with Visual Studio. The framework is implemented as a single C++ header file, so using the framework can be as simple as copying the header to your project and including it in the source file that implements your tests. However, Catch2 also supports relatively simple integration with CMake, and this integration drastically increases the power and scalability of testing with Catch2, so this is the approach we will explore here.

### Project Structure

This directory represents the basic structure of a project that implements unit testing with CMake and Catch2. 

First, there is a top-level `CMakeLists.txt` that builds both the primary application (a simple demo application, `demo.exe`) as well as the unit tests. In this simple example, the unit tests are designed to emulate testing of some functionality utilized in our main application - the `factorial()` function declared in the `utils.hpp` header and implemented in `utils.cpp`.

All sources related to the tests themselves are located in the `test/` subdirectory. Here, you will find another `CMakeLists.txt` file that performs a number of interesting functions related to the test suite. 

First, it pulls in the `Catch.cmake` CMake source from the Catch2 dependency directory. This is a CMake source file provided by Catch2 that aids in the integration of Catch2 with CMake - specifically, we use the `catch_discover_tests()` function that it provides to automatically register all of our Catch2 unit tests with CTest. 

Next, we define a static library called `catch-main` that links against Catch2 itself. The only source file provided for the static library is the custom `catch_main.cpp` we have defined. All `catch_main.cpp` does is define the `CATCH_CONFIG_MAIN` preprocessor macro which instructs Catch2 to generate a `main()` function for our test suite. The result of then linking against the `catch-main` static library is that our test suite has main function defined for it that knows how to discover all of our individual test cases.

Finally, we implement the test suite itself in `tests.cpp` and add this file (along with the source file from the `src/` directory that contains the function that it exercises) to a new executable target that links against the `catch-main` library described above.

### Procedure

Build the sample application with CMake and your favorite generator. For instance, using Ninja:

```
mkdir build && cd build
cmake .. -G Ninja 
ninja
```

Now run the application.

```
> demo.exe
10! = 0
```

That doesn't seem right - I don't know what 10! is off the top of my head, but I'm relatively certain that it is not 0. Lets try building the unit tests for the application and see if they can tell us anything.

Re-run CMake with the `ENABLE_TESTING` flag defined.

```
cmake .. -G Ninja -DENABLE_TESTING=ON
```

You should now see the CMake out confirm that the tests are being built.

```
> cmake .. -G Ninja -DENABLE_TESTING=ON
Building tests...
-- Configuring done
-- Generating done
-- Build files have been written to: build
```

Now, because Catch2 provides automatic integration with CTest, invoking `ctest` in the `build/` directory runs our test suite in the context of CTest.

```
> ctest
Test project /catch2-unit-test/build
    Start 1: factorials are computed correctly
1/1 Test #1: factorials are computed correctly ...***Failed    0.04 sec

0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.06 sec

The following tests FAILED:
          1 - factorials are computed correctly (Failed)
Errors while running CTest
```

The output from CTest gives us a high-level look at the output from our test suite. However, if we want more detailed output from the test suite, we can execute the test suite binary that Catch2 generated for us directly. 

```
cd test
tests.exe
...
..\test\tests.cpp(8): FAILED:
  REQUIRE( factorial(1) == 1 )
with expansion:
  0 == 1

===============================================================================
test cases: 1 | 1 failed
assertions: 1 | 1 failed
```

The output from Catch2 provides us with additional information. Specifically, it points out the exact assertion that assertion that fired and caused the test to fail - it even expands the result of the function call for us to show us the result inline. Here we see that `factorial(1)` evaluated to `0` - the same result we got for `factorial(10)`. At this point it would be reasonable to assume that something must be wrong in our `factorial()` implementation that is causing leading the function to incorrectly compute 0 for every input.

Fix the implementation of `factorial()` and rebuild the test suite (just re-run `ninja` in the build directly). Invoking `ctest` now should report all tests passing, and manually invoking the Catch2 test suite binary should produce reassuring green success output.

```
> tests.exe
===============================================================================
All tests passed (4 assertions in 1 test case)
```

Finally, with the tests passing, re-run the `demo` application:

```
> demo.exe
10! = 3628800
```

That looks about right!