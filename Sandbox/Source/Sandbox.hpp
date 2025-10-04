#pragma once

#include "NightLake.hpp"

class Sandbox : public nle::Application
{
public:
	Sandbox();
	Sandbox(nle::AppSpecifications& appSpecs);
	~Sandbox();
};

class MainLayer : public nle::Layer
{
public:
	MainLayer();

	void OnAttach() override;
	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(nle::Event& event) override;
};