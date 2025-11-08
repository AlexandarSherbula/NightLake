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

	TextureSpecification texSpec;
	Assets::Create<Texture>(texSpec, "awesomeface.png");
}

void MainLayer::OnUpdate()
{
	AIO_PROFILE_FUNCTION();

	Renderer::ClearColor(Vector4(0.1f, 0.1f, 0.1f, 1.0f));

	Renderer::DrawQuad(Vector2(-1.0f, -1.0f), Vector2(0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	Renderer::DrawQuad(Vector2(1.0f, 0.0f), Vector2(0.5f, 0.5f), Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	Renderer::DrawSprite(Assets::Get<Texture>("awesomeface"), Vector2(-0.5f, -0.5f), Vector2(1.0f, 1.0f));
	Renderer::DrawSprite(Assets::Get<Texture>("awesomeface"), Vector2( 0.8f, -0.5f), Vector2(0.5f, 0.5f));
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
