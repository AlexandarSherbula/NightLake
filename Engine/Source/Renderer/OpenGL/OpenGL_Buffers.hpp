#pragma once

#include "Renderer/Buffers.hpp"

namespace aio
{
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(uint32_t size);
		OpenGL_VertexBuffer(const void* data, uint32_t size);

		~OpenGL_VertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t mVBO;
		uint32_t mVAO;
	};

	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGL_IndexBuffer();

		void Bind() override;
		void Unbind() override;

	private:
		uint32_t mID;
	};

	class UniformBuffer : public ConstantBuffer
	{
	public:
		UniformBuffer(uint32_t block_size, uint32_t slot);
		~UniformBuffer();

		void SetData(const void* data, uint32_t data_size) override;
		void Bind(uint32_t binding) override;
	private:
		uint32_t mID;
	};

	class VertexArray : public VertexInput
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const override;
		void Unbind() const override;

		void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
	private:
		uint32_t mID;
	};
}