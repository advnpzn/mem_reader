#include <Windows.h>
#include <iostream>

int main() {

	int int_read = 0;
	int pid = 0;
	
	std::cout << "Enter Process ID : ";
	std::cin >> std::dec >> pid;
	std::cout << std::endl;

	HANDLE hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,	
		FALSE,
		pid			
	);

	if (hProcess == NULL) {
		std::cout << "OpenProcess Failed.\nProcessID : " << pid << "\Error Code : " << std::dec << GetLastError() << std::endl;
		CloseHandle(hProcess);
		system("pause");
		return EXIT_FAILURE;
	}

	std::cout << "OpenProcess Succeeded.\nProcessID : " << pid << std::endl;

	uintptr_t mem_addr = 0x0;

	std::cout << "Enter Memory Address (HEX) : 0x";
	std::cin >> std::hex >> mem_addr;

	std::cout << "You Entered : 0x" << std::hex << std::uppercase << mem_addr << std::endl;

	BOOL read_proc_mem = ReadProcessMemory(
		hProcess,
		(LPCVOID)mem_addr,
		&int_read,
		sizeof(int),
		NULL
	);

	CloseHandle(hProcess);

	if (read_proc_mem == 0) {
		std::cout << "Error!\nError Code : " << std::dec << GetLastError << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	std::cout << "RPM Success." << std::endl;

	std::cout << "int_read = " << std::dec << int_read << std::endl;
	
	return EXIT_SUCCESS;
}