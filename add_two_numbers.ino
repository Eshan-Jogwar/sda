void setup() {
  Serial.begin(9600);
  // This tells the Arduino how long to wait for a number (shorter is better here)
  Serial.setTimeout(50); 
  Serial.println("--- Arduino Simple Calculator ---");
}

void loop() {
  float num1, num2, result;
  char operation;

  // --- 1. Get Number 1 ---
  Serial.println(F("\nEnter Number 1:"));
  while (Serial.available() == 0); // Wait
  num1 = Serial.parseFloat();
  clearSerialBuffer(); 
  Serial.print(F("Input received: ")); Serial.println(num1);

  // --- 2. Get Number 2 ---
  Serial.println(F("Enter Number 2:"));
  while (Serial.available() == 0);
  num2 = Serial.parseFloat();
  clearSerialBuffer();
  Serial.print(F("Input received: ")); Serial.println(num2);

  // --- 3. Get Operation ---
  Serial.println(F("Enter Operation (+, -, *, /):"));
  while (Serial.available() == 0);
  // Peek and skip any leftover newlines before reading the char
  while (isspace(Serial.peek())) { Serial.read(); } 
  operation = Serial.read();
  clearSerialBuffer();

  // --- 4. Calculate ---
  bool valid = true;
  if (operation == '+') result = num1 + num2;
  else if (operation == '-') result = num1 - num2;
  else if (operation == '*') result = num1 * num2;
  else if (operation == '/') {
    if (num2 != 0) result = num1 / num2;
    else { Serial.println(F("Error: Divide by Zero")); valid = false; }
  } else {
    Serial.print(F("Error: Invalid Op -> ")); Serial.println(operation);
    valid = false;
  }

  if (valid) {
    Serial.print(F("Result: "));
    Serial.println(result);
  }
  
  // Crucial: Clear anything left before restarting the loop
  delay(100); 
  clearSerialBuffer();
}

void clearSerialBuffer() {
  delay(50); // Small delay to let all trailing bytes arrive
  while (Serial.available() > 0) {
    Serial.read();
  }
}
