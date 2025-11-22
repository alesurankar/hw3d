#pragma once
#include "Window.h"
#include "MyTimer.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	MyTimer timer;
	MyTimer timer2;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};