/**
 * @file Package.h
 * @brief Package class
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#ifndef PACKAGE_H
#define PACKAGE_H

#include <Arduino.h>

class Package
{
private:
    static const int INTERVAL_RFID_TO_DESTINATION = 21; // Number of step from RFID-Reader to destination to delivered the package

    String m_destination;
    String m_uuid;
    uint32_t m_motorStep;

public:
    /**
     * @brief Construct a new Package object
     *
     * @param uuid UUID of the package
     * @param destination Destination of the package
     * @param motorStepCounter Motor step counter
     *
     * @return Package
     */
    Package(String uuid, String destination, uint32_t motorStepCounter);

    /**
     * @brief Check if the package is delivered
     *
     * @param motorStepCounter Motor step counter
     *
     * @return true Package is delivered
     * @return false Package is not delivered
     */
    bool isDelivered(uint32_t motorStepCounter);

    /**
     * @brief Get the Uuid object
     *
     * @return String UUID of the package
     */
    String getUuid();

    /**
     * @brief Get the Destination object
     *
     * @return String Destination of the package
     */
    String getDestination();

    /**
     * @brief Get the Motor Step object
     *
     * @return uint32_t Motor step counter
     */
    uint32_t getMotorStep();

    /**
     * @brief Get the Json object
     *
     * @return String Json of the package
     */
    String toJson();
};

#endif