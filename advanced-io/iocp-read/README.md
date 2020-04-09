## Exercise: Reading a File with an IO Completion Port

This exercise introduces you to the basic semantics of asynchronous IO operations utilizing IO completion ports.

### Procedure

Write a program that reads the contents of a specified file asynchronously using an IO completion port. The file that is the target of the read operation should be specified as a command line argument to the program. Read the file's content in small chunks such that your program must handle multiple asynchronous IO completions. The processing of the file's content once it has been read is not important; feel free to write the content to standard output or simply write some diagnostic message that reports the completion of a read operation - whatever approach you need to take to convince yourself that the entirety of the file's content is read correctly by your implementation. 

Check for error conditions wherever applicable, taking particular care to ensure that you asynchronous read operations initiate successfully.

A sample application that meets the requirements of this exercise is provided in the `reference/` directory; don't refer to the sample implementation until you have attempted the exercise yourself!