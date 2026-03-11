#include "FileName.h"

int main() {
	// filename 변수는 세이브 파일의 이름을 저장하는 데 사용됩니다. 이 변수는 saveData와 loadData 함수에서 파일 입출력 작업을 수행할 때 사용됩니다.
	const char* filename = "userdata.bin";
	Userdata data = { "Player1", 10, 100.0f, 5, 20, 3, 1.5f, 0 };
	saveData(filename, data);	// saveData 함수를 호출하여 data 구조체의 데이터를 filename으로 지정된 파일에 저장.
	Userdata loadedData;	
	

	return 0;
}