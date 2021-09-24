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
#include <vector>
#include "Mem.h"
using namespace mem;
int main()
{
    int procID;
    int intRead;
    uintptr_t ptr2int = 0x0;
    uintptr_t ptr2ptr2 = 0x0;
    uintptr_t write2Addr = 0x0;
    uintptr_t readFromAddr = 0x0;
    int valToWrite;

    std::cout << "Enter the ProcID: ";
    std::cin >> procID;
    // Open a handle to a program
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD64)procID);
    if (hProc == NULL)
    {
        std::cout << "OpenProcess Failed\nError Code: " << GetLastError() << std::endl;
        system("pause");
        return -1;
    }
    
    // Get the value of a ptr to an int
    std::cout << "Enter the Address of ptr2int: ";
    std::cin >> std::hex >> ptr2int;
    if (ptr2int != NULL)
    {
        std::cout << "ptr2int = 0x" << std::hex << std::uppercase << ptr2int << std::endl;
        if (ReadProcessMemory(hProc, (LPCVOID*)ptr2int, &ptr2int, sizeof(uintptr_t), NULL) == 0 || ReadProcessMemory(hProc, (LPCVOID*)ptr2int, &intRead, sizeof(uintptr_t), NULL) == 0)
        {
            std::cout << "ReadProcessMemory call Failed\nError Code: " << GetLastError() << std::endl;
            system("pause");
            CloseHandle(hProc);
            return -1;
        }

        std::cout << "intRead = " << std::dec << intRead << std::endl;
    }
    
    // Write to a varInt
    std::cout << "Enter address of varInt: ";
    std::cin >> std::hex >> write2Addr;
    std::cout << "write2Addr = 0x" << std::hex << std::uppercase << write2Addr << std::endl;
    std::cout << "Enter value to write: ";
    std::cin >> std::dec >> valToWrite;

    if (WriteProcessMemory(hProc, (LPVOID)write2Addr, &valToWrite, sizeof(int), NULL) == 0)
    {
        std::cout << "WriteProcessMemory call Failed\nError Code: " << GetLastError() << std::endl;
        system("pause");
        CloseHandle(hProc);
        return -1;
    }

    // Get the value of a multilevel ptr to an int
    std::cout << "Enter address of ptr2ptr2: ";
    std::cin >> std::hex >> ptr2ptr2;
    if (ptr2ptr2 != NULL)
    {
        std::cout << "ptr2ptr2 = 0x" << std::hex << std::uppercase << ptr2ptr2 << std::endl;
        readFromAddr = GetAddrFromBase(hProc, ptr2ptr2, std::vector<unsigned int>{0, 0, 0});
        ReadFromAddress(hProc, readFromAddr, &intRead, sizeof(int));
        std::cout << "intRead = " << std::dec << intRead << std::endl;
    }
    
    // Write to multilevel ptr to an int
    write2Addr = GetAddrFromBase(hProc, ptr2ptr2, std::vector<unsigned int>{0, 0, 0});
    std::cout << "write2Addr = 0x" << std::hex << std::uppercase << write2Addr << std::endl;
    std::cout << "Enter value to write: ";
    std::cin >> std::dec >> valToWrite;
    
    WriteToAddress(hProc, write2Addr, &valToWrite, sizeof(int));
    CloseHandle(hProc);
    return 0;
}



