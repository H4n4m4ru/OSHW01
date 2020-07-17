#include "Process.h"

Process::Process(string ProcessName, int ExecuteTime){

	_processName = ProcessName;
	if (ExecuteTime < 0)
		ExecuteTime = 0;
	_executeTime = ExecuteTime;
}

Process::~Process(){
}

string Process::processName(){
	return _processName;
}

int Process::executeTime(){
	return _executeTime;
}

void Process::Execute(){
	if (_executeTime == 0)return;
	_executeTime--;
}