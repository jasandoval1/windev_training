// HelloIl.il
//
// Build
//  ilasm /DLL /out:HelloIl.dll HelloIl.il

.assembly HelloIl {}

.assembly extern mscorlib {}

.class public IlClass extends[mscorlib]System.Object {
    .method public static void SayHello() cil managed {
        ldstr "Hello from Microsoft Intermediate Language!"
        call void [mscorlib]System.Console::WriteLine(string)
        ret
    }
}
