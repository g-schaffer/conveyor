/**
 * @file AlarmManager.h
 * @brief Alarm manager file
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <M5Stack.h>
#include <WifiUtils.h>

enum Criticity
{
    Critical,
    Warning,
    Information
};


class WifiUtils;


/**
 * @brief Alarm manager class
 */
class AlarmManager
{
private:
    /**
     * @brief Alarm function
     * @param criticity Criticity of the alarm
     * @param error Error message
     * @param solution Solution message
     * @return void
     */
    static void alarm(Criticity criticity, String error, String solution);

public:
    /**
     * @brief Alert when a package is too close to the conveyor
     * @return void
     */
    static void packageToCloseAlarm();

    /**
     * @brief Alert when a package is already on the conveyor
     * @return void
     */
    static void initWithPackageOnDeliveryAlarm();

    /**
     * @brief Alert when the API is not available
     * @return void
     */
    static void cantCallAPIAlarm();
};

#endif