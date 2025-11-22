#pragma once
#include "DrawableBase.h"

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		float x_in = 0.0f, float y_in = 0.0f, float z_in = 0.0f);
	void Update(float dt, Keyboard& kbd) noexcept override;
	void UpdateWorld(Keyboard& kbd);
	void UpdatePlayer(Keyboard& kbd);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	float y;
	float z;
	float x;
	float u = 0.0f;
	float i = 20.0f;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};