#include "Object.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"

Object::Object(Graphics& gfx, float x_in, float u_in, float i_in)
	:
	x(x_in),
	u(u_in),
	i(i_in)
{
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};
	const std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f,-1.0f },
		{ -1.0f,1.0f,-1.0f },
		{ 1.0f,1.0f,-1.0f },
		{ -1.0f,-1.0f,1.0f },
		{ 1.0f,-1.0f,1.0f },
		{ -1.0f,1.0f,1.0f },
		{ 1.0f,1.0f,1.0f },
	};
	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantBuffer2 cb2 =
	{
		{
			{ 1.0f,0.0f,1.0f },
			{ 1.0f,0.0f,0.0f },
			{ 0.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f },
			{ 1.0f,1.0f,0.0f },
			{ 0.0f,1.0f,1.0f },
		}
	};
	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void Object::Update(float dt, Keyboard& kbd) noexcept
{
	float speed = 2.0f * dt;
	if (kbd.KeyIsPressed(VK_SHIFT)) {
		speed = 4.0f * dt;
	}
	if (kbd.KeyIsPressed('W')) {
		theta -= speed;
	}
	if (kbd.KeyIsPressed('S')) {
		phi += speed;
	}
	if (kbd.KeyIsPressed('A')) {
		chi += speed;
	}
	if (kbd.KeyIsPressed('Q')) {
		roll -= speed;
	}
	if (kbd.KeyIsPressed('E')) {
		pitch += speed;
	}
	if (kbd.KeyIsPressed('R')) {
		yaw += speed;
	}
	if (kbd.KeyIsPressed('D')) {
		r -= speed;
	}
	if (kbd.KeyIsPressed('H')) {
		x += speed;
	}
	if (kbd.KeyIsPressed('J')) {
		u += speed;
	}
	if (kbd.KeyIsPressed('K')) {
		i -= speed;
	}
	if (kbd.KeyIsPressed('B')) {
		x -= speed;
	}
	if (kbd.KeyIsPressed('N')) {
		u -= speed;
	}
	if (kbd.KeyIsPressed('M')) {
		i += speed;
	}
	if (kbd.KeyIsPressed(VK_CONTROL)) {
		y += speed;
	}
	if (kbd.KeyIsPressed(VK_SPACE)) {
		z -= speed;
	}
}

DirectX::XMMATRIX Object::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, y, z) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(x, u, i);
}