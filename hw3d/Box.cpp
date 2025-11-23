#include "Box.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"


Box::Box(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist,
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
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};
		const auto model = Cube::Make<Vertex>();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorIndexVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

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

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng))
	);
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

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(r, 0.0f, 0.0f) * 
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
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