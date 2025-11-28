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
};