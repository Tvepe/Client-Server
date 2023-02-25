#include <iostream>
#include <string>
#include "solution.h"
#include <thread>

int main(int args, char* argv[])
{
	Buff strBuff("");
	std::thread threadOne(&Buff::ThreadOneFunc,std::ref(strBuff));
	std::thread threadTwo(&Buff::ThreadTwoFunc,std::ref(strBuff));

	threadTwo.join();
	threadOne.join();
	
	system("pause");
}
