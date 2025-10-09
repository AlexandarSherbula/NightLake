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
		std::string title;
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

		void SetRenderingApi(RenderAPI_Flag flag);
		inline RenderAPI_Flag GetRenderingAPI_Flag() const { return mRenderingFlag; }

		inline Window* GetWindow() { return mMainWindow.get(); }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	public:
		Scope<Window> mMainWindow;
	private:
		bool mRunning;
		LayerStack mLayerStack;
		ImGuiLayer* imguiLayer;
		RenderAPI_Flag mRenderingFlag;
		AppSpecifications mAppSpecs;
	};
}
