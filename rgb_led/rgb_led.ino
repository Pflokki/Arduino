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

// весь спектр
void mode_1() {
  int timeout = 100;
  for (int i = 0; i < 360; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
}

// красный, оранжевый, желтый, зеленый
void mode_2() {
  int timeout = 100;
  for (int i = 0; i < 140; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
  for (int i = 140; i > 0; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
}

// голубой, синий, фиолетоый
void mode_3() {
  int timeout = 100;
  for (int i = 180; i < 280; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
  for (int i = 280; i > 180; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
}

// фиолетовый, розовый, красный
void mode_4() {
  int timeout = 100;
  for (int i = 280; i < 360; i++) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
  for (int i = 360; i > 280; i--) {
    set_RGB(HUE_to_RGB(i, 100, 100));
    delay(timeout);
  }
}

// просмотр всех цветов
void mode_5() {
  int timeout = 1000;
  set_RGB(RED);
  delay(timeout);
  set_RGB(ORANGE);
  delay(timeout);
  set_RGB(YELLOW);
  delay(timeout);
  set_RGB(GREEN);
  delay(timeout);
  set_RGB(BLUE);
  delay(timeout);
  set_RGB(VIOLET);
  delay(timeout);
  set_RGB(PINK);
  delay(timeout);
  set_RGB(WHITE);
  delay(timeout * 4);
}

// закат
void sunset() {
  int v = 100;
  int y_timeout = 1000;
  int o_timeout = 2000;
  int f_timeout = 20000;
  // 1 step: from h = 30 s = 90  v = 100 to h = 30 s = 100 v = 100 with delay = 300
  for (int s = 90; s <= 100; s++) {
    set_RGB(HUE_to_RGB(30, s, v));
    delay(y_timeout);
  }
  // 2 step: from h = 30 s = 100 v = 100 to h = 15 s = 100 v = 100 with delay = 500
  for (int h = 30; h >= 5; h--) {
      set_RGB(HUE_to_RGB(h, 100, v));
      delay(o_timeout);
  }
  delay(f_timeout);
}

// рассвет
void sunrise() {
  int v = 100;
  int y_timeout = 1000;
  int o_timeout = 2000;
  int f_timeout = 20000;
  // 1 step: from h = 15 s = 100 v = 100 to h = 30 s = 100 v = 100 with delay = 300
  for (int h = 10; h <= 30; h++) {
    set_RGB(HUE_to_RGB(h, 100, v));
    delay(y_timeout);
  }
  // 2 step: from h = 30 s = 100 v = 100 to h = 30 s = 90 v = 100 with delay = 500
  for (int s = 100; s >= 90; s--) {
      set_RGB(HUE_to_RGB(30, s, v));
      delay(o_timeout);
  }
  delay(f_timeout);
}

void setup() {
  pinMode(pin_Red, OUTPUT);
  pinMode(pin_Green, OUTPUT);
  pinMode(pin_Blue, OUTPUT);

  mode_5();
}

void loop() {
//  sunset();
//  sunrise();
//  set_RGB(ORANGE);
    mode_1();
}
