int pin_Red = 9;
int pin_Green = 10;
int pin_Blue = 11;

struct rgbColor {
  unsigned int r;
  unsigned int g;
  unsigned int b;
};

enum color {
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  VIOLET,
  PINK,
  WHITE
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

void set_RGB (color col) {
  rgbColor rgb;
  int s = 100;
  int v = 100;
  switch (col) {
    case RED: rgb = HUE_to_RGB(360, s, v); break;
    case ORANGE: rgb = HUE_to_RGB(25, s, v); break;
    case YELLOW: rgb = HUE_to_RGB(57, s, v); break;
    case GREEN: rgb = HUE_to_RGB(120, s, v); break;
    case BLUE: rgb = HUE_to_RGB(240, s, v); break;
    case VIOLET: rgb = HUE_to_RGB(275, s, v);break;
    case PINK: rgb = HUE_to_RGB(310, s, v); break;
    case WHITE: rgb = HUE_to_RGB(150, 0, 100); break;
  }

  set_RGB(rgb);
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
  pinMode(pin_Red, OUTPUT);
  pinMode(pin_Green, OUTPUT);
  pinMode(pin_Blue, OUTPUT);
}

void loop() {
  mode_2();
  //set_RGB(ORANGE);
}
