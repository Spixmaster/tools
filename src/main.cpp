#include <iostream>
#include "tools/Tools.h"

int main()
{
	std::setlocale(LC_ALL, "en_US.utf8");

	std::cout << "Some input: " << std::endl;
	std::wstring temp;
	wchar_t buffer[10000];
	std::wcin.getline(buffer, sizeof(buffer));

	std::cout << tools::Tools::encode_utf8(buffer) << std::endl;

	return 0;
}

