#include "aio_pch.hpp"
#include "Application.hpp"
#include "Renderer/Renderer.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

#include "Utils/Timer.hpp"

namespace aio
{
	static Application* sInstance = nullptr;
	static Ref<VertexBuffer> vb;

	Application::Application()
	{
	}

	Application::Application(AppSpecifications& appSpecs)
	{
		Log::Init();

		sInstance = this;

		mRunning = true;

		mAppSpecs = appSpecs;
	}

	Application::~Application()
	{		
		sInstance = nullptr;
	}

	void Application::Run()
	{
		mMainWindow = Window::Create({ mAppSpecs.title, mAppSpecs.width, mAppSpecs.height, mAppSpecs.vSync, AIO_BIND_EVENT_FN(Application::OnEvent) });
		Input::Init();

		Renderer::Init();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);

		float positions[6] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
		};

		vb = aio::VertexBuffer::Create(positions, sizeof(float) * 6);
		
		AppTimer::Start();
		while (mRunning)
		{
			AppTimer::Update();

			mMainWindow->PollEvents();
			Input::Scan();

			imguiLayer->Begin();

			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			vb->Bind();
			Renderer::Draw();
			vb->Unbind();

			for (Layer* layer : mLayerStack)
				layer->OnImGuiRender();

			mMainWindow->SwapBuffers();

			Input::Reset();
		}

		Input::Close();
	}

	void Application::Stop()
	{
		if (mRunning)
			mRunning = false;
	}

	Application& Application::Get()
	{
		AIO_ASSERT(sInstance, "Instance hasn't been made");
		return *sInstance;
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AIO_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(AIO_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<MouseMovedEvent>(AIO_BIND_EVENT_FN(Application::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(AIO_BIND_EVENT_FN(Application::OnMouseScrolled));

		for (auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RendererBackend* backend = Renderer::Backend().get();
		if (backend != nullptr)
		{
			Renderer::Backend()->SetViewport(Vector2(0.0f, 0.0f), Vector2(e.GetWidth(), e.GetHeight()));
		}
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{		
		Input::GetMouse()->SetPosition(Vector2(e.GetX(), e.GetY()));
		return true;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& e)
	{
		Input::GetMouse()->NewMouseWheelState(Vector2(e.GetXOffset(), e.GetYOffset()));
		return true;
	}
}


