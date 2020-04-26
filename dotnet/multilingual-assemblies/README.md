## Exercise: Language Agnosticism of the CLR

This short exercise is meant to illustrate the important concept that the Common Language Runtime - as the name implies - is completely agnostic of the source language used to produce that code that it executes. The CLR operates on Microsoft Intermediate Language (MSIL), and the manner in which this MSIL is produced is immaterial as far as the CLR is concerned at runtime.

### Procedure

In this exercise, we will build three very simple .NET _class libraries_ (essentially just a DLL that contains managed rather than native code) and a main application that references each of these class libraries to perform some operation. We'll start with the class libraries.

The first class library will be implemented in C# - perhaps the most popular and well-known .NET language. Create a file `HelloCSharp.cs` and insert the following C# source into the file:

```
// HelloCSharp.cs
public class CSharpClass
{
    public static void SayHello()
    {
        System.Console.WriteLine("Hello from C#!");
    }
}
```

Our focus here is not the syntax or semantics of the C# language, but it is pretty easy to determine exactly what this code is doing. In C#, all functions must be implemented as methods of some class (they can't just float around in the global scope as in C or C++). The class `CSharpClass` is declared `public` so that it may be referenced by other assemblies - without this modifier, the class would default to a visibility of `internal`, meaning that the class would not be visible outside of the assembly and referencing it from our main application later would fail. Finally, the `SayHello()` method is declared `static` so that it need not be invoked upon an instance of the `CSharpClass` class.

Build a class library from this source file with the command below. The C# compiler, `csc.exe`, should be included in the path provided it is invoked from a developer command prompt.

```
csc /target:library /out:HelloCSharp.dll HelloCSharp.cs
```

Next we'll implement a class library in Visual Basic - the .NET successor to the original Visual Basic programming language (for this reason, the modern Visual Basic implementation is sometimes called "Visual Basic .NET" or "VB.NET"). Create a file `HelloVB.vb` and insert the following Visual Basic source into the file:

```
' HelloVB.vb
Public Class VBClass
    Shared Sub SayHello()
        Console.WriteLine("Hello from Visual Basic!")
    End Sub
End Class
```

Many of the semantics of the Visual Basic source are the same as those mentioned above in regards to C#. The only difference is the substitution of the modifier `Shared` for C#'s `static` to indicate a method that need not be invoked on a class instance.

Build a class library from this source file with the command below. Like the C# compiler, the Visual Basic compiler, `vbc.exe`, should be available provided it is invoked from a developer command prompt.

```
vbc /target:library /out:HelloVB.dll HelloVB.vb
```

Finally, we'll implement a class library in Microsoft Intermediate Language directly. Writing MSIL directly allows us to skip the compilation step that translates a higher-level .NET language like C# or Visual Basic to MSIL and instead directly invoke the assembler to produce a .NET assembly. Create a file `HelloIl.il` and insert the following MSIL source into the file:

```
// HelloIl.il
.assembly HelloIl {}

.assembly extern mscorlib {}

.class public IlClass extends[mscorlib]System.Object {
    .method public static void SayHello() cil managed {
        ldstr "Hello from Microsoft Intermediate Language!"
        call void [mscorlib]System.Console::WriteLine(string)
        ret
    }
}
```

Its easy to see from this short example why we don't typically write MSIL directly. Now we can invoke the IL assembler, `ilasm`, to assemble this MSIL source directly to a class library assembly.

```
ilasm /DLL /out:HelloIl.dll HelloIl.il
```

At this point we have three class libraries (`.dll`s) built from three distinct .NET languages. Now we will implement a simple application that references all three of these class libraries and invokes the methods we have defined in each. Create a new file `Main.cs` and insert the following C# source into the file:

```
// Main.cs
class MainClass
{
    public static void Main()
    {
        CSharpClass.SayHello();
        VBClass.SayHello();
        IlClass.SayHello();
    }
}
```

Not much too it, as far as the source is concerned. Note that the choice of C# for this main application is totally arbitrary - we could accomplish the exact same thing by implementing this application in Visual Basic, MSIL, or any other .NET language. 

Now, how does this program "know" about the classes and methods we have implemented in our other assemblies? This is accomplished at the time the main application is compiled by specifying a _reference_ to these other assemblies. In our example, the complete command required to build the main application is as follows:

```
csc /r:HelloCSharp.dll /r:HelloVB.dll /r:HelloIl.dll /out:Main.exe Main.cs
```

The `/r` option is shorthand for `/reference`. Notice that when building an executable we can omit the `/target` option because `/target:exe` is the default assumed by the C# compiler. The result of this command is an executable `Main.exe` which we can invoke in the normal way:

```
> Main.exe
Hello from C#!
Hello from Visual Basic!
Hello from Microsoft Intermediate Language!
```

Our main application successully invokes methods implemented in the three other assemblies we have built. 

Before completing this exercise, lets dig just a bit deeper into the assemblies we have built to confirm that the source language used to produce them is immaterial. The `ildasm` tool, which is available directly from any developer command prompt, allows us to disassemble an assembly into its corresponding MSIL representation. 

Invoke `ildasm` on the class library built from the C# source and save the result to a file:

```
ildasm /out:csharp.txt HelloCSharp.dll
```

Perform a similar operation for the class library built from the Visual Basic source:

```
ildasm /out vb.txt HelloVB.dll
```

There is no reason to disassemble the class library built from the MSIL source; we already know exactly what the MSIL used to produce that assembly looks like because we wrote it ourselves.

Open up the two disassembly files, `csharp.txt` and `vb.txt`, and compare their contents. You'll notice that the disassembly from the Visual Basic class library is significantly more verbose than the disassembly from the C# class library (yet another reason to prefer C# over VB). In both files, just search for the `SayHello()` method to locate its MSIL implementation.

From the C# class library disassembly:

```
  .method public hidebysig static void  SayHello() cil managed
  {
    // Code size       13 (0xd)
    .maxstack  8
    IL_0000:  nop
    IL_0001:  ldstr      "Hello from C#!"
    IL_0006:  call       void [mscorlib]System.Console::WriteLine(string)
    IL_000b:  nop
    IL_000c:  ret
  } // end of method CSharpClass::SayHello
```

And from the Visual Basic class library disassembly:

```
  .method public static void  SayHello() cil managed
  {
    // Code size       13 (0xd)
    .maxstack  8
    IL_0000:  nop
    IL_0001:  ldstr      "Hello from Visual Basic!"
    IL_0006:  call       void [mscorlib]System.Console::WriteLine(string)
    IL_000b:  nop
    IL_000c:  ret
  } // end of method VBClass::SayHello
```

So even though the source language used to produce these two assemblies is distinct, the resulting MSIL code that the CLR ultimately executes is identical.

This exercise demonstrates the way in which .NET (and specifically, the .NET Framework in this case) achieves interoperability between many different source languages. Developers are free to write the source code that implements their applications in any language they want, so long as a compiler exists that is capable of translating the source language to Microsoft Intermediate Language. The .NET runtime (in the case of the .NET Framework, the Common Language Runtime) then operates solely on this MSIL code and is completely agnostic of the source language that its authors used to produce it.