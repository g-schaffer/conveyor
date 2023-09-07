#ifndef __SERVOMOTOR_H__
#define __SERVOMOTOR_H__

#include <GoPlus2.h>

class ServoMotor
{
public:
	ServoMotor();

	/**
	 * @brief servo motor turns left
	 *
	 */
	void turnLeft();

	/**
	 * @brief servo motor turns right
	 *
	 */
	void turnRight();

	/**
	 * @brief servo motor turns straight
	 *
	 */
	void turnStraight();

private:
	/**
	 * @brief servo motor turns to a specific angle
	 *
	 * @param angle
	 */
	void turn(uint16_t angle);

	GoPlus2 goPlus;

	const uint16_t angleLeft = 60;	   // green
	const uint16_t angleStraight = 40; // blue
	const uint16_t angleRight = 25;	   // red or yellow

	int speed; // servo motor speed
};

#endif