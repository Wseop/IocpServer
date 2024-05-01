#pragma once

class SendBuffer
{
public:
	SendBuffer(uint32 bufferSize);
	~SendBuffer();

	inline BYTE* getBuffer() { return _buffer.data(); }

	inline uint32 getBufferSize() const { return _bufferSize; }

private:
	vector<BYTE> _buffer;
	uint32 _bufferSize;
};

