int pin_Red = 9;
int pin_Green = 10;
int pin_Blue = 11;

int incomingByte = -1;

struct rgbColor {
  unsigned int r;
  unsigned int g;
  unsigned int b;
};

rgbColor HUE_to_RGB(int h, int s, int v) {
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

void set_RGB (rgbColor rgb) {
  analogWrite(pin_Red, rgb.r);
  analogWrite(pin_Green, rgb.g);
  analogWrite(pin_Blue, rgb.b);
}
void mode_1() {
  for (int i = 0; i < 360; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
}

void mode_2() {
  for (int i = 0; i < 120; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
  for (int i = 120; i > 0; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
}

void mode_3() {
  for (int i = 120; i < 240; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
  for (int i = 240; i > 120; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
}

void mode_4() {
  for (int i = 240; i < 360; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
  for (int i = 360; i > 240; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(30);
  }
}

void mode_5() {

}

void setup() {
  Serial.begin(9600);

  pinMode(pin_Red, OUTPUT);
  pinMode(pin_Green, OUTPUT);
  pinMode(pin_Blue, OUTPUT);

  //set_RGB(HUE_to_RGB(360, 100, 100));
}

void loop() {
  mode_1();
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("incomingByte: ");
    Serial.println(incomingByte);
  }
  incomingByte = -1;
  switch (incomingByte) {
    case 1: mode_1(); break;
    case 2: mode_2(); break;
    case 3: mode_3(); break;
    case 4: mode_4(); break;
    case 5: mode_5(); break;
  }
}
