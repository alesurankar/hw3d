#include "App.h"
#include "Box.h"
#include <memory>

App::App()
	:
	wnd(800, 600, "My Window"),
	rng(rd()),
	adist(0.0f, 6.283f),
	ddist(0.0f, 6.283f),
	odist(0.0f, 3.1415f * 0.3f),
	rdist(6.0f, 20.0f),
	ad(0.0f, 0.000000001f),
	dd(0.0f, 0.000000001f),
	od(0.0f, 0.000000001f),
	ld(0.0f, 0.000000001f),
	dist(0.0f, 10.0f)
{
	
	for (auto i = 0; i < 1000; i++)
	{
		boxes1.emplace_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
		));
	}
	box = std::make_unique<Box>(wnd.Gfx(), rng, ad,
		dd, od, ld, 0.0f, -20.9f, 1.2f);
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 1000.0f));
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
{
}

void App::UpdateFrame()
{
	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes1)
	{
		b->Update(dt, wnd.kbd);
		b->UpdateWorld(wnd.kbd);
	}
	for (auto& b : boxes2)
	{
		b->Update(dt, wnd.kbd);
		b->UpdateWorld(wnd.kbd);
	}
	box->UpdatePlayer(wnd.kbd);
	
	if (wnd.kbd.KeyIsPressed(VK_TAB)) {
		boxes2.emplace_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist, dist(rng), dist(rng), dist(rng)
		));
	}
}

void App::DoFrame()
{
	for (auto& b : boxes1)
	{
		b->Draw(wnd.Gfx());
	}
	for (auto& b : boxes2)
	{
		b->Draw(wnd.Gfx());
	}
	box->Draw(wnd.Gfx());
	wnd.Gfx().EndFrame();
}