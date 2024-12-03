#include "App.h"
#include "Box.h"
#include <memory>

App::App()
	:
	wnd(800, 600, "My Window")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
		));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		UpdateFrame();
		DoFrame();
	}
}

App::~App()
{}

void App::UpdateFrame()
{

	if (wnd.kbd.KeyIsPressed('W'))
	{
		y1 -= 0.02f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		y1 += 0.02f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		x1 += 0.02f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		x1 -= 0.02f;
	}
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		z1 += 0.002f;
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		z1 -= 0.002f;
	}
}

void App::DoFrame()
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(y1, 3*y1/4, z1, x1));
	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}