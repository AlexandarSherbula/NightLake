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
	float positions[6] = 
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	uint32_t indices[3] =
	{
		0, 1, 2
	};

	vi = aio::VertexInput::Create();
	vb = aio::VertexBuffer::Create(positions, sizeof(float) * 6);
	ib = aio::IndexBuffer::Create(indices, 3);

	aio::BufferLayout layout =
	{
		{aio::ShaderDataType::Float2, "aPosition" }
	};

	vb->SetLayout(layout);

	vi->SetVertexBuffer(vb);
	vi->SetIndexBuffer(ib);

	shader = aio::Shader::Create("shader", vi);
}

void MainLayer::OnUpdate()
{
	using namespace aio;
	if (Input::GetKeyboard()->IsHeld(KeyCode::F10))
		AIO_LOG_TRACE("F10 was Held");
	
	if (Input::GetKeyboard()->IsReleased(KeyCode::F10))
		AIO_LOG_TRACE("F10 was released");

	vi->Bind();
	shader->Bind();
	Renderer::Draw();
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
