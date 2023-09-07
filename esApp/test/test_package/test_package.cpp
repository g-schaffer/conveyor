#include <M5Stack.h>
#include <Package.h>

#include <unity.h>


void test_isDelivered(void){
    Package package = Package("uuid", "straight", 0);

    int32_t motorStepCounter = 0;
    TEST_ASSERT_FALSE(package.isDelivered(motorStepCounter));

    motorStepCounter = 20;
    TEST_ASSERT_FALSE(package.isDelivered(motorStepCounter));

    motorStepCounter = 21;
    TEST_ASSERT_TRUE(package.isDelivered(motorStepCounter));
}
    
void test_getUuid(void){
    String uuid = "uuid";

    Package package = Package(uuid, "straight", 0);

    TEST_ASSERT_EQUAL_STRING(uuid.c_str(), package.getUuid().c_str());

}
    
void test_getDestination(void){
    String destination = "straight";

    Package package = Package("uuid", destination, 0);

    TEST_ASSERT_EQUAL_STRING(destination.c_str(), package.getDestination().c_str());
    
}
    
void test_getMotorStep(void){
    uint32_t motorStep = 0;

    Package package = Package("uuid", "straight", motorStep);

    TEST_ASSERT_EQUAL(motorStep, package.getMotorStep());
}
    
void test_toJson(void){
    String uuid = "uuid";
    String destination = "straight";
    uint32_t motorStep = 0;

    Package package = Package(uuid, destination, motorStep);

    String expectedJson = "{\"uuid\": \"" + uuid + "\", \"destination\": \"" + destination + "\"}";
    TEST_ASSERT_EQUAL_STRING(expectedJson.c_str(), package.toJson().c_str());
}

void RUN_UNITY_TESTS_PACKAGE() {
    UNITY_BEGIN();
    RUN_TEST(test_isDelivered);
    RUN_TEST(test_getUuid);
    RUN_TEST(test_getDestination);
    RUN_TEST(test_getMotorStep);
    RUN_TEST(test_toJson);
    UNITY_END();
}


#ifdef ARDUINO

#include <Arduino.h>


void setup() {
    
    delay(1000);
    RUN_UNITY_TESTS_PACKAGE();
}

void loop() {
    
}

#else

int main(int argc, char **argv) {
    RUN_UNITY_TESTS_PACKAGE();
    return 0;
}

#endif

