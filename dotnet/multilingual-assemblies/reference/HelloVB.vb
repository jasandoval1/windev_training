' HelloVB.vb
'
' Build
'   vbc /target:library /out:HelloVB.dll HelloVB.vb

Public Class VBClass
    Shared Sub SayHello()
        Console.WriteLine("Hello from Visual Basic!")
    End Sub
End Class