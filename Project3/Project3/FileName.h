#include <iostream>
#include <fstream>

using namespace std;

struct Userdata {
	char name[32];
	int level;
	float hp;
	int difense;
	int attack;
	int speed;
	float attack_speed;
	// checksum는 Userdata 구조체의 멤버로, unsigned int 타입으로 선언되어 있다. 
	// 이 변수는 Userdata 구조체의 데이터를 기반으로 계산된 체크섬 값을 저장하는 데 사용됨.
	unsigned int Checksum;
};

// calculateChecksum 함수는 템플릿 함수로, 다양한 데이터 타입에 대해 체크섬을 계산할 수 있음.
unsigned int calculateChecksum(const Userdata& data) {
	// offsetof 매크로는 C++에서 제공하는 매크로로, 구조체에서 특정 멤버의 오프셋(바이트 단위)을 계산하는 데 사용됩니다.
	size_t sizeToCalculate = offsetof(Userdata, Checksum);	// offsetof 매크로를 사용하여 Userdata 구조체에서 Checksum 멤버의 오프셋을 계산하여 offsetofChecksum 변수에 저장.
	// data의 주소를 unsigned int 포인터로 변환하여 바이트 단위로 접근할 수 있도록 합니다.
	// reinterpret_cast는 C++에서 제공하는 타입 변환 연산자로, 포인터 타입 간의 변환을 수행할 때 사용됨.
	const unsigned int* bytes = reinterpret_cast<const unsigned int*>(&data);
	unsigned int checksum = 0;		// checksum 변수를 초기화하여 체크섬 계산을 시작합니다.
	//sizeToCalculate 변수는 Userdata 구조체에서 Checksum 멤버까지의 바이트 수를 나타내며, 이 범위 내의 데이터를 바이트 단위로 접근하여 체크섬을 계산.
	for (size_t i = 0; i < sizeToCalculate; ++i) {
		checksum += bytes[i];
	}
	
	return checksum;
}
// saveData 함수는 Userdata 구조체의 데이터를 파일에 저장하는 역할을 합니다.
void saveData(const char* userdata, const Userdata& data) {
	//ofstream outFile(filename, ios::binary); = outFile 객체를 생성하여 filename으로 지정된 파일을 바이너리 모드로 염.
	ofstream outFile(userdata, ios::binary);
	if (outFile.is_open()) {
		//reinterpret_cast<const char*>(&data) = data의 주소를 const char* 타입으로 변환하여, 바이너리 데이터로 파일에 쓸 수 있도록 함.
		outFile.write(reinterpret_cast<const char*>(&data), sizeof(Userdata));
		outFile.close();
	}
}

void loadData(const char* userdata, Userdata& data) {
	ifstream inFile(userdata, ios::binary);
	if (inFile.is_open()) {
		// File 객체를 사용하여 파일에서 Userdata 구조체의 데이터를 읽어와 data 변수에 저장합니다.
		inFile.read(reinterpret_cast<char*>(&data), sizeof(Userdata));
		// calculateChecksum 함수를 호출하여 data의 체크섬을 계산하고, 이를 calculatedChecksum 변수에 저장.
		unsigned int calculatedChecksum = calculateChecksum(data);
		// data.Checksum과 calculatedChecksum을 비교하여 세이브 파일이 정상적으로 로드되었는지 여부를 판단.
		if (calculatedChecksum == data.Checksum) {
			cout << "세이브 파일이 정상적으로 로드되었습니다. " << endl;
		}
		else {
			cout << "세이브 파일이 손상되었습니다. " << endl;
		}
	}

}