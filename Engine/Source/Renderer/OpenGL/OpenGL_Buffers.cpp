#include "aio_pch.hpp"
#include "OpenGL_Buffers.hpp"

namespace aio
{
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(uint32_t size)
	{
		glCreateVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glCreateBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
	}

	OpenGL_VertexBuffer::OpenGL_VertexBuffer(const void* data, uint32_t size)
	{
		glCreateVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glCreateBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		glBindVertexArray(0);
	}

	OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
	{
		glDeleteBuffers(1, &mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	void OpenGL_VertexBuffer::Bind() const
	{
		glBindVertexArray(mVAO);
	}

	void OpenGL_VertexBuffer::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGL_VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////
	///////////INDEX BUFFER//////////////////////////////
	/////////////////////////////////////////////////////

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* indices, uint32_t count)
	{
		glCreateBuffers(1, &mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
	{
		glDeleteBuffers(1, &mID);
	}

	void OpenGL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	}

	void OpenGL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////
	///////////UNIFORM BUFFER////////////////////////////
	/////////////////////////////////////////////////////

	UniformBuffer::UniformBuffer(uint32_t block_size, uint32_t slot)
	{
	}

	UniformBuffer::~UniformBuffer()
	{
	}

	void UniformBuffer::SetData(const void* data, uint32_t data_size)
	{
	}

	void UniformBuffer::Bind(uint32_t binding)
	{
	}

}