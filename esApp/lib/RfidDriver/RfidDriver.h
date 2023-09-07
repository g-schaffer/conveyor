#ifndef RFID_DRIVER_H
#define RFID_DRIVER_H

#include <Arduino.h>
#include <Wire.h>
#include <MFRC522_I2C.h>
#include <Queu.h>

#define RST_PIN 0
#define SS_PIN 0x28

class RfidDriver
{
public:
    RfidDriver();

    /**
     * @brief Init RFID driver
     * 
     */
    void init();

    /**
     * @brief Read RFID tag
     * 
     * @return String RFID tag
     */
    String readRfid();

    /**
     * @brief Set tag detected
     * 
     * @param b Tag detected
     */
    void setTagDetected(bool b);

    /**
     * @brief Get tag detected
     * 
     * @return true Tag detected
     * @return false Tag not detected
     */
    bool getTagDetected();

private:
    struct Variables
    {
        MFRC522_I2C mfrc522 = MFRC522_I2C(SS_PIN, RST_PIN); // Create MFRC522 instance.
        bool tagDetected = false;
    } variables;

    /**
     * @brief print reader version
     * 
     */
    void ShowReaderDetails();

    /**
     * @brief Task for simulating interrupt RFID detection
     * 
     * @param pvParameters 
     */
    static void vTaskRFIDInterrupt(void *pvParameters);
};

#endif