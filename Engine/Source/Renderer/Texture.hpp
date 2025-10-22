#pragma once

namespace aio
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		inline uint32_t GetWidth() const { return mWidth; }
		inline uint32_t GetHeight() const { return mHeight; }
		inline uint32_t GetID() const { return mID; }

		virtual void Bind(uint32_t slot) const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Ref<Texture> Create(uint32_t width, uint32_t height);
		static Ref<Texture> Create(const std::string& filepath);
	protected:
		uint32_t mID;
		uint32_t mWidth, mHeight;
	};
}
