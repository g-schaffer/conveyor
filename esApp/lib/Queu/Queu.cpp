/**
 * @file Queu.cpp
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 * @brief Queu class implementation
 * @version 1.0
 */

#include "Queu.h"

Queu::Queu()
{
	this->queu = {};
}
/**
 * @brief init queue
 *
 */
void Queu::init()
{
	initWifi();

	initMotor();

	M5.Lcd.println("Check if the convoyor is empty...");

	// if there are packages on convoyor
	if (clientWifi.getOnDeliveryPackage() > 0)
	{
		AlarmManager::initWithPackageOnDeliveryAlarm(); // init alarm

		clientWifi.cleanOnDeliveryPackages(); // clean packages
	}
}
/**
 * @brief init wifi
 *
 */
void Queu::initWifi()
{
	if (!clientWifi.connect(WIFI_SSID, WIFI_PASSWORD))
	{
		M5.Lcd.println("Echec de connexion au Wifi");
		ESP.restart();
	}

	M5.Lcd.println("Wifi Connected");
}

void Queu::initMotor()
{
	M5.Power.begin();
	Wire.begin(STEP_MOTOR_SDA, STEP_MOTOR_SCL);

	motor.Init(&Wire);
	motor.setMode("distance");
}

void Queu::motorForward()
{
	static const uint8_t FORWARD_STEP = 1;

	motor.setMotor(FORWARD_STEP, 0, 0, SPEED_STEP_MOTOR);

	motorStepCounter++;
}

bool Queu::exist(Package package)
{
	for (Package p : queu)
	{
		if (package.getUuid() == p.getUuid())
		{
			return true;
		}
	}

	return false;
}

String Queu::uuidExist(String uuid)
{
	for (Package p : queu)
	{
		if (uuid == p.getUuid())
		{
			return p.getDestination();
		}
	}

	return "";
}

void Queu::clear()
{
	while (queu.size() > 0)
	{
		this->pop_front();
	}
}

bool Queu::append(Package package)
{
	// Si le package n'existe pas dans la queu
	if (!this->exist(package))
	{
		// Dans le cas ou le file d'attente n'est pas vide
		if (queu.size() > 0)
		{
			// check si le dernier package est assez loin du package precedent
			if ((package.getMotorStep() - queu.front().getMotorStep()) <= MIN_INTERVAL_BETWEEN_PACKAGE)
			{
				AlarmManager::packageToCloseAlarm();

				this->clear();

				return false;
			}
		}

		// Ajoute le package dans la file d'attente
		this->queu.push_back(package);

		// Met à jour le servomoteur
		if (queu.size() == 1)
		{
			this->updateServoMotor();
		}
	}
	else
	{
		// M5.Lcd.println("\nQUEU::APPEND:: The package already exist in the queu!");
		return false;
	}

	M5UI::printTotalPackagesOnDelivery(queu.size());

	return true;
}

void Queu::updateServoMotor()
{
	// Oriente le servomoteur vers queu.front()
	if (queu.size() >= 1)
	{
		String destination = queu.front().getDestination();

		if (destination == "\"Left\"")
		{
			servoMotor.turnLeft();
		}
		else if (destination == "\"Straight\"")
		{
			servoMotor.turnStraight();
		}
		else if (destination == "\"Right\"")
		{
			servoMotor.turnRight();
		}
		else
		{
			M5.Lcd.println("QUEU::UPDATE_SERVO_MOTOR:: Error destination is not valid");
		}
	}
}

std::list<Package> Queu::getAll()
{
	return this->queu;
}

String Queu::toJson()
{
	String jsonQueu = "{\"queu\": [";

	// append package json to the list
	uint16_t cnt = 0;
	for (Package p : queu)
	{
		jsonQueu += p.toJson();

		if (cnt != queu.size() - 1)
		{
			jsonQueu += ",";
		}
		cnt++;
	}

	jsonQueu += "]}";

	return jsonQueu;
}

void Queu::appendWithUuid(String uuid)
{
	// Check if the package already exist in the queu
	String destination = this->uuidExist(uuid);

	// Skip if already exist
	if (destination != "")
		return;

	lastEventUI(true, uuid);

	// Boucle tant que l'API n'a pas retourné la destination du package
	while (destination == "")
	{
		destination = this->client.getPackageDestination(uuid);

		if (destination != "")
		{
			Package package = Package(uuid, destination, motorStepCounter);

			this->append(package);
		}
	}
}

// Check if the last package is on the destination
void Queu::checkIfFrontPackageIsDelivered()
{
	// Si la file d'attente n'est pas vide
	if (queu.size() > 0)
	{
		// Si le package en tete de file est livré
		if (queu.front().isDelivered(motorStepCounter))
		{
			this->pop_front();
		}
	}
}

void Queu::lastEventUI(bool isAdded, String uuid)
{
	M5.Lcd.setTextSize(3);
	M5.Lcd.fillRect(0, 100, 320, 40, TFT_BLACK);
	M5.Lcd.setCursor(60, 100);
	M5.Lcd.setTextColor(isAdded ? TFT_GREEN : TFT_RED);
	M5.Lcd.println(uuid);
}

void Queu::pop_front()
{
	String frontPackageUuid = queu.front().getUuid();

	lastEventUI(false, frontPackageUuid);

	// Informe l'API que le package est livré
	client.postDeliveredPackage(frontPackageUuid);

	// Supprime le package en tete de file
	this->queu.pop_front();

	// Met a jour la position du servomoteur
	updateServoMotor();

	M5UI::printTotalPackagesOnDelivery(queu.size());
}

int Queu::size()
{
	return queu.size();
}