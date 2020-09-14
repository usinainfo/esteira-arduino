/*******************************************************************************************************
------------------------------------ Autor: Gustavo R Stroschon -----------------------------------------
------------------------------------ Data: 09/03/2020 ----------------------------------------------------
Função do programa: Verificar a quantia de objetos que passa pela esteira através do sensor ultrassônico.
*******************************************************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>               

#define trigger_pin 9
#define echo_pin 8

#define max_distance 20
#define distance_good 10

#define pin_motor A0
#define pwm_value 200

LiquidCrystal_I2C lcd(0x27, 16, 2); // configura o display

NewPing sonar(trigger_pin, echo_pin, max_distance); // configura o  sensor ultrasonico

// inicializaçao variaveis
int counter = 0;
int last_counter = 0;
bool flag = 0;

void setup() {

Serial.begin(9600);

  lcd.begin(); // inicia a comunicaçao com o lcd
  lcd.backlight();// liga aluz de fundo do lcd

  lcd.setCursor(0, 0);
  lcd.print("USINAINFO");

  lcd.setCursor(0, 1);
  lcd.print("Objetos : ");
  lcd.setCursor(14, 1);
  lcd.print("0");

// configuraçoes dos pinos
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  pinMode(pin_motor, OUTPUT);
}

void loop() {

  int distancia = sonar.convert_cm(sonar.ping_median(10)); // faz um calculo para obter a media da distancia

Serial.println(distancia);

  if (distancia <= distance_good && distancia != 0) { // se a distancia for menor que a distancia ideal e nao for um 0 ...
    if (flag == 0) {       // verifica se antes ja havia sido identificado um objeto
      digitalWrite(pin_motor, LOW);    // desliga o motor

      flag = 1;            // indica que encontrou um objeto
      counter++;           // incrementa a variavel que guarda o numero de objetos contados

      delay(500);
    }
  } else {
    flag = 0;
  }

  digitalWrite(pin_motor, HIGH); // liga o motor

  if (counter != last_counter) { // verifica se o número da contagem é o mesmo da anterior
    last_counter = counter;

    lcd.setCursor(0, 1);
    lcd.print("Objetos : ");
    lcd.setCursor(14, 1);
    lcd.print(counter);

  }
}
