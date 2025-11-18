#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "TestPlane.h"
#include <set>
#include "Mesh.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
private:
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	MyTimer timer;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light; 
	Model wall{ wnd.Gfx(),"Models\\brick_wall\\brick_wall.obj" };
	TestPlane tp{ wnd.Gfx(),1.0 };
	//Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj" };
};