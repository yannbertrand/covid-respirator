// Décommenter pour activer les message de debug sur le serie
// #define DEBUG

// Décommenter pour simuler des valeurs de capteur de pression au lieu de lire les vraies
// #define SIMULATION 

// Définition des PIN pour les entrées / sorties
#define PIN_ALARM D13
#define PIN_LED_RED PC4
#define PIN_LED_GREEN PB13
#define PIN_MOTEUR_VENTILATEUR D5
#define PIN_SERVO_BLOWER D2
#define PIN_SERVO_PATIENT D4
#define PIN_CONTROL_BUTTONS A0
#define PIN_RUN_BUTTONS A4
#define PIN_BATTERY A2
#define PIN_PRESSURE_SENSOR A1

// PIN pour LCD
#define RS D7
#define EN D8
#define DB4 D9
#define DB5 D10
#define DB6 D11
#define DB7 D12 

// contrôle de l'écran LCD
#define LCD_20_CHARS_4_LINES // commenter pour soit utiliser un LCD 20x2 ou un 16x2
// #define LCD_20_CHARS_2_LINES // commenter pour utiliser un écran LCD 16 caratères
// #define LCD_16_CHARS_2_LINES

// Période en ms de la boucle de traitement
const uint32_t PERIODE_DE_TRAITEMENT = 10ul;

// Pressure sensor constants
const double KPA_TO_MMHG = 7.5006156130264;
const double KPA_MMH2O = 101.97162129779;
const double V_SUPPLY = 5.08;
const double RATIO_PONT_DIVISEUR = 0.8192; // 0.572727273;

// amplitude radiale des servomoteurs
const int ANGLE_OUVERTURE_MINI = 8;
const int ANGLE_OUVERTURE_MAXI = 45;

// multiplicateur à modifier pour inverser les angles (en cas de suppression de l'engrenage)
const int ANGLE_MULTIPLICATEUR = 1;

// borne pour le capteur de pression
const int CAPT_PRESSION_MINI = 0; // a adapter lors de la calibration
const int CAPT_PRESSION_MAXI = 800; // on ne va pas jusqu'à 1024 à cause de la saturation de l'AOP -> à adapter avec meilleur AOP

const int LCD_UPDATE_PERIOD = 20; // période (en centièmes de secondes) de mise à jour du feedback des consignes sur le LCD

// phases possibles du cycle
const int PHASE_PUSH_INSPI = 1; // pousée d'inspiration : on envoie l'air jusqu'à la pression crête paramétrée : valve blower ouverte à consigne, flux d'air vers le patient
const int PHASE_HOLD_INSPI = 2; // plateau d'inspiration : on a depassé la pression crête, la pression descend depuis plus d'un 1/10sec (arbitraire EFL) : 2 valves fermées
const int PHASE_EXPIRATION = 3; // expiration : flux d'air vers l'extérieur, air patient vers l'extérieur
const int PHASE_HOLD_EXPI  = 4; // expiration bloquée : les valves sont fermées car la pression est en dessous de la PEP

// minimums et maximums possible des paramètres modifiables à l'exécution
const int BORNE_SUP_PRESSION_CRETE = 70; // arbitraire
const int BORNE_INF_PRESSION_CRETE = 10; // arbitraire
const int BORNE_SUP_PRESSION_PLATEAU = 30; // PP MAX SDRA = 30
const int BORNE_INF_PRESSION_PLATEAU = 10; // arbitraire
const int BORNE_SUP_PRESSION_PEP = 30; // PP MAX = 30, or PEP < PP
const int BORNE_INF_PRESSION_PEP = 5; // arbitraire mais > 0

const int BORNE_SUP_CYCLE = 35; // demande medical
const int BORNE_INF_CYCLE = 5;  // demande medical

// durée d'appui des boutons (en centièmes de secondes) avant prise en compte
const int MAINTIEN_PARAMETRAGE = 21;

// valeurs de sécurité pour les actionneurs
const int SECURITE_COUPURE_BLOWER = 90 - ANGLE_OUVERTURE_MAXI;
const int SECURITE_OUVERTURE_EXPI = 90 - ANGLE_OUVERTURE_MAXI;

// servomoteur blower : connecte le flux d'air vers le Air Transistor patient ou vers l'extérieur
// 90° → tout est fermé
// entre 45° (90 - ANGLE_OUVERTURE_MAXI) et 82° (90 - ANGLE_OUVERTURE_MINI) → envoi du flux vers l'extérieur
// entre 98° (90 + ANGLE_OUVERTURE_MINI) et 135° (90 + ANGLE_OUVERTURE_MAXI) → envoi du flux vers le Air Transistor patient
Servo blower;

// servomoteur patient : connecte le patient au flux d'air entrant ou à l'extérieur
// 90° → tout est fermé
// entre 45° (90 - ANGLE_OUVERTURE_MAXI) et 82° (90 - ANGLE_OUVERTURE_MINI) → envoi du flux vers le patient
// entre 98° (90 + ANGLE_OUVERTURE_MINI) et 135° (90 + ANGLE_OUVERTURE_MAXI) → échappe l'air du patient vers l'extérieur
Servo patient;


// // contrôle de l'écran LCD
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

// AnalogButtons buttons = AnalogButtons(A0);




const int BTN_FREE2                       = 913;
const int BTN_FREE1                       = 821;
const int BTN_ALARM_OFF                   = 745;
const int BTN_ALARM_ON                    = 607;
const int BTN_CYCLE_MINUS                 = 509;
const int BTN_CYCLE_PLUS                  = 413;
const int BTN_PRESSION_PEP_MINUS          = 292;
const int BTN_PRESSION_PEP_PLUS           = 215;
const int BTN_PRESSION_PLATEAU_MINUS      = 109;
const int BTN_PRESSION_PLATEAU_PLUS       =   0;

// TODO revoir les tensions ici
const uint16_t TENSION_BTN_PRESSION_P_CRETE_PLUS   = 915;
const uint16_t TENSION_BTN_PRESSION_P_CRETE_MINUS  = 728;
const uint16_t TENSION_BTN_PRESSION_PLATEAU_PLUS   = 505;
const uint16_t TENSION_BTN_PRESSION_PLATEAU_MINUS  = 410;
const uint16_t TENSION_BTN_PEP_PLUS                = 0;
const uint16_t TENSION_BTN_PEP_MINUS               = 598;
const uint16_t TENSION_BTN_CYCLE_PLUS              = 291;
const uint16_t TENSION_BTN_CYCLE_MINUS             = 215;

const uint16_t TENSION_BTN_ALARME_ON        = BTN_ALARM_ON;
const uint16_t TENSION_BTN_ALARME_OFF       = BTN_ALARM_OFF;
const uint16_t TENSION_BTN_ALARME_SILENCE   = BTN_FREE1;