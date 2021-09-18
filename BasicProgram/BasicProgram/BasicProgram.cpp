/*
Directions:
Once this is done you will create an infinite loop in which you will:
- Print to console "Process ID: " followed by the process ID of the program using the Windows API function GetCurrentProcessId() (Therefore, don't forget to #include <Windows.h> !!)
- Print to console "varInt (0x[ADDRESS OR THE VARIABLE]) = [VALUE OF THE VARIABLE]" (Remember that you can get the address of a variable by prefixing it by "&")
- Same thing for varString and varChar
- Same thing for our 3 pointers, print for example "ptr2int (0x[ADDRESS OF THE POINTER]) = 0x[ADDRESS POINTED])
- Print to console "Press ENTER to print again."
- Put something to pause, you can either use getchar() or system("pause > nul")
- Print to console a line of dashes ("-") and then let it loop back to the beginning


My solution: 

#include <iostream>
#include <Windows.h>
using std::string;

int main()
{
    int varInt = 123456;
    string varString = "DeafaultString";
    char arrChar[128] = "Long char array right there ->";
    int* ptr2int = &varInt;
    int* ptr2ptr = ptr2int;
    int* ptr2ptr2 = ptr2ptr;

    while (true)
    {
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "Process ID: " << GetCurrentProcessId() << std::endl;
        std::cout << "varInt 0x" << std::hex << &varInt << "= " << std::dec << varInt << std::endl;
        std::cout << "varString 0x" << std::hex << &varString << "= " << varString << std::endl;
        std::cout << "arrChar 0x" << std::hex << &arrChar << "= " << arrChar << std::endl;
        std::cout << "ptr2int 0x" << std::hex << &ptr2int << "= 0x" << ptr2int << std::endl;
        std::cout << "ptr2ptr 0x" << std::hex << &ptr2ptr << "= 0x" << ptr2ptr << std::endl;
        std::cout << "ptr2ptr2 0x" << std::hex << &ptr2ptr2 << "= 0x" << ptr2ptr2 << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "\nPress any key to go again\n" << std::endl;
        getchar();
    }
}*/
// Suggestes Solution:
#include <Windows.h>
#include <iostream>
#include <string>

#define CHAR_ARRAY_SIZE 128

using namespace std;

int main() {
	int varInt(123456);
	string varString("DefaultString");
	char arrChar[CHAR_ARRAY_SIZE] = "Long char array right there ->";
	int* ptr2int(&varInt);
	int** ptr2ptr(&ptr2int);
	int*** ptr2ptr2(&ptr2ptr);

	do {
		cout << "Process ID: " << dec << GetCurrentProcessId() << endl;
		cout << endl;
		cout << "varInt       (0x" << hex << uppercase << (uintptr_t)&varInt << ") = " << dec << varInt << endl;
		cout << "varString    (0x" << hex << uppercase << (uintptr_t)&varString << ") = " << varString << endl;
		cout << "arrChar[" << dec << CHAR_ARRAY_SIZE << "] (0x" << hex << uppercase << (uintptr_t)&arrChar << ") = " << arrChar << endl;
		cout << endl;
		cout << "ptr2int      (0x" << hex << uppercase << (uintptr_t)&ptr2int << ") = 0x" << ptr2int << endl;
		cout << "ptr2ptr      (0x" << hex << uppercase << (uintptr_t)&ptr2ptr << ") = 0x" << ptr2ptr << endl;
		cout << "ptr2ptr2     (0x" << hex << uppercase << (uintptr_t)&ptr2ptr2 << ") = 0x" << ptr2ptr2 << endl;
		cout << endl;
		cout << "Press ENTER to print again." << endl;
		getchar();
		cout << endl << "---------------------------------------------------" << endl << endl;
	} while (true);

	return EXIT_SUCCESS;

}