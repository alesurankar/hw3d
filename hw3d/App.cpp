#include "App.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "MyMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd(800, 600, "My Window"),
	rng(rd()),
	adist(0.0f, 6.283f),
	ddist(0.0f, 6.283f),
	odist(0.0f, 3.1415f * 0.3f),
	rdist(6.0f, 20.0f),
	bdist( 0.4f,3.0f ),
	ad(0.0f, 0.000000001f),
	dd(0.0f, 0.000000001f),
	od(0.0f, 0.000000001f),
	ld(0.0f, 0.000000001f),
	bd(0.0f, 0.000000001f),
	dist(0.0f, 10.0f)
{

	for (auto i = 0; i < 1000; i++)
	{
		boxes1.emplace_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist, bdist
		));
	}
	box = std::make_unique<Box>(wnd.Gfx(), rng, ad,
		dd, od, ld, bd, 0.0f, -20.9f, 1.2f);
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 1000.0f));
}


void App::UpdateFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());

	if (wnd.kbd.KeyIsPressed(VK_TAB)) {
		boxes2.emplace_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist, bdist, dist(rng), dist(rng), dist(rng)
		));
	}

	for (auto& b : boxes1)
	{
		b->Update(dt, wnd.kbd);
		//b->UpdateWorld(wnd.kbd);
	}
	for (auto& b : boxes2)
	{
		b->Update(dt, wnd.kbd);
		//b->UpdateWorld(wnd.kbd);
	}
	box->UpdatePlayer(wnd.kbd);
	cam.UpdateWorld(wnd.kbd);
}


void App::DoFrame()
{

	//for (auto& b : boxes1)
	//{
	//	b->Draw(wnd.Gfx());
	//}
	for (auto& b : boxes2)
	{
		b->Draw(wnd.Gfx());
	}
	box->Draw(wnd.Gfx());

	// imgui window to control simulation speed
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 4.0f);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
	}
	ImGui::End();

	// imgui window to control camera
	cam.SpawnControlWindow();
}


App::~App()
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
		UpdateFrame();
		DoFrame();
		// present
		wnd.Gfx().EndFrame();
	}
}