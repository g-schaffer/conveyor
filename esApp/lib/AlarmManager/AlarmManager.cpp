/**
 * @file AlarmManager.cpp
 * @brief Alarm manager file
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#include "AlarmManager.h"

void AlarmManager::alarm(Criticity criticity, String error, String solution)
{
    bool reseted = false;

    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextColor(TFT_RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("      ERROR");
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("");
    M5.Lcd.println(error + ", " + solution);
    M5.Lcd.setCursor(0, 200);
    M5.Lcd.println("      ==> Appuyer <==");
    M5.Lcd.println("");

    // Wait intervention for reset alarm
    while (!reseted)
    {
        M5.update();

        // Reset alarm
        if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed())
        {
            reseted = true;
        }

        M5.Speaker.tone(700);
        delay(100);
        M5.Speaker.end();
        delay(2000);
    }

    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0, 0);
}

void AlarmManager::initWithPackageOnDeliveryAlarm()
{
    String error = "Colis deja en cours de livraison";
    WifiUtils clientWifi = WifiUtils();

    clientWifi.postAlarm(error);
    alarm(Critical, error, "Veuillez retirer les colis du convoyeur");
    clientWifi.postResetAlarm();
}

void AlarmManager::packageToCloseAlarm()
{
    String error = "Colis trop proche du precedent";
    WifiUtils clientWifi = WifiUtils();

    clientWifi.postAlarm(error);
    alarm(Critical, error, "Veuillez retirer les colis du convoyeur");
    clientWifi.postResetAlarm();
}

void AlarmManager::cantCallAPIAlarm()
{
    alarm(Critical, "Impossible de contacter l'API", "Veuillez verifier la connexion internet");
}
