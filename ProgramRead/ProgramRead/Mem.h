#pragma once
#include <windows.h>
#include <vector>
#include <iostream>
namespace Mem
{
    uintptr_t GetValueFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets);

    uintptr_t GetAddrFromBase(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets);

    void ReadFromAddress(HANDLE hProc, LPCVOID lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize);
    void WriteToAddress(HANDLE hProc, LPCVOID lpBaseAddr, LPVOID lpBuffer, SIZE_T nSize);
};

