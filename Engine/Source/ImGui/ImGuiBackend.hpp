#pragma once



namespace aio
{
	class ImGuiBackend
	{
	public:
		virtual void Init() = 0;
		virtual void Begin() = 0;
		virtual void Update() = 0;
		virtual void ShutDown() = 0;
	};
}