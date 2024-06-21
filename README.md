**Global Solution FIAP (1° Semestre) - Arduino para monitorar e registrar a temperatura da água e a incidência solar.**

# Descrição
O projeto Aqua Future é uma solução ao desafio "Blue Future" apresentado pela FIAP. Ele tem como objetivo monitorar e registrar a temperatura da água e a incidência solar, contribuindo para a proteção dos oceanos. Ele implementa um sistema de monitoramento de temperatura e luminosidade usando um Arduino. O sistema simula a leitura de temperatura e luminosidade através de potenciômetros. Além disso, o projeto inclui funcionalidades como alertas visuais e sonoros quando a temperatura excede um certo limite e o registro dos dados em uma memória EEPROM.

Este projeto foi simulado na plataforma [wokwi](https://wokwi.com/projects/401109789842699265), usando um [código em C++](https://github.com/DFedizko/arduino-aquafuture/blob/main/codigo_aquafuture.ino).


# Funcionalidades
- Leitura de temperatura e luminosidade utilizando potenciômetros.

- Exibição dos valores de temperatura e luminosidade em um display LCD 16x2.

- Barra de LEDs que indica o nível de luminosidade.

- Alerta visual (LED vermelho) e sonoro (buzzer) quando a temperatura média excede 23ºC.

- Registro de dados na EEPROM com indicação de anomalias.

- Recuperação de registros armazenados na EEPROM.

# Componentes Utilizados
- 1 Arduino Uno R3

- 1 Display LCD 16x2 com interface I2C

- 2 Potenciômetros (simulando sensores NTC e LDR)

- 1 Barra de LEDs

- 1 LED vermelho

- 1 Buzzer (Piezo)

- 1 Resistor (220Ω)

- 35 Jumpers Macho/Macho

# Bibliotecas Utilizadas
- EEPROM: Para leitura e escrita na memória EEPROM.
  
- Wire: Para comunicação I2C com o display LCD.
  
- LiquidCrystal I2C: Para controle do display LCD via I2C.

# Circuito
**Sensores Simulados** 

Para o circuito, seria necessário o uso de NTC e LDR porém seria necessário um resistor aplicado ao NTC. Devido à plataforma wokwi estar com limitações de uso nos resistores, foi utilizado potenciômetros para simular as leituras de temperatura e luminosidade.

**Potenciômetro para Temperatura:**

- Pino central conectado ao pino analógico A0 do Arduino.

- Outros dois pinos conectados ao VCC e GND.
  
**Potenciômetro para Luminosidade:**

- Pino central conectado ao pino analógico A1 do Arduino.

- Outros dois pinos conectados ao VCC e GND.
  
**Display LCD 16x2 com interface I2C:**
  
- VCC -> 5V

- GND -> GND

- SDA -> A4

- SCL -> A5

**Barra de LEDs:**

Pinos anodos (positivos):

- LED 1(A1) -> Pino D2

- LED 2(A2) -> Pino D3

- LED 3(A3) -> Pino D4

- LED 4(A4) -> Pino D5

- LED 5(A5) -> Pino D6

- LED 6(A6) -> Pino D7

- LED 7(A7) -> Pino D8

- LED 8(A8) -> Pino D9

- LED 9(A9) -> Pino D10

- LED 10(A10) -> Pino D11

Pinos Catodos (negativos):

- LED C1 a C10 -> GND

**Alerta de Anomalia**

LED Vermelho:
  
- Anodo (perna longa) conectado ao pino D12.

- Catodo (perna curta) conectado ao GND através de um resistor de 220Ω.

**Buzzer(Piezo):** 

- Pino positivo conectado ao pino D13.

- Pino negativo conectado ao GND.

# Contribuição
Contribuições são bem-vindas! Se você tiver sugestões ou encontrar bugs, por favor, abra uma issue ou faça um pull request.
