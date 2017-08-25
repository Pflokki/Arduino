/*
	
	9 - красный, 10 - зеленый, 11 - синий
	2 - кнопка

*/

int pin_Red = 9;
int pin_Green = 10;
int pin_Blue = 11;

int pin_Button = 2;

int current_mode = 0;

bool f_first_enter = true;
unsigned long time_old = 0;
int h, s;
int h_old, s_old;
bool f_return = false;

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
void mode_full_spectr() {
	int timeout = 100;

	if (f_first_enter) {
		time_old = millis();
		h = 0;
		h_old = -1;
		f_first_enter = false;
	}
	if (millis() - time_old  >= timeout) {
		h++;
		time_old = millis();
	}
	if (h > 360)
		h = 0;
	if (h != h_old) {
		set_RGB(HUE_to_RGB(h, 100, 100));
		h_old = h;
	}
}

// 0-140    красный, оранжевый, желтый, зеленый
// 180-280  голубой, синий, фиолетоый
// 280-360  фиолетовый, розовый, красный
void mode_range(int h_min, int h_max) {
  int timeout = 100;

  if (f_first_enter) {
	  time_old = millis();
	  h = h_min;
	  h_old = -1;
	  f_return = false;
	  f_first_enter = false;
  }

  if (!f_return) {
	  if (millis() - time_old  >= timeout) {
		  h++;
		  time_old = millis();
	  }
	  if (h >= h_max)
		  f_return = !f_return;
	  if (h != h_old) {
		  set_RGB(HUE_to_RGB(h, 100, 100));
		  h_old = h;
	  }
  }
  else {
	  if (millis() - time_old  >= timeout) {
		  h--;
		  time_old = millis();
	  }
	  if (h <= h_min)
		  f_return = !f_return;
	  if (h != h_old) {
		  set_RGB(HUE_to_RGB(h, 100, 100));
		  h_old = h;
	  }
  }
}

// просмотр всех цветов
void mode_full_color() {
	int timeout = 1000;
  
	if (f_first_enter) {
		time_old = millis();
		f_first_enter = false;
	}
	if (millis() - time_old  >= 12 * timeout)
		time_old = millis();
	else if (millis() - time_old  >= 8 * timeout)
		set_RGB(RED);
	else if (millis() - time_old  >= 7 * timeout)
		set_RGB(ORANGE);
	else if (millis() - time_old  >= 6 * timeout)
		set_RGB(YELLOW);
	else if (millis() - time_old  >= 5 * timeout)
		set_RGB(GREEN);
	else if (millis() - time_old  >= 4 * timeout)
		set_RGB(BLUE);
	else if (millis() - time_old  >= 3 * timeout)
		set_RGB(VIOLET);
	else if (millis() - time_old  >= 2 * timeout)
		set_RGB(PINK);
	else if (millis() - time_old  >= timeout)
		set_RGB(WHITE);
}

// закат

// 1 step: from h = 30 s = 90  to h = 30 s = 100
// 2 step: from h = 30 s = 100 to h = 15 s = 100
void sunset() {
  int y_timeout = 1000;
  int o_timeout = 2000;

  if (f_first_enter) {
	  time_old = millis();
	  h = 30;
	  h_old = 31;
	  s = 90;
	  s_old = -1;
	  f_first_enter = false;
  }
  if (s != 100) {
	  if (millis() - time_old  >= y_timeout) {
		  s++;
		  time_old = millis();
	  }
	  if (s != s_old) {
		  set_RGB(HUE_to_RGB(30, s, 100));
		  s_old = s;
	  }
  }
  else if (h != 5) {
	  if (millis() - time_old  >= o_timeout) {
		  h--;
		  time_old = millis();
	  }
	  if (h != h_old) {
		  set_RGB(HUE_to_RGB(h, 100, 100));
		  h_old = h;
	  }
  }
}

// рассвет
// 1 step: from h = 10 s = 100 to h = 30 s = 100
// 2 step: from h = 30 s = 100 to h = 30 s = 90
void sunrise() {
  int v = 100;
  int y_timeout = 1000;
  int o_timeout = 2000;
  int f_timeout = 20000;

  if (f_first_enter) {
	  time_old = millis();
	  h = 10;
	  h_old = 9;
	  s = 100;
	  s_old = 101;
	  f_first_enter = false;
  }

  if (h != 30) {
	  if (millis() - time_old  >= y_timeout) {
		  h++;
		  time_old = millis();
	  }
	  if (h != h_old) {
		  set_RGB(HUE_to_RGB(h, 100, 100));
		  h_old = h;
	  }
  }
  else if (s != 90) {
	  if (millis() - time_old  >= o_timeout) {
		  s--;
		  time_old = millis();
	  }
	  if (s != s_old) {
		  set_RGB(HUE_to_RGB(30, s, 100));
		  s_old = s;
	  }
  }
}


void setup() {
  pinMode(pin_Red, OUTPUT);
  pinMode(pin_Green, OUTPUT);
  pinMode(pin_Blue, OUTPUT);

  pinMode(pin_Button, INPUT_PULLUP);
  digitalWrite(pin_Button, HIGH);
}


void loop() {

	if (digitalRead(pin_Button) == LOW) {
    delay(300);
		current_mode++;
		f_first_enter = true;
	}
	if (current_mode > 14)
		current_mode = 0;

	switch (current_mode) {
		case 0: mode_full_spectr(); break;
		case 1: mode_range(0, 140); break;
		case 2: mode_range(180, 280); break;
		case 3: mode_range(280, 360); break;

		case 4: set_RGB(RED); break;
		case 5: set_RGB(ORANGE); break;
		case 6: set_RGB(YELLOW); break;
		case 7: set_RGB(GREEN); break;
		case 8: set_RGB(BLUE); break;
		case 9: set_RGB(VIOLET); break;
		case 10: set_RGB(PINK); break;
		case 11: set_RGB(WHITE); break;
		case 12: mode_full_color(); break;

		case 13: sunset(); break;
		case 14: sunrise(); break;
  }
}
