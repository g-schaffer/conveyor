/**
 * @file M5UI.h
 * @brief M5UI class declaration
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#ifndef M5_UI_H
#define M5_UI_H

#include <M5Stack.h>

#define M5STACK_FIRE_NEO_NUM_LEDS 10
#define M5STACK_FIRE_NEO_DATA_PIN 15

class M5UI
{
public:
    /**
     * @brief Construct a new M5UI object
     */
    M5UI();

    /**
     * @brief Init M5UI
     */
    void init();

    /**
     * @brief Run light
     */
    void runLight();

    /**
     * @brief Notification RFID read with success
     */
    void notificationRFIDReadWithSuccess();

    /**
     * @brief Notification RFID read with error
     */
    void notificationRFIDReadWithError();

    /**
     * @brief Speaker bip with light
     *
     * @param repeat Number of bip is repeat
     * @param during During of bip
     * @param color Color of light
     */
    void speakerBipWithLight(int repeat, int during, uint32_t color);

    /**
     * @brief Print progress bar on M5Stack
     *
     * @param pourcent Pourcent of progress
     */
    static void initProgressBar(int pourcent);

    /**
     * @brief Print wait packages
     */
    static void printWaitPackages();

    /**
     * @brief Print total packages on delivery
     *
     * @param queuSize Size of the queue
     */
    static void printTotalPackagesOnDelivery(int queuSize);
};

#endif