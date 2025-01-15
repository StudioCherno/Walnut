#include "StreamReader.h"

namespace Walnut
{
	bool StreamReader::ReadBuffer(Buffer& buffer, uint32_t size)
	{
		buffer.Size = size;
		if (size == 0)
		{
			if (!ReadData((char*)&buffer.Size, sizeof(uint32_t)))
				return false;
		}

		buffer.Allocate(buffer.Size);
		return ReadData((char*)buffer.Data, buffer.Size);
	}

	bool StreamReader::ReadString(std::string& string)
	{
		size_t size;
		if (!ReadData((char*)&size, sizeof(size_t)))
			return false;

		string.resize(size);
		return ReadData((char*)string.data(), sizeof(char) * size);
	}

} // namespace Hazel
