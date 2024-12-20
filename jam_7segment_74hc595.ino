#include <DS3231.h>

DS3231  rtc(SDA, SCL);
Time  t;

int jam;
int menit;
int detik;

int jam_satuan, jam_puluhan, menit_satuan, menit_puluhan, detik_satuan, detik_puluhan;

int angka[] = {
      B00000011, //angka 0
      B10011111, //angka 1
      B00100101, //angka 2
      B00001101, //angka 3
      B10011001, //angka 4
      B01001001, //angka 5
      B01000001, //angka 6
      B00011111, //angka 7
      B00000001, //angka 8
      B00001001 //angka 9
    };

// Globals
const int dataPin = 4;  // blue wire to 74HC595 pin 14
const int latchPin = 7; // green to 74HC595 pin 12
const int clockPin = 8; // yellow to 74HC595 pin 11

void setup() {
  
  Serial.begin(9600); //set komunikasi baut serial monitor pada 115200
  rtc.begin();
  
  // initialize the digital pins as outputs.
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(9,OUTPUT);
  
  //uncomment baris dibawah ini bila ingin mengatur jam
  rtc.setTime(21,54,35);
 
}

void loop()
{
  t = rtc.getTime();
  
  jam = t.hour;
  menit = t.min;
  detik = t.sec;

 
jam_satuan = jam % 10;
jam_puluhan = jam / 10;
menit_satuan = menit % 10;
menit_puluhan = menit / 10;
detik_satuan = detik % 10;
detik_puluhan = detik / 10;

delay(1000);
  
digitalWrite(latchPin, LOW);
shiftData(detik_satuan);
shiftData(detik_puluhan);
shiftData(menit_satuan);
shiftData(menit_puluhan);
shiftData(jam_satuan);
shiftData(jam_puluhan);
digitalWrite(latchPin, HIGH);

if (detik == 1 || detik == 3 || detik == 5 || detik == 7 || detik == 9 || detik == 11 || detik == 13 || detik == 15 || detik == 17 || detik == 19 || detik == 21 ||
detik == 23 || detik == 25 || detik == 27 || detik == 29 || detik == 31 || detik == 33 || detik == 35 || detik == 37 || detik == 39
|| detik == 41 || detik == 43 || detik == 45 || detik == 47 || detik == 49 ||
detik == 51 || detik == 53 || detik == 55 || detik == 57 || detik == 59 ) {
    digitalWrite(9, LOW);
  }
else
  {
    digitalWrite(9, HIGH);
  }
}

// Menampilakn angka pada 7-segment
void shiftData(int nilai) {
switch (nilai) {
case 0: shiftOut(dataPin, clockPin, LSBFIRST, angka[0]); break;
case 1: shiftOut(dataPin, clockPin, LSBFIRST, angka[1]); break;
case 2: shiftOut(dataPin, clockPin, LSBFIRST, angka[2]); break;
case 3: shiftOut(dataPin, clockPin, LSBFIRST, angka[3]); break;
case 4: shiftOut(dataPin, clockPin, LSBFIRST, angka[4]); break;
case 5: shiftOut(dataPin, clockPin, LSBFIRST, angka[5]); break;
case 6: shiftOut(dataPin, clockPin, LSBFIRST, angka[6]); break;
case 7: shiftOut(dataPin, clockPin, LSBFIRST, angka[7]); break;
case 8: shiftOut(dataPin, clockPin, LSBFIRST, angka[8]); break;
case 9: shiftOut(dataPin, clockPin, LSBFIRST, angka[9]); break;
}
}
