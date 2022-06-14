/// <summary>
/// show logo
/// </summary>
void showLogo() {

  (flipScreen) ? tft.setRotation(2) : tft.setRotation(0);
  tft.setScroll(0);
  memcpy(frontBuffer, logoTFT, 153600);
  drawTextCenterX(im, VERSION, 220, 240, RGB565_White, Arial_10_Bold);
  drawTextCenterX(im, "Screen 1", 240, 240, RGB565_White, Arial_10);
  drawTextCenterX(im, "(c) DIYLAB", 260, 240, RGB565_White, Arial_10);
  tft.update(frontBuffer, true);
  //tft1.update(frontBuffer, true);
  delay(30);
  
  // added by Mark Donners
  // now show logo on tft2
  (flipScreen) ? tft1.setRotation(2) : tft1.setRotation(0);
  tft1.setScroll(0);
  memcpy(frontBuffer1, TEELOGO, 153600);
  drawTextCenterX(im1, "Screen 2", 290, 240, RGB565_Yellow, Arial_10);
  drawTextCenterX(im1, "(c) The Electronic Engineer", 310, 240, RGB565_Orange, Arial_10);
  tft1.update(frontBuffer1, true);
  Serial.print("display show complete wait 6 seconds");

  delay(6000);

}

/// <summary>
/// center text horizontaly
/// </summary>
/// <param name="img"></param>
/// <param name="text"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="color"></param>
/// <param name="font"></param>
void drawTextCenterX(Image<RGB565> img, const char* text, int y, int w, RGB565 color, const ILI9341_t3_font_t& font) {
  auto b = im.measureText(text, { 0, 0 }, font, false);
  img.drawText(text, iVec2((w / 2) - b.lx() / 2, y), color, font, false);
}

/// <summary>
/// draw a long integer
/// </summary>
/// <param name="img"></param>
/// <param name="long_num"></param>
/// <param name="poX"></param>
/// <param name="poY"></param>
/// <param name="color"></param>
/// <param name="fnt"></param>
void drawNumber(Image<RGB565> img, long long_num, int poX, int poY, RGB565 color, const ILI9341_t3_font_t& font) {
  char str[14];
  ltoa(long_num, str, 10);
  img.drawText(str, iVec2(poX, poY), color, font, false);
}

/// <summary>
/// draw a float
/// </summary>
/// <param name="img"></param>
/// <param name="floatNumber"></param>
/// <param name="dp"></param>
/// <param name="poX"></param>
/// <param name="poY"></param>
/// <param name="color"></param>
/// <param name="fnt"></param>
void drawFloat(Image<RGB565> img, float floatNumber, int dp, int poX, int poY, RGB565 color, const ILI9341_t3_font_t& font) {
  char str[14];                   // array to contain decimal string
  uint8_t ptr = 0;                // initialise pointer for array
  int8_t digits = 1;              // count the digits to avoid array overflow
  float rounding = 0.5;           // round up down delta

  if (dp > 7) dp = 7;             // limit the size of decimal portion

  // adjust the rounding value
  for (uint8_t i = 0; i < dp; ++i)
    rounding /= 10.0f;

  // add sign, avoid adding - sign to 0.0!
  if (floatNumber < -rounding) {
    str[ptr++] = '-';           // negative number
    str[ptr] = 0;               // put a null in the array as a precaution
    digits = 0;                 // set digits to 0 to compensate so pointer value can be used later
    floatNumber = -floatNumber; // make positive
  }

  floatNumber += rounding;        // round up or down

  // for error put ... in string and return (all TFT_ILI9341_ESP library fonts contain . character)
  if (floatNumber >= 2147483647) {
    strcpy(str, "...");
  }

  // no chance of overflow from here on
  // get integer part
  unsigned long temp = (unsigned long)floatNumber;

  // put integer part into array
  ltoa(temp, str + ptr, 10);

  // find out where the null is to get the digit count loaded
  while ((uint8_t)str[ptr] != 0)
    ptr++;                     // move the pointer along
  digits += ptr;                 // count the digits

  str[ptr++] = '.';              // add decimal point
  str[ptr] = '0';                // add a dummy zero
  str[ptr + 1] = 0;              // add a null but don't increment pointer so it can be overwritten

  // get the decimal portion
  floatNumber = floatNumber - temp;

  // get decimal digits one by one and put in array
  // limit digit count so we don't get a false sense of resolution
  uint8_t i = 0;
  // while (i < dp) for no limit but array size must be increased
  while ((i < dp) && (digits < 9)) {
    i++;
    floatNumber *= 10;         // for the next decimal
    temp = floatNumber;        // get the decimal
    ltoa(temp, str + ptr, 10);
    ptr++;
    digits++;                  // increment pointer and digits count
    floatNumber -= temp;       // Remove that digit
  }

  // finally we can plot the string and return pixel length
  img.drawText(str, iVec2(poX, poY), color, font, false);
}

/// <summary>
/// copy rectangle in memory
/// </summary>
/// <param name="dest"></param>
/// <param name="src"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
static inline __attribute__((always_inline)) void copyRect(uint16_t* dest, uint16_t* src, int16_t x, int16_t y, int16_t w, int16_t h) {
  for (uint16_t i = y; i < y + h; i++)
    memcpy(dest + (x + i * 240), src + (x + i * 240), w * 2);
}

/// <summary>
/// fill a rounded rectangle, changed to horizontal lines (faster in sprites).
/// </summary>
/// <param name="img"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="r"></param>
/// <param name="color"></param>
/// <param name="fillInner"></param>
void fillRoundRect(Image<RGB565> img, int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color, bool fillInner) {
  if (fillInner) img.fillRect(x, y + r, w, h - r - r, color);
  // draw four corners
  fillCircleHelper(img, x + r, y + h - r - 1, r, 1, w - r - r - 1, color);
  fillCircleHelper(img, x + r, y + r, r, 2, w - r - r - 1, color);
}

/// <summary>
/// fillCircle helper
/// </summary>
/// <param name="img"></param>
/// <param name="x0"></param>
/// <param name="y0"></param>
/// <param name="r"></param>
/// <param name="cornername"></param>
/// <param name="delta"></param>
/// <param name="color"></param>
void fillCircleHelper(Image<RGB565> img, int16_t x0, int16_t y0, int16_t r, int16_t cornername, int16_t delta, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -r - r;
  int16_t y = 0;

  delta++;

  while (y < r) {
    if (f >= 0) {
      if (cornername & 0x1) img.drawFastHLine(x0 - y, y0 + r, y + y + delta, color);
      if (cornername & 0x2) img.drawFastHLine(x0 - y, y0 - r, y + y + delta, color);
      r--;
      ddF_y += 2;
      f += ddF_y;
    }

    y++;
    ddF_x += 2;
    f += ddF_x;

    if (cornername & 0x1) img.drawFastHLine(x0 - r, y0 + y, r + r + delta, color);
    if (cornername & 0x2) img.drawFastHLine(x0 - r, y0 - y, r + r + delta, color);
  }
}

/// <summary>
/// get color from background
/// </summary>
/// <param name="_mode"></param>
/// <returns>background color</returns>
uint16_t getBackgroundColor(uint16_t _mode) {
  uint16_t color = 0;
  if (_mode == 0) color = analog_black[119 + 160 * 240];
  if (_mode == 1) color = analog_white[119 + 160 * 240];
  if (_mode == 2) color = analog_warm[119 + 160 * 240];
  return color;
}

/// <summary>
/// take a screenshot from display
/// </summary>
void takeScreenshot() {
  // Line Buffer
  uint8_t displayLine[480];

  lockScreenUpdate = true;
  Serial.print("*");
  for (uint16_t y = 0; y < 320; y++) {
    memcpy(displayLine, frontBuffer + y * 240, 480);
    Serial.write(displayLine, 480);
    delay(2);
  }
  Serial.print("#");
  lockScreenUpdate = false;
}

/// <summary>
/// if 'value' is in the range 0-159 it is converted to a spectrum colour
/// from 0 = red through to 127 = blue to 159 = violet
/// extending the range to 0-191 adds a further violet to red band
/// </summary>
/// <param name="value"></param>
/// <returns>return a 16 bit rainbow colour</returns>
uint16_t rainbow(byte value) {
  value = value % 192;

  byte red = 0; // red is the top 5 bits of a 16 bit colour value
  byte green = 0; // green is the middle 6 bits, but only top 5 bits used here
  byte blue = 0; // blue is the bottom 5 bits

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector) {
    case 0:
      red = 0x1F;
      green = amplit; // green ramps up
      blue = 0;
      break;
    case 1:
      red = 0x1F - amplit; // red ramps down
      green = 0x1F;
      blue = 0;
      break;
    case 2:
      red = 0;
      green = 0x1F;
      blue = amplit; // blue ramps up
      break;
    case 3:
      red = 0;
      green = 0x1F - amplit; // green ramps down
      blue = 0x1F;
      break;
    case 4:
      red = amplit; // red ramps up
      green = 0;
      blue = 0x1F;
      break;
    case 5:
      red = 0x1F;
      green = 0;
      blue = 0x1F - amplit; // blue ramps down
      break;
  }

  return red << 11 | green << 6 | blue;
}

/// <summary>
/// show messagebox with rounded corners
/// </summary>
/// <param name="message"></param>
void messageBox(const char* message) {
  uint16_t h = 50;
  uint16_t w = 220;
  uint16_t x = 120 - (w / 2);
  uint16_t y = 160 - (h / 2);

  lockScreenUpdate = true;
  im.fillRect(x, y, w, h, frontBuffer[8 + 240 * 240]);
  im.fillRoundRect(x, y, w, h, 7, (uint16_t)0x8410);
  im.fillRoundRect(x + 2, y + 2, w - 4, h - 4, 7, (uint16_t)0x4208);
  drawTextCenterX(im, message, y + (h / 2) + 8, 240, RGB565_White, Arial_16_Bold);
  tft.update(frontBuffer, true);
  delay(1000);
  lockScreenUpdate = false;

  if (moduleType == 0) displayInitDigital(false);
  if (moduleType == 1) displayInitAnalog();
  if (moduleType == 2) displayInitFFT(false);
  if (moduleType == 3) displayInitGonio(false);
}
