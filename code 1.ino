// ============================================================
// Smart Temperature Monitor - Arduino UNO
// Maincrafts Technology | Embedded Systems Task-1
// Author  : Soham | Walchand College of Engineering
// Platform: Arduino UNO + LM35 Sensor
// ============================================================

// ---------------- PIN DEFINITIONS ----------------
const int TEMP_SENSOR_PIN = A0;   // LM35 output pin
const int RED_LED_PIN     = 8;    // Red LED
const int GREEN_LED_PIN   = 9;    // Green LED
const int BUZZER_PIN      = 10;   // Buzzer

// ---------------- TEMPERATURE THRESHOLD ----------------
const float TEMP_THRESHOLD = 30.0;   // Alert above 30°C

// ============================================================
// SETUP FUNCTION
// Runs once when Arduino starts
// ============================================================
void setup() {

  // Initialize Serial Monitor
  Serial.begin(9600);

  // Configure output pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial states
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Startup message
  Serial.println("=================================");
  Serial.println(" SMART TEMPERATURE MONITOR ");
  Serial.println("=================================");
  Serial.print("Threshold Temperature : ");
  Serial.print(TEMP_THRESHOLD);
  Serial.println(" C");
  Serial.println("System Started...");
  Serial.println();
}

// ============================================================
// LOOP FUNCTION
// Runs continuously
// ============================================================
void loop() {

  // -------- STEP 1: Read Analog Value --------
  int sensorValue = analogRead(TEMP_SENSOR_PIN);

  // -------- STEP 2: Convert to Voltage --------
  float voltage = sensorValue * (5.0 / 1023.0);

  // -------- STEP 3: Convert Voltage to Temperature --------
  // LM35 gives 10mV per degree Celsius
  float temperature = voltage * 100.0;

  // -------- STEP 4: Print Data --------
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  // -------- STEP 5: Alert Condition --------
  if (temperature >= TEMP_THRESHOLD) {

    // High temperature alert
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

    // Buzzer ON
    tone(BUZZER_PIN, 1000);

    Serial.println("STATUS : HIGH TEMPERATURE ALERT!");

  }
  else {

    // Normal condition
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);

    // Buzzer OFF
    noTone(BUZZER_PIN);

    Serial.println("STATUS : TEMPERATURE NORMAL");
  }

  Serial.println("--------------------------------");

  // Wait 1 second
  delay(1000);
}