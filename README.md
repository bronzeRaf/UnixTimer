
# UnixTimer
A minimal project to count the runtime of linux commands.

## Compile
In the working directory, make sure you have "makefile" and "MyTime.c". Open a terminal and hit the commands:

``` $ make all```

``` $ make clean```

## Run

After the compile process run the mytime.exe given the command and its arguments, separated by spaces. The timer will respond with the runtime of the command. For example:

``` $ ./mytime /bin/ls -la```

and the respond is:

``` ...folder, files and
Real wall clock time for execution is 0.002733 
CPU system time for executing is 0.000000 
CPU user time for executing is 0.000000 ```

That's it... You have your timer!
