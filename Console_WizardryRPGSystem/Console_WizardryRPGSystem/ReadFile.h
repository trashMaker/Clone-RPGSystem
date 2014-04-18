#pragma once 
#include "Common.h"
#include <fstream>
#include "Stage.h"

class ReadFile{
public:

	ReadFile();
	~ReadFile();

	bool readFile(Stage& obj);
};