#include "App.h"
#include <algorithm>
#include "MyMath.h"
#include "imgui/imgui.h"
#include "MyUtil.h"
#include "Testing.h"
#include "PerfLog.h"
#include "TestModelProbe.h"
#include "Camera.h"
#include "Channels.h"

namespace dx = DirectX;

App::App(const std::string& commandLine)
	:
	commandLine(commandLine),
	wnd(1280, 720, "My DirectX Framework"),
	scriptCommander(TokenizeQuoted(commandLine)),
	light(wnd.Gfx(), { 10.0f,80.0f,0.0f })
{
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, PI / 2.0f));

	sphere.SetPos({ 10.0f,5.0f,6.0f });

	sphere.LinkTechniques(rg);
	rg.BindShadowCamera(*light.ShareCamera());
	light.LinkTechniques(rg);
	cameras.LinkTechniques(rg);
}
void App::HandleInput(float dt)
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}
	
		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		case VK_RETURN:
			savingDepth = true;
			break;
		}
	}
	
	float speed = 2* dt;
	
	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			cameras->Translate({ 0.0f,0.0f,speed });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			cameras->Translate({ -speed,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			cameras->Translate({ 0.0f,0.0f,-speed });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			cameras->Translate({ speed,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			cameras->Translate({ 0.0f,speed,0.0f });
		}
		if (wnd.kbd.KeyIsPressed(VK_SHIFT))
		{
			cameras->Translate({ 0.0f,-speed,0.0f });
		}
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			cameras->Rotate((float)delta->x, (float)delta->y);
		}
	}
}

void App::DoFrame(float dt)
{
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	rg.BindMainCamera(cameras.GetActiveCamera());

	light.Submit(Chan::main);
	sphere.Submit(Chan::main);
	cameras.Submit(Chan::main);

	rg.Execute(wnd.Gfx());

	// imgui windows
	light.SpawnControlWindow(wnd.Gfx(), "light 1");
	//ShowImguiDemoWindow();

	//rg.RenderWindows(wnd.Gfx());

	// present
	wnd.Gfx().EndFrame();
	rg.Reset();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}

App::~App()
{
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
		// execute the game logic
		const auto dt = timer.Mark() * speed_factor;
		HandleInput(dt);
		DoFrame(dt);
	}
}