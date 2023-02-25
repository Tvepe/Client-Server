#pragma once
#include <string>
#include <mutex>
#include <condition_variable>

class Buff 
{	
	std::string buff;
public:
	std::mutex lockmx;
	std::condition_variable cv;
	std::string status;
	Buff(std::string str);
	Buff() {};
	~Buff() {};
	std::string ReadBuffer();
	void SetBuffer(std::string str);
	void ThreadOneFunc();
	void ThreadTwoFunc();
};

bool isNumeric(std::string const& str);

