#include "esphome.h"
#include "PZEM017.h"

// Custom component for PZEM017
class PZEM017CustomComponent : public PollingComponent {
 public:
  PZEM017CustomComponent() : PollingComponent(1000) {}  // Update every second

  void setup() override {
    // Initialize PZEM017 sensor here
    pzem = new PZEM017(&my_serial);
  }

  void update() override {
    // Read data from PZEM017 sensor and update values
    float voltage = pzem->read_voltage();
    float current = pzem->read_current();
    float power = pzem->read_power();
    float energy = pzem->read_energy();

    voltage_sensor->publish_state(voltage);
    current_sensor->publish_state(current);
    power_sensor->publish_state(power);
    energy_sensor->publish_state(energy);
  }

  Sensor *voltage_sensor;
  Sensor *current_sensor;
  Sensor *power_sensor;
  Sensor *energy_sensor;

 private:
  PZEM017 *pzem;
  HardwareSerial my_serial = HardwareSerial(1); // Use UART1
};
