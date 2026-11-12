/*
  LED controlado por gestos de la mano - ESP32
  --------------------------------------------
  Recibe por USB (puerto serie, 115200 baudios) los comandos que envía el notebook:
    "1" o "ON"  -> enciende el LED
    "0" o "OFF" -> apaga el LED
  y responde "OK:1" / "OK:0".

  Conexión del LED externo:
    GPIO 26 -> resistencia de 220 ohm -> pata LARGA del LED (ánodo, +)
    pata CORTA del LED (cátodo, -)     -> GND del ESP32

  No conectes nada a los pines CLK, SD0, SD1, SD2, SD3 ni CMD (son de la memoria flash).
*/

const int PIN_LED = 26;  // pin donde está conectado el LED externo

String comando = "";

void ponerLed(bool encendido) {
  digitalWrite(PIN_LED, encendido ? HIGH : LOW);
  Serial.println(encendido ? "OK:1" : "OK:0");
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  ponerLed(false);  // arrancar con el LED apagado
  Serial.println("ESP32 listo");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      comando.trim();
      comando.toUpperCase();
      if (comando == "1" || comando == "ON") {
        ponerLed(true);
      } else if (comando == "0" || comando == "OFF") {
        ponerLed(false);
      } else if (comando.length() > 0) {
        Serial.println("ERROR: comando desconocido -> " + comando);
      }
      comando = "";
    } else if (comando.length() < 20) {
      comando += c;
    }
  }
}
