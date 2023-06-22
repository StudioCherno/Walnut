#pragma once

#include "StreamWriter.h"
#include "StreamReader.h"

#include "Walnut/Core/Assert.h"

#include <filesystem>
#include <fstream>

namespace Walnut
{
	//==============================================================================
	/// BufferStreamWriter
	class BufferStreamWriter : public StreamWriter
	{
	public:
		BufferStreamWriter(Buffer targetBuffer, uint64_t position = 0);
		BufferStreamWriter(const BufferStreamWriter&) = delete;
		virtual ~BufferStreamWriter() override = default;

		bool IsStreamGood() const final { return (bool)m_TargetBuffer; }
		uint64_t GetStreamPosition() override { return m_BufferPosition; }
		void SetStreamPosition(uint64_t position) override { m_BufferPosition = position; }
		bool WriteData(const char* data, size_t size) final;

		// Returns Buffer with currently written size
		Buffer GetBuffer() const { return Buffer(m_TargetBuffer, m_BufferPosition); }
	private:
		Buffer m_TargetBuffer;
		uint64_t m_BufferPosition = 0;
	};

	//==============================================================================
	/// BufferStreamReader
	class BufferStreamReader : public StreamReader
	{
	public:
		BufferStreamReader(Buffer targetBuffer, uint64_t position = 0);
		BufferStreamReader(const BufferStreamReader&) = delete;
		virtual ~BufferStreamReader() override = default;

		bool IsStreamGood() const final { return (bool)m_TargetBuffer; }
		uint64_t GetStreamPosition() override { return m_BufferPosition; }
		void SetStreamPosition(uint64_t position) override { m_BufferPosition = position; }
		bool ReadData(char* destination, size_t size) override;

		// Returns Buffer with currently read size
		Buffer GetBuffer() const { return Buffer(m_TargetBuffer, m_BufferPosition); }
	private:
		Buffer m_TargetBuffer;
		uint64_t m_BufferPosition = 0;
	};

} // namespace Walnut
