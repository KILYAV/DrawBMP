#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

class DrawBMP {
public:
	bool OpenBMP(const std::string& fileName);
	bool DisplayBMP();
	void CloseBMP();
private:
	void Clear();

	std::string name;
	std::fstream file;
};