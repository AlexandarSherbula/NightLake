#include "aio_pch.hpp"
#include "Application.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

#include "Utils/Timer.hpp"

namespace aio
{
	static Application* sInstance = nullptr;

	Application::Application()
	{
	}

	Application::Application(AppSpecifications& appSpecs)
	{
		mRenderingFlag = OpenGL;

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
		Log::Init();

		mMainWindow = Window::Create({ mAppSpecs.title, mAppSpecs.width, mAppSpecs.height, mAppSpecs.vSync, AIO_BIND_EVENT_FN(Application::OnEvent) });
		Input::Init();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
		
		AppTimer::Start();
		while (mRunning)
		{
			AppTimer::Update();

			mMainWindow->PollEvents();
			Input::Scan();

			imguiLayer->Begin();

			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			mMainWindow->Update();

			for (Layer* layer : mLayerStack)
				layer->OnImGuiRender();

			mMainWindow->SwapChain();

			Input::Reset();
		}

		//Temporal untill there is ImGui support for both DX11 and OpenGL
		mLayerStack.EndAndClear();

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

	void Application::SetRenderingApi(RenderAPI_Flag flag)
	{
#if defined (AIO_WINDOWS)
		mRenderingFlag = flag;
#else
		mRenderingFlag = OpenGL;
#endif
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
		//glViewport(0, 0, e.GetWidth(), e.GetHeight());
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


