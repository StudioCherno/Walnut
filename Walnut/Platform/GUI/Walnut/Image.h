#pragma once

#include <string>

#include "vulkan/vulkan.h"

namespace Walnut {

	enum class ImageFormat
	{
		None = 0,
		RGBA,
		RGBA32F
	};

	class Image
	{
	public:
		Image(std::string_view path);
		Image(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr);
		~Image();

		void SetData(const void* data);

		VkDescriptorSet GetDescriptorSet() const { return m_DescriptorSet; }

		void Resize(uint32_t width, uint32_t height);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		static void* Decode(const void* data, uint64_t length, uint32_t& outWidth, uint32_t& outHeight);
	private:
		void AllocateMemory(uint64_t size);
		void Release();
	private:
		uint32_t m_Width = 0, m_Height = 0;

		VkImage m_Image = 0;
		VkImageView m_ImageView = 0;
		VkDeviceMemory m_Memory = 0;
		VkSampler m_Sampler = 0;

		ImageFormat m_Format = ImageFormat::None;

		VkBuffer m_StagingBuffer = 0;
		VkDeviceMemory m_StagingBufferMemory = 0;

		size_t m_AlignedSize = 0;

		VkDescriptorSet m_DescriptorSet = 0;

		std::string m_Filepath;
	};

}



