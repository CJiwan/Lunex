/***************************************************
 *  Includes                                       *
 ***************************************************/
#include <MsTimer2.h>
 
/***************************************************
 * Déclarations des I/O pour les moteurs           *    
 * et autres constantes                            *
 ***************************************************/
// Moteur de gauche
#define pwm_Left 10 // Consigne de vitesse
#define dir_Left 8  // Sense de rotation
#define mes_Left 3  // Entrée pour mesure de la vitesse

// Moteur de droite
#define pwm_Right 9 // Consigne de vitesse
#define dir_Right 7 // Sense de rotation
#define mes_Right 2 // Entrée pour mesure de la vitesse

// Constantes divers
#define length_Cmd 6  // Chaque commande émise par le Raspberry comporte 6 caractères
#define DMT B0100   // 4  Start mesure distance cyclique
#define DST B0000  // 0  Arrêt mesure cyclique
#define DMP B1100  // 12 Mesure la distance à une position donnée
#define RMF B0101  // 5  Marche Forward Moteur Droite
#define RMB B1101  // 13 Marche Backward Moteur Droite
#define RST B0001  // 1  Arrêt Moteur Droite
#define LMF B0110  // 6  Marche Forward Moteur Gauche
#define LMB B1110  // 14 Marche Backward Moteur Gauche
#define LST B0010  // 2  Arrêt Moteur Gauche
#define Pos_Left  1
#define Pos_Middle  2
#define Pos_Right  3

/***************************************************
 *  Déclaration des Variables globales             *
 **************************************************/
char gSerial_Buffer[6];
byte gCmd;
byte gDmd_Pos;
word gDM_Time;
word gRM_Speed;
word gLM_Speed;

void Move_Servo() {
  
}

void setup() {
  Serial.begin(115200);
  pinMode(pwm_Left, OUTPUT);
  pinMode(dir_Left, OUTPUT);
  pinMode(pwm_Right, OUTPUT);
  pinMode(dir_Right, OUTPUT);

  analogWrite(pwm_Right, 255);
  analogWrite(pwm_Left, 255);
}

void loop() {
  if (Serial.available()>=6) {
    Serial.readBytes(gSerial_Buffer, length_Cmd);
    gCmd=0;
    switch (gSerial_Buffer[0]) {
      case 'D' : gCmd = B000;
        break;
      case 'R' : gCmd = B001;
        break;
      case 'L' : gCmd = B010;
        break;
    }
    if (gSerial_Buffer[1] == 'M')
    { gCmd = gCmd | B100; }

    if (gSerial_Buffer[2] == 'B' || gSerial_Buffer[2] == 'P')
    { gCmd = gCmd | B1000; }

    gDmd_Pos = 0;
    switch (gCmd) {
       case DMP : 
          switch (gSerial_Buffer[5]) {
            case 'L' : gDmd_Pos = Pos_Left;
              break;
            case 'M' : gDmd_Pos = Pos_Middle;
              break;
            case 'R' : gDmd_Pos = Pos_Right;
              break;
          }
          break;
        case DMT :
          gDM_Time = (gSerial_Buffer[3]-48)*100 + (gSerial_Buffer[4]-48)*10 + gSerial_Buffer[5]-48;
          break;
        case RMF :
        case RMB :
          gRM_Speed = 255 - ((gSerial_Buffer[3]-48)*100 + (gSerial_Buffer[4]-48)*10 + gSerial_Buffer[5]-48);
          break;
        case LMF :
        case LMB :
          gLM_Speed = 255 - ((gSerial_Buffer[3]-48)*100 + (gSerial_Buffer[4]-48)*10 + gSerial_Buffer[5]-48);
          break;
    }

    switch (gCmd) {
      case RST : 
          analogWrite(pwm_Right, 255);
        break;
      case LST : 
          analogWrite(pwm_Left, 255);
        break;
       case RMB : 
          digitalWrite(dir_Right, true);
          analogWrite(pwm_Right, gRM_Speed);
        break;
        case RMF : 
          digitalWrite(dir_Right, false);
          analogWrite(pwm_Right, gRM_Speed);
        break;
        case LMB : 
          digitalWrite(dir_Left, false);
          analogWrite(pwm_Left, gLM_Speed);
        break;
        case LMF : 
          digitalWrite(dir_Left, true);
          analogWrite(pwm_Left, gLM_Speed);
        break;
    }
  }
}
