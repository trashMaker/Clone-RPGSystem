
#include "Header.h"

int main(){
	using namespace Cto;

	Tool tool;

	tool.callReadFile();

	int max = tool.getManyLines();

	for (int i = 0; i < max; i++){
		tool.setSockect();
		tool.setMsg(i);
		
		tool.setTempBuf();
		tool.setBuf();
		tool.setLen();
		tool.sendData(i);
		tool.deleteSokect();

		tool.draw(i);

	}

	return 0;
}
