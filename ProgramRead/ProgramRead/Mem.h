#pragma once
#include <windows.h>
#include <vector>
#include <iostream>
#include <tlhelp32.h>
namespace mem
{
    //uintptr_t GetValueFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets);

    uintptr_t GetAddrFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets);

    void ReadFromAddress(HANDLE hProc, uintptr_t lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize);
    void WriteToAddress(HANDLE hProc, uintptr_t lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize);
    HANDLE GetProcessByName(std::wstring name);
    void readByte(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void readInt(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void readString(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer, size_t nSize);
    void readFloat(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void readDouble(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void writeByte(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void writeInt(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void writeString(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer, size_t nSize);
    void writeFloat(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
    void writeDouble(HANDLE hProc, uintptr_t addr, LPVOID lpBuffer);
};

