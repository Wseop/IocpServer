#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(uint32 bufferSize) :
	_bufferCount(10),
	_bufferSize(bufferSize),
	_capacity(_bufferCount * _bufferSize),
	_readPos(0),
	_writePos(0)
{
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

bool RecvBuffer::read(uint32 numOfBytes)
{
	if (numOfBytes > getDataSize())
	{
		cout << "[RecvBuffer] read overflow." << endl;
		return false;
	}
	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::write(uint32 numOfBytes)
{
	if (numOfBytes > getFreeSize())
	{
		cout << "[RecvBuffer] write overflow." << endl;
		return false;
	}
	_writePos += numOfBytes;
	return true;
}

void RecvBuffer::clean()
{
	uint32 dataSize = getDataSize();
	if (dataSize == 0)
	{
		_readPos = 0;
		_writePos = 0;
	}
	else if (getFreeSize() < _bufferSize)
	{
		::memcpy(_buffer.data(), getReadPos(), dataSize);
		_readPos = 0;
		_writePos = dataSize;
	}
}
