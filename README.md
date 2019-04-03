# Bomba arduino para simulacion airsoft

- ## Menu
	- ### 1.Iniciar juego
		- #### 1.-Counterstrike
		- #### 2.-Asalto
		- #### 3.-Dominacion
		- #### 4.-Explosivo
	- ### 2.Configuracion
		- #### 1.-Tiempo
			- #### 1.-Tiempo de juego
			- #### 2.-Tiempo bomba
			- #### 3.-Tiempo des/armado
			- #### 4.-Tiempo inicio
		- #### 2.-Mecanismo bloqueo
			- #### 1.-Bloqueos activos
			- #### 2.-Contraseña
			- #### 3.-Cables
			- #### 4.-Llaves NFC
		- #### 3.-Otras opciones
			- #### 1.-Sonido
			- #### 2.-Alarma
			- #### 3.-Granada
		- #### 4.-Test

# I2C pins (LCD)
| MODELO | SDA | SCK |
| --- | --- | --- |
| Uno | A4 | A5 |
| Nano | A4 | A5 |
| Mini Pro | A4 | A5 |
| Mega     | 20  | 21  |

# MFR522 pins
| Signal | MFRC522 | Arduino Uno | Arduino Mega | Arduino Nano v3 | Arduino Leonardo/Micro | Arduino Pro Micro |
| --- | --- | --- | --- | --- | --- | --- |
| RST/Reset | RST | 9 | 5 | D9 | RESET/ICSP-5 | RST |
| SPI SS | SDA(SS) | 10 | 53 | D10 | 10 | 10 |
| SPI MOSI | MOSI | 11 / ICSP-4 | 51 | D11 | ICSP-4 | 16 |
| SPI MISO | MISO | 12 / ICSP-1 | 50 | D12 | ICSP-1 | 14 |
| SPI SCK | SCK | 13 / ICSP-3 | 52 | D13 | ICSP-3 | 15 |
