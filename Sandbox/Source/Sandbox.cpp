#include "Sandbox.hpp"

#include <string>
#include <sstream>
#include <fstream>

Sandbox::Sandbox()
{
	
}

Sandbox::Sandbox(aio::AppSpecifications& appSpecs)
	: Application (appSpecs)
{
	aio::Renderer::SetAPI(DX11);
}

Sandbox::~Sandbox()
{
}

void Sandbox::Start()
{
	PushLayer(new MainLayer());
}

MainLayer::MainLayer()
	: Layer("Main")
{
}

void MainLayer::OnAttach()
{
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

	vb->SetLayout(layout);

	vi->SetVertexBuffer(vb);
	vi->SetIndexBuffer(ib);

	aio::Renderer::GetShaderLibrary().LoadSlang("Quad", vi);
	texture = aio::Texture::Create("../../Sandbox/Assets/images/awesomeface.png");
	//texture = aio::Texture::Create(1, 1);
}

void MainLayer::OnUpdate()
{
	using namespace aio;

	if (Input::GetKeyboard()->IsHeld(KeyCode::F10))
		AIO_LOG_TRACE("F10 was Held");
	
	if (Input::GetKeyboard()->IsReleased(KeyCode::F10))
		AIO_LOG_TRACE("F10 was released");

	vi->Bind();
	aio::Renderer::GetShaderLibrary().Get("Quad")->Bind();
	texture->Bind(0);
	Renderer::Draw();
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
