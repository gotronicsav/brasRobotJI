#include <Servo.h>

Servo base; Servo epaule; Servo coude; Servo poignet; Servo rotapince; Servo ouvepince;

int J1, J2, J3, J4;
int BP1, BP2;

int angle1, angle2, angle3, angle4, angle5, angle6;
int pas1, pas2, pas3, pas4;

void setup() {

  base.attach(6); //sortie numérique 6
  epaule.attach(3); //sortie numérique 3
  coude.attach(9); //sortie numérique 9
  poignet.attach(5); //sortie numérique 5
  rotapince.attach(11); //sortie numérique 11
  ouvepince.attach(10); //sortie numérique 10

  pinMode(4, INPUT_PULLUP); //sortie numérique 4
  pinMode(2, INPUT_PULLUP); //sortie numérique 2
  //utilise le VCC et la résistance de pullup de l’Arduino >> évite de rajouter un VCC et une résistance dans le montage

  J1 = J2 = J3 = J4 = 0;
  BP1 = BP2 = 1;

  angle1 = angle2 = angle3 = angle4 = angle5 = 1500; //90°
  angle6 = 2000; //180°

}

void loop() {

  J1 = analogRead(A2);  J3 = analogRead(A0); //Joystick gauche mouvement horizontal et vertical
  J2 = analogRead(A3);  J4 = analogRead(A1); //Joystick droit mouvement vertical et horizontal
  BP1 = digitalRead(4); BP2 = digitalRead(2); //Bouton poussoir gauche et droit

  base.writeMicroseconds(angle1);
  epaule.writeMicroseconds(angle2);
  coude.writeMicroseconds(angle3);
  poignet.writeMicroseconds(angle4);
  rotapince.writeMicroseconds(angle5);
  ouvepince.writeMicroseconds(angle6);

  //lecture J1
  if (J1 > 1000) {
    angle6 -= 10;  //action sur la fermeture de la pince
    if (angle6 < 1650) {
      angle6 = 1650;
    }
  }
  else
  { //action sur la base
    pas1 = map(J1, 200, 800, -10, 10);
    if (pas1 < 5 && pas1 > -5) {}  //offset
    else
    {
      angle1 += pas1;
      if (angle1 > 2200) {
        angle1 = 2200;
      }
      if (angle1 < 800) {
        angle1 = 800;
      }

    }
  }

  //lecture J2 et action sur le coude
  pas3 = map(J2, 100, 900, -10, 10);
  if (pas3 < 5 && pas3 > -5) {}
  else
  {
    angle3 += pas3;
    if (angle3 > 2100) {
      angle3 = 2100;
    }
    if (angle3 < 900) {
      angle3 = 900;
    }
  }

  //lecture J3 et action sur l'épaule
  if (J3 > 1000) {
    angle6 += 10;  //action sur la l'ouverture de la pince
    if (angle6 > 2400) {
      angle6 = 2400;
    }
  }
  else
  {
    pas2 = map(J3, 200, 800, -10, 10);
    if (pas2 < 5 && pas2 > -5) {}
    else
    {
      angle2 -= pas2;
      if (angle2 > 2200) {
        angle2 = 2200;
      }
      if (angle2 < 1000) {
        angle2 = 1000;
      }
    }
  }

  //lecture J4 et action sur le poignet
  pas4 = map(J4, 100, 900, -10, 10);
  if (pas4 < 5 && pas4 > -5) {}
  else
  {
    angle4 -= pas4;
    if (angle4 > 2100) {
      angle4 = 2100;
    }
    if (angle4 < 900) {
      angle4 = 900;
    }
  }

  //lecture BP1 et BP2, et action sur la rotation de la pince
  if (BP1 == LOW) {
    angle5 -= 10;
    if (angle5 < 600) {
      angle5 = 600;
    }
  }
  if (BP2 == LOW) {
    angle5 += 10;
    if (angle5 > 2100) {
      angle5 = 2100;
    }
  }

  delay(15);

}
