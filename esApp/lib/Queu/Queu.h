/**
 * @file Queu.h
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 * @brief Queu class declaration
 */

#ifndef QUEU_H
#define QUEU_H

#include <list>
#include <ArduinoJson.h>
#include <WifiUtils.h>
#include <Package.h>
#include <ServoMotor.h>
#include <M5Stack.h>
#include <AlarmManager.h>
#include <M5UI.h>
#include "MODULE_GRBL13.2.h" // attention il y a un problème dans la lib de base, il faut bien penser à importer la lib modifiée qui est sur git dans lib

#define STEPMOTOR_I2C_ADDR 0x70
#define STEP_MOTOR_SDA 21
#define STEP_MOTOR_SCL 22

class Queu
{
private:
	const int SPEED_STEP_MOTOR = 100;			// 100 speed = (900ms await between each step)
	const int MIN_INTERVAL_BETWEEN_PACKAGE = 5; // need 5 step motor between each package

	uint32_t motorStepCounter = 0;

	ServoMotor servoMotor;

	WifiUtils clientWifi = WifiUtils();

	WifiUtils client = WifiUtils();

	std::list<Package> queu;

	/**
	 * @brief Append package to queue
	 *
	 * @param package Package to append
	 *
	 * @return true Package is queued
	 */
	bool append(Package package);

	/**
	 * @brief Check if the package is delivered
	 *
	 * @param package Package to check
	 *
	 * @return true Package is delivered
	 */
	bool exist(Package package);

public:
	GRBL motor = GRBL(STEPMOTOR_I2C_ADDR);

	/**
	 * @brief Construct a new Queu object
	 *
	 * @return Queu
	 */
	Queu();

	/**
	 * @brief Move to forward the motor
	 */
	void motorForward();

	/**
	 * @brief Init the motor
	 */
	void initMotor();

	/**
	 * @brief Init the queue
	 */
	void init();

	/**
	 * @brief Init the wifi
	 */
	void initWifi();

	/**
	 * @brief Check if the front package is delivered
	 */
	void checkIfFrontPackageIsDelivered();

	/**
	 * @brief clear queue
	 * 
	 */
	void clear();

	/**
	 * @brief print last event on m5stack screen
	 * 
	 * @param isAdded 
	 * @param uuid 
	 */
	void lastEventUI(bool isAdded, String uuid);

	/**
	 * @brief Update servomotoro destination according to front queue value
	 */
	void updateServoMotor();

	/**
	 * @brief get destination of specific package by uuid
	 * 
	 * @param uuid 
	 * @return String 
	 */
	String uuidExist(String uuid);

	/**
	 * @brief Get the All destination
	 * 
	 * @return std::list<Package> 
	 */
	std::list<Package> getAll();

	/**
	 * @brief string to json
	 * 
	 * @return String 
	 */
	String toJson();

	/**
	 * @brief append package to queue
	 * 
	 * @param uuid 
	 */
	void appendWithUuid(String uuid);

	/**
	 * @brief pop the Front package
	 * 
	 * @return Package 
	 */
	void pop_front();

	/**
	 * @brief Get the Size queue
	 * 
	 * @return int 
	 */
	int size();
};

#endif
