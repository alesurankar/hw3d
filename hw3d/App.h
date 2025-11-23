#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include <random>

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
	ImguiManager imgui;
	Window wnd;
	MyTimer timer; 
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> adist;
	std::uniform_real_distribution<float> ddist;
	std::uniform_real_distribution<float> odist;
	std::uniform_real_distribution<float> rdist;
	std::uniform_real_distribution<float> bdist;
	std::uniform_real_distribution<float> ad;
	std::uniform_real_distribution<float> dd;
	std::uniform_real_distribution<float> od;
	std::uniform_real_distribution<float> ld;
	std::uniform_real_distribution<float> bd;
	std::uniform_real_distribution<float> dist;
	std::vector<std::unique_ptr<class Box>> boxes1;
	std::vector<std::unique_ptr<class Box>> boxes2;
	std::unique_ptr<class Box> box;
	float speed_factor = 1.0f;
	Camera cam;
};