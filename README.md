# Temp_Arduino_be

Projekt beskrivning:

Detta projekt skickar sensor data från ett Arduino R4 kort över wifi och denna hanteras sedan med en java backend.
Frontenden är byggd med Node.js och vi använder MongoDb som databas för att spara sensor data.
Syftet med projektet är att samla in data (just nu med en intervall på 15 minuter) och sedan hantera datan och visa statistik.

* Backend: <br>
	* Java 21 <br>
	* Spring <br>

* dependencies: <br>
	* spring dev tools <br>
	*  spring web <br>
	*  spring data mongodb <br>

* Frontend: <br>
	* vite <br>
	* Node.js med npm <br>
	* javascript <br>

* Arduino: <br>
	* model - R4 <br>
	* sensor - Dht11 temp/humidty sensor <br>
