#pragma once
#include "CollisionComponent.h"
#include <iostream>
namespace Collisions {

inline bool IsColliding(CollisionComponent* colisionA, CollisionComponent* colisionB)
{
	//Need to rework everything except aabb aabb
	if (colisionA->colType ==CollisionType::point || colisionB->colType == CollisionType::point)
	{

		if (colisionA->colType == CollisionType::point && colisionB->colType == CollisionType::point)
		{
			// collision a point b point
			return (colisionA->getPosition()[0] == colisionB->getPosition()[0] &&
				colisionA->getPosition()[1] == colisionB->getPosition()[1] &&
				colisionA->getPosition()[2] == colisionB->getPosition()[2]);
		}
		if (colisionA->colType == CollisionType::point)
		{
			if (colisionB->colType == CollisionType::sphere)
			{
				//colision a point b sphere
				float distance = Maths::sqrt((colisionA->getPosition()[0] - colisionB->getPosition()[0]) * ((colisionA->getPosition()[0] - colisionB->getPosition()[0])) +
					(colisionA->getPosition()[1] - colisionB->getPosition()[1]) * ((colisionA->getPosition()[1] - colisionB->getPosition()[1])) +
					(colisionA->getPosition()[2] - colisionB->getPosition()[2]) * ((colisionA->getPosition()[2] - colisionB->getPosition()[2])));
				return distance < colisionB->radius;
			}
			//colision a point b aabb
			float boxmin[3] = { colisionA->getMin()[0] ,colisionA->getMin()[1],colisionA->getMin()[2] };
			float boxmax[3] = { colisionA->getMax()[0] ,colisionA->getMax()[1],colisionA->getMax()[2] };
			return ((colisionA->getPosition()[0] >= boxmin[0] && (colisionA->getPosition()[0] <= boxmax[0])) &&
				(colisionA->getPosition()[1] >= boxmin[1] && (colisionA->getPosition()[1] <= boxmax[1])) &&
				(colisionA->getPosition()[2] >= boxmin[2] && (colisionA->getPosition()[2] <= boxmax[2])));
		}
		if (colisionA->colType == CollisionType::sphere)
		{
			//colision a sphere point b
			float distance = Maths::sqrt((colisionB->getPosition()[0] - colisionA->getPosition()[0]) * ((colisionB->getPosition()[0] - colisionA->getPosition()[0])) +
				(colisionB->getPosition()[1] - colisionA->getPosition()[1]) * ((colisionB->getPosition()[1] - colisionA->getPosition()[1])) +
				(colisionB->getPosition()[2] - colisionA->getPosition()[2]) * ((colisionB->getPosition()[2] - colisionA->getPosition()[2])));
			return distance < colisionA->radius;
		}
		//colision a aabb point b	
		float boxmin[3] = { colisionA->getMin()[0] ,colisionA->getMin()[1],colisionA->getMin()[2] };
		float boxmax[3] = { colisionA->getMax()[0] ,colisionA->getMax()[1],colisionA->getMax()[2] };
		return ((colisionB->getPosition()[0] >= boxmin[0] && (colisionB->getPosition()[0] <= boxmax[0])) &&
			(colisionB->getPosition()[1] >= boxmin[1] && (colisionB->getPosition()[1] <= boxmax[1])) &&
			(colisionB->getPosition()[2] >= boxmin[2] && (colisionB->getPosition()[2] <= boxmax[2])));
	}
	else if (colisionA->colType == CollisionType::sphere || colisionB->colType == CollisionType::sphere) {
		if (colisionA->colType == CollisionType::sphere) {
			if (colisionB->colType == CollisionType::sphere) {
				//colision a sphere b sphere
				float distance = Maths::sqrt((colisionA->getPosition()[0] - colisionB->getPosition()[0]) * (colisionA->getPosition()[0] - colisionB->getPosition()[0]) +
					(colisionA->getPosition()[1] - colisionB->getPosition()[1]) * (colisionA->getPosition()[1] - colisionB->getPosition()[1]) +
					(colisionA->getPosition()[0] - colisionA->getPosition()[0]) * (colisionA->getPosition()[0] - colisionA->getPosition()[0]));
				return distance < (colisionA->radius + colisionB->radius);
			}
			//colision a sphere b aabb
			float boxmin[3] = { colisionA->getMin()[0] ,colisionA->getMin()[1],colisionA->getMin()[2] };
			float boxmax[3] = { colisionA->getMax()[0] ,colisionA->getMax()[1],colisionA->getMax()[2] };

			float x = (float)Maths::max(boxmin[0], (float)Maths::min(colisionA->getPosition()[0], boxmax[0]));
			float y = (float)Maths::max(boxmin[1], (float)Maths::min(colisionA->getPosition()[1], boxmax[1]));
			float z = (float)Maths::max(boxmin[2], (float)Maths::min(colisionA->getPosition()[2], boxmax[2]));

			float distance = Maths::sqrt((x - colisionA->getPosition()[0]) * (x - colisionA->getPosition()[0]) +
				(y - colisionA->getPosition()[1]) * (y - colisionA->getPosition()[1]) +
				(z - colisionA->getPosition()[2]) * (z - colisionA->getPosition()[2]));
			return distance < colisionA->radius;

		}
		//colision a aabb b sphere
		float boxmin[3] = { colisionA->getMin()[0] ,colisionA->getMin()[1],colisionA->getMin()[2] };
		float boxmax[3] = { colisionA->getMax()[0] ,colisionA->getMax()[1],colisionA->getMax()[2] };


		float x = (float)Maths::max(boxmin[0], (float)Maths::min(colisionB->getPosition()[0], boxmax[0]));
		float y = (float)Maths::max(boxmin[1], (float)Maths::min(colisionB->getPosition()[1], boxmax[1]));
		float z = (float)Maths::max(boxmin[2], (float)Maths::min(colisionB->getPosition()[2], boxmax[2]));

		float distance = Maths::sqrt((x - colisionB->getPosition()[0]) * (x - colisionB->getPosition()[0]) +
			(y - colisionB->getPosition()[1]) * (y - colisionB->getPosition()[1]) +
			(z - colisionB->getPosition()[2]) * (z - colisionB->getPosition()[2]));
		return distance < colisionB->radius;



	}
	else {
		//colision a aabb b aabb
		float aboxmin[3] = { colisionA->getMin()[0] ,colisionA->getMin()[1],colisionA->getMin()[2] };
		float aboxmax[3] = { colisionA->getMax()[0] ,colisionA->getMax()[1],colisionA->getMax()[2] };


		float bboxmin[3] = { colisionB->getMin()[0] ,colisionB->getMin()[1],colisionB->getMin()[2] };
		float bboxmax[3] = { colisionB->getMax()[0] ,colisionB->getMax()[1],colisionB->getMax()[2] };
		if ((aboxmin[0] <= bboxmax[0] && aboxmax[0] >= bboxmin[0]) &&
			(aboxmin[1] <= bboxmax[1] && aboxmax[1] >= bboxmin[1]) &&
			(aboxmin[2] <= bboxmax[2] && aboxmax[2] >= bboxmin[2])) {

			std::cout << "Collision Effective Between "<< colisionA->getName() << " and " << colisionB->getName() << "\n";
			bboxmin[0] =  colisionB->getMin()[0];
			bboxmin[1] = colisionB->getMin()[1];
			bboxmin[2] = colisionB->getMin()[2] ;

		}
		return (aboxmin[0] <= bboxmax[0] && aboxmax[0] >= bboxmin[0]) &&
			(aboxmin[1] <= bboxmax[1] && aboxmax[1] >= bboxmin[1]) &&
			(aboxmin[2] <= bboxmax[2] && aboxmax[2] >= bboxmin[2]);
}
};
};
