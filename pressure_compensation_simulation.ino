#include <math.h>

int16_t altitude_meters = 0;
const int16_t lowest_altitude_meters = -413;
const int16_t highest_altitude_meters = 2500;
const uint16_t altitude_step_meters = 1;

float temperature_degc = 0;
const float lowest_temperature_degc = -20.0f;
const float highest_temperature_degc = 40.0f;
const float temperature_step_degc = 0.5f;

const float kelvin_offset_degC = 273.15f;
const float lapse_rate_K_per_m = -0.0065f;
const float pressure_exponentiation_constant = 5.2558774324f;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World");
  Serial.print("N/A,");
  for(temperature_degc = lowest_temperature_degc; temperature_degc <= highest_temperature_degc; temperature_degc += temperature_step_degc){
    Serial.print(temperature_degc, 1);
    Serial.print(",");  
  }  
  Serial.println();
  for(altitude_meters = lowest_altitude_meters; altitude_meters <= highest_altitude_meters; altitude_meters += altitude_step_meters){
    Serial.print(altitude_meters);
    Serial.print(",");
    for(temperature_degc = lowest_temperature_degc; temperature_degc <= highest_temperature_degc; temperature_degc += temperature_step_degc){
      float temperature_degk = 273.15f + temperature_degc;
      float temperature_degk_at_sea_level = temperature_degk - lapse_rate_K_per_m * altitude_meters; // temperature is always higher at sea level
                                                                                                     // because lapse rate is negative
      float pow_arg = 1.0f + ((lapse_rate_K_per_m * altitude_meters) / temperature_degk_at_sea_level);
      float partial_pressure = powf(pow_arg, pressure_exponentiation_constant);

      Serial.print(partial_pressure, 4);
      Serial.print(",");      
    }
    Serial.println();
  }
}

void loop() {
  
}
