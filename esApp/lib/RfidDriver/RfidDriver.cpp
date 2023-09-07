#include "RfidDriver.h"

RfidDriver::RfidDriver() {}

void RfidDriver::init()
{
	Serial.println("RFID init started");

	Wire.begin();														// Initialize I2C
	variables.mfrc522.PCD_Init();										// Init MFRC522
	variables.mfrc522.PCD_SetAntennaGain(variables.mfrc522.RxGain_max); // Set maximum antenna gain

	// Create task for simulating interrupt RFID detection
	xTaskCreate(
		vTaskRFIDInterrupt, /* Task function. */
		"vTaskRFID",		/* name of task. */
		10000,				/* Stack size of task */
		(void *)&variables, /* parameter of the task */
		9,					/* priority of the task */
		NULL);				/* Task handle to keep track of created task */
}

String RfidDriver::readRfid()
{
	if (!variables.tagDetected)
		return "";

	String result = "";

	// Dump tag
	for (byte i = 0; i < variables.mfrc522.uid.size; i++)
	{
		result += String(variables.mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
		result += String(variables.mfrc522.uid.uidByte[i]);
	}

	return result;
}

void RfidDriver::ShowReaderDetails()
{
	// Get the MFRC522 software version
	byte v = variables.mfrc522.PCD_ReadRegister(variables.mfrc522.VersionReg);
	Serial.print(F("MFRC522 Software Version: 0x"));
	Serial.print(v, HEX);
	if (v == 0x91)
		Serial.print(F(" = v1.0"));
	else if (v == 0x92)
		Serial.print(F(" = v2.0"));
	else
		Serial.print(F(" (unknown)"));
	Serial.println("");
	// When 0x00 or 0xFF is returned, communication probably failed
	if ((v == 0x00) || (v == 0xFF))
	{
		Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
	}
}

// Works as an interrupt for the RFID
void RfidDriver::vTaskRFIDInterrupt(void *pvParameters)
{
	Variables *variables = (Variables *)pvParameters;

	for (;;)
	{
		// Look for new 1 cards & Verify if the NUID has been readed
		if (variables->mfrc522.PICC_IsNewCardPresent() && variables->mfrc522.PICC_ReadCardSerial())
		{
			variables->tagDetected = true;
		}

		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}

void RfidDriver::setTagDetected(bool b)
{
	variables.tagDetected = b;
}

bool RfidDriver::getTagDetected()
{
	return variables.tagDetected;
}
