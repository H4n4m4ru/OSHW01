#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include "HanaQueue.h"
#include "Process.h"
using namespace std;

void main(){
	
	ifstream InputData;
	string filePath, buffer_STR;
	int buffer_INT = 0, timeLimit = 0, tick = 0, counter = 0;
	bool IO_flag = false;
	HanaQueue<Process*> Ready, Waiting, Running, Exit;
	
	//Load data
	do{
		cout << "Enter a file path to load data : ";
		cin >> filePath;
		InputData.open(filePath);
	} while (!InputData);

	//Initialize 
	InputData >> buffer_STR;
	InputData >> timeLimit;	//Got time limit.

	cout << "\n<< Execution time limit : " << timeLimit << "(s) >>\n";

	while (InputData >> buffer_STR){
		InputData >> buffer_INT;
		Ready.Push(new Process(buffer_STR, buffer_INT));
	}

	Running.Push(Ready.Pop());

	//Show Results (Start)
	cout << "\nTime(s) : " << tick << "\n";

	cout << "Ready   : ";
	for (int i = 0; i < Ready.size(); i++){
		cout << Ready.ElementAt(i)->processName() << "(" << Ready.ElementAt(i)->executeTime() << ")";
		if (i != (Ready.size() - 1))cout << ",";
	}
	cout << "\n";

	cout << "Waiting : ";
	for (int i = 0; i < Waiting.size(); i++){
		cout << Waiting.ElementAt(i)->processName() << "(" << Waiting.ElementAt(i)->executeTime() << ")";
		if (i != (Waiting.size() - 1))cout << ",";
	}
	cout << "\n";

	cout << "Running : ";
	for (int i = 0; i < Running.size(); i++){
		cout << Running.ElementAt(i)->processName() << "(" << Running.ElementAt(i)->executeTime() << ")";
		if (i != (Running.size() - 1))cout << ",";
	}
	cout << "\n";

	cout << "Exit    : ";
	for (int i = 0; i < Exit.size(); i++){
		cout << Exit.ElementAt(i)->processName() << "(" << Exit.ElementAt(i)->executeTime() << ")";
		if (i != (Exit.size() - 1))cout << ",";
	}
	cout << "\n\n";

	//Show Results (End)

	//Simulation Start
	while (true){
		
		//Get command
		while (IO_flag){
			//Only available for "C"(Complete) or "E"(Execute)
			cout << "Enter \"C\" to complete I/O or \"E\" to continue executing : ";
			cin >> buffer_STR;

			if (buffer_STR == "c" || buffer_STR == "C")break;
			else if (buffer_STR == "e" || buffer_STR == "E")break;
		}

		while (!IO_flag){
			//Only available for "I"(I/O) or "E"(Execute)
			cout << "Enter \"I\" to trigger I/O event or \"E\" to continue executing : ";
			cin >> buffer_STR;

			if (buffer_STR == "i" || buffer_STR == "I")break;
			else if (buffer_STR == "e" || buffer_STR == "E")break;
		}

		//
		tick++;	//Time never stop unless u have...ZAWARUDOOOOO!!!

		if ((!IO_flag) && (buffer_STR == "e" || buffer_STR == "E")){
			//Process execute
			Running.Front()->Execute();
			
			if (Running.Front()->executeTime() == 0){
				//Process end
				Exit.Push(Running.Pop());
				if (Ready.size() > 0)Running.Push(Ready.Pop());
				counter = 0;
			}
			else if((++counter)==timeLimit){
				//Overtime
				Ready.Push(Running.Pop());
				Running.Push(Ready.Pop());
				counter = 0;
			}
		}
		else if((!IO_flag) && (buffer_STR == "i" || buffer_STR == "I")){
			// I/O event
			cout << "\n<< I/O! >>\n";
			Waiting.Push(Running.Pop());
			IO_flag = true;
		}
		else if (IO_flag && (buffer_STR == "c" || buffer_STR == "C")){
			// I/O complete
			cout << "\n<< I/O Complete! >>\n";
			Ready.Push(Waiting.Pop());
			Running.Push(Ready.Pop());
			counter = 0;
			IO_flag = false;
		}
		
		//Show Results (Start)
		cout << "\nTime(s) : " << tick << "\n";

		cout << "Ready   : ";
		for (int i = 0; i < Ready.size(); i++){
			cout << Ready.ElementAt(i)->processName() << "(" << Ready.ElementAt(i)->executeTime() << ")";
			if (i != (Ready.size() - 1))cout << ",";
		}
		cout << "\n";

		cout << "Waiting : ";
		for (int i = 0; i < Waiting.size(); i++){
			cout << Waiting.ElementAt(i)->processName() << "(" << Waiting.ElementAt(i)->executeTime() << ")";
			if (i != (Waiting.size() - 1))cout << ",";
		}
		cout << "\n";

		cout << "Running : ";
		for (int i = 0; i < Running.size(); i++){
			cout << Running.ElementAt(i)->processName() << "(" << Running.ElementAt(i)->executeTime() << ")";
			if (i != (Running.size() - 1))cout << ",";
		}
		cout << "\n";

		cout << "Exit    : ";
		for (int i = 0; i < Exit.size(); i++){
			cout << Exit.ElementAt(i)->processName() << "(" << Exit.ElementAt(i)->executeTime() << ")";
			if (i != (Exit.size() - 1))cout << ",";
		}
		cout << "\n\n";

		//Show Results (End)
	
		if (Running.size() == 0 && Waiting.size() == 0)break;
	}

	InputData.close();
	system("PAUSE");
}

