#include "aio_pch.hpp"
#include "Application.hpp"
#include "Renderer/Renderer.hpp"

#include "Utils/Timer.hpp"
#include "Renderer/Camera.hpp"

#include "Utils/FileReading.hpp"

#include "slang.h"
#include "slang-com-helper.h"
#include "slang-com-ptr.h"

namespace aio
{
	static Application* sInstance = nullptr;

	Ref<Camera> Application::sMainCamera = nullptr;

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
		Slang::ComPtr<slang::IGlobalSession> globalSession;
		createGlobalSession(globalSession.writeRef());

		// 2. Create Session
		slang::SessionDesc sessionDesc = {};
		slang::TargetDesc targetDesc = {};

		// --- GLSL target instead of SPIR-V ---
		targetDesc.format = SLANG_GLSL;
		targetDesc.profile = globalSession->findProfile("glsl_450");

		sessionDesc.targets = &targetDesc;
		sessionDesc.targetCount = 1;

		Slang::ComPtr<slang::ISession> session;
		globalSession->createSession(sessionDesc, session.writeRef());

		mAppWindow = Window::Create({ mAppSpecs.title, mAppSpecs.width, mAppSpecs.height, mAppSpecs.vSync, AIO_BIND_EVENT_FN(Application::OnEvent) });
		Input::Init();

		Renderer::Init();

		sMainCamera = CreateRef<Camera>(static_cast<float>(mAppSpecs.width) / static_cast<float>(mAppSpecs.height));

		Start();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
		
		AppTimer::Start();
		while (mRunning)
		{
			AppTimer::Update();

			mAppWindow->PollEvents();
			Input::Scan();

			imguiLayer->Begin();

			sMainCamera->OnUpdate(AppTimer::DeltaTime());

			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			for (Layer* layer : mLayerStack)
				layer->OnImGuiRender();

			mAppWindow->SwapBuffers();
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

		if (sMainCamera != nullptr)
			sMainCamera->OnEvent(e);

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


