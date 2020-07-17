#ifndef _HANAQUEUE_H_
#define _HANAQUEUE_H_

#include <stdlib.h>
using namespace std;

template <class DataType>
class HanaQueue{

public:
	HanaQueue(int = 200);
	~HanaQueue();

	int size();
	int maxLength();

	DataType Front();
	DataType Back();
	void Push(DataType);
	DataType Pop();
	DataType ElementAt(int);

private:

	DataType* _dataArray = 0;
	DataType* _front = 0;
	DataType* _back = 0;

	int _size = 0;		//Amount of Data
	int _maxLength = 0;	//Maximum length of queue
	DataType _popData;	//Used to store data that popped
};

#include "HanaQueue.cpp"
#endif