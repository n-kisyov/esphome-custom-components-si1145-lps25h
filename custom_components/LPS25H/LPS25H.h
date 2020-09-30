#include "esphome.h"
#include "LPS.h"

using namespace esphome;

class LPS25H_sensor : public PollingComponent, public Sensor {
  public:

    LPS lps25h;
    sensor::Sensor *pressure_sensor = new sensor::Sensor();
    sensor::Sensor *temperature_sensor = new sensor::Sensor();
    sensor::Sensor *altitude_sensor = new sensor::Sensor();

    LPS25H_sensor() : PollingComponent(2000) { }
	
	float pressure;
	float temperature;
	float altitude;

    void setup() override {
      lps25h.init();
      lps25h.enableDefault();
	}
    
    void update() override {
	pressure = lps25h.readPressureMillibars();
	pressure_sensor->publish_state(pressure);
	temperature = lps25h.readTemperatureC();
	temperature_sensor->publish_state(temperature);
	altitude = lps25h.pressureToAltitudeMeters(pressure);
	altitude_sensor->publish_state(altitude);

	}
};
