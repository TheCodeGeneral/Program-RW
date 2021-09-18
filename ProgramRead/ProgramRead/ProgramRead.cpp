/*
Before starting this exercise, start our dummy program and let it run.

You are going to code a console program that will:
- Declare a variable of type integer named "intRead" initialised to 0
- Get a handle to our running dummy program (use OpenProcess and check that it succeeded with the checking code that I provided in the lesson
    in case of error use the error codes to investigate the reason)
- Read the value of the variable "varInt" in our dummy program and store the result in our variable "intRead"
    (Use ReadProcessMemory with the handle you got, the memory address shown in the console of our dummy program
    don't forget to add the prefix (LPCVOID) to type-cast it so the function doesn't bother you, 
    store the result in our variable "intRead" by using it as a buffer simply by giving its memory address with &intRead,
    use sizeof(int) for the size, and let the last optional parameter as NULL)
- Print to the console the new value of our variable "intRead" ( cout << "intRead = " << dec << intRead << endl; )
- Print to the console a message "Press ENTER to quit." and pause the execution with either getchar() or system("pause > nul");

*/

#include <iostream>
#include <Windows.h>
int main()
{
    int* intRead = 0;
    int procID = 16896;
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD)procID);
    if (hProc == NULL)
    {
        std::cout << "OpenProcess Failed\nError Code: " << GetLastError() << std::endl;
        getchar();
        exit(-1);
    }
    if (ReadProcessMemory(hProc, (LPCVOID*)0xF8FB44, &intRead, sizeof(int*), NULL) == 0)
    {
        std::cout << "ReadProcessMemory Failed\nError Code: " << GetLastError() << std::endl;
        getchar();
        exit(-1);
    }
    else
    {
        std::cout << "intRead = " << *intRead << std::endl;
        std::cout << "Press ENTER to quit" << std::endl;
        getchar();
    }
    CloseHandle(hProc);
    return 0;
}

