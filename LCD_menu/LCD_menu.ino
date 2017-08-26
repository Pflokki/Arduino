#include <DHT.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PLAY      0x40BF00FF
#define CH_LOW    0x40BF807F
#define CH_HIGH   0x40BF40BF
#define EQ        0x40BF20DF
#define VOL_LOW   0x40BFA05F
#define VOL_HIGH  0x40BF609F
#define PREV      0x40BF906F
#define NEXT      0x40BF50AF
#define CH0       0x40BF10EF
#define CH1       0x40BF30CF
#define CH2       0x40BFB04F
#define CH3       0x40BF708F
#define CH4       0x40BF08F7
#define CH5       0x40BF8877
#define CH6       0x40BF48B7
#define CH7       0x40BF28D7
//#define CH8       0x40BFA857
//#define CH9       0x40BF6897
//String pick     = "40BF18E7";
//String ch_set   = "40BF58A7";

LiquidCrystal_I2C lcd (0x3F,20,4);
IRrecv irrecv(6);
DHT dht(4, DHT22);

decode_results results;

/*
 * 0 - соновное меню
 * 1 - температура
 * 2 - время
 * 3 - освещение
 */
	int current_menu = 0;
	int current_index_of_item_menu = 0;
	int size_of_main_menu = 3;
	String menu[3] = {
		"Temp / Hum",
		"Time",
		"Led",
	};
	int current_index_of_temphum_menu = -1;
	int size_of_temphum_menu = 4;
	String temphum_menu[4] = {
		"in",
		"out",
		"temp: ",
		"hum:  ",
	};
  
  String timeM = "21:25";

	unsigned long current_millis = millis();
	unsigned long previous_millis = 0;

	bool light = true;

	float dht_temp = 0.0;
	float dht_hum = 0.0;

	unsigned int line_led = 2;
	unsigned int mode_led = 1;
	bool power_led = false;
  
/*
 * Вывод сообщения
 */
void writeMsg(String msg) {
	for (int i = 0; i < msg.length(); i++)
		lcd.print(msg[i]);
}

/*
 * Вывод указателя
 */
void writeImage() {
	writeMsg(">");
}

/*
 * Вывод заголовка основного меню
 */
void writeHeadOfMenu(int current_page, int count_of_page) {
	lcd.setCursor(10,0);
	writeMsg(timeM);
  
	lcd.setCursor(17,0);
	String msg = "";
	msg = msg + current_page + "/" + count_of_page;
	writeMsg(msg);
}

/*
 * Вывод основного меню
 */
void writeMenu(int page, int line) {
	page--;
	lcd.clear();
	writeHeadOfMenu(page + 1, (int) size_of_main_menu / 3 + 1);

	int count_of_menu_items = 3 + 1;
  
	if (size_of_main_menu - (page + 1) * 3 < 0)
		count_of_menu_items = size_of_main_menu - (page + 1) * 3 + 4;
    
	int idx = page * 3;
	for (int i = 1; i < count_of_menu_items; i++, idx++) {
		if (i == line) {
			lcd.setCursor(0, i);
			writeImage();
		}
		lcd.setCursor(1, i);
		writeMsg(menu[idx]);
	}
}

/*
 * Отображение основного меню
 */
void drawMenu() {
	int current_page = (int) current_index_of_item_menu / 3 + 1;
	int current_line = current_index_of_item_menu - (current_page - 1) * 3 + 1;

	writeMenu(current_page, current_line);
}

/*
 * Вывод меню температуры и влажности
 */
void drawTempHum() {
	lcd.setCursor(1,0);
	writeMsg("Temp / Hum");

	lcd.setCursor(15,0);
	writeMsg(timeM);

	lcd.setCursor(8, 1);
	writeMsg(temphum_menu[0]);

	lcd.setCursor(15, 1);
	writeMsg(temphum_menu[1]);

	lcd.setCursor(1, 2);
	writeMsg(temphum_menu[2]);

	String temp = "";
	String hum = "";

	temp = temp + dht_temp + "C";
	hum = hum + dht_hum + "%";
	lcd.setCursor(7, 2);
	writeMsg(temp);

	lcd.setCursor(14, 2);
	writeMsg(temp);
  
	lcd.setCursor(1, 3);
	writeMsg(temphum_menu[3]);

	lcd.setCursor(7, 3);
	writeMsg(hum);

	lcd.setCursor(14, 3);
	writeMsg(hum);
}

/*
 * Вывод меню времени
 */
void drawTime() {
	lcd.setCursor(1,0);
	writeMsg("Time");

	lcd.setCursor(15,0);
	writeMsg(timeM);

	lcd.setCursor(2, 2);
	writeMsg(timeM);
	lcd.setCursor(9, 2);
	writeMsg("31.05.1995");
}

/*
 * Вывод меню подсветки
 */
void drawLed() {
	lcd.setCursor(1,0);
	writeMsg("Led");

	lcd.setCursor(15,0);
	writeMsg(timeM);

	lcd.setCursor(1, 2);
	writeMsg("mode:");

	lcd.setCursor(12, 2);
	writeMsg("<");

	lcd.setCursor(15, 2);
	String mode = "";
	mode = mode + mode_led;
	writeMsg(mode);
  
	lcd.setCursor(18, 2);
	writeMsg(">");

	lcd.setCursor(1, 3);
	writeMsg("power:");

	lcd.setCursor(12, 3);
	writeMsg("<");

	String power = "off";
	if (power_led)
	power = "on";
	else
	power = "off";
	lcd.setCursor(14, 3);
	writeMsg(power);
  
	lcd.setCursor(18, 3);
	writeMsg(">");
}






/*
 * 0
 * Основное меню
 */
void menuMain(decode_results result) {

	if (results.value == CH_LOW) {
		current_index_of_item_menu--;
		drawMenu();
		previous_millis = -1;
	}

	if (results.value == CH_HIGH) {
		current_index_of_item_menu++;
		drawMenu();
	}

	if (results.value == VOL_HIGH) {
		switch (current_index_of_item_menu) {
		case 0: current_menu = 1; break;
		case 1: current_menu = 2; lcd.cursor(); break;
		case 2: current_menu = 3; break;
		default: break;
		};

		previous_millis = -1;
		return;
	}

	if (current_index_of_item_menu > size_of_main_menu - 1)
		current_index_of_item_menu = 0;
	if (current_index_of_item_menu < 0)
		current_index_of_item_menu = size_of_main_menu - 1;

	lcd.clear();
	drawMenu();
}

/*
 * 1
 * Меню температуры и влажности
 */
void menuTempHum(decode_results results) {
  
	if (results.value == VOL_LOW) {
		current_menu = 0;
		previous_millis = -1;
		return;
	}
  
	if (previous_millis == -1 || current_millis - previous_millis > 2000) {
		previous_millis = current_millis;
		dht_temp = dht.readTemperature();
		dht_hum = dht.readHumidity();
		lcd.clear(); 
		drawTempHum();
	}
}

/*
 * 2
 * Меню времени
 */
unsigned int pos_time = 2;
void menuTime(decode_results results) {
	  
	if (results.value == VOL_LOW) {
		current_menu = 0;
		pos_time = 0;
		previous_millis = -1;
		lcd.noCursor();
		return;
	}

	if (results.value == PREV) {
		pos_time--;
	}

	if (results.value == NEXT) {
		pos_time++;
	}
    
	if (pos_time > 18)
		pos_time = 2;
	if (pos_time < 2)
		pos_time = 18;

	lcd.setCursor(pos_time, 2);
      
	lcd.clear(); 
	drawTime();
	
}

/*
 * 3
 * Меню освещения
 */
void menuLed(decode_results results) {

	if (results.value == CH_HIGH) {
		line_led++;
		lcd.clear(); 
		drawLed();
		lcd.setCursor(0, line_led);
		writeImage();
	}

	if (results.value == CH_LOW) {
		line_led--;
		lcd.clear(); 
		drawLed();
		lcd.setCursor(0, line_led);
		writeImage();
	}
    
	if (results.value == VOL_LOW) {
		current_menu = 0;
		line_led = 2;
		previous_millis = -1;
		return;
	}

	if (results.value == PREV) {
		if (line_led == 2)
			mode_led--;
		if (line_led == 3)
			power_led = !power_led;
		lcd.clear(); 
		drawLed();
		lcd.setCursor(0, line_led);
		writeImage();
	}

	if (results.value == NEXT) {
		if (line_led == 2)
			mode_led++;
		if (line_led == 3)
			power_led = !power_led;
		lcd.clear(); 
		drawLed();
		lcd.setCursor(0, line_led);
		writeImage();
	}
    
	if (line_led > 3)
		line_led = 2;
	if (line_led < 2)
		line_led = 3;

	lcd.clear(); 
	drawLed();
	lcd.setCursor(0, line_led);
	writeImage();
}

void setup() {
	lcd.begin();
	lcd.backlight();

	dht.begin();
	writeMenu(1, 1);
	irrecv.enableIRIn();

}
void loop() {
	current_millis = millis();
	if (irrecv.decode(&results)) { // если данные пришли
		
		if (results.value == EQ) {
			if (light) {
				light = false;
				lcd.noBacklight();
			}
			else {
				light = true;
				lcd.backlight();
			}
		} 
		if (results.value == PLAY) {
			current_index_of_item_menu = 0;
			current_menu = 0;
			line_led = 2;
			previous_millis = -1;
		}
		if (results.value == CH0) {
			power_led = !power_led;
		}

		if (results.value == CH1) {
			mode_led = 0;
			power_led = true;
		}
		
		if (results.value == CH2) {
			mode_led = 1;
			power_led = true;
		}
		
		if (results.value == CH3) {
			mode_led = 2;
			power_led = true;
		}
		
		if (results.value == CH4) {
			mode_led = 3;
			power_led = true;
		}
		
		if (results.value == CH5) {
			mode_led = 12;
			power_led = true;
		}
		
		if (results.value == CH6) {
			mode_led = 13;
			power_led = true;
		}

		if (results.value == CH7) {
			mode_led = 14;
			power_led = true;
		}

		switch (current_menu) {
			case 0: menuMain(results); break;
			case 1: menuTempHum(results); break;
			case 2: menuTime(results); break;
			case 3: menuLed(results); break;
			default: break;
		}

		irrecv.resume(); // принимаем следующую команду
	}
}



