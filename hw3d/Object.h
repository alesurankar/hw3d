#pragma once
#include "Drawable.h"

class Object : public Drawable
{
public:
	Object(Graphics& gfx, float x_in = 0.0f, float u_in = 0.0f, float i_in = 20.0f);
	void Update(float dt, Keyboard& kbd) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	// positional
	float r = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta =  0.0f;
	float phi = 0.0f;
	float chi = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float x = 0.0f;
	float u = 0.0f;
	float i = 20.0f;
};