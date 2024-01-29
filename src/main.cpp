#include <Arduino.h>
#include "cards.h"
#include "TFT_eSPI.h"
#include "my_font_md.h"

#define MY_FONT my_font

#define UP_BTN 14
#define DOWN_BTN 0

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int curr_hand = 0;

const int diff_hands = 10;

const int rank_hands[diff_hands][5] = {
    {12, 11, 10, 9, 8},   // 1 皇家同花顺
    {21, 20, 19, 18, 17}, // 2 同花顺
    {7, 20, 33, 46, 2},   // 3 四条
    {12, 25, 38, 5, 18},  // 4 葫芦
    {10, 8, 7, 3, 2},     // 5 同花
    {24, 10, 35, 47, 33}, // 6 顺子
    {3, 16, 29, 1, 50},   // 7 三条
    {11, 24, 15, 28, 0},  // 8 两对
    {9, 22, 1, 15, 29},   // 9 一队
    {12, 15, 17, 2, 33}   // 10 高牌
};

void _draw()
{
  sprite.fillSprite(TFT_BLACK); // Clear screen

  for (int i = 0; i < 5; i++)
  {
    sprite.pushImage(62 * i, 10, 60, 84, card[rank_hands[curr_hand][i]]);

    if (curr_hand == 0 || curr_hand == 1 || curr_hand == 4 || curr_hand == 5)
      sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
    else if (curr_hand == 2 && i < 4)
      sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
    else if ((curr_hand == 3))
    {
      if (i < 3)
        sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
      else
        sprite.fillRect(62 * i, 98, 60, 5, TFT_YELLOW);
    }
    else if (curr_hand == 6 && i < 3)
      sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
    else if ((curr_hand == 7))
    {
      if (i < 2)
        sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
      else if (i < 4)
        sprite.fillRect(62 * i, 98, 60, 5, TFT_YELLOW);
    }
    else if (curr_hand == 8 && i < 2)
      sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
    else if (curr_hand == 9 && i < 1)
      sprite.fillRect(62 * i, 98, 60, 5, TFT_GREEN);
  }

  // 文字画提示
  String text = "当前牌型: ";
  if (curr_hand == 0)
    text += "1 皇家同花顺";
  else if (curr_hand == 1)
    text += "2 同花顺";
  else if (curr_hand == 2)
    text += "3 四条";
  else if (curr_hand == 3)
    text += "4 葫芦";
  else if (curr_hand == 4)
    text += "5 同花";
  else if (curr_hand == 5)
    text += "6 顺子";
  else if (curr_hand == 6)
    text += "7 三条";
  else if (curr_hand == 7)
    text += "8 两对";
  else if (curr_hand == 8)
    text += "9 一对";
  else if (curr_hand == 9)
    text += "10 高牌";

  sprite.loadFont(MY_FONT);
  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.setTextSize(2);
  sprite.drawString(text, 0, 115);

  sprite.pushSprite(0, 0);

  sprite.unloadFont();
}


void setup()
{
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);

  tft.init();
  tft.setRotation(3);

  sprite.createSprite(320, 170);
  sprite.setSwapBytes(1);

  tft.fillScreen(TFT_BLACK);
  _draw();
}

void loop()
{
  if (digitalRead(UP_BTN) == 0)
  {
    curr_hand++;
    if (curr_hand >= 10)
      curr_hand = 0;

    _draw();

    delay(200);
  }

  if (digitalRead(DOWN_BTN) == 0)
  {
    curr_hand--;
    if (curr_hand < 0)
      curr_hand = diff_hands - 1;

    _draw();

    delay(200);
  }
}