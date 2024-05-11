#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(uint32 bufferSize) :
	_bufferSize(bufferSize),
	_capacity(BUFFER_COUNT * _bufferSize),
	_readPos(0),
	_writePos(0)
{
	// buffer의 크기는 BUFFER_COUNT * _bufferSize로 설정.
	// 커서 초기화 시(cleanPos) 복사가 일어날 확률을 줄임.
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

BYTE* RecvBuffer::getReadPos()
{
	assert(_readPos < _capacity);
	return &_buffer[_readPos];
}

BYTE* RecvBuffer::getWritePos()
{
	assert(_writePos < _capacity);
	return &_buffer[_writePos];
}

uint32 RecvBuffer::getDataSize() const
{
	assert(_readPos <= _writePos);
	return _writePos - _readPos;
}

uint32 RecvBuffer::getFreeSize() const
{
	assert(_writePos <= _capacity);
	return _capacity - _writePos;
}

bool RecvBuffer::moveReadPos(uint32 numOfBytes)
{
	if (numOfBytes > getDataSize())
	{
		cout << "[RecvBuffer] read overflow." << endl;
		return false;
	}
	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::moveWritePos(uint32 numOfBytes)
{
	if (numOfBytes > getFreeSize())
	{
		cout << "[RecvBuffer] write overflow." << endl;
		return false;
	}
	_writePos += numOfBytes;
	return true;
}

void RecvBuffer::cleanPos()
{
	uint32 dataSize = getDataSize();
	if (dataSize == 0)
	{
		// 복사할 데이터가 없는 상황. 커서만 초기화.
		_readPos = 0;
		_writePos = 0;
	}
	else if (getFreeSize() < _bufferSize)
	{
		// 데이터를 맨 앞으로 복사 후 커서 정리.
		::memcpy(_buffer.data(), getReadPos(), dataSize);
		_readPos = 0;
		_writePos = dataSize;
	}
}
