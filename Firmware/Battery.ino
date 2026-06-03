void battry_filtering() {
  float adcValueSum = 0;

  // ADC Averaging
  for (int i = 0; i < numSamples; i++) {
    adcValueSum += analogRead(batteryPin);
    delay(2);
  }

  float adcValueAvg = adcValueSum / numSamples;
  batteryVoltage = adcValueAvg * (vRef / adcMax) * calibrationFactor;
  batteryVoltage = batteryVoltage * ((R1 + R2) / R2);

  // Publishing the calculated battery voltage to Adafruit IO
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  //photocell.publish(batteryVoltage);