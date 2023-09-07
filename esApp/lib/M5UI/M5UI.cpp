/**
 * @file M5UI.cpp
 * @brief M5UI class implementation
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#include "M5UI.h"

M5UI::M5UI()
{
}

void M5UI::init()
{
	// pixels.begin();

	// Alert init
	// this->speakerBipWithLight(4, 200, blue);
}

void M5UI::runLight()
{
	// pixels.fill(white, 0, 10);
	// pixels.show();
}

void M5UI::notificationRFIDReadWithSuccess()
{
	//   speakerBipWithLight(1, 200, green);
}

void M5UI::notificationRFIDReadWithError()
{
	//   speakerBipWithLight(5, 500, red);
}

void M5UI::speakerBipWithLight(int repeat, int during, uint32_t color)
{
	const int tonality = 661;

	// loop bips
	for (int i = 0; i < repeat; i++)
	{

		if (i != 0)
		{
			delay(during);
		}

		M5.Speaker.tone(tonality); // Set the speaker to ring at 661Hz

		// pixels.fill(color, 0, M5STACK_FIRE_NEO_NUM_LEDS);
		// pixels.show();

		delay(during);

		M5.Speaker.end(); // Turn off the speaker.

		// pixels.fill(black, 0, M5STACK_FIRE_NEO_NUM_LEDS);
		// pixels.show();
	}

	// Light for the run
	this->runLight();
}

void M5UI::initProgressBar(int pourcent)
{
	uint8_t x = 40;
	uint8_t y = 200;
	uint8_t w = 240;
	uint8_t h = 20;

	M5.Lcd.setTextSize(2);
	M5.Lcd.fillRect(x, y, w - 20, h, 0);
	M5.Lcd.progressBar(x, y, w, h, pourcent);
}

void M5UI::printWaitPackages()
{
	delay(50);

	M5.Lcd.fillScreen(0);
	M5.Lcd.setTextSize(2);
	M5.Lcd.setCursor(30, 100);
	M5.Lcd.setTextColor(TFT_WHITE);
	M5.Lcd.println("En attente de colis...");
}

void M5UI::printTotalPackagesOnDelivery(int queuSize)
{
	M5.Lcd.setTextSize(3);
	M5.Lcd.setTextColor(TFT_WHITE);
	M5.Lcd.setCursor(0, 0);
	M5.Lcd.fillRect(0, 0, 320, 30, BLACK);
	M5.Lcd.setCursor(70, 0);
	M5.Lcd.println(String(queuSize) + " packages");
}
