#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <M5Stack.h>
#include <AlarmManager.h>
#include <WifiUtils.h>

#define WIFI_SSID "Livebox-auguste-comte"
#define WIFI_PASSWORD "Comte69002"
#define SERVER_ADDRESS "http://192.168.1.58:8000/"

// #define WIFI_SSID "AP_Thomas"
// #define WIFI_PASSWORD "ornr4405"
// #define SERVER_ADDRESS "http://192.168.0.106:8000/"


class AlarmManager;

class WifiUtils
{
public:
    const String URL_DESTINATION = String(SERVER_ADDRESS) + "destination?uuid=";
    const String URL_ON_DELIVERY = String(SERVER_ADDRESS) + "onDelivery";
    const String URL_DELIVERED = String(SERVER_ADDRESS) + "delivered";
    const String URL_ALARM = String(SERVER_ADDRESS) + "alarm";
    const String URL_RESET_ALARM = String(SERVER_ADDRESS) + "resetAlarm";

    /**
     * @brief connect ESP to wifi
     *
     * @param ssid wifi id
     * @param password password wifi
     */
    bool connect(const char *ssid, const char *password);

    /**
     * @brief call API, get the number of the package on delivery
     */
    int getOnDeliveryPackage();

    /**
     * @brief in case of brutal shutdown, call API to get list of packages in convoyor
     *
     * @return String list of packages
     */
    String cleanOnDeliveryPackages();

    /**
     * @brief Call API, get the destination of the package
     *
     * @param uuid
     * @return String destination
     */
    String getPackageDestination(String uuid);

    /**
     * @brief call API, push the delivered package
     *
     * @param uuid package id
     * @return String
     */
    String postDeliveredPackage(String uuid);

    /**
     * @brief call API because alarm is on
     *
     * @param message error message
     * @return String
     */
    String postAlarm(String message);

    /**
     * @brief call API because alarm shutdown
     *
     * @return String
     */
    String postResetAlarm();

    /**
     * @brief returns bool if API is connected or not
     *
     * @return true API is connected
     * @return false API is not connected
     */
    bool isConnected();

private:
    /**
     * @brief send http request to api
     *
     * @param method
     * @param url
     * @param body
     * @return String response from server
     */
    String sendRequest(String method, String url, String body);
};

#endif