#pragma once

#include "Renderer/Shader.hpp"

namespace aio
{
	class OpenGL_Shader : public Shader
	{
	public:
		OpenGL_Shader(const std::string& name, const std::string& filepath, const Ref<VertexInput>& vertexInput);
		OpenGL_Shader(const std::string& name, const std::string& vertexFile, const std::string& pixelFile, const Ref<VertexInput>& vertexInput);
		~OpenGL_Shader();

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int32_t value);
		void SetIntArray(const std::string& name, int32_t* values, uint32_t count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const Vector2& value);
		void SetFloat3(const std::string& name, const Vector3& value);
		void SetFloat4(const std::string& name, const Vector4& value);

		void SetMat3x3(const std::string& name, const glm::mat3x3& matrix);
		void SetMat4x4(const std::string& name, const Mat4x4& matrix);
	private:
		void Compile(const Ref<VertexInput>& vertexBuffer);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	private:
		uint32_t mID;
		std::unordered_map<GLenum, std::string> mShaderSource;
	};
}