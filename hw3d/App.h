#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "CameraContainer.h"
#include "PointLight.h"
#include "TestCube.h"
#include "Model.h"
#include "ScriptCommander.h"
#include "BlurOutlineRenderGraph.h"
#include "MyMath.h"

class App
{
public:
	App(const std::string& commandLine = "");
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame(float dt);
	void HandleInput(float dt);
	void ShowImguiDemoWindow();
private:
	std::string commandLine;
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	ScriptCommander scriptCommander;
	Rgph::BlurOutlineRenderGraph rg{ wnd.Gfx() };
	MyTimer timer;
	float speed_factor = 1.0f;
	CameraContainer cameras;
	PointLight light;

	SolidSphere sphere{ wnd.Gfx(),4.0f, /*DirectX::XMFLOAT3{0.5f,0.4f,0.8f}*/ };
	bool savingDepth = false;
};