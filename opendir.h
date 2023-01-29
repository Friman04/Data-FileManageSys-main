#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BUFSIZE 4096
#define LONG_DIR_NAME TEXT("data")

void _tmain(int argc, TCHAR* argv[])
{
    DWORD  retval = 0;
    BOOL   success;
    TCHAR  buffer[BUFSIZE] = TEXT("");
    TCHAR  buf[BUFSIZE] = TEXT("");
    TCHAR** lppPart = { NULL };

    if (argc != 2)
    {
        _tprintf(TEXT("Usage: %s [file]\n"), argv[0]);
        return;
    }

    // Retrieve the full path name for a file. 
    // The file does not need to exist.

    retval = GetFullPathName(argv[1],
        BUFSIZE,
        buffer,
        lppPart);

    if (retval == 0)
    {
        // Handle an error condition.
        printf("GetFullPathName failed (%d)\n", GetLastError());
        return;
    }
    else
    {
        _tprintf(TEXT("The full path name is:  %s\n"), buffer);
        if (lppPart != NULL && *lppPart != 0)
        {
            _tprintf(TEXT("The final component in the path name is:  %s\n"), *lppPart);
        }
    }


    // Create a long directory name for use with the next two examples.

    success = CreateDirectory(LONG_DIR_NAME,
        NULL);

    if (!success)
    {
        // Handle an error condition.
        printf("CreateDirectory failed (%d)\n", GetLastError());
        return;
    }


    // Retrieve the short path name.  

    retval = GetShortPathName(LONG_DIR_NAME,
        buf,
        BUFSIZE);

    if (retval == 0)
    {
        // Handle an error condition.
        printf("GetShortPathName failed (%d)\n", GetLastError());
        return;
    }
    else _tprintf(TEXT("The short name for %s is %s\n"),
        LONG_DIR_NAME, buf);


    // Retrieve the long path name.  

    retval = GetLongPathName(buf,
        buffer,
        BUFSIZE);

    if (retval == 0)
    {
        // Handle an error condition.
        printf("GetLongPathName failed (%d)\n", GetLastError());
        return;
    }
    else _tprintf(TEXT("The long name for %s is %s\n"), buf, buffer);

    // Clean up the directory.

    success = RemoveDirectory(LONG_DIR_NAME);
    if (!success)
    {
        // Handle an error condition.
        printf("RemoveDirectory failed (%d)\n", GetLastError());
        return;
    }
}