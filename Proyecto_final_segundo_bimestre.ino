/*
   Fundacion Kinal
   Centro educativo técnico laboral Kinal
   Quinto perito
   Quinto electrónica
   Código Técnico: EB5AV / EB5AV
   Curso: Taller de electrónica digital y reparación de computadoras I
   Proyecto: Proyecto final
   Dev: Josivar Sebastián Rayjam Alva López
   Fecha: 27 de mayo del año 2024
   link de la simulación: 
*/

#include <Wire.h>
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Directivas de procesador servomotor
#define pin_servo 11

// Directivas de procesador teclado matricial
#define filas_teclado 2
#define columnas_teclado 3

#define f1_teclado 13
#define f2_teclado 12

#define c1_teclado 10
#define c2_teclado 9
#define c3_teclado 8

// Directivas de procesador pantalla LCD
#define direccion_LCD 0x27 
#define filas_LCD 2
#define columnas_LCD 16

// Definición de pines para los LEDs
const int ledPins[] = {A3, A2, A1, A0};
// Definición de pines del display
#define A 7
#define B 6
#define C 5
#define D 4
#define E 3
#define F 2
#define G 1

const int Segmentos[] = {A, B, C, D, E, F, G};

// Variables para el uso del teclado
char keys[filas_teclado][columnas_teclado] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};

byte pines_filas[filas_teclado] = {f1_teclado, f2_teclado};
byte pines_columnas[columnas_teclado] = {c1_teclado, c2_teclado, c3_teclado};

// Variables para el uso del servomotor
const int inicial_pos = 0;   
const int final_pos = 180; 

// Constructor
LiquidCrystal_I2C lcd(direccion_LCD, columnas_LCD, filas_LCD);
Servo Servodeteccion;
Keypad tecladoDeteccion = Keypad(makeKeymap(keys), pines_filas, pines_columnas, filas_teclado, columnas_teclado);

// Funciones
void config_outputs(void);
void config_HMI(void);
void display();
void Autofantastico(void);

// Función para configurar el HMI
void config_HMI(void) {
  Servodeteccion.attach(pin_servo);
  Servodeteccion.write(inicial_pos);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Josivar Alva");
  delay(100); 
  lcd.setCursor(1, 1);
  lcd.print("Proyecto final");
  delay(100); 
}

// Función para controlar el display
void display() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(Segmentos[i], HIGH);
    delay(250);
    digitalWrite(Segmentos[i], LOW);
  }
  for (int i = 7; i >= 0; i--) {
    digitalWrite(Segmentos[i], HIGH);
    delay(250);
    digitalWrite(Segmentos[i], LOW);
  }
}

// Función para el "Autofantástico"
void Autofantastico(void) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(250);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 4; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(250);
    digitalWrite(ledPins[i], LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Proyecto final");

  config_outputs();
  config_HMI();
}

void loop() {
  char key = tecladoDeteccion.getKey();

  if (key) {

    // Acción para la tecla '1'
    // Contador 0-99
    if (key == '1') {
      Serial.println("Se presiono la tecla 1");
      Serial.println("Contador automático de 0 a 99");
      for (int ascendente = 0; ascendente <= 99; ascendente++) {
        Serial.println(ascendente);
        delay(100);
      }
    }
    // Acción para la tecla '2'
    // Contador 99-0
    else if (key == '2') {
      Serial.println("Se presiono la tecla 2");
      Serial.println("Contador automático de 99 a 0");
      for (int descenso = 99; descenso >= 0; descenso--) {
        Serial.println(descenso);
        delay(100);
      }
    }
    // Acción para la tecla '3'
    // Efecto Autofantástico
    else if (key == '3') {
      Serial.println("Se presiono la tecla 3");
      Serial.println("Animacion del auto fantástico");
      Autofantastico();
    }
    // Acción para la tecla '4'
    // Display innovación
    else if (key == '4') {
      Serial.println("Se presiono la tecla 4");
      Serial.println("Animacion por medio del Display");
      display();
    }
    // Acción para la tecla '5'
    // Movimiento del servomotor
    else if (key == '5') {
      Serial.println("Se presiono la tecla 5");
      Serial.println("Movimiento de 0 a 180 grados,servomotor");
      Servodeteccion.write(final_pos);
      delay(500);  // Espera 0.5 segundos
      Servodeteccion.write(inicial_pos);
    }
  }
}

void config_outputs(void) {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  for (int i = 0; i < 7; i++) {
    pinMode(Segmentos[i], OUTPUT);
  }  
}
