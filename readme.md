This is some test code for a windows service to impersonate a logged user to access his certificate store.

# Test

Follow this [link](https://stackoverflow.com/questions/77528/how-do-you-run-cmd-exe-under-the-local-system-account).

*psexec -i -s cmd.exe*

Now run imcert.exe (it will be run as local system account),

```
e:\projects\imcert\x64\Debug>imcert.exe
Hello World!
Number of Entries: 128

The system store was opened successfully.
The desired certificate was found.
```

If we run it normally,

```
e:\projects\imcert\x64\Debug>imcert.exe
Hello World!
Number of Entries: 132

WTSQueryUserToken failed with error = 1314
```





