#pragma once

namespace game {

	enum struct CollisionType
	{
		Player,
		Wall,
		Enemy,
		Projectile,
		COUNT
	};

namespace components{

	struct SphereCollider
	{
		SphereCollider(float _radius, CollisionType _type) 
			: radius(_radius), type(_type) {}

		CollisionType type;
		float radius;
	};

	struct AreaRestriction
	{
		enum struct Areas
		{
			Left, Right, COUNT
		};
		explicit AreaRestriction(Areas _area) : area(_area) {}

		Areas area;
	};
}
}