#pragma once

#include "Layer.hpp"

namespace nle
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		bool mBlockEvents = true;
	};
}