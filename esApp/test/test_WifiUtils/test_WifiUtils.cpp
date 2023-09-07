#include <WifiUtils.h>
#include <unity.h>

WifiUtils wifiUtils;

#define TEST_SSID "Livebox-auguste-comte"
#define TEST_PASSWORD "Comte69002"

void test_connect(void){
    // const char *ssid = TEST_SSID;
    // const char *password = TEST_PASSWORD;
    bool connection = wifiUtils.connect(TEST_SSID, TEST_PASSWORD);
    TEST_ASSERT_TRUE(connection);
}

void test_isConnected(void){
    TEST_ASSERT_TRUE(wifiUtils.isConnected());
}

void test_getOnDeliveryPackage(void){

    wifiUtils.cleanOnDeliveryPackages();
    wifiUtils.postDeliveredPackage("666002");
    int n_package = wifiUtils.getOnDeliveryPackage();
    TEST_ASSERT_EQUAL_INT(0, n_package);

}

void test_cleanOnDeliveryPackages(void){
    wifiUtils.cleanOnDeliveryPackages();
    int n_package = wifiUtils.getOnDeliveryPackage();
    TEST_ASSERT_EQUAL_INT(0, n_package);

}

void test_getPackageDestination(void){
    String uuid = "666001";
    String destination = wifiUtils.getPackageDestination(uuid);
    TEST_ASSERT_EQUAL_STRING("\"Left\"", destination.c_str());
}


void test_postAlarm(void){
    wifiUtils.postAlarm("test unitaire");
    wifiUtils.postResetAlarm();
}

void RUN_UNITY_TESTS_WIFIUTILS() {

    Serial.begin(115200);
    
    UNITY_BEGIN();
    RUN_TEST(test_connect);
    RUN_TEST(test_isConnected);
    RUN_TEST(test_getPackageDestination);
    RUN_TEST(test_getOnDeliveryPackage);
    RUN_TEST(test_cleanOnDeliveryPackages);
    RUN_TEST(test_postAlarm);
    UNITY_END();
}


#ifdef ARDUINO

#include <Arduino.h>


void setup() {
    
    delay(1000);
    RUN_UNITY_TESTS_WIFIUTILS();
}

void loop() {
    
}

#else

int main(int argc, char **argv) {
    RUN_UNITY_TESTS_WIFIUTILS();
    return 0;
}

#endif
