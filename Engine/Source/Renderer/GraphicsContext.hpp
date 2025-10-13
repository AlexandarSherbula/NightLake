#pragma once


namespace aio
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void SwapChain() = 0;

		inline void SetVSync(bool vSync) { mVSync = vSync; }
		inline bool IsVSync() const { return mVSync; }

		virtual void ImGuiBackendInit() = 0;
		virtual void ImGuiBackendBegin() = 0;
		virtual void ImGuiBackendUpdate() = 0;
		virtual void ImGuiBackendShutDown() = 0;
	protected:
		bool mVSync;
	};
}