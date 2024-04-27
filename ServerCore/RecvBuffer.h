#pragma once

class RecvBuffer
{
public:
	RecvBuffer(uint32 bufferSize);
	~RecvBuffer();

	BYTE* getReadPos();
	BYTE* getWritePos();

	uint32 getDataSize() const;
	uint32 getFreeSize() const;

	bool read(uint32 numOfBytes);
	bool write(uint32 numOfBytes);

	void clean();

private:
	const uint32 _bufferCount;
	const uint32 _bufferSize;
	const uint32 _capacity;

	vector<BYTE> _buffer;
	uint32 _readPos;
	uint32 _writePos;
};

