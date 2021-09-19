#include "Mem.h"
namespace Mem {
    uintptr_t GetValueFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets)
    {
        uintptr_t newPtr = addr;
        offsets.push_back(0);

        return GetAddrFromBase(hProc, addr, offsets);
    }

    uintptr_t GetAddrFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets)
    {
        uintptr_t newPtr = addr;
        uintptr_t* ThisProg = &addr;
        /*  Given address of value
            address = Value = ?

            base ptr -> address + offset4 = address

            base ptr -> address + offset3 = address

            base ptr -> address + offset2 = address

            static base -> address + offset1 = address
        */
        for (unsigned int i = 0; i < offsets.size(); ++i)
        {
            ReadFromAddress(hProc, (LPCVOID)newPtr, &newPtr, sizeof(addr));
            newPtr += offsets[i];
        }
        return newPtr;
    }

    void ReadFromAddress(HANDLE hProc, LPCVOID lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize)
    {
        bool rpmStatus = ReadProcessMemory(hProc, (LPCVOID*)lpBaseAddr, &lpBuffer, nSize, NULL);
        if (rpmStatus == 0)
        {
            std::cout << "ReadProcessMemory call1 Failed\nError Code: " << GetLastError() << std::endl;
            system("pause");
            CloseHandle(hProc);
            exit(-1);
        }
    }
    void WriteToAddress(HANDLE hProc, LPCVOID lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize)
    {
        bool rpmStatus = WriteProcessMemory(hProc, (LPCVOID*)lpBaseAddr, &lpBuffer, nSize, NULL);
        if (rpmStatus == 0)
        {
            std::cout << "ReadProcessMemory call1 Failed\nError Code: " << GetLastError() << std::endl;
            system("pause");
            CloseHandle(hProc);
            exit(-1);
        }
    }
}