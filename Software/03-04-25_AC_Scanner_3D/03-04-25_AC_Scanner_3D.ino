//******************* Alexandros Chrissantakis *******************
//************************* 2024 - 2025 **************************
//************************* Arduino IDE **************************
//***************** M5Stack, TMC5072-BOB, VL53L0X ****************

//**Include**
#include "TMC5072.h"
#include <Wire.h>
#include <VL53L0X.h>

//**Initialisation**

// Initialisation du driver pour chaque moteur (canal 0 pour le moteur 1, canal 1 pour le moteur 2)
TMC5072 driver1 = TMC5072(SPI, SPISettings(100000, SPI_MSBFIRST, SPI_MODE3), 0, 0.00001951, 0.0000144, 0.00025, 0, 1.25, 1, 1, 1, 1);
TMC5072 driver2 = TMC5072(SPI, SPISettings(100000, SPI_MSBFIRST, SPI_MODE3), 1, 0.00001951, 0.0000144, 0.00025, 0, 1.25, 1, 1, 1, 1);

// Création d'un objet capteur VL53L0X
VL53L0X sensor;


void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialisation de la communication I2C

  sensor.setTimeout(500);  // Définit un temps d'attente maximal de 500 ms
  if (!sensor.init())      // Vérifie si le capteur est correctement initialisé
  {
    Serial.println("Code erreur 001 : Échec de la détection et de l'initialisation du capteur !");
    while (1) {}  // Boucle infinie en cas d'erreur
  }

  // Initialisation du bus SPI
  driver1.beginSPI(SCK, MISO, MOSI, SS);  // SS est utilisé pour sélectionner le bus SPI
  driver2.beginSPI(SCK, MISO, MOSI, SS);  // SS est utilisé pour sélectionner le bus SPI
  delay(1);

  // Configuration des courants et des vitesses pour les moteurs
  driver1.setCurrent(18, 17);  // Moteur 1
  driver2.setCurrent(18, 17);  // Moteur 2

  //Définition de la vélocité des moteurs
  driver1.setDefaultVelocitiesAndAccelerations(0, 255, 1, 255, 255, 0.1, true);
  driver2.setDefaultVelocitiesAndAccelerations(0, 255, 1, 255, 255, 0.1, true);

  //Définition du voltage pour les drivers moteurs
  driver1.setVStopAndVStartRaw(1, 10);
  driver2.setVStopAndVStartRaw(1, 10);

  //Rénitialisation des erreurs du driver moteur
  driver1.clearGSTAT();
  driver2.clearGSTAT();

  //Activation des drivers moteurs
  driver1.enable();
  driver2.enable();

  delay(2000);
  Serial.println(driver1.home());  // Home du premier moteur
  Serial.println(driver2.home());  // Home du deuxième moteur
  Serial.println("---");
}

void loop() {
  // put your main code here, to run repeatedly:
}
