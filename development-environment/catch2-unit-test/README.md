## Exercise: Unit Testing Essentials with CMake and Catch2

This exercise introduces the fundamentals of writing C/C++ unit tests and integrating them with CMake projects.

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