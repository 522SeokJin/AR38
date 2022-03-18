#pragma once

enum class CollisionType
{
	// 2D
	Point2D,
	Circle,
	Rect,
	OrientedRect,

	// 3D
	Point3D,
	Sphere,
	AABBBox,
	OBBBox,

	MAX,
};

enum class RenderingOrder
{
	BackBuffer,	// 백버퍼에 직접 그리는것
	World,
	UI,
	Debug,
};