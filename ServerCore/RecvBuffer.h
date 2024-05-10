#pragma once

class RecvBuffer
{
	const uint32 BUFFER_COUNT = 10;

public:
	RecvBuffer(uint32 bufferSize);
	~RecvBuffer();

	BYTE* getReadPos();
	BYTE* getWritePos();

	uint32 getDataSize() const;
	uint32 getFreeSize() const;

	bool moveReadPos(uint32 numOfBytes);
	bool moveWritePos(uint32 numOfBytes);

	void cleanPos();

private:
	const uint32 _bufferSize;
	const uint32 _capacity;

	vector<BYTE> _buffer;
	uint32 _readPos;
	uint32 _writePos;
};

