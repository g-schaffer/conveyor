#include "WifiUtils.h"

bool WifiUtils::connect(const char *ssid, const char *password)
{
    M5.Lcd.print("Connecting to ");
    M5.Lcd.println(ssid);

    WiFi.begin(ssid, password);

    while (!isConnected())
    {
        Serial.println("LOOP CONNECT END");
        delay(500);
    }

    return true;
}

String WifiUtils::sendRequest(String method, String url, String body)
{
    // Check if connected to the WiFi network
    if (!isConnected())
    {
        return "";
    }

    String response = "";
    bool resultOK = false;
    uint64_t start = millis();

    // Wait result OK
    while (!resultOK)
    {
        Serial.println(url);

        if (millis() - start > 20000)
        {
            AlarmManager::cantCallAPIAlarm();

            start = millis();
        }

        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(url.c_str());
        http.setTimeout(5000);

        // Send HTTP request
        int httpResponseCode = 0;

        if (method == "POST")
        {
            httpResponseCode = http.POST(body);
        }
        else if (method == "GET")
        {
            httpResponseCode = http.GET();
        }

        if (httpResponseCode == 200)
        {
            response = http.getString();
            resultOK = true;
        }
        else
        {
            Serial.println("\nError code: ");
            Serial.println(httpResponseCode);
            Serial.println("\n");
            Serial.println(http.getString());
            Serial.println("\n");
        }

        // Free resources
        http.end();

        delay(1000);
    }

    return response;
}

String WifiUtils::getPackageDestination(String uuid)
{
    return sendRequest("GET", URL_DESTINATION + uuid, "");
}

int WifiUtils::getOnDeliveryPackage()
{
    return sendRequest("GET", URL_ON_DELIVERY, "").toInt();
}

String WifiUtils::cleanOnDeliveryPackages()
{
    return sendRequest("POST", URL_ON_DELIVERY + "/clean", "");
}

String WifiUtils::postDeliveredPackage(String uuid)
{
    return sendRequest("POST", URL_DELIVERED, uuid);
}

String WifiUtils::postAlarm(String message)
{
    return sendRequest("POST", URL_ALARM, message);
}

String WifiUtils::postResetAlarm()
{
    return sendRequest("POST", URL_RESET_ALARM, "");
}

bool WifiUtils::isConnected()
{
    bool isConn = WiFi.status() == WL_CONNECTED;
    Serial.println(WiFi.status());
    Serial.println(WL_CONNECTED);
    if (isConn)
    {
        Serial.println("WiFi Connected\n");
        return true;
    }
    else
    {
        Serial.println("WiFi Disconnected\n");
        return false;
    }
}
