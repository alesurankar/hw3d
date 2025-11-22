#include "Box.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"

Box::Box(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	float x_in, float y_in, float z_in)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng)),
	x(x_in),
	y(y_in),
	z(z_in)
{
	if (!IsStaticInitialized())
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
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		const std::vector<unsigned short> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

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
		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void Box::Update(float dt, Keyboard& kbd) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

void Box::UpdateWorld(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('W'))
	{
		z -= 0.15f;
	}
	if (kbd.KeyIsPressed('S'))
	{
		z += 0.15f;
	}
	if (kbd.KeyIsPressed('A'))
	{
		x += 0.15f;
	}
	if (kbd.KeyIsPressed('D'))
	{
		x -= 0.15f;
	}
	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		y += 0.15f;
	}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		y -= 0.15f;
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
		chi -= 0.015f;
	}
	if (kbd.KeyIsPressed('Z'))
	{
		i -= 0.15f;
	}
	if (kbd.KeyIsPressed('T'))
	{
		pitch -= 0.15f;
	}
	if (kbd.KeyIsPressed('R'))
	{
		yaw -= 0.15f;
	}
	/*if (kbd.KeyIsPressed('E'))
	{
		r -= 0.15f;
	}*/
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, i, u) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(x, y, z);
}

void Box::UpdatePlayer(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('W') && !kbd.KeyIsPressed('S')) {
		if (u <= 0.2f)
			u += 0.005f;
	}
	else if (!kbd.KeyIsPressed('W') && kbd.KeyIsPressed('S')) {
		if (u >= -0.2f)
			u -= 0.005f;
	}
	else if (!kbd.KeyIsPressed('W') && !kbd.KeyIsPressed('S')) {
		if (u > 0.0f)
			u -= 0.005f;
		if (u < 0.0f)
			u += 0.005f;
	}

	if (kbd.KeyIsPressed('D') && !kbd.KeyIsPressed('A')) {
		if (yaw <= 0.2f)
			yaw += 0.01f;
	}
	else if (!kbd.KeyIsPressed('D') && kbd.KeyIsPressed('A')) {
		if (yaw >= -0.2f)
			yaw -= 0.01f;
	}
	else if (!kbd.KeyIsPressed('D') && !kbd.KeyIsPressed('A')) {
		if (yaw > 0.0f)
			yaw -= 0.01f;
		if (yaw < 0.0f)
			yaw += 0.01f;
	}

	if (kbd.KeyIsPressed(VK_SHIFT) && !kbd.KeyIsPressed(VK_SPACE)) {
		if (pitch <= 0.2f)
			pitch += 0.01f;
	}
	else if (!kbd.KeyIsPressed(VK_SHIFT) && kbd.KeyIsPressed(VK_SPACE)) {
		if (pitch >= -0.2f)
			pitch -= 0.01f;
	}
	else if (!kbd.KeyIsPressed(VK_SHIFT) && !kbd.KeyIsPressed(VK_SPACE)) {
		if (pitch > 0.0f)
			pitch -= 0.01f;
		if (pitch < 0.0f)
			pitch += 0.01f;
	}



	/*if (kbd.KeyIsPressed('D')) {
		if (pitch <= 0.2f)
			pitch += 0.01f;
	}
	else {
		if (pitch > 0.0f)
			pitch -= 0.01f;
	}
	if (kbd.KeyIsPressed('A')) {
		if (pitch <= 0.2f)
			pitch += 0.01f;
	}
	else {
		if (pitch > 0.0f)
			pitch -= 0.01f;
	}
	if (kbd.KeyIsPressed('S'))
	{
		dpitch -= 0.01f;
	}
	if (kbd.KeyIsPressed('D'))
	{
		dyaw += 0.01f;
	}
	if (kbd.KeyIsPressed('A'))
	{
		dyaw -= 0.01f;
	}*/
}