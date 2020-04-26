// Main.cs
//
// Build
//  csc /reference:HelloCSharp.dll /reference:HelloVB.dll /reference:HelloIl.dll /out:Main.exe Main.cs

class MainClass
{
    public static void Main()
    {
        CSharpClass.SayHello();
        VBClass.SayHello();
        IlClass.SayHello();
    }
}