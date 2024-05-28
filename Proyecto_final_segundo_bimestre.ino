/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Proyecto final
   Dev: Josivar Sebastián Rayjam Alva López
   Fecha: 27 de mayo del año 2024
   link de la simulacion: 
*/


#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Directivas de procesador servomotor
#define pin_servo 5

// Directivas de procesador teclado matricial
#define filas_teclado 4
#define columnas_teclado 4

#define f1_teclado 13
#define f2_teclado 12
#define f3_teclado 11
#define f4_teclado 10

#define c1_teclado 9
#define c2_teclado 8
#define c3_teclado 7
#define c4_teclado 6

// Directivas de procesador pantalla LCD
#define direccion_LCD 0x27 // Usa el escáner I2C para confirmar esta dirección
#define filas_LCD 2
#define columnas_LCD 16

// Directivas de procesador otros componentes
#define led_rojo A0
#define led_naranja A1
#define led_amarillo A2
#define led_verde A3

#define decodificador_A 4
#define decodificador_B 3
#define decodificador_C 2
#define decodificador_D 1

// Directivas de procesador para encendido y apagado
#define ON(pin) digitalWrite(pin, HIGH)
#define OFF(pin) digitalWrite(pin, LOW)

// Variables para el uso del teclado
char keys[filas_teclado][columnas_teclado] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pines_filas[filas_teclado] = {f1_teclado, f2_teclado, f3_teclado, f4_teclado};
byte pines_columnas[columnas_teclado] = {c1_teclado, c2_teclado, c3_teclado, c4_teclado};

// Variables para el uso del servomotor
const int inicial_pos = 0;          // Posición inicial del servo
const int deteccion_tecla5 = 180;    // Posición de 180 grados para indicar que se presionó la tecla 5

// Constructor
LiquidCrystal_I2C lcd(direccion_LCD, columnas_LCD, filas_LCD);
Servo Servodeteccion;
Keypad tecladoCerradura = Keypad(makeKeymap(keys), pines_filas, pines_columnas, filas_teclado, columnas_teclado);

// Funciones
void config_outputs(void);
void config_HMI(void);
void display();

// Función para controlar el servomotor y la LCD
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
}
// función para controlar el display
void display() {
  OFF(decodificador_A);
  OFF(decodificador_B);
  ON(decodificador_C);
  ON(decodificador_D);
  delay(100);
  
  OFF(decodificador_A);
  OFF(decodificador_B);
  ON(decodificador_C);
  OFF(decodificador_D);
  delay(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Proyecto final");

  config_outputs();
  config_HMI();
  display();
}

void loop() {
  char key = tecladoCerradura.getKey();

  if (key) {
    Serial.println(key);

    // Acción para la tecla '1'
     // contador 0-99
    if (key == '1') {
      Serial.println("Se presionó la tecla 1");
      for (int ascendente = 0; ascendente <= 99; ascendente++) {
        Serial.println(ascendente);
        delay(100);
      }
    }
    // Acción para la tecla '2'
    // contador 99-0
    else if (key == '2') {
      Serial.println("Se presionó la tecla 2");
      for (int descenso = 99; descenso >= 0; descenso--) {
        Serial.println(descenso);
        delay(100);
      }
    }
    // Acción para la tecla '3'
    // suto fantastico
    else if (key == '3') {
      Serial.println("Se presionó la tecla 3");

      ON(led_verde);
      delay(500);
      OFF(led_verde);
      ON(led_amarillo);
      delay(500);
      OFF(led_amarillo);
      ON(led_naranja);
      delay(500);
      OFF(led_naranja);
      ON(led_rojo);
      delay(500);
      OFF(led_rojo);
      delay(500);
    }

    // Acción para la tecla '4'
    // display innovaciòn
    else if (key == '4') {
      Serial.println("Se presionó la tecla 4");
      display();    
    }
    
    // Acción para la tecla '5'
    // movimiento del servomotor
    else if (key == '5') {
      Serial.println("Se presionó la tecla 5");
      Servodeteccion.write(180);  
      delay(100);  // Espera 1 segundo
      Servodeteccion.write(0);  
    }
  }
}

void config_outputs(void) {
  pinMode(led_rojo, OUTPUT);
  pinMode(led_naranja, OUTPUT);
  pinMode(led_amarillo, OUTPUT);
  pinMode(led_verde, OUTPUT);

  pinMode(decodificador_A, OUTPUT);
  pinMode(decodificador_B, OUTPUT);
  pinMode(decodificador_C, OUTPUT);
  pinMode(decodificador_D, OUTPUT);
}
