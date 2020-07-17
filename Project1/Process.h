#include <stdlib.h>
#include <string>
using namespace std;

class Process{

public:

	Process(string, int);
	~Process();

	int executeTime();
	string processName();
	void Execute();

private:

	int _executeTime = 0;
	string _processName = "";
};