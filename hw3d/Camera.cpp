#include "Camera.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	const auto pos = dx::XMVector3Transform(
		dx::XMVectorSet( 0.0f,0.0f,-r,0.0f ),
		dx::XMMatrixRotationRollPitchYaw( phi,-theta,0.0f )
	);
	return dx::XMMatrixLookAtLH(
		pos,dx::XMVectorZero(),
		dx::XMVectorSet( 0.0f,1.0f,0.0f,0.0f )
	) * dx::XMMatrixRotationRollPitchYaw(
		pitch,-yaw,roll
	);
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
		r -= 0.05f;
	}
	if (kbd.KeyIsPressed('S'))
	{
		r += 0.05f;
	}
	if (kbd.KeyIsPressed('A'))
	{
		yaw -= 0.015f;
	}
	if (kbd.KeyIsPressed('D'))
	{
		yaw += 0.015f;
	}
	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		pitch -= 0.015f;
	}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		pitch += 0.015f;
	}
	if (kbd.KeyIsPressed('P'))
	{
		roll -= 0.15f;
	}
	if (kbd.KeyIsPressed('O'))
	{
		theta -= 0.015f;
	}
	if (kbd.KeyIsPressed('I'))
	{
		phi -= 0.015f;
	}
	if (kbd.KeyIsPressed('U'))
	{
		yaw -= 0.015f;
	}
	if (kbd.KeyIsPressed('Z'))
	{
		pitch -= 0.15f;
	}
	if (kbd.KeyIsPressed('T'))
	{
		pitch -= 0.15f;
	}
	if (kbd.KeyIsPressed('R'))
	{
		yaw -= 0.15f;
	}
	if (kbd.KeyIsPressed('E'))
	{
		r -= 0.15f;
	}
}