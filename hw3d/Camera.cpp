#include "Camera.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	// camera rotation (pitch, yaw, roll)
	const auto rotation = dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// camera position in world space
	const auto position = dx::XMVectorSet(x, y, z, 1.0f);

	// local forward direction (camera looks down +Z in LH)
	const auto localForward = dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// rotate the forward direction by camera rotation (w=0 -> direction)
	auto rotatedForward = dx::XMVector3TransformNormal(localForward, rotation);
	rotatedForward = dx::XMVector3Normalize(rotatedForward);

	// compute the target position in world space
	const auto target = dx::XMVectorAdd(position, rotatedForward);

	// rotate the up vector as well (w=0 -> direction)
	auto up = dx::XMVector3TransformNormal(dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
	up = dx::XMVector3Normalize(up);

	// build and return the view matrix (eye, at, up)
	return dx::XMMatrixLookAtLH(position, target, up);
}



void Camera::SpawnControlWindow() noexcept
{
	if( ImGui::Begin( "Camera" ) )
	{
		ImGui::Text( "Position" );
		ImGui::SliderFloat( "R",&r,0.0f,80.0f,"%.1f" );
		ImGui::SliderAngle( "Theta",&theta,-180.0f,180.0f );
		ImGui::SliderAngle( "Phi",&phi,-89.0f,89.0f );
		ImGui::Text( "Orientation" );
		ImGui::SliderAngle( "Roll",&roll,-180.0f,180.0f );
		ImGui::SliderAngle( "Pitch",&pitch,-180.0f,180.0f );
		ImGui::SliderAngle( "Yaw",&yaw,-180.0f,180.0f );
		if( ImGui::Button( "Reset" ) )
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset() noexcept
{
	r = 20.0f;
	theta = 0.0f;
	phi = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
}

void Camera::UpdateWorld(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('W'))
	{
		z += 0.15f;
	}
	if (kbd.KeyIsPressed('S'))
	{
		z -= 0.15f;
	}
	if (kbd.KeyIsPressed('A'))
	{
		x -= 0.15f;
	}
	if (kbd.KeyIsPressed('D'))
	{
		x += 0.15f;
	}
	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		y -= 0.15f;
	}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		y += 0.15f;
	}
	if (kbd.KeyIsPressed('Q'))
	{
		yaw -= 0.02f;
	}
	if (kbd.KeyIsPressed('E'))
	{
		yaw += 0.02f;
	}
	if (kbd.KeyIsPressed('R'))
	{
		roll -= 0.02f;
	}
	//if (kbd.KeyIsPressed('O'))
	//{
	//	theta -= 0.015f;
	//}
	//if (kbd.KeyIsPressed('I'))
	//{
	//	phi -= 0.015f;
	//}
	//if (kbd.KeyIsPressed('U'))
	//{
	//	yaw -= 0.015f;
	//}
	//if (kbd.KeyIsPressed('Z'))
	//{
	//	pitch -= 0.15f;
	//}
	//if (kbd.KeyIsPressed('T'))
	//{
	//	x += 0.15f;
	//}
	//if (kbd.KeyIsPressed('R'))
	//{
	//	z += 0.15f;
	//}
	//if (kbd.KeyIsPressed('E'))
	//{
	//	y += 0.15f;
	//}
}