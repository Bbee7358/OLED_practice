/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
**************************************************************************/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <timer.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C for 128x64, 0x3D for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}


int flash_OLED = 0;  //ディスプレイの中で白黒点滅させたいときにつかう
int OLED_select = 0;  //スイッチとか押されたときにどこを選択しているかを示す変数
int A = 0;  //ステートのための変数
int Ball_on = 0;  //ボールの有無を示す変数
double Ball_Dir = 0;   //ボールの方向を示す変数
double Ball_far = 0;   //ボールの距離を示す変数
double Ball_Value = 0; //ボールの最大値を示す変数
double Lvec_Dir = 0;   //ラインの角度を示す変数
double Lvec_long = 0;  //ラインの長さを示す変数
double Lwhite = 0;     //白線の平均値
double Lgreen = 0;     //緑コートの平均値
int L_side;  //コート上のラインの位置の判定に使う変数(0:左,1:右,999:どこかわからん)
int LINE_on; //ラインがロボットの下になかったら0,あったら1にする

timer timer_OLED; //タイマーの宣言(OLED用)

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50000); //タイムアウト時間の設定

  pinMode(LED_BUILTIN, OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //OLEDの初期化
  display.display();
  display.clearDisplay();

  timer_OLED.reset(); //タイマーのリセット(OLED用)
}

void loop() {
  if(timer_OLED.read_ms() > 500) //0.5秒ごとに実行(OLEDにかかれてある文字を点滅させるときにこの周期で点滅させる)
  {
    if(flash_OLED == 0){
      flash_OLED = 1;
    }
    else{
      flash_OLED = 0;
    }
    timer_OLED.reset(); //タイマーのリセット(OLED用)
  }


  if(A == 0)  //メインメニュー
  {
    //OLEDの初期化
    display.display();
    display.clearDisplay();

    //選択画面だということをしらせる言葉を表示
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Hi! bro!");
    display.setCursor(0,10);
    display.println("What's up?");

    //文字と選択画面の境目の横線を表示
    display.drawLine(0, 21, 128, 21, WHITE);

    //選択画面の表示
    if(OLED_select == 0)  //Check Ballを選択しているとき
    {
      //Check Ballの文字設定
      display.setTextSize(2);
      if(flash_OLED == 0){  //白黒反転　何秒かの周期で白黒が変化するようにタイマーを使っている（flash_OLEDについて調べたらわかる）
        display.setTextColor(BLACK, WHITE);
      }
      else{
        display.setTextColor(WHITE);
      }
      display.setCursor(0,34);
      display.println("Check");
      display.println("Ball");

      //選択画面で矢印マークを中央に表示
      display.fillTriangle(72, 43, 64, 35, 64, 51, WHITE);  //▶の描画

      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(80,38);
      display.println("Check");
      display.println("Line");
    }
    else if(OLED_select == 1)  //Check Lineを選択しているとき
    {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,38);
      display.println("Check");
      display.println("Ball");

      //選択画面で矢印マークを中央に表示
      display.fillTriangle(56, 43, 64, 35, 64, 51, WHITE);  //◀の描画

      display.setTextSize(2);
      if(flash_OLED == 0){  //白黒反転　何秒かの周期で白黒が変化するようにタイマーを使っている（flash_OLEDについて調べたらわかる）
        display.setTextColor(BLACK, WHITE);
      }
      else{
        display.setTextColor(WHITE);
      }
      display.setCursor(70,34);
      display.println("Check");
      display.println("Line");
    }
  }
  else if(A == 10)  //Check Ball
  {
    if(Ball_Value > 600)  //ボールを見つけていたら目印を付けて置く、そしてその変数を使ってボールがあれば値を表示し、ボールがなければ白い四角形を変わりに出す(ここの値は適当につけたから、しおからが勝手に変更して）
    {
      Ball_on = 1;  //ボールがある
    }
    else
    {
      Ball_on = 0;  //ボールがない
    }

    display.display();
    display.clearDisplay();

    //ボールの位置状況マップを表示する
    display.drawCircle(32, 32, 30, WHITE);  //○ 30
    display.drawCircle(32, 32, 20, WHITE);  //○ 20
    display.drawCircle(32, 32, 10, WHITE);  //○ 10
    display.drawLine(0, 32, 64, 32, WHITE); //|
    display.drawLine(32, 0, 32, 64, WHITE); //-

    //"Ball"と表示する
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(64,0);
    display.println("Ball");

    //ここから下のコードのテキストをsize1にする
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //ボールの角度を表示する
    display.setCursor(64,24);
    display.println("Dir   :");
    if(Ball_on == 1){  //ボールがあれば値を表示
      display.setCursor(96,24);
      display.println(Ball_Dir);
    }
    else{  //ボールがなければ白い四角形を表示
      display.fillRect(96, 24, 34, 10, WHITE);
    }

    //ボールの距離を表示する
    display.setCursor(64,38);
    display.println("far   :");
    if(Ball_on == 1){  //ボールがあれば値を表示
      display.setCursor(96,38);
      display.println(Ball_far);
    }
    else{  //ボールがなければ白い四角形を表示
      display.fillRect(96, 38, 34, 10, WHITE);
    }

    //ボールの最大値を表示する
    display.setCursor(64,52);
    display.println("Value :");
    display.setCursor(96,52);
    display.println(Ball_Value);
  }
  else if(A == 20)  //Check Line
  {
    display.display();
    display.clearDisplay();

    //ラインの位置状況マップを表示する
    display.drawCircle(32, 32, 30, WHITE);  //○ 30

    //"Line"と表示する
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(64,0);
    display.println("Line");

    //ここから下のコードのテキストをsize1にする
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //ラインの角度を表示する
    display.setCursor(64,20);
    display.println("Dir   :");
    if(LINE_on == 1){  //ラインがロボットの下にある
      display.setCursor(96,20);
      display.println(Lvec_Dir);
    }
    else{  //ラインがロボットの下にない
      display.fillRect(96, 20, 34, 10, WHITE);

    }

    //ラインの距離を表示する
    display.setCursor(64,30);
    display.println("far   :");
    if(LINE_on == 1){  //ラインがロボットの下にある
      display.setCursor(96,30);
      display.println(Lvec_long);
    }
    else{  //ラインがロボットの下にない
      display.fillRect(96, 30, 34, 10, WHITE);
    }

    //白線の平均値を表示する
    display.setCursor(64,40);
    display.println("white :");
    display.setCursor(96,40);
    display.println(Lwhite);

    //緑コートの平均値を表示する
    display.setCursor(64,50);
    display.println("green :");
    display.setCursor(96,50);
    display.println(Lgreen);
    
    //コート上の左右どちら側にいるのかを表示する
    display.setCursor(64,60);
    display.println("Side  :");
    display.setCursor(96,60);
    if(L_side == 0){  //左側にいる
      display.println("Left");
    }
    else if(L_side == 1){  //右側にいる
      display.println("Right");
    }
    else{  //どちらでもない
      display.println("None");
    }
  }

  //シリアルモニタで値を入力していろいろ変更できるようにしとく
  Serial.println("What do you want to put in?");

  // 返答を受信(タイムアウトまで待つ)
  String str = Serial.readString();

  if(str == "A")  //ステート変更したいと希望があったら
  {
    Serial.println("A...ok SO,put number");

    // 返答を受信(タイムアウトまで待つ)
    String str_num = Serial.readString();

    A = str_num.toInt();
  }
  else if(str == "OLED_select")  //選択画面でラインチェックかボールチェックかを変更したかったら
  {
    Serial.println("OLED_select...ok SO,put number");

    // 返答を受信(タイムアウトまで待つ)
    String str_num = Serial.readString();

    OLED_select = str_num.toInt();
  }
  else if(str == "Ball_on")  //ボールの有無を変更したいと希望があったら
  {
    Serial.println("Ball_on...ok SO,put number");

    // 返答を受信(タイムアウトまで待つ)
    String str_num = Serial.readString();

    Ball_on = str_num.toInt();
  }
  else if(str == "LINE_on")  //ライン上にロボットがあるかどうか変更したいと希望があったら
  {
    Serial.println("LINE_on...ok SO,put number");

    // 返答を受信(タイムアウトまで待つ)
    String str_num = Serial.readString();

    LINE_on = str_num.toInt();
  }
  else if(str == "L_side")  //ロボットの位置を変更したいと希望があったら
  {
    Serial.println ("L_side...ok SO,put number");

    // 返答を受信(タイムアウトまで待つ)
    String str_num = Serial.readString();

    L_side = str_num.toInt();
  }
  else
  {
    //それ以外の文字列が入力されたら
    Serial.println("Error");
  }
}