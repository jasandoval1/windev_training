// Main2.cs
//
// Build
//  csc /addmodule:Module1.netmodule,Module2.netmodule /out:Main2.exe Main2.cs

class MainClass
{
    public static void Main()
    {
        Module1Class.SayHello();
        Module2Class.SayHello();
    }
}