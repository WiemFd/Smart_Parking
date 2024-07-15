#include <LiquidCrystal.h>// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#include <Servo.h> //includes the servo library

Servo myservo1; // servomotor
int IR1 = 2; // infra_rouge 
int IR2 = 4; // infra_rouge 

int Bi_Led= 7; // led bicolor red and green 

int IR1_etat;
int IR2_etat;

int green = 8;
int red = 7;

int Total = 5;
int Full = 0; 
int Empty = 0;

void setup() {
pinMode(IR1, INPUT); // pinMote for declaration input or output
pinMode(IR2, INPUT);
pinMode(red, OUTPUT); // bi color led : red
pinMode(green, OUTPUT); // bi color led : green

myservo1.attach(3); // pin (port 3 arduino)/
myservo1.write(0); 

lcd.begin(16, 2);  //  17 colones  3 lignes for show LCD
lcd.setCursor (0,0); // position in LCD 1st line 
lcd.print("  Smart Parking ");
lcd.setCursor (0,1); 
lcd.print("     System     ");
//delay (1000);
//lcd.clear();  
digitalWrite(red,HIGH);
digitalWrite(green,LOW);
}

void loop(){ 

IR1_etat = digitalRead (IR1);
IR2_etat = digitalRead (IR2);

if(IR1_etat == 0 && IR2_etat == 1 ){ // presence d'un vehicule à lentree et absence d'un vehicule à la sortie
    
     if(Full< Total) // véhicule veut entrer et il y des places vides
     {
          digitalWrite(red,LOW);
         digitalWrite(green,HIGH);
        myservo1.write(90);
        delay(2000); // attendre l'entree de la voiture.
        digitalWrite(green,LOW);
         digitalWrite(red,HIGH);
        myservo1.write(0);
        //delay(1000); // barrire attend 1 s apres sa fermeture
        Full=Full+1; 
        Empty=Total-Full;
        lcd.clear(); 
        lcd.setCursor (0,0);
        lcd.print("Total Spaces: ");
        lcd.print(Total);
        
        lcd.setCursor (0,1);
        lcd.print("Empty Spaces: ");
        lcd.print(Empty);
     }

   if( Full== Total) { // véhicule veut enter et parking full

    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
    myservo1.write(0);
    lcd.clear(); 
    lcd.setCursor (0,0);
    lcd.print("Total Spaces: ");
    lcd.print(Total);
    lcd.setCursor (0,1);
    lcd.print(" Full ");
 
    }
}

if (IR2_etat == 0 && IR1_etat == 1 && Empty < Total) // vehicule veut sortir */
   {

    lcd.clear(); 
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    myservo1.write(90);
    delay(2000); // attendre la sortie du véhicule 
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
    myservo1.write(0);
    //delay(1000);
    Full=Full-1;
    Empty=Total-Full;
    lcd.setCursor (0,0);
    lcd.print("Total Spaces: ");
    lcd.print(Total);
    
    lcd.setCursor (0,1);
    lcd.print("Empty Spaces: ");
    lcd.print(Empty);
      }
}
