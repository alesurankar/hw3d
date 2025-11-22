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
		const float c = sin(timer.Peek()) / 2.0f + 0.5f;
		wnd.Gfx().ClearBuffer(c, c, 1.0f);
		DoFrame();
	}
}

void App::DoFrame()
{
	float dt = timer2.Mark();
	float speed = 4 * dt;
	if (wnd.kbd.KeyIsPressed('D'))
	{
		x -= speed;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		x += speed;
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		z -= speed;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		z += speed;
	}
	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		y += speed;
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		y -= speed;
	}
	wnd.Gfx().DrawTestTriangle(-timer.Peek(),x,y,z);
	//wnd.Gfx().DrawTestTriangle(timer.Peek(),wnd.mouse.GetPosX() / 400.0f - 1.0f,-wnd.mouse.GetPosY() / 300.0f + 1.0f);
	wnd.Gfx().EndFrame();
}