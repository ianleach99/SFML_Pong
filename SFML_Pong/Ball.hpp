#pragma once
#include "Paddle.hpp"
#include <cstdlib>
#include <ctime>

class Ball : public Paddle {
public:
	Ball(float spawnX, float spawnY);
	virtual void Clamp(float xMin, float xMax, float yMin, float yMax) override;	/* This is overridden to make it easy to change directions of the ball upon collision with the edges. */

private:
	int RandomNumberHelper();	/* This will return randomly an integer that is either -1 or 1 */
	void SetRandomDirection();
};