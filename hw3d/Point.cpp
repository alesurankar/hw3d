#include "Point.h"
#include "imgui/imgui.h"

Point::Point(Graphics& gfx, float radius)
	:
	pos(1.0f, 1.0f, 1.0f),
	mesh(gfx, radius),
	tcbuf(gfx, mesh)
{
	// Apply initial position to sphere
	mesh.SetPos(pos);

	// Attach transform constant buffer to mesh
	mesh.AddBind(std::make_unique<TransformCbuf>(gfx, mesh));
}

void Point::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Point"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &pos.z, -60.0f, 60.0f, "%.1f");
	}
	ImGui::End();
}


void Point::Draw(Graphics& gfx) const noexcept(!NDEBUG)
{
	mesh.SetPos(pos);
	mesh.Draw(gfx);
}