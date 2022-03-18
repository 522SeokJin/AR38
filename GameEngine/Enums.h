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
	BackBuffer,	// ����ۿ� ���� �׸��°�
	World,
	UI,
	Debug,
};