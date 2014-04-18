#pragma once 
#include "Common.h"

class Stage{
private:
	int Width;
	int Height;
	char* stageData;
public:
	Stage(char* stage){
		stageData = new char[strlen(stage)+1];
		strcpy(stageData, stage);
	};
	Stage(const Stage& obj){
		stageData = new char[strlen(obj.stageData) + 1];
		strcpy(stageData, obj.stageData);
	};
	~Stage(){
		delete[] stageData;
	};

	Stage operator=(const Stage& obj){
		if (this != &obj){
			delete[] stageData;
			stageData = new char[strlen(obj.stageData) + 1];
			strcpy(stageData, obj.stageData);
		}
	};
	void setWidth(int argumentWidth){ Width = argumentWidth; }
	void setHeight(int argumentHeight){ Height = argumentHeight; }
	void setStageData(char* argumentStage){ stageData = argumentStage; }
};