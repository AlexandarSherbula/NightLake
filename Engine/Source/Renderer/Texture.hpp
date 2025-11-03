#pragma once

namespace aio
{
	enum class ImageFormat {
		None = 0, 
		RED8UN, 
		RED8UI, 
		RED16UI, 
		RED32UI, 
		RED32F, 
		RG8, 
		RG16F, 
		RG32F, 
		RGB, 
		RGBA, 
		RGBA16F, 
		RGBA32F, 
		B10R11G11UF, 
		SRGB,
		SRGBA,
		DEPTH32FSTENCIL8UINT,
		DEPTH32F,
		DEPTH24STENCIL8,
		// Defaults
		Depth = DEPTH24STENCIL8, 
	};

	enum class TextureWrap
	{
		None = 0,
		Clamp,
		Repeat
	};

	enum class TextureFilter
	{
		None = 0,
		Linear,
		Nearest,
		Cubic
	};

	struct TextureSpecification
	{
		ImageFormat Format = ImageFormat::RGBA;
		uint32_t Width = 1;
		uint32_t Height = 1;
		TextureWrap SamplerWrap = TextureWrap::Repeat;
		TextureFilter SamplerFilter = TextureFilter::Linear;

		bool GenerateMips = true;

		std::string DebugName;
	};


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
		static Ref<Texture> Create(const std::filesystem::path& filepath, std::string name = "");
		static Ref<Texture> CreateAsset(const std::string& imageFile, std::string name = "");

		static Ref<Texture> Get(const std::string& name);
		static void Add(const Ref<Texture>& texture, std::string name = "");
		static bool Exists(const std::string& name);
	protected:
		uint32_t mID;
		uint32_t mWidth, mHeight;
		std::string mName;

		static std::unordered_map<std::string, Ref<Texture>> sTextures;
	};
}
