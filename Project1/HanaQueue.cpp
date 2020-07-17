#include "HanaQueue.h"

template <class DataType>
HanaQueue<DataType>::HanaQueue(int MaxLength){

	if (MaxLength <= 0) MaxLength = 200;

	_maxLength = MaxLength;
	_dataArray = new DataType[_maxLength];

	for (int i = 0; i < _maxLength; i++)
		*(_dataArray + i) = 0;				//Initialize DataArray

	_front = _dataArray;
	_back = _dataArray;
}

template <class DataType>
HanaQueue<DataType>::~HanaQueue(){
	delete[]_dataArray;
}

template <class DataType>
int HanaQueue<DataType>::size(){
	return _size;
}

template <class DataType>
int HanaQueue<DataType>::maxLength(){
	return _maxLength;
}

template <class DataType>
DataType HanaQueue<DataType>::Front(){
	if (_size != 0) return *_front;
	else return 0;
}

template <class DataType>
DataType HanaQueue<DataType>::Back(){
	if (_size != 0) return *_back;
	else return 0;
}

template <class DataType>
DataType HanaQueue<DataType>::ElementAt(int Index){
	if ((Index >= _size) || (Index < 0))return 0;		//Out of range

	int subLength = _maxLength - 1 - (_front - _dataArray);

	if (Index> subLength) return*(_dataArray + Index - subLength - 1);
	else return *(_front + Index);
}

template <class DataType>
void HanaQueue<DataType>::Push(DataType InputData){

	if (_size == _maxLength)return;		//Array is full

	if (_size > 0){
		if (_back == (_dataArray + _maxLength - 1)){
			//_back points to end of array
			_back = _dataArray;
		}
		else _back++;
	}

	*(_back) = InputData;
	_size++;
	return;
}

template <class DataType>
DataType HanaQueue<DataType>::Pop(){

	if (_size == 0)return 0;	//Array is empty

	_popData = *_front;		//Store data in _popData
	*_front = 0;			//Clear data in *(_front)

	if (_size > 1){
		if (_front == (_dataArray + _maxLength - 1)){
			//_front points to end of array
			_front = _dataArray;
		}
		else _front++;
	}
	_size--;
	return _popData;
}