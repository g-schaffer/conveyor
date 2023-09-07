/**
 * @file Package.cpp
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#include "Package.h"

Package::Package(String uuid, String destination, uint32_t motorStepCounter)
{
	m_uuid = uuid;
	m_destination = destination;
	m_motorStep = motorStepCounter;
}

bool Package::isDelivered(uint32_t motorStepCounter)
{
	return motorStepCounter - m_motorStep >= INTERVAL_RFID_TO_DESTINATION;
}

String Package::getUuid()
{
	return m_uuid;
}

String Package::getDestination()
{
	return m_destination;
}

uint32_t Package::getMotorStep()
{
	return m_motorStep;
}

String Package::toJson()
{
	return "{\"uuid\": \"" + m_uuid + "\", \"destination\": \"" + m_destination + "\"}";
}
