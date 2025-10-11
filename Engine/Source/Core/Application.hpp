#pragma once

#include "Layer.hpp"
#include "ImGui/ImGuiLayer.hpp"

#include "Window/Window.hpp"
#include "Events/Events.hpp"
#include "Input/Input.hpp"

namespace aio
{
	struct AppSpecifications
	{
		const char* title;
		uint32_t width;
		uint32_t height;
		bool vSync = true;
	};

	class Application
	{
	public:
		Application();
		Application(AppSpecifications& appSpecs);
		~Application();

		void Run();
		void Stop();

		static Application& Get();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window* GetWindow() { return mMainWindow.get(); }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		Ref<Window> mMainWindow;
		bool mRunning;
		LayerStack mLayerStack;
		ImGuiLayer* imguiLayer;
		AppSpecifications mAppSpecs;
	};
}
