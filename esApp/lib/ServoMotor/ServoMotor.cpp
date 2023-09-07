#include "ServoMotor.h"

ServoMotor::ServoMotor()
{
	goPlus.begin();
	delay(100);
}

void ServoMotor::turnLeft()
{
	this->turn(angleLeft);
}

void ServoMotor::turnRight()
{
	turn(angleRight);
}
void ServoMotor::turnStraight()
{
	this->turn(angleStraight);
}

void ServoMotor::turn(uint16_t angle)
{

	// all pin are push to the same angle so we dont have to care about the pin =)
	goPlus.Servo_write_angle(SERVO_NUM0, angle);
	goPlus.Servo_write_angle(SERVO_NUM1, angle);
	goPlus.Servo_write_angle(SERVO_NUM2, angle);
	goPlus.Servo_write_angle(SERVO_NUM3, angle);
}