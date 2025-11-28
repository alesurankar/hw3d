#include "App.h"
#include "Box.h"

App::App()
	:
	wnd(800, 600, "My Window")
{
	obj.emplace_back(std::make_unique<Object>(wnd.Gfx()));
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 800.0f));
}


void App::UpdateFrame()
{
	auto dt = timer.Mark();
	for (auto& o : obj) {
		o->Update(dt, wnd.kbd);
	}
	if (wnd.kbd.KeyIsPressed(VK_TAB)) {
		if (pressed == false) {
			obj.emplace_back(std::make_unique<Object>(wnd.Gfx()));
		}
		pressed = true;
	}
	else {
		pressed = false;
	}
}


void App::DoFrame()
{
	for (auto& o : obj) {
		o->Draw(wnd.Gfx());
	}
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
		wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
		UpdateFrame();
		DoFrame();
		wnd.Gfx().EndFrame();
	}
}

App::~App()
{}