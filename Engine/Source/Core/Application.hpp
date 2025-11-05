#pragma once

#include "Layer.hpp"
#include "ImGui/ImGuiLayer.hpp"

#include "Window/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Events/Events.hpp"
#include "Input/Input.hpp"

namespace aio
{
	struct AppSpecifications
	{
		const char* title = "Alexio Engine";
		int32_t width = 1280;
		int32_t height = 720;
		bool vSync = true;
		bool isFullScreen = false;

		GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL;
	};

	class Application
	{
	public:
		Application();
		Application(AppSpecifications& appSpecs);
		~Application();

		virtual void Start() = 0;
		void Run();
		void Stop();

		static Application& Get();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline const Ref<Window>& GetAppWindow() const { return mAppWindow; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		bool mRunning;
		AppSpecifications mAppSpecs;

		Ref<Window> mAppWindow;
		LayerStack mLayerStack;
		ImGuiLayer* imguiLayer;
	private:
		static Ref<Camera> sMainCamera;
	};
}
