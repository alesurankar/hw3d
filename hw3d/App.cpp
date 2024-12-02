#include "App.h"

App::App()
	:
	wnd(800, 600, "My Window")
{}

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
		
		if (wnd.kbd.KeyIsPressed('W'))
		{
			z1 -= 0.02f;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			z1 += 0.02f;
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
			z1 += 0.1f;
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			z1 -= 0.1f;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	

	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle(
		-timer.Peek(),
		x1,
		z1
	);
	/*wnd.Gfx().DrawTestTriangle(
		timer.Peek(),
		wnd.mouse.GetPosX() / 400.0f - 1.0f,
		-wnd.mouse.GetPosY() / 300.0f + 1.0f
	);*/
	wnd.Gfx().EndFrame();
}