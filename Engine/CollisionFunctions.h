#include "CollisionComponent.h"
enum CollisionType { point, sphere, aabb };

bool IsColliding(CollisionComponent colisionA, CollisionComponent colisionB)
{
	if (colisionA.colType == point || colisionB.colType == point)
	{

		if (colisionA.colType == point && colisionB.colType == point)
		{
			// collision a point b point
			return (colisionA.getPosition()[0] == colisionB.getPosition()[0] &&
				colisionA.getPosition()[1] == colisionB.getPosition()[1] &&
				colisionA.getPosition()[2] == colisionB.getPosition()[2]);
		}
		if (colisionA.colType == point)
		{
			if (colisionB.colType == sphere)
			{
				//colision a point b sphere
				float distance = Maths::sqrt((colisionA.getPosition()[0] - colisionB.getPosition()[0]) * ((colisionA.getPosition()[0] - colisionB.getPosition()[0])) +
					(colisionA.getPosition()[1] - colisionB.getPosition()[1]) * ((colisionA.getPosition()[1] - colisionB.getPosition()[1])) +
					(colisionA.getPosition()[2] - colisionB.getPosition()[2]) * ((colisionA.getPosition()[2] - colisionB.getPosition()[2])));
				return distance < colisionB.radius;
			}
			//colision a point b aabb
			float boxmin[3] = { 0,0,0 };
			float boxmax[3] = { 0,0,0 };
			boxmin[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] < colisionB.getPosition()[0] + colisionB.getScale()[0] ?
				colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
			boxmin[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] < colisionB.getPosition()[1] + colisionB.getScale()[1] ?
				colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
			boxmin[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] < colisionB.getPosition()[2] + colisionB.getScale()[2] ?
				colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];
			boxmax[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] > colisionB.getPosition()[0] + colisionB.getScale()[0] ?
				colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
			boxmax[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] > colisionB.getPosition()[1] + colisionB.getScale()[1] ?
				colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
			boxmax[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] > colisionB.getPosition()[2] + colisionB.getScale()[2] ?
				colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];
			return ((colisionA.getPosition()[0] >= boxmin[0] && (colisionA.getPosition()[0] <= boxmax[0])) &&
				(colisionA.getPosition()[1] >= boxmin[1] && (colisionA.getPosition()[1] <= boxmax[1])) &&
				(colisionA.getPosition()[2] >= boxmin[2] && (colisionA.getPosition()[2] <= boxmax[2])));
		}
		if (colisionA.colType == sphere)
		{
			//colision a sphere point b
			float distance = Maths::sqrt((colisionB.getPosition()[0] - colisionA.getPosition()[0]) * ((colisionB.getPosition()[0] - colisionA.getPosition()[0])) +
				(colisionB.getPosition()[1] - colisionA.getPosition()[1]) * ((colisionB.getPosition()[1] - colisionA.getPosition()[1])) +
				(colisionB.getPosition()[2] - colisionA.getPosition()[2]) * ((colisionB.getPosition()[2] - colisionA.getPosition()[2])));
			return distance < colisionA.radius;
		}
		//colision a aabb point b	
		float boxmin[3] = { 0,0,0 };
		float boxmax[3] = { 0,0,0 };
		boxmin[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] < colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		boxmin[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] < colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		boxmin[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] < colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];
		boxmax[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] > colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		boxmax[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] > colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		boxmax[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] > colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];
		return ((colisionB.getPosition()[0] >= boxmin[0] && (colisionB.getPosition()[0] <= boxmax[0])) &&
			(colisionB.getPosition()[1] >= boxmin[1] && (colisionB.getPosition()[1] <= boxmax[1])) &&
			(colisionB.getPosition()[2] >= boxmin[2] && (colisionB.getPosition()[2] <= boxmax[2])));
	}
	else if (colisionA.colType == sphere || colisionB.colType == sphere) {
		if (colisionA.colType == sphere) {
			if (colisionB.colType == sphere) {
				//colision a sphere b sphere
				float distance = Maths::sqrt((colisionA.getPosition()[0] - colisionB.getPosition()[0]) * (colisionA.getPosition()[0] - colisionB.getPosition()[0]) +
					(colisionA.getPosition()[1] - colisionB.getPosition()[1]) * (colisionA.getPosition()[1] - colisionB.getPosition()[1]) +
					(colisionA.getPosition()[0] - colisionA.getPosition()[0]) * (colisionA.getPosition()[0] - colisionA.getPosition()[0]));
				return distance < (colisionA.radius + colisionB.radius);
			}
			//colision a sphere b aabb
			float boxmin[3] = { 0,0,0 };
			float boxmax[3] = { 0,0,0 };

			boxmin[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] < colisionB.getPosition()[0] + colisionB.getScale()[0] ?
				colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
			boxmin[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] < colisionB.getPosition()[1] + colisionB.getScale()[1] ?
				colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
			boxmin[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] < colisionB.getPosition()[2] + colisionB.getScale()[2] ?
				colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];
			boxmax[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] > colisionB.getPosition()[0] + colisionB.getScale()[0] ?
				colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
			boxmax[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] > colisionB.getPosition()[1] + colisionB.getScale()[1] ?
				colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
			boxmax[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] > colisionB.getPosition()[2] + colisionB.getScale()[2] ?
				colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];

			float x = (float)Maths::max(boxmin[0], (float)Maths::min(colisionA.getPosition()[0], boxmax[0]));
			float y = (float)Maths::max(boxmin[1], (float)Maths::min(colisionA.getPosition()[1], boxmax[1]));
			float z = (float)Maths::max(boxmin[2], (float)Maths::min(colisionA.getPosition()[2], boxmax[2]));

			float distance = Maths::sqrt((x - colisionA.getPosition()[0]) * (x - colisionA.getPosition()[0]) +
				(y - colisionA.getPosition()[1]) * (y - colisionA.getPosition()[1]) +
				(z - colisionA.getPosition()[2]) * (z - colisionA.getPosition()[2]));
			return distance < colisionA.radius;

		}
		//colision a aabb b sphere
		float boxmin[3] = { 0,0,0 };
		float boxmax[3] = { 0,0,0 };

		boxmin[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] < colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		boxmin[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] < colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		boxmin[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] < colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];
		boxmax[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] > colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		boxmax[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] > colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		boxmax[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] > colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];

		float x = (float)Maths::max(boxmin[0], (float)Maths::min(colisionB.getPosition()[0], boxmax[0]));
		float y = (float)Maths::max(boxmin[1], (float)Maths::min(colisionB.getPosition()[1], boxmax[1]));
		float z = (float)Maths::max(boxmin[2], (float)Maths::min(colisionB.getPosition()[2], boxmax[2]));

		float distance = Maths::sqrt((x - colisionB.getPosition()[0]) * (x - colisionB.getPosition()[0]) +
			(y - colisionB.getPosition()[1]) * (y - colisionB.getPosition()[1]) +
			(z - colisionB.getPosition()[2]) * (z - colisionB.getPosition()[2]));
		return distance < colisionB.radius;



	}
	else {
		//colision a aabb b aabb
		float aboxmin[3] = { 0,0,0 };
		float aboxmax[3] = { 0,0,0 };

		aboxmin[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] < colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		aboxmin[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] < colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		aboxmin[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] < colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];
		aboxmax[0] = colisionA.getPosition()[0] - colisionA.getScale()[0] > colisionA.getPosition()[0] + colisionA.getScale()[0] ?
			colisionA.getPosition()[0] - colisionA.getScale()[0] : colisionA.getPosition()[0] + colisionA.getScale()[0];
		aboxmax[1] = colisionA.getPosition()[1] - colisionA.getScale()[1] > colisionA.getPosition()[1] + colisionA.getScale()[1] ?
			colisionA.getPosition()[1] - colisionA.getScale()[1] : colisionA.getPosition()[1] + colisionA.getScale()[1];
		aboxmax[2] = colisionA.getPosition()[2] - colisionA.getScale()[2] > colisionA.getPosition()[2] + colisionA.getScale()[2] ?
			colisionA.getPosition()[2] - colisionA.getScale()[2] : colisionA.getPosition()[2] + colisionA.getScale()[2];

		float bboxmin[3] = { 0,0,0 };
		float bboxmax[3] = { 0,0,0 };

		bboxmin[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] < colisionB.getPosition()[0] + colisionB.getScale()[0] ?
			colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
		bboxmin[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] < colisionB.getPosition()[1] + colisionB.getScale()[1] ?
			colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
		bboxmin[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] < colisionB.getPosition()[2] + colisionB.getScale()[2] ?
			colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];
		bboxmax[0] = colisionB.getPosition()[0] - colisionB.getScale()[0] > colisionB.getPosition()[0] + colisionB.getScale()[0] ?
			colisionB.getPosition()[0] - colisionB.getScale()[0] : colisionB.getPosition()[0] + colisionB.getScale()[0];
		bboxmax[1] = colisionB.getPosition()[1] - colisionB.getScale()[1] > colisionB.getPosition()[1] + colisionB.getScale()[1] ?
			colisionB.getPosition()[1] - colisionB.getScale()[1] : colisionB.getPosition()[1] + colisionB.getScale()[1];
		bboxmax[2] = colisionB.getPosition()[2] - colisionB.getScale()[2] > colisionB.getPosition()[2] + colisionB.getScale()[2] ?
			colisionB.getPosition()[2] - colisionB.getScale()[2] : colisionB.getPosition()[2] + colisionB.getScale()[2];
		return (aboxmin[0] <= bboxmax[0] && aboxmax[0] >= bboxmin[0]) &&
			(aboxmin[1] <= bboxmax[1] && aboxmax[1] >= bboxmin[1]) &&
			(aboxmin[2] <= bboxmax[2] && aboxmax[2] >= bboxmin[2]);
}
};