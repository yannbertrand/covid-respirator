#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <AnalogButtons.h>
#include <Wire.h>
#include <common.h>

// nombre de cycles par minute (cycle = inspi + plateau + expi)
int consigneNbCycle = 20;
int futureConsigneNbCycle = consigneNbCycle;

// degré d'ouverture de la valve blower (quantité d'air du blower qu'on envoie vers le Air Transistor patient)
int consigneOuverture = 70;
int futureConsigneOuverture = consigneOuverture;

// consigne de pression de crête maximum
int consignePressionCrete = 50;

// consigne de pression plateau maximum
int consignePressionPlateauMax = 30;
int futureConsignePressionPlateauMax = consignePressionPlateauMax;

// consigne de pression PEP
int consignePressionPEP = 5;
int futureConsignePressionPEP = consignePressionPEP;

// données pour affichage (du cycle précédent pour ne pas afficher des valeurs aberrantes)
int previousPressionCrete = -1;
int previousPressionPlateau = -1;
int previousPressionPep = -1;

void onPressionCretePlus() {
  //#ifdef DEBUG
  Serial.println("free2");
  //#endif
}

void onPressionCreteMinus() {
  //#ifdef DEBUG
  Serial.println("free1");
  //#endif
}

void onCycleMinus() {
  //#ifdef DEBUG
  Serial.println("nb cycle --");
  //#endif
  futureConsigneNbCycle--;
  if (futureConsigneNbCycle < BORNE_INF_CYCLE) {
    futureConsigneNbCycle = BORNE_INF_CYCLE;
  }
}

void onCyclePlus() {
  //#ifdef DEBUG
  Serial.println("nb cycle ++");
  //#endif
  futureConsigneNbCycle++;
  if (futureConsigneNbCycle > BORNE_SUP_CYCLE) {
    futureConsigneNbCycle = BORNE_SUP_CYCLE;
  }
}

void onPressionPepMinus() {
  //#ifdef DEBUG
  Serial.println("pression PEP --");
  //#endif
  futureConsignePressionPEP--;
  if (futureConsignePressionPEP < BORNE_INF_PRESSION_PEP) {
    futureConsignePressionPEP = BORNE_INF_PRESSION_PEP;
  }
}

void onPressionPepPlus() {
  //#ifdef DEBUG
  Serial.println("pression PEP ++");
  //#endif
  futureConsignePressionPEP++;
  if (futureConsignePressionPEP > BORNE_SUP_PRESSION_PEP) {
    futureConsignePressionPEP = BORNE_SUP_PRESSION_PEP;
  }
}

void onPressionPlateauMinus() {
  // #ifdef DEBUG
  Serial.println("pression plateau --");
  // #endif
  futureConsignePressionPlateauMax--;
  if (futureConsignePressionPlateauMax < BORNE_INF_PRESSION_PLATEAU) {
    futureConsignePressionPlateauMax = BORNE_INF_PRESSION_PLATEAU;
  }
}

void onPressionPlateauPlus() {
  //#ifdef DEBUG
  Serial.println("pression plateau ++");
  //#endif
  futureConsignePressionPlateauMax++;
  if (futureConsignePressionPlateauMax > BORNE_SUP_PRESSION_PLATEAU) {
    futureConsignePressionPlateauMax = BORNE_SUP_PRESSION_PLATEAU;
  }
}

void onAlarmOff() {
  #ifdef DEBUG
  Serial.println("alarm OFF");
  #endif
}

void onAlarmOn() {
  #ifdef DEBUG
  Serial.println("alarm ON");
  #endif
}

double filteredVout = 0;

int readPressureSensor() {
  
  double rawVout = analogRead(PIN_PRESSURE_SENSOR) * 3.3 / 1024.0;
  
  filteredVout = filteredVout + (rawVout - filteredVout) * 0.2;
  
  // Ratio a cause du pont diviseur
  double vOut = filteredVout / RATIO_PONT_DIVISEUR;

  // Pression en kPA
  double pressure  = (vOut / V_SUPPLY - 0.04) / 0.09;

  return pressure * KPA_MMH2O / 10.0;
}

// boutons
AnalogButtons analogButtons(PIN_RUN_BUTTONS, INPUT);

Button btnPressionCretePlus(TENSION_BTN_PRESSION_P_CRETE_PLUS, &onPressionCretePlus);
Button btnPressionCreteMinus(TENSION_BTN_PRESSION_P_CRETE_MINUS, &onPressionCreteMinus);
Button btnPressionPlateauPlus(TENSION_BTN_PRESSION_PLATEAU_PLUS, &onPressionPlateauPlus);
Button btnPressionPlateauMinus(TENSION_BTN_PRESSION_PLATEAU_MINUS, &onPressionPlateauMinus);
Button btnPressionPepPlus(TENSION_BTN_PEP_PLUS, &onPressionPepPlus);
Button btnPressionPepMinus(TENSION_BTN_PEP_MINUS, &onPressionPepMinus);
Button btnCyclePlus(TENSION_BTN_CYCLE_PLUS, &onCyclePlus);
Button btnCycleMinus(TENSION_BTN_CYCLE_MINUS, &onCycleMinus);

// Button btnAlarmOff(BTN_ALARM_OFF, &onAlarmOff);
// Button btnAlarmOn(BTN_ALARM_ON, &onAlarmOn);

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("demarrage");
  #endif
  //patient.attach(PIN_SERVO_PATIENT);
  blower.attach(PIN_SERVO_PATIENT);

  #ifdef DEBUG
  Serial.print("mise en secu initiale");
  #endif
  blower.write(SECURITE_COUPURE_BLOWER);
  //patient.write(SECURITE_OUVERTURE_EXPI);

  #ifdef LCD_20_CHARS_4_LINES
  lcd.begin(20, 4);
  #endif
  #ifdef LCD_20_CHARS_2_LINESe
  lcd.begin(20, 2);
  #endif
  #ifdef LCD_20_CHARS_2_LINES
  lcd.begin(16, 2);
  #endif

  // analogButtons.add(btnPressionCretePlus);
  // analogButtons.add(btnPressionCretePlus);
  // analogButtons.add(btnPressionPlateauPlus);
  // analogButtons.add(btnPressionPlateauMinus);
  // analogButtons.add(btnPressionPepPlus);
  // analogButtons.add(btnPressionPepMinus);
  // analogButtons.add(btnCyclePlus);
  // analogButtons.add(btnCycleMinus);

  Wire.begin();
  
  pinMode(PIN_ALARM, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_MOTEUR_VENTILATEUR, OUTPUT);
  pinMode(PIN_SERVO_BLOWER, OUTPUT);
  pinMode(PIN_SERVO_PATIENT, OUTPUT);
  pinMode(PIN_CONTROL_BUTTONS, INPUT);
  pinMode(PIN_RUN_BUTTONS, INPUT);
  pinMode(PIN_BATTERY, INPUT);
  pinMode(PIN_PRESSURE_SENSOR, INPUT);

  digitalWrite(PIN_ALARM, LOW);
  Serial.begin(9600);
}


//Call this in loop() to help find analog values of buttons
void calibrateButtons() {
	unsigned int value = analogRead(A0);
	Serial.println(value);
	delay(250);
}

void loop() {

  int nbreCentiemeSecParCycle = 60 * 100 / consigneNbCycle;
  int nbreCentiemeSecParInspi = nbreCentiemeSecParCycle / 3; // inspiration = 1/3 du cycle, expiration = 2/3 du cycle

  #ifdef DEBUG
  Serial.println();
  Serial.println("------ Starting cycle ------");
  Serial.print("nbreCentiemeSecParCycle = ");
  Serial.println(nbreCentiemeSecParCycle);
  Serial.print("nbreCentiemeSecParInspi = ");
  Serial.println(nbreCentiemeSecParInspi);
  #endif

  int currentPressionCrete = -1;
  int currentPressionPlateau = -1;
  int currentPressionPep = -1;

  int currentPositionBlower = SECURITE_COUPURE_BLOWER;

  int dureeBaissePression = 0; // compteur de centièmes pour la détection du pic de pression (pression crête)

  // phase courante du cycle
  int currentPhase = PHASE_PUSH_INSPI;

  // état des actionneurs au tick précédent
  int positionBlower = 90;
  int positionPatient = 90;

  // nouvelles consignes pour les actionneurs
  int consigneBlower = 90;
  int consignePatient = 90;

  consigneNbCycle = futureConsigneNbCycle;
  consigneOuverture = futureConsigneOuverture;
  consignePressionPEP = futureConsignePressionPEP;
  consignePressionPlateauMax = futureConsignePressionPlateauMax;
  #ifdef DEBUG
  Serial.print("consigneNbCycle = ");
  Serial.println(consigneNbCycle);
  Serial.print("consigneOuverture = ");
  Serial.println(consigneOuverture);
  Serial.print("consignePressionPEP = ");
  Serial.println(consignePressionPEP);
  Serial.print("consignePressionPlateauMax = ");
  Serial.println(consignePressionPlateauMax);
  #endif

  affichageDebutCycle();

  /********************************************/
  // Début d'un cycle
  /********************************************/
  int currentCentieme = 0;

  while (currentCentieme < nbreCentiemeSecParCycle) {

    static uint32_t dateDernierTraitement = 0ul;
    uint32_t dateCourante = millis();
    if (dateCourante - dateDernierTraitement >= PERIODE_DE_TRAITEMENT) {

      currentCentieme++;
      
      /********************************************/
      // Le traitement est effectué toutes les 
      // PERIODE_DE_TRAITEMENT millisecondes
      // Note sur la gestion du temps. La date en
      // millisecondes de l'Arduino déborde tous
      // les 40 jours environ. Il faut donc comparer
      // des intervalles et non des dates absolues
      // Sinon, au bout de 40 jours, ça plante.
      /********************************************/
      dateDernierTraitement = dateCourante;

      /********************************************/
      // Mesure pression pour rétro-action
      /********************************************/
      #ifdef SIMULATION
      double currentPression = 0.0;
      if (currentCentieme < 50.0) {
        currentPression = 60.0;
      } else {
        currentPression = 30.0;
      }
      if (currentCentieme > nbreCentiemeSecParInspi) {
        currentPression = 5.0;
      }
      #else
      double currentPression = readPressureSensor();
      Serial.println(currentPression);
      #endif

      /********************************************/
      // Calcul des consignes normales
      /********************************************/

      if (currentCentieme <= nbreCentiemeSecParInspi) { // on est dans la phase temporelle d'inspiration (poussée puis plateau)
        if (currentPression >= currentPressionCrete) {
          // phase montante jusqu'à crète
          currentPhase = PHASE_PUSH_INSPI;
          currentPressionCrete = currentPression;

          consigneBlower = ANGLE_MULTIPLICATEUR * consigneOuverture ;//90 - ANGLE_MULTIPLICATEUR * consigneOuverture; // on ouvre le blower vers patient à la consigne paramétrée
          //consignePatient = 90 + ANGLE_MULTIPLICATEUR * ANGLE_OUVERTURE_MAXI; // on ouvre le flux IN patient
        } else {
          // phase plateau
          currentPhase = PHASE_HOLD_INSPI;
          currentPressionPlateau = currentPression;

          consigneBlower =  50; //90 + ANGLE_MULTIPLICATEUR * ANGLE_OUVERTURE_MAXI; // on shunt vers l'extérieur
          consignePatient = 90; // on bloque les flux patient
        }
      } else { // on gère l'expiration on est phase PHASE_EXPIRATION
        currentPhase = PHASE_EXPIRATION;
        currentPressionPep = currentPression;
        consigneBlower = 20;//90 + ANGLE_MULTIPLICATEUR * ANGLE_OUVERTURE_MAXI; // on shunt vers l'extérieur
        consignePatient = SECURITE_OUVERTURE_EXPI; // on ouvre le flux OUT patient (expiration vers l'extérieur)
      }

      /********************************************/
      // Calcul des consignes de mise en sécurité
      /********************************************/
      // si pression crête > max, alors fermeture blower de 2°
      if (currentPression > consignePressionCrete) {
        #ifdef DEBUG
        if (currentCentieme % 80) {
          Serial.println("Mise en securite : pression crete trop importante");
        }
        #endif
        consigneBlower = positionBlower - 2;
      }
      // si pression plateau > consigne param, alors ouverture expiration de 1°
      if (currentPhase == PHASE_HOLD_INSPI && currentPression > consignePressionPlateauMax) {
        #ifdef DEBUG
        if (currentCentieme % 80) {
          Serial.println("Mise en securite : pression plateau trop importante");
        }
        #endif
        consigneBlower = positionBlower - 2;
      }
      // si pression PEP < PEP mini, alors fermeture complète valve expiration
      if (currentPression < consignePressionPEP) {
        #ifdef DEBUG
        if (currentCentieme % 80) {
          Serial.println("Mise en securite : pression d'expiration positive (PEP) trop faible");
        }
        #endif
        consigneBlower = positionBlower + 2;
        consignePatient = 90;
        currentPhase = PHASE_HOLD_EXPI;
      }

      #ifdef DEBUG
      if (currentCentieme % 50 == 0) {
        Serial.print("Phase : ");
        Serial.println(currentPhase);
        Serial.print("Pression : ");
        Serial.println(currentPression);
      }
      #endif

      /********************************************/
      // Envoi des nouvelles valeurs aux actionneurs
      /********************************************/
      if (consigneBlower != positionBlower) {
        blower.write(consigneBlower);
        positionBlower = consigneBlower;
      }

      if (consignePatient != positionPatient) {
        //patient.write(consignePatient);
        positionPatient = consignePatient;
      }

      /********************************************/
      // Préparation des valeurs pour affichage
      /********************************************/
      previousPressionCrete = currentPressionCrete;
      previousPressionPlateau = currentPressionPlateau;
      previousPressionPep = currentPressionPep;

      /********************************************/
      // Écoute des appuis boutons
      /********************************************/
      analogButtons.check();
      //calibrateButtons();
        if (currentCentieme % LCD_UPDATE_PERIOD == 0) {
            afficherPendantCycle(currentPression);
        }
    }
  }
  /********************************************/
  // Fin du cycle
  /********************************************/

}

/********************************************/
// Affichage une fois par cycle respiratoire
/********************************************/
void affichageDebutCycle() {
  lcd.setCursor(0, 0);
  #ifdef LCD_20_CHARS_4_LINES
  lcd.print("pc=");
  lcd.print(previousPressionCrete);
  lcd.print("  pp=");
  lcd.print(previousPressionPlateau);
  lcd.setCursor(0, 1);
  lcd.print("pep=");
  lcd.print(previousPressionPep);
  lcd.print("  ");
  #endif
  #ifdef LCD_20_CHARS_2_LINES
  lcd.print("pc=");
  lcd.print(previousPressionCrete);
  lcd.print("/pp=");
  lcd.print(previousPressionPlateau);
  lcd.print("/pep=");
  lcd.print(previousPressionPep);
  lcd.print("  ");
  #endif
  #ifdef LCD_16_CHARS_2_LINES
  lcd.print("pc");
  lcd.print(previousPressionCrete);
  lcd.print("/pp");
  lcd.print(previousPressionPlateau);
  lcd.print("/pep");
  lcd.print(previousPressionPep);
  lcd.print("  ");
  #endif
}

/********************************************/
// Affichage pendant le cycle
/********************************************/
void afficherPendantCycle(double currentPression) {     
    lcd.setCursor(0, 2);
    #ifdef LCD_20_CHARS_4_LINES
    lcd.print("c=");
    lcd.print(futureConsigneNbCycle);
    lcd.print("  pl=");
    lcd.print(futureConsignePressionPlateauMax);
    lcd.setCursor(0, 3);
    lcd.print("pep=");
    lcd.print(futureConsignePressionPEP);
    lcd.print("  Curr=");
    lcd.print(currentPression);
    #endif
    #ifdef LCD_20_CHARS_2_LINES
    lcd.print("c=");
    lcd.print(futureConsigneNbCycle);
    lcd.print("/pl=");
    lcd.print(futureConsignePressionPlateauMax);
    lcd.print("/pep=");
    lcd.print(futureConsignePressionPEP);
    lcd.print("|");
    lcd.print(currentPression);
    #endif
    #ifdef LCD_16_CHARS_2_LINES
    lcd.print("c");
    lcd.print(futureConsigneNbCycle);
    lcd.print("/pl");
    lcd.print(futureConsignePressionPlateauMax);
    lcd.print("/pep");
    lcd.print(futureConsignePressionPEP);
    #endif
}
