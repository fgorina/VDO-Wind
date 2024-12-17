#include <Arduino.h>

#define V_SIN 32
#define V_COS 33

#define PWM_CHAN_SIN 0
#define PWM_CHAN_COS 1

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  ledcSetup(PWM_CHAN_SIN, 10000, 10);
  ledcAttachPin(V_SIN, PWM_CHAN_SIN);
  ledcSetup(PWM_CHAN_COS, 10000, 10);
  ledcAttachPin(V_COS, PWM_CHAN_COS);
}

// Wrires value to PWM. angle in rads.
void writeAngle(float angle)
{
  float s = sin(angle + PI) + 1.0; // Get a 0-2 value
  float c = cos(angle + PI) + 1.0; // Get a 0-2 value

  unsigned int is = floor(s * 510.0+4); // 0-1024
  unsigned int ic = floor(c * 510.0+2); // 0 - 1024

  Serial.print((angle + PI) / PI * 180.0); Serial.print("   ");Serial.println(is);
  ledcWrite(PWM_CHAN_SIN, is);
  ledcWrite(PWM_CHAN_COS, ic);
}


void loop()
{
  float angle = -PI;

  while (true)
  {
    if ((millis() % 200) == 0)
    {
      writeAngle(angle);
      angle += PI / 180.0;

      if (angle >= PI)
      {
        angle = -PI;
      }
    }
  }
}
