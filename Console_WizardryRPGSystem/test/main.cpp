#include <iostream>
#include <fstream>
using namespace std;
const char* const STAGEDATA = "../Stage/stage.txt";

int add(int digit);
int main(){

	int width = 0,height = 0;

	char BufferName[10];
	char BufferSize[30];
	char BufferStage[100];
	char* pBuffer = BufferSize;
	int tempArray[10];
	ifstream fin(STAGEDATA);

	if (!fin){
		cout << "ファイルをオープンできませんでした\n";
		return 1;
	}

	fin >> BufferName >> BufferSize;
	
	do{
		if (*pBuffer == ','){ ++pBuffer; }

		for (; 0x41 <= *pBuffer && *pBuffer <= 0x7A; ++pBuffer){}

		if (width == 0){
			int digit = 0;

			if (*pBuffer == '='){
				++pBuffer;
				while (*pBuffer != ','){
					tempArray[digit] = (int)((*pBuffer) - 0x30);
					++digit;
					++pBuffer;
				}
			}	
			for (int i = 0; i < digit; ++i){//10かける回数
				width += tempArray[i] * add(digit-i);
			}
		}
		else {
			int digit = 0;

			if (*pBuffer == '='){
				++pBuffer;
				while (*pBuffer != '\0'){
					tempArray[digit] = (int)((*pBuffer) - 0x30);
					++digit;
					++pBuffer;
				}
			}
			for (int i = 0; i < digit; ++i){//10かける回数
				height += tempArray[i] * add(digit - i);
			}
		}
		
	} while (*pBuffer == ',');

	pBuffer = BufferStage;

	for (int y = 0; y < height; ++y){
		fin >> pBuffer;
		pBuffer += width;
	}
	cout << "(width,height)(" << width << "," << height << ")" << endl;
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			cout <<  BufferStage[y*width + x] ;
		}
		cout << endl;
	}

	return 0;
}

int add(int digit){
	if (digit == 1){
		return 1;
	}
	else{
		return 10 * add(digit - 1);
	}
}

//#include <iostream>
//#include <string.h>
//using namespace std;
//
//int main() {
//	char str[] = "Width12,Height3456";
//	strtok(str, ",");
//	auto width = str + strlen("Width");
//	auto height = strtok(NULL, ",") + strlen("Height");
//	cout << atoi(width) << ", " << atoi(height);
//	return 0;
//}
