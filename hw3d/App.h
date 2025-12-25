#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "Object.h"
#include <memory>
#include <vector>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void UpdateFrame();
	void DoFrame();
private:
	Window wnd;
	MyTimer timer;
	std::vector<std::unique_ptr<Object>> obj;
	bool pressed = false;
	static constexpr float aspect_ratio = Window::ScreenWidth / float(Window::ScreenHeight);
	static constexpr float nearZ = 0.5f;
	static constexpr float farZ = 800.0f;
	static constexpr float hfov = 70.0f;
	static constexpr float hfovRad = hfov * 3.14159265f / 180.0f;
};