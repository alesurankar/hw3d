#pragma once
#include "Graphics.h"
#include "SolidSphere.h"
#include "TransformCbuf.h"

class Point
{
public:
    Point(Graphics& gfx, float radius = 1.0f);
    void SpawnControlWindow() noexcept;
    void Draw(Graphics& gfx) const noexcept(!NDEBUG);
private:
    DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
    SolidSphere mesh;
    mutable TransformCbuf tcbuf;
};
