# Bomba arduino para simulacion airsoft

- ## Menu
	- ### 1.Iniciar juego
		- #### Modos de juego
			- ##### 1.1.Bomba
			- ##### 1.2.Dominacion
	- ### 2.Configuracion
		- #### 2.1.Tiempo
		- #### 2.2.Seleccion juegos
			- ##### 2.2.1.Contraseña
				- ###### Si/No
				- ###### Introducir contraseña
			- ##### 2.2.2.Cables
				- ###### Si/No
				- ###### Cable 1
					- Reducir tiempo
					- Parar bomba
					- No hacer nada
					- Explotar
				- ###### Cable 2
					- Reducir tiempo
					- Parar bomba
					- No hacer nada
					- Explotar
				- ###### Cable 3
					- Reducir tiempo
					- Parar bomba
					- No hacer nada
					- Explotar
				- ###### Cable 4
					- Reducir tiempo
					- Parar bomba
					- No hacer nada
					- Explotar
			- ##### 2.2.3.Llaves NFC
				- ###### Si/No
				- ###### Funcion llave
					- Reducir tiempo
					- Parar bomba
					- No hacer nada
					- Explotar
		- #### 2.3.Bombba armada
			- ##### Si/No
			- ##### Tiempo armado/desarmado
		- #### 2.4.Otras opciones
			- ##### Sonido
			- ##### Alarma explosion
			- ##### Granada explosion

# I2C pins
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
