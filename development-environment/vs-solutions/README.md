## Creating Complex Solutions in Visual Studio

We will use Visual Studio to create a complex solution and configure build properties

### Background

Visual Studio is a powerful IDE that has tons of configurable options. Getting familiar with some of the more commone ones will help you succeed in future projects.

### Project Structure

- Create a blank solution
- Add a console application project
- Look into configuration options


### Procedure

- Start Visual Studio 2019
- Click Create a New Project
    - Select Blank Solution
    - Name it TestSolution; Click Create
    - Notice how everything is greyed out
- Add a new project
    - File->Add->New Project
    - Type 'Console App'; Make sure it is the C++, Windows, Console tagged version
    - Name it TestProject; Click Create
    - Build->Build Solution to compile your 'hello world' program
        - Notice how it defaulted to DEBUG/x86 configuration/platform
- Configuration Options
    - Right click 'TestProject' in Solution Explorer; Select properties
    - Click the 'Configuration:' and 'Platform' dropdown and notice what is available by default
    - Look through General, Advanced, Debugging, VC++ Directories, C/C++, Linker, Build Events settings to see what is available to modify

- Adding Second Project
    - File->Add->New Project
    - Type 'Static Library'; Click next
    - Name it TestStaticLib; Click Create
    - Add following code to TestStaticLib.cpp
    ```
    // TestStaticLib.cpp : Defines the functions for the static library.
    //

    #include "pch.h"
    #include "framework.h"
    #include <iostream>

    void fnTestStaticLib()
    {
        std::cout << "Hello from static lib" << std::endl;
    }

    ```
    - Add following code to TestProject.cpp in TestProject
    ```
    // TestProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
    //

    #include <iostream>

    void fnTestStaticLib();

    int main()
    {
        fnTestStaticLib();
    }
    ```
    - Attempt to compile TestProject
    - Right click TestProject->Add->Reference and put a check next to TestStaticLib
    - Compile again

- On your own
    - Create another static library project
    - Create a function
    - Link against it in TestProject
    - Change configuration to Release/x64 for TestProject
    - Change warning level to W4 for TestProject
    - Disable Precompiled headers for all configurations
