#include "Sandbox.hpp"

#include <string>
#include <sstream>
#include <fstream>

using namespace aio;

Sandbox::Sandbox()
{
	
}

Sandbox::Sandbox(aio::AppSpecifications& appSpecs)
	: Application (appSpecs)
{
	PushLayer(new MainLayer());
}

Sandbox::~Sandbox()
{
}

void Sandbox::Start()
{
}

MainLayer::MainLayer()
	: Layer("Main")
{
}

void MainLayer::OnAttach()
{
	AIO_PROFILE_FUNCTION();
	float positions[] = 
	{
		 0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    0.0f,
		-0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f,
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,    0.0f,
		 0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f,
	};

	uint32_t indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	vi = aio::VertexInput::Create();
	vb = aio::VertexBuffer::Create(positions, sizeof(positions));
	ib = aio::IndexBuffer::Create(indices, 6);

	aio::BufferLayout layout =
	{
		{aio::ShaderDataType::Float3, "aPosition" },
		{aio::ShaderDataType::Float4, "aColor"    },
		{aio::ShaderDataType::Float2, "aTexCoord" },
		{aio::ShaderDataType::Float,  "aTexIndex" }
	};

	TextureSpecification texSpec;

	vb->SetLayout(layout);

	vi->SetVertexBuffer(vb);
	vi->SetIndexBuffer(ib);

	Assets::Create<Shader>("Quad.slang", vi);
	Assets::Create<Texture>(texSpec, "awesomeface.png");

	texture = Texture::Create(texSpec);
}

void MainLayer::OnUpdate()
{
	AIO_PROFILE_FUNCTION();

	vi->Bind();
	Assets::Get<Shader>("Quad")->Bind();
	Assets::Get<Texture>("awesomeface")->Bind(0);
	Renderer::Draw();
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
