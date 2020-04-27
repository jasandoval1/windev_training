## Exercise: Multimodule Assemblies

This exercise explores some aspects of the internals of .NET assemblies and the distinction between modules and assemblies.

### Procedure

.NET distinguishes between _managed modules_ and _assemblies_, but what exactly does this distinction entail? Fundamentally, an assembly is simply a module with some additional metadata embedded in it that allows it to be executed as a standalone application by a .NET runtime (such as the CLR). This implies, then, that managed modules cannot be executed on their own - a managed module provides no utility if it is not included in some assembly (I use the word "included" here with some trepidation because managed modules are not embedded in assemblies the way that source from a header file is copied directly into a source file in a native language like C or C++; we will look at exactly how this is done in due course). To get an intuitive understanding for this distinction, we'll build a couple applications in this exercise, one of which will be a single-module assembly while the other will be a multimodule assembly.

We'll start with the simpler case, the single-module assembly. In single-module assemblies, the assembly is composed of a single managed module, and the source of this managed module is contained in the same physical file that hosts the assembly's _manifest_ - the metdata that distinguishes .NET assemblies. Most of the time when working with .NET applications, single-module assemblies are what you will encounter.

Create a file `Main1.cs` and insert the following C# source into the file:

```
// Main1.cs
class MainClass
{
    public static void Main()
    {
        System.Console.WriteLine("Hello from Main1!");
    }
}
```

This is the simplest possible C# application - the "hello world" program. Compile this source to an executable with the following command:

```
csc /out:Main1.exe Main1.cs
```

You can run it to verify that it works as expected.

```
> Main1.exe
Hello from Main1!
```

But that's not very interesting, so let's disassemble the executable and take a look at what is going on under the hood. The command below disassembles the executable `Main1.exe` to a text file `main1.txt`. 

```
ildasm /out:main1.txt Main1.exe
```

Some quick background on MSIL is required to understand the contents of this disassembly. Any line that begins with a `.` is metadata; this is data that is embedded in the executable that is not IL code executed by the .NET runtime. For instance, the line

```
.subsystem 0x0003
```

defines the subsystem for this executable as a Windows console application, much like we would expect to find in the Optional Header for a standard Windows executable. However, the metadata we are interested in is denoted by the `.assembly` symbol, of which there are two in this particular disassembly output:

```
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
```

This first instance of assembly metdata is actually an assembly _reference_, as evidenced by the `extern` symbol, denoting that our own assembly references some type provided by `mscorlib` assembly. Of course, we did not specify any assembly references on the commandline when we built this application, so where did this reference come from? `mscorlib` is the core assembly for the .NET Framework provided by Microsoft, and a reference to this assembly is always automatically included by the C# compiler. This assembly contains many of the Framework Class Library types, including all of the primitive types such as `int` and `string` that we expect to be able to use in our applications without any additional ceremony. We didn't use any primitive types in our application directly, but we did invoke the `WriteLine` method of the `Console` class, implemented within the `System` namespace, which is provided by `mscorlib`.

So this first instance of assembly metdata is actually an assembly reference, implying that the other instance of assembly metdata is the assembly manifest for our assembly.

```
.assembly Main1
{
  .custom instance void [truncated]
  .custom instance void [truncated]

  // --- The following custom attribute is added automatically, do not uncomment -------
  //  .custom instance void [mscorlib]System.Diagnostics.DebuggableAttribute::.ctor(valuetype [mscorlib]System.Diagnostics.DebuggableAttribute/DebuggingModes) = ( 01 00 07 01 00 00 00 00 ) 

  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
```

Because this application is so simple, there is not much to look at in this assembly manifest. However, it is the presence of this manifest that establishes the assembly that is ultimately executed by the .NET runtime.

Directly following our assembly manifest is the following line:

```
.module Main1.exe
```

So this physical file not only contains the assembly manifest but defines a managed module named `Main1.exe`. Furthermore, this is the only instance of the `.module` symbol in this disassembly output, so we can conclude that this assembly is composed of this module alone. This isn't very exciting though - we would expect to find that this simple assembly is composed of only a single module, so lets move on to a more interesting example in which we create an assembly composed of multiple modules.

Create a new file `Module1.cs` and insert the following C# source into the file:

```
// Module1.cs
class Module1Class 
{
    public static void SayHello()
    {
        System.Console.WriteLine("Hello from Module1!");
    }
}
```

Similarly, create a new file `Module2.cs` and insert the following C# source into the file:

```
// Module2.cs
class Module2Class 
{
    public static void SayHello()
    {
        System.Console.WriteLine("Hello from Module2!");
    }
}
```

Now, use the C# compiler to build each of these source files into managed modules:

```
csc /target:module /out:Module1.netmodule Module1.cs
csc /target:module /out:Module2.netmodule Module2.cs
```

The `.netmodule` extension is not required - it is merely a common convention.

Finally, create one more new file `Main2.cs` and insert the following C# source:

```
// Main2.cs
class MainClass
{
    public static void Main()
    {
        Module1Class.SayHello();
        Module2Class.SayHello();
    }
}
```

This new version of the main application obviously utilizes some functionality defined in our managed modules, so we must specify these modules during the build process for our new executable:

```
csc /addmodule:Module1.netmodule,Module2.netmodule /out:Main2.exe Main2.cs
```

So now we have a new executable `Main2.exe` that utilizes functionality in two external managed modules. You can execute this application to verify that it works as expected:

```
> Main2.exe
Hello from Module1!
Hello from Module2!
```

Lets open up the main executable and one of our managed modules and look at what is going on under the hood. First, one of the managed modules:

```
ildasm /out:module1.txt Module1.netmodule
```

In the disassembly for `Module1` you'll find the expected IL code that implements the `SayHello()` method (as well as the constructor for the `Module1Class` class) along with the two following familiar metdata sections:

```
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
```

```
.module Module1.netmodule
```

We recognize the first as an assembly reference to the `mscorlib` assembly, and the second as the line that declares `Module1.netmodule` as a .NET managed module. What is conspicuously absent is an assembly manifest, implying that this module, on its own, is _not_ an assembly.

Now lets look at the main application itself.

```
ildasm /out:main2.txt Main2.exe
```

The resulting disassembly contains an assembly manifest that defines the `Main2` assembly:

```
.assembly Main2
{
  .custom instance void [truncated]
  .custom instance void [truncated]

  // --- The following custom attribute is added automatically, do not uncomment -------
  //  .custom instance void [mscorlib]System.Diagnostics.DebuggableAttribute::.ctor(valuetype [mscorlib]System.Diagnostics.DebuggableAttribute/DebuggingModes) = ( 01 00 07 01 00 00 00 00 ) 

  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
```

Furthermore it is declares a managed module `Main2.exe`:

```
.module Main2.exe
```

However, in addition to these, we find the following lines:

```
.module extern Module1.netmodule
.module extern Module2.netmodule
```

These lines denote that the `Main2` assembly is actually composed of three distinct managed modules: `Main2.exe` (which happens to be implemented in the source file whose compilation produced the final assembly), `Module1.netmodule1`, and `Module2.netmodule` (both of which are implemented externally). When we compiled `Main2.cs` with the implicit `/target:exe` flag, the C# compiler generated the assembly manifest in the output file that we specified (`Main2.exe`) in addition to compiling the source of `Main2.cs` into a managed module.

This second example illustrates a fundamental yet often misunderstood characteristic of .NET assemblies: they are _logical_ units of execution rather than _physical_ units of execution as is the case with standard Windows executables produced from native code. The `Main2` assembly is composed of three distinct managed modules, each of which happen to be implemented in a distinct physical file: `Main2.exe`, `Module1.netmodule`, and `Module2.netmodule`.  Notice how this paradigm differs from that typically encountered when programming in native languages like C and C++. In native languages, when an executable depends on some source implemented within another physical file, this source is linked directly into the final executable. In contrast, the IL code in `Module1.netmodule` and `Module2.netmodule` that implements the two versions of the `SayHello()` method is nowhere to be found in the disassembly of `Main2.exe` - it is only at runtime that these three managed modules are combined to form a complete assembly that the .NET runtime is capable of executing.

Hopefully this exercise has helped make concrete the distinction between managed modules and .NET assemblies; a firm understanding of what assemblies are and how they work is critical to recognizing the power and flexibility offered by the .NET platform.