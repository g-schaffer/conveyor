/**
 * @file main.cpp
 * @brief Main file of the project
 * @author Thomas DESCHOMBECK
 * @date 2023-02-03
 */

#include <M5Stack.h>
#include <M5UI.h>
#include <Queu.h>
#include <RfidDriver.h>

// Declare constants
const int MIN_DELAY_STEP_MOTOR = 850; // Delay for wait the motor to move

// Declare objects
Queu queu = Queu();
RfidDriver rfid = RfidDriver();

/**
 * @brief Listen for a package
 *
 * This function listen for a package and add it to the queue if it is detected.
 * It is called in the main loop.
 * 
 * @return void
 */
void packageListener()
{
  String packageId = rfid.readRfid();

  if (packageId != "")
  {
    Serial.println("\nMAIN_LOOP:: Tag detected");

    queu.appendWithUuid(packageId);

    rfid.setTagDetected(false);
  }
}

/**
 * @brief Main function
 *
 * This is the main entry point for the program. 
 * It is called once at the start of the program.
 *
 * @return 0 if the program runs successfully, non-zero otherwise
 */
void setup() 
{  
  Serial.begin(115200);
  Serial.println("\n\n===== SETUP =====");
  M5.begin();

  M5UI::initProgressBar(25);

  queu.init();
  M5UI::initProgressBar(75);

  rfid.init();
  M5UI::initProgressBar(100);

  M5UI::printWaitPackages();
  
  M5UI::printTotalPackagesOnDelivery(queu.size());

  Serial.println("===== READY =====");
}


/**
 * @brief Main loop
 *
 * This is the main loop of the program. 
 * It is called repeatedly until the program is stopped.
 *
 * @return void
 */
void loop()
{
  Serial.print(".");

  packageListener();

  queu.checkIfFrontPackageIsDelivered();

  queu.motorForward();

  delay(MIN_DELAY_STEP_MOTOR);
}

