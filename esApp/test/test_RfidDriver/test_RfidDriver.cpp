#include <RfidDriver.h>
#include <unity.h>

RfidDriver rfidDriver;


void test_readRfid(void){
    // String tag = "";
    // rfidDriver.init();
    // TEST_ASSERT_EQUAL_STRING(rfidDriver.readRfid().c_str(), tag);
}
void test_setTagDetected(void){
    rfidDriver.setTagDetected(true);
    TEST_ASSERT_TRUE(rfidDriver.getTagDetected());
}

void test_getTagDetected(void){
    rfidDriver.setTagDetected(true);
    TEST_ASSERT_TRUE(rfidDriver.getTagDetected());
}


void RUN_UNITY_TESTS_RFIDDRIVER() {
    UNITY_BEGIN();
    RUN_TEST(test_readRfid);
    RUN_TEST(test_setTagDetected);
    RUN_TEST(test_getTagDetected);
    UNITY_END();
}


#ifdef ARDUINO

#include <Arduino.h>


void setup() {
    
    delay(1000);
    RUN_UNITY_TESTS_RFIDDRIVER();
}

void loop() {
    
}

#else

int main(int argc, char **argv) {
    RUN_UNITY_TESTS_RFIDDRIVER();
    return 0;
}

#endif
