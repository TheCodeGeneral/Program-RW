#include "Mem.h"
namespace mem {
   /* uintptr_t GetValueFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets)
    {
        uintptr_t newPtr = addr;
        offsets.push_back(0);

        return GetAddrFromBase(hProc, addr, offsets);
    }*/

    uintptr_t GetAddrFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets)
    {
        uintptr_t newPtr = addr;
        /*  Given address of static base
            address = Value = ?
            base ptr -> address + offset4 = address
            base ptr -> address + offset3 = address
            base ptr -> address + offset2 = address
            static base -> address + offset1 = address
        */
        for (unsigned int i = 0; i < offsets.size(); ++i)
        {
            ReadFromAddress(hProc, newPtr, &newPtr, sizeof(addr));
            newPtr += offsets[i];
        }
        return newPtr;
    }

    void ReadFromAddress(HANDLE hProc, uintptr_t lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize)
    {
        bool rpmStatus = ReadProcessMemory(hProc, (LPCVOID*)lpBaseAddr, lpBuffer, nSize, NULL);
        if (rpmStatus == 0)
        {
            std::cout << "ReadProcessMemory call Failed\nError Code: " << std::dec << GetLastError() << std::endl;
            system("pause");
            CloseHandle(hProc);
            exit(-1);
        }
    }
    void WriteToAddress(HANDLE hProc, uintptr_t lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize)
    {
        bool rpmStatus = WriteProcessMemory(hProc, (LPCVOID*)lpBaseAddr, lpBuffer, nSize, NULL);
        if (rpmStatus == 0)
        {
            std::cout << "WiteProcessMemory call Failed\nError Code: " << std::dec << GetLastError() << std::endl;
            system("pause");
            CloseHandle(hProc);
            exit(-1);
        }
    }
    HANDLE GetProcessByName(std::wstring name)
    {
        DWORD procID = 0;

        // Create toolhelp snapshot.
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 proc;

        ZeroMemory(&proc, sizeof(proc));
        proc.dwSize = sizeof(proc);

        // Walkthrough all processes.
        if (Process32First(snapshot, &proc))
        {
            do
            {
                // Compare process.szExeFile based on format of name, i.e., trim file path
                // trim .exe if necessary, etc.
                if (proc.szExeFile == name)
                {
                    procID = proc.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &proc));
        }

        CloseHandle(snapshot);

        if (procID != 0)
        {
            return OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        }
        else
        {
            return NULL;
        }
    }
    void readByte(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        ReadFromAddress(hProc, addr, lpBuffer, sizeof(byte));
    }
    void readInt(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        ReadFromAddress(hProc, addr, lpBuffer, sizeof(int));
    }
    void readString(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer, size_t nSize)
    {
        ReadFromAddress(hProc, addr, lpBuffer, nSize);
    }
    void readFloat(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        ReadFromAddress(hProc, addr, lpBuffer, sizeof(float));
    }
    void readDouble(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        ReadFromAddress(hProc, addr, lpBuffer, sizeof(double));
    }

    void writeByte(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        WriteToAddress(hProc, addr, lpBuffer, sizeof(byte));
    }
    void writeInt(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        WriteToAddress(hProc, addr, lpBuffer, sizeof(int));
    }
    void writeString(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer, size_t nSize)
    {
        WriteToAddress(hProc, addr, lpBuffer, nSize);
    }
    void writeFloat(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        WriteToAddress(hProc, addr, lpBuffer, sizeof(float));
    }
    void writeDouble(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer)
    {
        WriteToAddress(hProc, addr, lpBuffer, sizeof(double));
    }
}