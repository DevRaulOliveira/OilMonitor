// C++ code
//TRABALHO DE CONCLUSÃO DE CURSO -  MONITORAMENTO DA PRESSÃO DE ÓLEO
// Inclusão da biblioteca do LCD

#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

bool ign = 13 ; // Botão Ignição
bool motor = 12 ; // Botão Motor

int pot = A0 ; // Potenciometro simulando a pressão
int valorPot = 0; // Valor inicial do potenciometro "Sensor de Pressão" = 0
int valorcorrigidopot = 0;

int sensorTemp = A1; // Sensor de Temperatura
int celsius = 0; // Temperatura inicial em Graus Celsius
double realDegree; // Conversão para a temperatura em fgraus Celsius
String lcdBuffer;

int rotacaomotor = A2; // Entrada do sinal analogico do corpo de borboleta.
int valorRotacaoMotor = 0; // Valor inicial da rotação motor
int valorCorrigidoRotacaoMotor = 0;



void setup()//Definição de parametros, sistemas, pinos de entrada e de saída
{
  {
  Serial.begin (9600);
 
  pinMode (13,INPUT); // Liga Ignição
  pinMode (12,INPUT); // Liga Motor pinMode (11, OUTPUT);
  pinMode (11, OUTPUT);// Ativa o potenciometro da rotação do motor
  pinMode (10, OUTPUT);// Saída do potenciometro que controla a rotação do motor 
  pinMode (9, OUTPUT); // Led luz da bateria
  pinMode (8, OUTPUT); // Led luz do sensor de óleo
  pinMode (0, INPUT);
  pinMode (1, INPUT);
  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (2, OUTPUT);
  }
  {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Tmp:");
  lcd.setCursor(0,1);
  lcd.print("Press: V");
  lcd.setCursor(14, 0);
  lcd.print(" V");
  sensorTemp = 0;
  realDegree = 0;
  }
}
void loop()
{
  {// Posição da informação no LCD.
  lcd.setCursor(4, 0);
  lcd.print("");
  }
  
  { // Variavel Temperatura
  sensorTemp = analogRead(A1);
  realDegree = (double)sensorTemp/1024;
  realDegree *= 5;
  realDegree -= 0.5;
  realDegree *= 100;
  String output = String(realDegree) + String((char)178)+"C";
  lcd.print(output); 
  
   
       
  {// Potenciometro "Sensor de pressão"
	valorPot = analogRead(A0);
	valorcorrigidopot = map(valorPot, 0, 1023, 0, 5);
	lcd.setCursor(6, 1);
	lcd.print(valorcorrigidopot);
  } 
    

  {//Potenciometro Rotação do motor
  valorRotacaoMotor = analogRead(A2);
  valorCorrigidoRotacaoMotor = map(valorRotacaoMotor, 0, 1023, 0, 7);
  lcd.setCursor(14, 0);
  lcd.print(valorCorrigidoRotacaoMotor);
  }}
    //COMBINAÇÃO DAS VARIAVEIS PRESSÃO, ROTAÇÃO MOTOR e TEMPERATURA para fazer o LED VERMELHO acender
   		 if ((realDegree > 80)&&(valorcorrigidopot >= 2)&&(valorCorrigidoRotacaoMotor == 3))
  		 {
         digitalWrite (8, HIGH);
   		 }
			else
			{
			 digitalWrite (8,LOW);
			}
      
      
    
  { // Programação ignição e motor.
  ign = digitalRead (13);
  motor = digitalRead (12);
  
  
  if (ign) 
  {
  digitalWrite (9, LOW);
  digitalWrite (8,LOW);
  }
 
  	else
  	{
   	digitalWrite (9,HIGH);
   	digitalWrite (8,HIGH);
 	 }
  
  
  if (motor) 
  {
  digitalWrite (11,HIGH);
  digitalWrite (9,LOW);
  digitalWrite (8,LOW);
  }
      else
      {
 	  digitalWrite (11,LOW);
  	  digitalWrite (9,LOW);
 	  digitalWrite (8,LOW);
  	  } 
      
  if (valorCorrigidoRotacaoMotor)
  {
  analogWrite(10, constrain(analogRead(A2), 0, 255));
  }
      else
      {
      analogWrite (10, LOW);
      }

  

  }}

   

 
