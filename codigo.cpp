//variaveis lum
int bin; float tensao, res, lum; // Declara variáveis

//variaveis lcd
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// Define o endereço do LCD no barramento I2C e o
// número de colunas e linhas (16x2)
LiquidCrystal_I2C lcd(0x27,16,2);

//variaveis umidade
#include <DHT.h>
DHT dht(2,DHT22); // Declara objeto do tipo DHT
float umid, temp; // Declara variáveis

//variaveis pressao
#include <Adafruit_BMP280.h>
#include <Wire.h>
Adafruit_BMP280 bmp; // Declara objeto do tipo BMP
float press, temp1; // Declara variáveis

//variaveis temp(lm35)
int bin1; float tensao1, temp2; // Declara variáveis

void setup()
{
//setup lum
Serial.begin(9600); // Inicializa serial

//setup lcd
lcd.init(); // Inicializa LCD

//criar caracteres no lcd
uint8_t o_agudo[8] PROGMEM = {B00010,B00100,B00000,B01110,B10001,B10001,B10001,B01110};
lcd.createChar(0,o_agudo);
uint8_t grau[8] PROGMEM = {B00111,B00101,B00111,B00000,B00000,B00000,B00000,B00000};
lcd.createChar(1,grau);
uint8_t a_tio[8] PROGMEM = {B00101,B01010,B00000,B01110,B00001,B01111,B10001,B01111};
lcd.createChar(2,a_tio);
uint8_t ccedilha[8] PROGMEM = {B00000,B00000,B01110,B10000,B10000,B10000,B01110,B00100};
lcd.createChar(5,ccedilha);
uint8_t maisoumenos[8] PROGMEM = {B00100,B00100,B11111,B00100,B00100,B00000,B11111,B00000};
lcd.createChar(3,maisoumenos);

lcd.backlight(); // Liga luz do LCD
lcd.setCursor(0,0);
lcd.print("Estacao"); // Escreve no LCD
lcd.setCursor(4,0);
lcd.write(5);
lcd.setCursor(5,0);
lcd.write(2);
lcd.setCursor(0,1); // Move cursor no LCD
lcd.print("meteorologica");// Escreve no LCD
lcd.setCursor(8,1);
lcd.write(0);
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Turma 1B");
lcd.setCursor(0,1);
lcd.print("Instrumed");
delay(2000);
lcd.clear();
lcd.setCursor(0,0); // Move cursor no LCD
lcd.print("Luis");// Escreve no LCD
lcd.setCursor(0,1); // Move cursor no LCD
lcd.print("Rodrigues");// Escreve no LCD
delay(2000);
lcd.clear();
lcd.setCursor(0,0); // Move cursor no LCD
lcd.print("Ilana");// Escreve no LCD
lcd.setCursor(0,1); // Move cursor no LCD
lcd.print("Finger");// Escreve no LCD
delay(2000);
lcd.clear();
lcd.setCursor(0,0); // Move cursor no LCD
lcd.print("Fernando");// Escreve no LCD
lcd.setCursor(0,1); // Move cursor no LCD
lcd.print("Alzueta");// Escreve no LCD
delay(2000);
lcd.clear();

//setup umidade
Serial.begin(9600);// Inicializa serial
dht.begin(); // Inicializa objeto dht

//setup pressao
Serial.begin(9600); // Inicializa serial
bmp.begin(0x76); // Inicializa objeto BMP

//setup temp(lm35)
Serial.begin(9600); // Inicializa serial

}
void loop()
{

//loop lum
bin = analogRead(A1); // Lê binário
tensao = (bin/1023.0)*5.0; // Calc. tensão
res = tensao*10000.0/(5.0-tensao); // Calc. resist.
lum = pow(10,3.871-0.291*log10(res)); // Calc. lumnos.
Serial.print("\n\nDado: ");
Serial.print(bin); // Exibe binário
Serial.print("\nTensão [V]: ");
Serial.print(tensao); // Exibe tensão
Serial.print("\nResistência [kΩ]: ");
Serial.print(res/1000); // Exibe resistência
Serial.print("\nLuminosidade [Lux]: ");
Serial.print(lum); // Exibe luminosidade

//loop lcd
lcd.setCursor(0,1); // Move cursor no LCD

//loop umidade
umid = dht.readHumidity(); // Lê umidade
temp = dht.readTemperature(); // Lê temperatura
umid = 1.4087884*umid - 20.6683071; // Calibração
Serial.print("\n\nUmidade [%]: ");
Serial.print(umid); // Exibe umidade
Serial.print("\nTemperatura [ºC]: ");
Serial.print(temp); // Exibe temp.

//loop pressao
press = bmp.readPressure(); // Lê pressão
temp1 = bmp.readTemperature();// Lê temperatura
Serial.print("\n\nPressão [hPa]: ");
Serial.print(press/100); // Exibe pressão
Serial.print("\nTemperatura [ºC]: ");
Serial.print(temp1); // Exibe temperatura

//loop temp(lm35)
bin1 = analogRead(A0); // Lê valor binário
tensao1 = (bin1/1023.0)*5.0; // Converte em tensão
temp2 = 100.832524543919*tensao1-0.017646507539873; // Converte em temp.
Serial.print("\n\nDado: ");
Serial.print(bin1); // Exibe dado binário
Serial.print("\nTensão [V]: ");
Serial.print(tensao1,3); // Exibe tensão
Serial.print("\nTemperatura [ºC]: ");
Serial.print(temp2); // Exibe temperatura

Serial.print("\n\n=================================================================");

lcd.setCursor(0,0);
lcd.print("Temperatura( C): ");
lcd.setCursor(12,0);
lcd.write(1);
lcd.setCursor(0,1);
lcd.print(temp2);
lcd.write(3);
lcd.print("0.5");
lcd.write(1);
lcd.print("C");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Umidade(%): ");
lcd.setCursor(0,1);
lcd.print(umid);
lcd.write(3);
lcd.print("2%");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Pressao(atm): ");
lcd.setCursor(5,0);
lcd.write(2);
lcd.setCursor(0,1);
lcd.print(press/100/1023);
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Luz (lux): ");
lcd.setCursor(0,1);
lcd.print(lum);
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
}
