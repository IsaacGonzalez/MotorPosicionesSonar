/**
 * Librería para utilizar sensores ultrasonicos.
 * http://playground.arduino.cc/Code/NewPinghttp://playground.arduino.cc/Code/NewPing
 */ 
#include <NewPing.h>

/**
 * Pines utilizados para el motor ultrasonico en el arduino uno.
 */
#define TRIGGER_PIN  8
#define ECHO_PIN     9
#define MAX_DISTANCE 200

// Inicializamos la variable con la cual accedemos al sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// push buttons para ubicar al motor en distintas posiciones
const int pin_boton_1 = 2;
const int pin_boton_2 = 3;
const int pin_boton_3 = 4;
const int pin_boton_4 = 6;
const int pin_boton_5 = 7;

// valores de los botones
int boton_1 = 0;
int boton_2 = 0;
int boton_3 = 0;
int boton_4 = 0;
int boton_5 = 0;

// salidas para el puente H que mueve el motor en una direccion u otra
const int pin_motor_adelante = 10;
const int pin_motor_atras = 11;

// pin para el led incluido en el arduino uno
const int pin_led =  13;

// variable en la que se guarda la distancia que nos regresa el sensor
int distancia = 0;

void setup() {
  
  pinMode(pin_led, OUTPUT);
  
  pinMode(pin_boton_1, INPUT);
  pinMode(pin_boton_2, INPUT);
  pinMode(pin_boton_3, INPUT);
  pinMode(pin_boton_4, INPUT);
  pinMode(pin_boton_5, INPUT);

  pinMode(pin_motor_adelante, OUTPUT);
  pinMode(pin_motor_atras, OUTPUT);

  Serial.begin(9600);  
}

void loop() {
  
  boton_1 = digitalRead(pin_boton_1);
  boton_2 = digitalRead(pin_boton_2);
  boton_3 = digitalRead(pin_boton_3);
  boton_4 = digitalRead(pin_boton_4);
  boton_5 = digitalRead(pin_boton_5);

  // imprimirEstatusBotones();
  distancia = getDistanciaEnCentimetros(sonar);

  // Cada boton corresponde a una posicion y cada posicion tiene un rango. 
  if (boton_1 == HIGH) {
    posicionarMotor(distancia, 9, 10);
  } else  if (boton_2 == HIGH) {
    posicionarMotor(distancia, 14, 15);
  } else  if (boton_3 == HIGH) {
    posicionarMotor(distancia, 20, 22);
  } else  if (boton_4 == HIGH) {
    posicionarMotor(distancia, 26, 27);
  } else  if (boton_5 == HIGH) {
    posicionarMotor(distancia, 33, 34);
  } else {
    detener();
  }

  /**
   * Este intervalo era inicialmente 100, pero se bajo porque 
   * ocasionaba que el motor se moviera muy bruscamente porque 
   * variaba mucho la medida entre intervalos.
   */
  delay(10); 
}

/**
 * Mover el motor hacia adelante
 */
void adelante(){
  digitalWrite(pin_motor_adelante, HIGH);
  digitalWrite(pin_motor_atras, LOW);
}

/**
 * Mover el motor hacia atras
 */
void atras(){
  digitalWrite(pin_motor_adelante, LOW);
  digitalWrite(pin_motor_atras, HIGH);
}

/**
 * Detener el motor
 */
void detener(){
  digitalWrite(pin_motor_adelante, LOW);
  digitalWrite(pin_motor_atras, LOW);
}

/** 
 * Imprime en la consola una linea con lo que reciben los botones.
 * 
 * Ej. 
 *  Botones: 0 0 0 0 0
 */
void imprimirEstatusBotones(){
  Serial.print("Botones: ");
  Serial.print(boton_1);
  Serial.print(" ");
  Serial.print(boton_2);
  Serial.print(" ");
  Serial.print(boton_3);
  Serial.print(" ");
  Serial.print(boton_4);
  Serial.print(" ");
  Serial.print(boton_5);
  Serial.print(" ");
  Serial.println("");
}

/**
 * Obtiene la distancia entre el motor y el sensor en centimetros.
 */
int getDistanciaEnCentimetros(NewPing sonar){
  int uS = sonar.ping();

  return uS / US_ROUNDTRIP_CM;
}

/**
 * Mueve el motor hacia atras o hacia enfrente, dependiendo de la distancia.
 * La distancia que se envía es la distancia actual que está regresando el sensor.
 * El límite inferior y limite superior definen el rango en el que se tiene que posicionar el motor.
 */
void posicionarMotor(int distancia, int limiteInferior, int limiteSuperior){
  if(distancia < limiteInferior){
      adelante();  
    } else if (distancia > limiteSuperior ){
      atras();
    } else {
      detener();
    }
}

