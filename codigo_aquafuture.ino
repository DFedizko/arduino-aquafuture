#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

// DESENHO DO LOGO AQUA FUTURE NO LCD

byte SIMB1[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00011
};

byte SIMB2[8] = {
B00000,
B00000,
B00110,
B00110,
B00110,
B00110,
B00110,
B11110
};

byte SIMB3[8] = {
B00000,
B00000,
B01100,
B01100,
B01100,
B01100,
B01100,
B01111
};

byte SIMB4[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11000
};

byte SIMB5[8] = {
B00011,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000
};

byte SIMB6[8] = {
B11110,
B00110,
B00110,
B00110,
B00110,
B00110,
B00000,
B00000
};

byte SIMB7[8] = {
B01111,
B01100,
B01100,
B01100,
B01100,
B01100,
B00000,
B00000
};

byte SIMB8[8] = {
B11000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000
};

// DEFINIÇÃO DOS PINOS

const int pinoTempPot = A0;
const int pinoLuzPot = A1;

const int pinosLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int numLEDs = 10;

const int pinoLedVermelho = 12;
const int pinoBuzzer = 13;

// VARIÁVEL QUE SALVA 30 LEITURAS PARA CALCULAR A MÉDIA

const int numLeituras = 30;

// ARRAYS PARA ARMAZENAR AS LEITURAS
int leiturasTemperatura[numLeituras];
int leiturasLuminosidade[numLeituras];
int indiceLeitura = 0;

// VARIÁVEIS PARA SOMAR AS LEITURAS

int somaTemperatura = 0;
int somaLuminosidade = 0;

// ENDEREÇO EEPROM

int enderecoEEPROM = 0;

// FUNÇÃO PARA LER A TEMPERATURA

int lerTemperatura() {
  int valorBruto = analogRead(pinoTempPot);
  float temperatura = (valorBruto * (5.0 / 1023.0)) * 100.0; // Simulação simples
  return round(temperatura);
}

// FUNÇÃO PARA LER A LUMINOSIDADE

int lerLuminosidade() {
  int valorBruto = analogRead(pinoLuzPot);
  float luminosidade = (valorBruto / 1023.0) * 100.0; // Simulação simples
  return round(luminosidade);
}

// BARRA DE LED BASEADA NA LUMINOSIDADE (10% POR BARRA)

void atualizarBarraDeLEDs(int luminosidade) {
  int numLEDsAcesos = luminosidade / (100.0 / numLEDs);
  for (int i = 0; i < numLEDs; i++) {
    if (i < numLEDsAcesos) {
      digitalWrite(pinosLEDs[i], HIGH);
    } else {
      digitalWrite(pinosLEDs[i], LOW);
    }
  }
}

// FUNÇÃO PARA LER A EEPROM

void lerEEPROM() {
  int temp, luz;
  bool anomalia;
  int endereco = 0;
  bool registrosEncontrados = false;
  
  Serial.println("Lendo registros da EEPROM...");
  
  while (endereco < 900 * (sizeof(int) * 2 + sizeof(bool))) {
    EEPROM.get(endereco, temp);
    endereco += sizeof(int);
    EEPROM.get(endereco, luz);
    endereco += sizeof(int);
    EEPROM.get(endereco, anomalia);
    endereco += sizeof(bool);

    // SE OS VALORES FOREM 0xFFFF, SIGNIFICA QUE NÃO VALORES REGISTRADOS

    if (temp == 0xFFFF && luz == 0xFFFF) {
      break;
    }

    registrosEncontrados = true;
    
    Serial.print("Registro ");
    Serial.print(endereco / (sizeof(int) * 2 + sizeof(bool)));
    Serial.print(": Temp = ");
    Serial.print(temp);
    Serial.print("°C, Luz = ");
    Serial.print(luz);
    Serial.print("%");

    if (anomalia) {
      Serial.println(" - Anomalia encontrada e registrada!");
    } else {
      Serial.println();
    }
  }

  if (!registrosEncontrados) {
    Serial.println("Nenhum registro encontrado na EEPROM.");
  }
}

// FUNÇÃO PARA REGISTRAR OS VALORES NA EEPROM

void registrarNaEEPROM(int temperatura, int luminosidade, bool anomalia) {

  EEPROM.put(enderecoEEPROM, temperatura);
  enderecoEEPROM += sizeof(int);
  EEPROM.put(enderecoEEPROM, luminosidade);
  enderecoEEPROM += sizeof(int);
  EEPROM.put(enderecoEEPROM, anomalia);
  enderecoEEPROM += sizeof(bool);

  // VERIFICA SE O ENDEREÇO EEPROM ESTÁ NO LIMITE

  if (enderecoEEPROM >= 900 * (sizeof(int) * 2 + sizeof(bool))) { // 
    enderecoEEPROM = 0; // 
  }
}

void setup() {
  Serial.begin(9600); 

  // INÍCIO DO LCD

  lcd.init();
  lcd.backlight();
  lcd.createChar(1, SIMB1);
  lcd.createChar(2, SIMB2);
  lcd.createChar(3, SIMB3);
  lcd.createChar(4, SIMB4);
  lcd.createChar(5, SIMB5);
  lcd.createChar(6, SIMB6);
  lcd.createChar(7, SIMB7);
  lcd.createChar(8, SIMB8);
 
  byte Count = 1;
 
  lcd.clear();

  // PRINT DE BYTES PARA A LOGO

  for (byte y = 0; y < 2; y++) {
    for (byte x = 0; x < 4; x++) {
      lcd.setCursor(x, y);
      lcd.write(Count);
      Count++;
      
    }
  }
  lcd.setCursor(4, 0);
  lcd.print("   AQUA");
  lcd.setCursor(4, 1);
  lcd.print("   FUTURE"); 
 
  for (int i = 0; i < numLEDs; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
  }

  // CONFIGURAÇÕES DO LED VERMELHO E BUZZER

  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);

  // INICIALIZA AS ARRAYS PARA LEITURA
  
  for (int i = 0; i < numLeituras; i++) {
    leiturasTemperatura[i] = 0;
    leiturasLuminosidade[i] = 0;
  }
  delay(2000); 

  // LÊ OS REGISTROS DA EEPROM AO INICIAR

  lerEEPROM();
}

void loop() {

  int temperaturaAtual = lerTemperatura();
  int luminosidadeAtual = lerLuminosidade();

  // EXIBIÇÃO DE VALORES NO LCD

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperaturaAtual);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Luz: ");
  lcd.print(luminosidadeAtual);
  lcd.print("%");

  // ATUALIZA A BARRA DE LED COM BASE NA LUMINOSIDADE

  atualizarBarraDeLEDs(luminosidadeAtual);

  // LÓGICA PARA ATUALIZAR OS VALORES DA SOMA TOTAL

  somaTemperatura -= leiturasTemperatura[indiceLeitura];
  somaLuminosidade -= leiturasLuminosidade[indiceLeitura];

  leiturasTemperatura[indiceLeitura] = temperaturaAtual;
  leiturasLuminosidade[indiceLeitura] = luminosidadeAtual;

  somaTemperatura += leiturasTemperatura[indiceLeitura];
  somaLuminosidade += leiturasLuminosidade[indiceLeitura];

  indiceLeitura++;

  if (indiceLeitura >= numLeituras) {
    indiceLeitura = 0;

    // CALCULO DAS MÉDIAS

    int mediaTemperatura = round(somaTemperatura / numLeituras);
    int mediaLuminosidade = round(somaLuminosidade / numLeituras);

    Serial.println();
    Serial.print("Temperatura Média: ");
    Serial.print(mediaTemperatura);
    Serial.println("°C");

    Serial.print("Luminosidade Média: ");
    Serial.print(mediaLuminosidade);
    Serial.println("%");

    // LÓGICA PARA VERIFICAR SE A TEMPERATURA EXCEDE 23°C

    if (mediaTemperatura > 23) {
      digitalWrite(pinoLedVermelho, HIGH);
      digitalWrite(pinoBuzzer, HIGH);

      delay(3000);

      digitalWrite(pinoLedVermelho, LOW);
      digitalWrite(pinoBuzzer, LOW);

      Serial.println("Anomalia encontrada! Temperatura excedeu 23°C.");
      Serial.println("Registrando anomalia na EEPROM...");

      // FUNÇÃO PARA REGISTRAR AS ANOMALIAS E VALORES MÉDIOS NA EEPROM 

      registrarNaEEPROM(mediaTemperatura, mediaLuminosidade, true);

      Serial.println("Média registrada na EEPROM.");
    } else {
      Serial.println("Média calculada.");
    }
  }
  delay(2000);
}
