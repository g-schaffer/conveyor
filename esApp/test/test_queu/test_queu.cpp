#include <Queu.h>
#include <unity.h>

Queu queu;

void test_checkIfFrontPackageIsDelivered(void)
{
    queu.clear();
    queu.appendWithUuid("666001");

    for (int i = 0; i < 25; i++)
    {
        queu.motorForward();
    }

    queu.checkIfFrontPackageIsDelivered();
    TEST_ASSERT_EQUAL(0, queu.size());
}

void test_clear(void)
{
    queu.clear();
    TEST_ASSERT_EQUAL(0, queu.size());
}

void test_uuidExist(void)
{
    String toto = queu.uuidExist("test");
    TEST_ASSERT_EQUAL_STRING("", toto.c_str());

}

void test_getAll(void)
{
    queu.clear();
    queu.appendWithUuid("666002");
    queu.appendWithUuid("666003");
    std::list<Package> list = queu.getAll();
    TEST_ASSERT_EQUAL(2, list.size());
}

void test_toJson(void)
{
    // queu.clear();
    // queu.appendWithUuid("666007");
    // String json = queu.toJson();
    // String expected = "{\"queu\": [{\"uuid\": \"test\", \"destination\": \"\"}]";

    // TEST_ASSERT_EQUAL_STRING(expected.c_str(), json.c_str());
}

void test_appendWithUuid(void)
{   
    queu.clear();
    queu.appendWithUuid("666004");
    TEST_ASSERT_EQUAL(1, queu.size());
}

void test_pop_front(void)
{
    // Queu q = Queu();
    // q.init();
    // queu.clear();
    // String str1 = "666004";
    // String str2 = "666005";
    // String str3 = "666006";
    // queu.appendWithUuid(str1);
    // queu.appendWithUuid(str2);
    // queu.appendWithUuid(str3);
    // queu.pop_front();
    // TEST_ASSERT_EQUAL(2, queu.size());
}

void test_size(void)
{
    queu.clear();
    queu.appendWithUuid("666005");
    queu.appendWithUuid("666006");
    TEST_ASSERT_EQUAL(2, queu.size());

    
}

void RUN_UNITY_TESTS_QUEU()
{
    Serial.begin(115200);

    queu.initWifi();

    UNITY_BEGIN();
    RUN_TEST(test_checkIfFrontPackageIsDelivered);
    RUN_TEST(test_clear);
    RUN_TEST(test_uuidExist);
    // RUN_TEST(test_getAll);
    RUN_TEST(test_toJson);
    RUN_TEST(test_pop_front);
    // RUN_TEST(test_size);
    RUN_TEST(test_appendWithUuid);
    
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup()
{

    delay(1000);
    RUN_UNITY_TESTS_QUEU();
}

void loop()
{
}

#else

int main(int argc, char **argv)
{
    RUN_UNITY_TESTS_QUEU();
    return 0;
}

#endif
