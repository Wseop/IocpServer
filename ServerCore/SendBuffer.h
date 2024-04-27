#pragma once

class SendBuffer
{
public:
	SendBuffer(uint32 bufferSize);
	~SendBuffer();

	BYTE* getBuffer() { return _buffer.data(); }

	uint32 getBufferSize() const { return _bufferSize; }

private:
	vector<BYTE> _buffer;
	uint32 _bufferSize;
};

