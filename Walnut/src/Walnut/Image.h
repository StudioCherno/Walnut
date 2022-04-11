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

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		void AllocateMemory(uint64_t size);
	private:
		uint32_t m_Width = 0, m_Height = 0;

		VkImage m_Image = nullptr;
		VkImageView m_ImageView = nullptr;
		VkDeviceMemory m_Memory = nullptr;
		VkSampler m_Sampler = nullptr;

		ImageFormat m_Format = ImageFormat::None;

		VkBuffer m_StagingBuffer = nullptr;
		VkDeviceMemory m_StagingBufferMemory = nullptr;

		size_t m_AlignedSize = 0;

		VkDescriptorSet m_DescriptorSet = nullptr;

		std::string m_Filepath;
	};

}



