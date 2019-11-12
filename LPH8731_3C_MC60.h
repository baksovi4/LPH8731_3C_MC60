/*
 LPH8731_3C_MC60.h

 Created by BAKS
 Date: November 2019.

 Based on: https://cxem.net/mc/mc218.php

 * These changes required hardware changes to pin configurations

 PERMISSION TO DISTRIBUTE

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.


 LIMITATION OF LIABILITY

 The software is provided "as is", without warranty of any kind, express or implied,
 including but not limited to the warranties of merchantability, fitness for a particular
 purpose and noninfringement. In no event shall the authors or copyright holders be liable
 for any claim, damages or other liability, whether in an action of contract,
 tort or otherwise, arising from, out of or in connection with the software
 or the use or other dealings in the software.

 */

#include "Arduino.h"

#ifndef LPH8731_3C_MC60_H
#define LPH8731_3C_MC60_H

#define _8_BIT_COLOR  1     //  0 - 12 bit color;   1 - 8 bit color;

//===============================================================
//                     
//===============================================================
#ifdef _8_BIT_COLOR
//8-bit (256 color)
#define GREEN       0x1C
#define DARK_GREEN  0x15
#define RED         0xE0
#define BLUE        0x1F
#define DARK_BLUE   0x03
#define YELLOW      0xFC
#define ORANGE      0xEC
#define VIOLET      0xE3
#define WHITE       0xFF
#define BLACK       0x00
#define GREY        0x6D
#else
//12-bit (4096 color)
#define WHITE       0xFFF
#define BLACK       0x000
#define RED         0xF00
#define GREEN       0x0F0
#define BLUE        0x00F
#define CYAN        0x0FF
#define MAGENTA     0xF0F
#define YELLOW      0xFF0
#define BROWN       0xB22
#define ORANGE      0xFA0
#define PINK        0xF9E
#endif

//*************************************************************
//ESP8266 NodeMCU v3 pin
#define LCD_CS      5    //  D1
#define LCD_RESET   4    //  D2
#define LCD_RS      14   //  D5
#define LCD_CLK     12   //  D6
#define LCD_DATA    10   //  SD3

//*************************************************************

class LPH8731_3C_MC60
{
private:

  void fillTriangleA 	(char x1, char y1, char x2, char y2, char x3, char y3, int color); 
  void stringNum  	(char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rotation);

public:

  void reset 		(void);
  void begin 		(void);
  void lcdSend 		(unsigned char RS, unsigned char data);
  void setArea 		(char x1, char x2, char y1, char y2);
  void fillScreen 	(unsigned int color);
  void white		(void);
  void black		(void);
  void setPixColor 	(char x, char y, unsigned int color);
  void setSymbol 	(unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height,  int rotation);
  void setSymbolShadow	(unsigned char symbol, char x, char y, int t_color, 		 char zoom_width, char zoom_height,  int rotation);
  void setChar 		(unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height,  int rotation);
  void setCharShadow 	(unsigned char symbol, char x, char y, int t_color, 		 char zoom_width, char zoom_height,  int rotation);
  void string  		(char *str, 	       int x,  int y,  int t_color, int b_color, char zoom_width, char zoom_height,  int rotation);
  void stringShadow 	(char *str, 	       int x,  int y,  int t_color,		 char zoom_width, char zoom_height,  int rotation);

  void drawLine 	(char x1, char y1, char x2, char y2, int color);
  void drawRect 	(char x1, char y1, char width, char height, char size, int color);
  void fillRect 	(char x1, char y1, char width, char height, 	       int color);
  void drawCircle 	(char xcenter, char ycenter, char rad, int color);
  void fillCircle 	(char xcenter, char ycenter, char rad, int color);
  void drawTriangle 	(char x1, char y1, char x2, char y2, char x3, char y3, int color);
  void fillTriangle 	(char x1, char y1, char x2, char y2, char x3, char y3, int color);

  // EXPERIMENTAL
  void sendImage 	(char x, char y, char width, char height, char *img, int rotation);
  void outputImage 	(char x, char y, char width, char height, char *img, int rotation);

};

#endif  // LPH8731_3C_MC60_H

