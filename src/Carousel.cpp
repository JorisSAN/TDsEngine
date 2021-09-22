#include "Carousel.h"
#include "Cube.h"
#include "Maths.h"
#include "MathMatrix.h"
#include "Timer.h"

Carousel::Carousel(char* nameP) :
	Actor(nameP)
{}

Carousel::~Carousel() {}

void Carousel::init()
{
	Cube* base1 = new Cube(this, "base1");
	base1->setScale(5.0f, 0.1f, 0.5f);
	base1->setPosition(5.0f, 0.0f, 0.0f);

	Cube* base2 = new Cube(this, "base2");
	base2->setScale(4.0f, 0.05f, 0.5f);
	base2->setRotation(0.0f, 90, 0.0f);
	base2->setPosition(6.0f, 0.0f, 0.0f);

	Cube* arm1 = new Cube(this, "Arm1");
	arm1->setScale(2.0f, 0.1f, 0.5f);
	arm1->setPosition(6.0f, 0.1f, 3.5f);

	Cube* arm2 = new Cube(this, "Arm2");
	arm2->setScale(2.0f, 0.1f, 0.5f);
	arm2->setPosition(6.0f, 0.1f, -3.5);

	Cube* arm3 = new Cube(this, "Arm3");
	arm3->setScale(2.0f, 0.1f, 0.5f);
	arm3->setPosition(9.0f, 0.1f, 0.0f);

	Cube* tase1 = new Cube(this, "tase1");
	tase1->setScale(0.5f, 0.5f, 0.5f);
	tase1->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tase2 = new Cube(this, "tase2");
	tase2->setScale(0.5f, 0.5f, 0.5f);
	tase2->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tase3 = new Cube(this, "tase3");
	tase3->setScale(0.5f, 0.5f, 0.5f);
	tase3->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tase4 = new Cube(this, "tase4");
	tase4->setScale(0.5f, 0.5f, 0.5f);
	tase4->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tase5 = new Cube(this, "tase5");
	tase5->setScale(0.5f, 0.5f, 0.5f);
	tase5->setPosition(0.0f, 0.7f, 0.0f);

	Cube* tase6 = new Cube(this, "tase6");
	tase6->setScale(0.5f, 0.5f, 0.5f);
	tase6->setPosition(0.0f, 0.7f, 0.0f);

	Actor::init(); // Imperatively after the creation of the component
}

void Carousel::update()
{
	float rayon[3] = { 1.5f, 0.0f, 0.0f };
	float rayonInv[3] = { -1.5f, 0.0f, 0.0f };
	float time = Timer::getTime();

	Component* arm1 = searchComponent("Arm1");

	arm1->setRotation(0, time * 45, 0);

	Component* arm2 = searchComponent("Arm2");

	arm2->setRotation(0, time * 45, 0);

	Component* arm3 = searchComponent("Arm3");

	arm3->setRotation(0, time * 45, 0);

	Component* tase1 = searchComponent("tase1");

	float* armPosition = arm1->getPosition();
	float* armRotation = arm1->getRotation();

	float* calculPositionTase = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition, armRotation, rayon);

	tase1->setRotation(0, -time * 45 * 2, 0);
	tase1->setPosition(calculPositionTase[0], tase1->getPosition()[1], calculPositionTase[2]);

	Component* tase2 = searchComponent("tase2");

	float* calculPositionTase2 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition, armRotation, rayonInv);

	tase2->setRotation(0, -time * 45 * 2, 0);
	tase2->setPosition(calculPositionTase2[0], tase2->getPosition()[1], calculPositionTase2[2]);

	Component* tase3 = searchComponent("tase3");

	float* armPosition2 = arm2->getPosition();
	float* armRotation2 = arm2->getRotation();

	float* calculPositionTase3 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition2, armRotation2, rayon);

	tase3->setRotation(0, -time * 45 * 2, 0);
	tase3->setPosition(calculPositionTase[0], tase3->getPosition()[1], calculPositionTase[2]);

	Component* tase4 = searchComponent("tase4");

	float* calculPositionTase4 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition2, armRotation2, rayonInv);

	tase4->setRotation(0, -time * 45 * 2, 0);
	tase4->setPosition(calculPositionTase2[0], tase4->getPosition()[1], calculPositionTase2[2]);

	Component* tase5 = searchComponent("tase5");

	float* armPosition3 = arm3->getPosition();
	float* armRotation3 = arm3->getRotation();

	float* calculPositionTase5 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition3, armRotation3, rayon);

	tase5->setRotation(0, -time * 45 * 2, 0);
	tase5->setPosition(calculPositionTase[0], tase5->getPosition()[1], calculPositionTase[2]);

	Component* tase6 = searchComponent("tase6");

	float* calculPositionTase6 = mathMatrix::calculPositionWithCenterRotationAndRayon(armPosition3, armRotation3, rayonInv);

	tase6->setRotation(0, -time * 45 * 2, 0);
	tase6->setPosition(calculPositionTase2[0], tase6->getPosition()[1], calculPositionTase2[2]);

	Actor::update(); // Imperatively after the modification
}
