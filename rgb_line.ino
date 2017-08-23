int pin_Red = 9;
int pin_Green = 10;
int pin_Blue = 11;

struct rgbColor {
  unsigned int r;
  unsigned int g;
  unsigned int b;
};

rgbColor HUE_to_RGB(const int h, const int s, const int v) {
  int h_i = h / 60 % 6;
  int v_min = (100 - s) * v / 100;
  int a = (v - v_min) * (h % 60) / 60;
  int v_inc = v_min + a;
  int v_dec = v - a;

  rgbColor rgb;
  switch (h_i) {
    case 0: rgb.r = v; rgb.g = v_inc; rgb.b = v_min; break;
    case 1: rgb.r = v_dec; rgb.g = v; rgb.b = v_min; break;
    case 2: rgb.r = v_min; rgb.g = v; rgb.b = v_inc; break;
    case 3: rgb.r = v_min; rgb.g = v_dec; rgb.b = v; break;
    case 4: rgb.r = v_inc; rgb.g = v_min; rgb.b = v; break;
    case 5: rgb.r = v; rgb.g = v_min; rgb.b = v_dec; break;
  }
  rgb.r = rgb.r * 255 / 100;  
  rgb.g = rgb.g * 255 / 100; 
  rgb.b = rgb.b * 255 / 100;

  return rgb;

}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

}
