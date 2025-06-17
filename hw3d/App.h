#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
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
	void ShowRawInputWindow();
private:
	bool cursorEnabled = true;
	int x = 0, y = 0;
	ImguiManager imgui;
	Window wnd;
	MyTimer timer;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light; 
	Model nano{ wnd.Gfx(),"Models\\nano.gltf" };
};