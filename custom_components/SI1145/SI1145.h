#include "esphome.h"
#include "Adafruit_SI1145.h"

using namespace esphome;

class SI1145_sensor : public PollingComponent, public Sensor {
  public:

    //Adafruit_SI1145 uv = Adafruit_SI1145();
    Adafruit_SI1145 uv;
    sensor::Sensor *visible_sensor = new sensor::Sensor();
    sensor::Sensor *ir_sensor = new sensor::Sensor();
    sensor::Sensor *uvindex_sensor = new sensor::Sensor();

    SI1145_sensor() : PollingComponent(2000) { }

    float visible;
    float irlight;
    float uvindex;

    void setup() override {
      //uv.reset();
      uv.begin(0x60);

    }
    void update() override {
      visible = uv.readVisible();
      visible_sensor->publish_state(visible);

      irlight = uv.readIR();
      ir_sensor->publish_state(irlight);
      uvindex = uv.readUV();
      uvindex_sensor->publish_state(uvindex / 100.0);
    }
};

