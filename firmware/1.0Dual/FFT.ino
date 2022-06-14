/// <summary>
/// initialize display
/// </summary>
/// <param name="reset"></param>
void displayInitFFT(bool reset) {
  // refresh: 200, frames: 100
  tft.setRefreshRate(200);
  tft.setVSyncSpacing(2);

  // queue not needed
  queueStop();
  setMode(false);

  (flipScreen) ? tft.setRotation(2) : tft.setRotation(0);
  tft.setScroll((flipScreen) ? 320 - FFT_Offset : FFT_Offset);

  // fill screen
  bg.fillScreen(FFT_ShowA700Frame ? RGB565_Black : FFT_DisplayBackColor);

  // show the A700 frame
  if (FFT_ShowA700Frame) bg.fillRoundRect(0, 26, 240, 294, 7, FFT_DisplayBackColor);

  // show the calibration frame
  if (showCalibrationFrame) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Magenta);

  // send calibration data
  if (calibrate) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Red);

  // write descriptions over bars
  bg.drawText((FFT_LevelBarMode == 0 /*PPM*/) ? "PPM" : "RMS", (FFT_LevelBarMode == 0 /*PPM*/) ? iVec2(216, 36) : iVec2(215, 36), FFT_HeaderForeColor, Arial_8, false);

  // write bar 'dB' description
  float dBPre = 0.0f;
  for (uint16_t y = 0; y < 275; y++) {
    float dB = roundf((float)map(y, 0, 275, FFT_dBLow, 6.0f));
    if (dB != dBPre) {
      if (dB == 6) {
        bg.drawText("6", iVec2(223, 319 - y), RGB565_Red, Arial_8, false);
      }
      if (dB == 3) {
        bg.drawText("3", iVec2(223, 319 - y), RGB565_Red, Arial_8, false);
      }
      if (dB == 0) {
        bg.drawText("0", iVec2(223, 319 - y), RGB565_Red, Arial_8, false);
      }
      if (dB == -5) {
        bg.drawText("5", iVec2(223, 319 - y), FFT_ScaleForeColor, Arial_8, false);
      }
      if (dB == -10) {
        bg.drawText("10", iVec2(220, 319 - y), FFT_ScaleForeColor, Arial_8, false);
      }
      if (dB == -20) {
        bg.drawText("20", iVec2(220, 319 - y), FFT_ScaleForeColor, Arial_8, false);
      }
      if (dB == -30) {
        bg.drawText("30", iVec2(220, 319 - y), FFT_ScaleForeColor, Arial_8, false);
      }
      if (dB == -40) {
        bg.drawText("40", iVec2(220, 319 - y), FFT_ScaleForeColor, Arial_8, false);
      }
      dBPre = dB;
    }
  }

  // vertical 2x25 bars (tree)
  if (FFT_BarMode == 0) {
    bg.drawFastVLine(94, 42, 276, FFT_LineColor);
    bg.drawFastVLine(120, 42, 276, FFT_LineColor);
    bg.fillRect(95, 42, 25, 276, FFT_ScaleBackgroundColor);
    drawTextCenterX(bg, "SPECTRUM ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);
    bg.drawText("L", iVec2(24, 42), FFT_LRColor, Arial_14_Bold, false);
    bg.drawText("R", iVec2(180, 42), FFT_LRColor, Arial_14_Bold, false);

    for (uint16_t x = 0; x < 25; x++) {
      float freq = 43.0f + 43.0f * (binStart25[x] + ((binEnd25[x] - binStart25[x]) / 2.));

      uint16_t yPos = 315 - map(x, 0, 25, 0, 275);
      if (freq >= 10000.0f) {
        drawNumber(bg, round(freq / 1000.0f), 99, yPos, FFT_ScaleForeColor, Arial_8);
        bg.drawText("k", iVec2(112, yPos), FFT_ScaleForeColor, Arial_8, false);
      } else if (freq >= 1000.0f) {
        drawFloat(bg, freq / 1000.0f, 1, 98, yPos, FFT_ScaleForeColor, Arial_8);
        bg.drawText("k", iVec2(114, yPos), FFT_ScaleForeColor, Arial_8, false);
      } else if (freq >= 100.0f) {
        drawNumber(bg, freq, 99, yPos, FFT_ScaleForeColor, Arial_8);
      } else if (freq >= 10.0f) {
        drawNumber(bg, freq, 102, yPos, FFT_ScaleForeColor, Arial_8);
      } else {
        drawNumber(bg, freq, 105, yPos, FFT_ScaleForeColor, Arial_8);
      }
    }
    // vertical 2x69 bars (tree)
  } else if (FFT_BarMode == 3) {
    bg.drawFastVLine(94, 42, 276, FFT_LineColor);
    bg.drawFastVLine(120, 42, 276, FFT_LineColor);
    bg.fillRect(95, 42, 25, 276, FFT_ScaleBackgroundColor);
    drawTextCenterX(bg, "HI-RES ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);
    bg.drawText("L", iVec2(24, 42), FFT_LRColor, Arial_14_Bold, false);
    bg.drawText("R", iVec2(180, 42), FFT_LRColor, Arial_14_Bold, false);

    for (uint16_t x = 0; x < 69; x++) {
      if (x % 3 == 0) {
        float freq = 43.0f * (binStart69[x + 1] + ((binEnd69[x + 1] - binStart69[x + 1]) / 2.0f));
        uint16_t yPos = 315 - map(x, 0, 69, 0, 275);
        if (freq >= 10000.0f) {
          drawNumber(bg, round(freq / 1000.0f), 99, yPos, FFT_ScaleForeColor, Arial_8);
          bg.drawText("k", iVec2(112, yPos), FFT_ScaleForeColor, Arial_8, false);
        } else if (freq >= 1000.0f) {
          drawFloat(bg, freq / 1000.0f, 1, 98, yPos, FFT_ScaleForeColor, Arial_8);
          bg.drawText("k", iVec2(114, yPos), FFT_ScaleForeColor, Arial_8, false);
        } else if (freq >= 100.0f) {
          drawNumber(bg, freq, 99, yPos, FFT_ScaleForeColor, Arial_8);
        } else if (freq >= 10.0f) {
          drawNumber(bg, freq, 102, yPos, FFT_ScaleForeColor, Arial_8);
        } else {
          drawNumber(bg, freq, 105, yPos, FFT_ScaleForeColor, Arial_8);
        }
      }
    }

    // horizontal 16 bars
  } else if (FFT_BarMode == 1) {
    drawTextCenterX(bg, "SPECTRUM ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);
    bg.drawFastHLine(2, 170, 207, FFT_LineColor);
    bg.drawFastHLine(2, 315, 207, FFT_LineColor);
    bg.fillRect(2, 171, 206, 13, FFT_ScaleBackgroundColor);

    for (uint16_t x = 0; x < 16; x++) {
      if (x % 2 == 0) {
        float freq = 43.0f * (binStart16[x + 1] + ((binEnd16[x + 1] - binStart16[x + 1]) / 2.0f));
        uint16_t vSep = map(x, 0, 16, 2, 206);
        if (x > 12) vSep -= 4;
        bg.drawFastVLine(vSep, 171, 13, FFT_LineColor);
        char buf[4];
        (freq >= 1000.0f) ? sprintf(buf, "%u%c\n", (uint16_t)round(freq / 1000.0f), 'k') : sprintf(buf, "%u", (uint16_t)freq);
        bg.drawText(buf, iVec2(vSep + 3, 182), FFT_ScaleForeColor, Arial_8, false);
      }
    }

    bg.drawText("L", iVec2(8, 66), FFT_LRColor, Arial_14_Bold, false);
    bg.drawText("R", iVec2(8, 210), FFT_LRColor, Arial_14_Bold, false);

    // horizontal 52 bars
  } else if (FFT_BarMode == 4) {
    drawTextCenterX(bg, "HI-RES ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);
    bg.drawFastHLine(2, 170, 207, FFT_LineColor);
    bg.drawFastHLine(2, 315, 207, FFT_LineColor);
    bg.fillRect(2, 171, 206, 13, FFT_ScaleBackgroundColor);

    for (uint16_t x = 0; x < 52; x++) {
      if (x % 6 == 0) {
        float freq = 43.0f * (binStart52[x + 1] + ((binEnd52[x + 1] - binStart52[x + 1]) / 2.0f));
        uint16_t vSep = map(x, 0, 52, 2, 206);
        if (x > 12) vSep -= 4;
        bg.drawFastVLine(vSep, 171, 13, FFT_LineColor);
        char buf[4];
        (freq >= 1000.0f) ? sprintf(buf, "%u%c\n", (uint16_t)round(freq / 1000.0f), 'k') : sprintf(buf, "%u", (uint16_t)freq);
        bg.drawText(buf, iVec2(vSep + 3, 182), FFT_ScaleForeColor, Arial_8, false);
      }
    }

    bg.drawText("L", iVec2(2, 66), FFT_LRColor, Arial_14_Bold, false);
    bg.drawText("R", iVec2(2, 210), FFT_LRColor, Arial_14_Bold, false);

    // sum vertical 25 bars
  } else if (FFT_BarMode == 2) {
    bg.drawFastVLine(2, 42, 276, FFT_LineColor);
    bg.drawFastVLine(28, 42, 276, FFT_LineColor);
    bg.fillRect(3, 42, 25, 276, FFT_ScaleBackgroundColor);
    drawTextCenterX(bg, "SPECTRUM ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);

    for (uint16_t x = 0; x < 25; x++) {
      float freq = 43.0f + 43.0f * (binStart25[x] + ((binEnd25[x] - binStart25[x]) / 2.0f));
      uint16_t yPos = 315 - map(x, 0, 25, 0, 275);

      if (freq >= 10000.0f) {
        drawNumber(bg, round(freq / 1000.0f), 7, yPos, FFT_ScaleForeColor, Arial_8);
        bg.drawText("k", iVec2(20, yPos), FFT_ScaleForeColor, Arial_8, false);
      } else if (freq >= 1000.0f) {
        drawFloat(bg, freq / 1000.0f, 1, 6, yPos, FFT_ScaleForeColor, Arial_8);
        bg.drawText("k", iVec2(21, yPos), FFT_ScaleForeColor, Arial_8, false);
      } else if (freq >= 100.0f) {
        drawNumber(bg, freq, 7, yPos, FFT_ScaleForeColor, Arial_8);
      } else if (freq >= 10.0f) {
        drawNumber(bg, freq, 10, yPos, FFT_ScaleForeColor, Arial_8);
      } else {
        drawNumber(bg, freq, 13, yPos, FFT_ScaleForeColor, Arial_8);
      }
    }

    // sum vertical 69 bars
  } else if (FFT_BarMode == 5) {
    bg.drawFastVLine(2, 42, 276, FFT_LineColor);
    bg.drawFastVLine(28, 42, 276, FFT_LineColor);
    bg.fillRect(3, 42, 25, 276, FFT_ScaleBackgroundColor);
    drawTextCenterX(bg, "HI-RES ANALYZER", 36, 215, FFT_HeaderForeColor, Arial_8);

    for (uint16_t x = 0; x < 69; x++) {
      if (x % 3 == 0) {
        float freq = 43.0f * (binStart69[x + 1] + ((binEnd69[x + 1] - binStart69[x + 1]) / 2.0f));
        uint16_t yPos = 315 - map(x, 0, 69, 0, 275);

        if (freq >= 10000.0f) {
          drawNumber(bg, round(freq / 1000.0f), 7, yPos, FFT_ScaleForeColor, Arial_8);
          bg.drawText("k", iVec2(20, yPos), FFT_ScaleForeColor, Arial_8, false);
        } else if (freq >= 1000.0f) {
          drawFloat(bg, freq / 1000.0f, 1, 6, yPos, FFT_ScaleForeColor, Arial_8);
          bg.drawText("k", iVec2(21, yPos), FFT_ScaleForeColor, Arial_8, false);
        } else if (freq >= 100.0f) {
          drawNumber(bg, freq, 7, yPos, FFT_ScaleForeColor, Arial_8);
        } else if (freq >= 10.0f) {
          drawNumber(bg, freq, 10, yPos, FFT_ScaleForeColor, Arial_8);
        } else {
          drawNumber(bg, freq, 13, yPos, FFT_ScaleForeColor, Arial_8);
        }
      }
    }
  }

  // copy background to front
  memcpy(frontBuffer, backBuffer, 153600);
  drawFFT(reset);
  tft.update(frontBuffer, true);
}

/// <summary>
/// draw FFT depending on BarMode
/// </summary>
/// <param name="reset"></param>
void drawFFT(bool reset) {
  drawLeftBarFFT(reset);
  drawRightBarFFT(reset);

  switch (FFT_BarMode) {
    case 0:
      drawFFTLeftV(reset, false);
      drawFFTRightV(reset, false);
      break;
    case 1:
      drawFFTLeftH(reset, false);
      drawFFTRightH(reset, false);
      break;
    case 2:
      drawFFTBothV(reset, false);
      break;
    case 3:
      drawFFTLeftV(reset, true);
      drawFFTRightV(reset, true);
      break;
    case 4:
      drawFFTLeftH(reset, true);
      drawFFTRightH(reset, true);
      break;
    case 5:
      drawFFTBothV(reset, true);
      break;

  }

  tft.update(frontBuffer, false);

}

/// <summary>
/// draw horizontal FFT for left channel
/// </summary>
/// <param name="reset"></param>
/// <param name="fine">true=52, false=16</param>
void drawFFTLeftH(bool reset, bool fine) {
  // Static vars
  static elapsedMillis clearMaxHold = 0;
  static uint16_t bar = 0;
  static uint16_t pastData[52] = { 0 };
  static uint16_t peakHoldCounter[52] = { 0 };
  static uint16_t fallingCounter[52] = { 0 };
  static uint16_t peakHoldMax[52] = { 0 };

  // vars
  float n = 0.0f;                           // FFT value in dB
  uint16_t posY = 169;                      // y position
  uint16_t barCount = fine ? 52 : 16;       // bars count
  uint16_t barLimit = 128;                  // bar length limit
  uint16_t barWideTotal = fine ? 4 : 13;    // total bar wide
  uint16_t barWideVisible = fine ? 3 : 11;  // visible bar wide
  uint16_t rainbowSteps = fine ? 2 : 9;     // for rainbow colors

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) {
    for (uint16_t i = 0; i < 52; i++)
      peakHoldMax[i] = 0;
  }

  if (fft1024_1.available()) {
    for (bar = 0; bar < barCount; bar++) {

      /* READ & SCALE SECTION
       *************************************************/
      if (fine) {
        n = fftAmplitudeTodB(fft1024_1.read(binStart52[bar], binEnd52[bar]));
      } else {
        n = fftAmplitudeTodB(fft1024_1.read(binStart16[bar], binEnd16[bar]));
      }

      uint16_t val = map(n, FFT_dBLow, dBHigh, 0, barLimit);

      // reset maxhold counter.
      if (val > 0) clearMaxHold = 0;

      /* BALLISTICS SECTION
       *************************************************/
      // Get previous bar data.
      uint16_t pastVal = pastData[bar];

      // Meter ballistics.
      if (val < pastVal - FFT_FFTBarRelease) val = pastVal - FFT_FFTBarRelease;
      if (pastVal < val - FFT_FFTBarAttack) val = pastVal + FFT_FFTBarAttack;
      if (++peakHoldCounter[bar] > FFT_FFTPeakHoldTime && fallingCounter[bar] > FFT_FFTPeakRelease) fallingCounter[bar] -= FFT_FFTPeakRelease;

      // Store bar data.
      pastData[bar] = val;

      // store new peak level and reset the peak hold counter
      if (val > fallingCounter[bar]) {
        fallingCounter[bar] = val + 1; // +1 is very important!
        peakHoldCounter[bar] = 0;
      }

      // store new max level for peakhold
      if (val > peakHoldMax[bar]) {
        peakHoldMax[bar] = val + 1; // +1 is very important!
      }

      /* DRAW BARS SECTION
       *************************************************/
      for (int y = 0; y < barLimit; y++) {
        uint16_t color = (FFT_UseWheel) ? rainbow(bar * rainbowSteps) : FFT_FFTBarColor;

        // draw bars.
        if (y < pastVal) {
          im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideVisible, (FFT_FFTSegmentHeight == 0) ? color : (y % (FFT_FFTSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
          im.drawFastHLine(2 + barWideVisible + bar * barWideTotal, posY - y, barWideTotal - barWideVisible, FFT_DisplayBackColor); // clear gap
        } else {
          if (!FFT_PeakHold && y > 10 /*ShowFromPoint*/ && y >= fallingCounter[bar] && y < fallingCounter[bar] + FFT_FFTPeakHeight) im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideVisible, FFT_FFTPeakColor); // peaks
          else im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideTotal, FFT_DisplayBackColor); // clear
        }
      }
    }
  }

  // draw peak graph
  if (FFT_PeakHold) {
    for (uint16_t b = 0; b < barCount - 1; b++) {
      im.drawLine(2 + (b * barWideTotal) + (barWideTotal / 2), posY - peakHoldMax[b], 2 + ((b + 1) * barWideTotal) + (barWideTotal / 2), posY - peakHoldMax[b + 1], FFT_FFTPeakColor);
    }
  }

  im.drawText("L", iVec2(8, 66), FFT_LRColor, Arial_14_Bold, false);
}

/// <summary>
/// draw horizontal FFT for right channel
/// </summary>
/// <param name="reset"></param>
/// <param name="fine">true=52, false=16</param>
void drawFFTRightH(bool reset, bool fine) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static uint16_t bar = 0;
  static uint16_t pastData[52] = { 0 };
  static uint16_t peakHoldCounter[52] = { 0 };
  static uint16_t fallingCounter[52] = { 0 };
  static uint16_t peakHoldMax[52] = { 0 };

  // vars
  float n = 0.0f;                           // FFT value in dB
  uint16_t posY = 314;                      // y position
  uint16_t barCount = fine ? 52 : 16;       // bars count
  uint16_t barLimit = 128;                  // bar length limit
  uint16_t barWideTotal = fine ? 4 : 13;    // total bar wide
  uint16_t barWideVisible = fine ? 3 : 11;  // visible bar wide
  uint16_t rainbowSteps = fine ? 2 : 9;     // for rainbow colors

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) {
    for (uint16_t i = 0; i < 52; i++)
      peakHoldMax[i] = 0;
  }

  if (fft1024_2.available()) {
    for (bar = 0; bar < barCount; bar++) {

      /* READ & SCALE SECTION
       *************************************************/
      if (fine) {
        n = fftAmplitudeTodB(fft1024_2.read(binStart52[bar], binEnd52[bar]));
      } else {
        n = fftAmplitudeTodB(fft1024_2.read(binStart16[bar], binEnd16[bar]));
      }

      uint16_t val = map(n, FFT_dBLow, dBHigh, 0, barLimit);

      // reset maxhold counter
      if (val > 0) clearMaxHold = 0;

      /* BALLISTICS SECTION
       *************************************************/
      // get previous bar data
      uint16_t pastVal = pastData[bar];

      // meter ballistics
      if (val < pastVal - FFT_FFTBarRelease) val = pastVal - FFT_FFTBarRelease;
      if (pastVal < val - FFT_FFTBarAttack) val = pastVal + FFT_FFTBarAttack;
      if (++peakHoldCounter[bar] > FFT_FFTPeakHoldTime && fallingCounter[bar] > FFT_FFTPeakRelease) fallingCounter[bar] -= FFT_FFTPeakRelease;

      // store bar data
      pastData[bar] = val;

      // store new peak level and reset the peak hold counter
      if (val > fallingCounter[bar]) {
        fallingCounter[bar] = val + 1; // +1 is very important!
        peakHoldCounter[bar] = 0;
      }

      // store new max level for peakhold
      if (val > peakHoldMax[bar]) {
        peakHoldMax[bar] = val + 1; // +1 is very important!
      }

      /* DRAW BARS SECTION
       *************************************************/
      for (int y = 0; y < barLimit; y++) {
        uint16_t color = (FFT_UseWheel) ? rainbow(bar * rainbowSteps) : FFT_FFTBarColor;

        // draw bars
        if (y < pastVal) {
          im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideVisible, (FFT_FFTSegmentHeight == 0) ? color : (y % (FFT_FFTSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
          im.drawFastHLine(2 + barWideVisible + bar * barWideTotal, posY - y, barWideTotal - barWideVisible, FFT_DisplayBackColor); // clear gap
        } else {
          if (!FFT_PeakHold && y > 10 /*ShowFromPoint*/ && y >= fallingCounter[bar] && y < fallingCounter[bar] + FFT_FFTPeakHeight) im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideVisible, FFT_FFTPeakColor); // peaks
          else im.drawFastHLine(2 + bar * barWideTotal, posY - y, barWideTotal, FFT_DisplayBackColor); // clear
        }
      }
    }
  }

  // draw peak graph
  if (FFT_PeakHold) {
    for (uint16_t b = 0; b < barCount - 1; b++) {
      im.drawLine(2 + (b * barWideTotal) + (barWideTotal / 2), posY - peakHoldMax[b], 2 + ((b + 1) * barWideTotal) + (barWideTotal / 2), posY - peakHoldMax[b + 1], FFT_FFTPeakColor);
    }
  }

  im.drawText("R", iVec2(8, 210), FFT_LRColor, Arial_14_Bold, false);
}

/// <summary>
/// draw vertical FFT for left channel
/// </summary>
/// <param name="reset"></param>
/// <param name="fine">true=69, false=25</param>
void drawFFTLeftV(bool reset, bool fine) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static uint16_t bar = 0;
  static uint16_t pastData[69] = { 0 };
  static uint16_t peakHoldCounter[69] = { 0 };
  static uint16_t fallingCounter[69] = { 0 };
  static uint16_t peakHoldMax[69] = { 0 };

  // vars
  float n = 0.0f;                           // FFT value in dB
  uint16_t posX = 93;                       // x position
  uint16_t posY = fine ? 315 : 307;         // y position
  uint16_t barCount = fine ? 69 : 25;       // bars count
  uint16_t barLimit = 90;                   // bar length limit
  uint16_t barHeightTotal = fine ? 4 : 11;  // total bar height
  uint16_t barHeightVisible = fine ? 3 : 9; // visible bar height
  uint16_t rainbowSteps = fine ? 2 : 6;     // for rainbow colors

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) {
    for (uint16_t i = 0; i < 69; i++)
      peakHoldMax[i] = 0;
  }

  if (fft1024_1.available()) {
    for (bar = 0; bar < barCount; bar++) {

      /* READ & SCALE SECTION
       *************************************************/
      if (fine) {
        n = fftAmplitudeTodB(fft1024_1.read(binStart69[bar], binEnd69[bar]));
      } else {
        n = fftAmplitudeTodB(fft1024_1.read(binStart25[bar], binEnd25[bar]));
      }

      uint16_t val = map(n, FFT_dBLow, dBHigh, 0, barLimit);

      // reset maxhold counter
      if (val > 0) clearMaxHold = 0;

      /* BALLISTICS SECTION
       *************************************************/
      // get previous bar data
      uint16_t pastVal = pastData[bar];

      // meter ballistics
      if (val < pastVal - FFT_FFTBarRelease) val = pastVal - FFT_FFTBarRelease;
      if (pastVal < val - FFT_FFTBarAttack) val = pastVal + FFT_FFTBarAttack;
      if (++peakHoldCounter[bar] > FFT_FFTPeakHoldTime && fallingCounter[bar] > FFT_FFTPeakRelease) fallingCounter[bar] -= FFT_FFTPeakRelease;

      // store bar data
      pastData[bar] = val;

      // store new peak level and reset the peak hold counter
      if (val > fallingCounter[bar]) {
        fallingCounter[bar] = val + 1; // +1 is very important!
        peakHoldCounter[bar] = 0;
      }

      // store new max level for peakhold
      if (val > peakHoldMax[bar]) {
        peakHoldMax[bar] = val + 1; // +1 is very important!
      }

      /* DRAW BARS SECTION
       *************************************************/
      for (int x = 0; x < barLimit; x++) {
        uint16_t color = (FFT_UseWheel) ? rainbow(bar * rainbowSteps) : FFT_FFTBarColor;

        // draw bars
        if (x < pastVal) {
          im.drawFastVLine(posX - x, posY - bar * barHeightTotal, barHeightVisible, (FFT_FFTSegmentHeight == 0) ? color : (x % (FFT_FFTSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
          im.drawFastVLine(posX - x, posY - bar * barHeightTotal + barHeightVisible, barHeightTotal - barHeightVisible, FFT_DisplayBackColor); // clear gap
        } else {
          if (!FFT_PeakHold && x > 10 /*ShowFromPoint*/ && x >= fallingCounter[bar] && x < fallingCounter[bar] + FFT_FFTPeakHeight) im.drawFastVLine(posX - x, posY - bar * barHeightTotal, barHeightVisible, FFT_FFTPeakColor); // peaks
          else im.drawFastVLine(posX - x, posY - bar * barHeightTotal, barHeightTotal, FFT_DisplayBackColor); // clear
        }
      }
    }
  }

  // draw peak graph
  if (FFT_PeakHold) {
    for (uint16_t b = 0; b < barCount - 1; b++) {
      im.drawLine(posX - peakHoldMax[b], posY - (b * barHeightTotal) + (barHeightTotal / 2), posX - peakHoldMax[b + 1], posY - ((b + 1) * barHeightTotal) + (barHeightTotal / 2), FFT_FFTPeakColor);
    }
  }
}

/// <summary>
/// draw vertical FFT for right channel
/// </summary>
/// <param name="reset"></param>
/// <param name="fine">true=69, false=25</param>
void drawFFTRightV(bool reset, bool fine) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static uint16_t bar = 0;
  static uint16_t pastData[69] = { 0 };
  static uint16_t peakHoldCounter[69] = { 0 };
  static uint16_t fallingCounter[69] = { 0 };
  static uint16_t peakHoldMax[69] = { 0 };

  // vars
  float n = 0.0f;                           // FFT value in dB
  uint16_t posX = 122;                      // x position
  uint16_t posY = fine ? 315 : 307;         // y position
  uint16_t barCount = fine ? 69 : 25;       // bars count
  uint16_t barLimit = 90;                   // bar length limit
  uint16_t barHeightTotal = fine ? 4 : 11;  // total bar height
  uint16_t barHeightVisible = fine ? 3 : 9; // visible bar height
  uint16_t rainbowSteps = fine ? 2 : 6;     // for rainbow colors

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) {
    for (uint16_t i = 0; i < 69; i++)
      peakHoldMax[i] = 0;
  }

  if (fft1024_2.available()) {
    for (bar = 0; bar < barCount; bar++) {

      /* READ & SCALE SECTION
       *************************************************/
      if (fine) {
        n = fftAmplitudeTodB(fft1024_2.read(binStart69[bar], binEnd69[bar]));
      } else {
        n = fftAmplitudeTodB(fft1024_2.read(binStart25[bar], binEnd25[bar]));
      }

      uint16_t val = map(n, FFT_dBLow, dBHigh, 0, barLimit);

      // reset maxhold counter
      if (val > 0) clearMaxHold = 0;

      /* BALLISTICS SECTION
       *************************************************/
      // get previous bar data
      uint16_t pastVal = pastData[bar];

      // meter ballistics
      if (val < pastVal - FFT_FFTBarRelease) val = pastVal - FFT_FFTBarRelease;
      if (pastVal < val - FFT_FFTBarAttack) val = pastVal + FFT_FFTBarAttack;
      if (++peakHoldCounter[bar] > FFT_FFTPeakHoldTime && fallingCounter[bar] > FFT_FFTPeakRelease) fallingCounter[bar] -= FFT_FFTPeakRelease;

      // store bar data
      pastData[bar] = val;

      // store new peak level and reset the peak hold counter
      if (val > fallingCounter[bar]) {
        fallingCounter[bar] = val + 1; // +1 is very important!
        peakHoldCounter[bar] = 0;
      }

      // store new max level for peakhold
      if (val > peakHoldMax[bar]) {
        peakHoldMax[bar] = val + 1; // +1 is very important!
      }

      /* DRAW BARS SECTION
       *************************************************/
      for (int x = 0; x < barLimit; x++) {
        uint16_t color = (FFT_UseWheel) ? rainbow(bar * rainbowSteps) : FFT_FFTBarColor;

        // draw bars
        if (x < pastVal) {
          im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightVisible, (FFT_FFTSegmentHeight == 0) ? color : (x % (FFT_FFTSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
          im.drawFastVLine(posX + x, posY - bar * barHeightTotal + barHeightVisible, barHeightTotal - barHeightVisible, FFT_DisplayBackColor); // clear gap
        } else {
          if (!FFT_PeakHold && x > 10 /*ShowFromPoint*/ && x >= fallingCounter[bar] && x < fallingCounter[bar] + FFT_FFTPeakHeight) im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightVisible, FFT_FFTPeakColor); // peaks
          else im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightTotal, FFT_DisplayBackColor); // clear
        }
      }
    }
  }

  // draw peak graph
  if (FFT_PeakHold) {
    for (uint16_t b = 0; b < barCount - 1; b++) {
      im.drawLine(posX + peakHoldMax[b], posY - (b * barHeightTotal) + (barHeightTotal / 2), posX + peakHoldMax[b + 1], posY - ((b + 1) * barHeightTotal) + (barHeightTotal / 2), FFT_FFTPeakColor);
    }
  }
}

/// <summary>
/// draw vertical 69 or 25 bars for both channels
/// </summary>
/// <param name="reset"></param>
/// <param name="fine">true=69, false=25</param>
void drawFFTBothV(bool reset, bool fine) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static uint16_t bar = 0;
  static uint16_t pastData[69] = { 0 };
  static uint16_t peakHoldCounter[69] = { 0 };
  static uint16_t fallingCounter[69] = { 0 };
  static uint16_t peakHoldMax[69] = { 0 };

  // vars
  float n = 0.0f;                           // FFT value in dB
  uint16_t posX = 30;                       // x position
  uint16_t posY = fine ? 315 : 307;         // y position
  uint16_t barCount = fine ? 69 : 25;       // bars count
  uint16_t barLimit = 180;                  // bar length limit
  uint16_t barHeightTotal = fine ? 4 : 11;  // total bar height
  uint16_t barHeightVisible = fine ? 3 : 9; // visible bar height
  uint16_t rainbowSteps = fine ? 2 : 6;     // for rainbow colors

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) {
    for (uint16_t i = 0; i < 69; i++)
      peakHoldMax[i] = 0;
  }

  if (fft1024_3.available()) {
    for (bar = 0; bar < barCount; bar++) {

      /* READ & SCALE SECTION
       *************************************************/
      if (fine) {
        n = fftAmplitudeTodB(fft1024_3.read(binStart69[bar], binEnd69[bar]));
      } else {
        n = fftAmplitudeTodB(fft1024_3.read(binStart25[bar], binEnd25[bar]));
      }

      uint16_t val = map(n, FFT_dBLow, dBHigh, 0, barLimit);

      // reset maxhold counter
      if (val > 0) clearMaxHold = 0;

      /* BALLISTICS SECTION
       *************************************************/
      // get previous bar data
      uint16_t pastVal = pastData[bar];

      // meter ballistics
      if (val < pastVal - FFT_FFTBarRelease) val = pastVal - FFT_FFTBarRelease;
      if (pastVal < val - FFT_FFTBarAttack) val = pastVal + FFT_FFTBarAttack;
      if (++peakHoldCounter[bar] > FFT_FFTPeakHoldTime && fallingCounter[bar] > FFT_FFTPeakRelease) fallingCounter[bar] -= FFT_FFTPeakRelease;

      // store bar data
      pastData[bar] = val;

      // store new peak level and reset the peak hold counter
      if (val > fallingCounter[bar]) {
        fallingCounter[bar] = val + 1; // +1 is very important!
        peakHoldCounter[bar] = 0;
      }

      // store new max level for peakhold.
      if (val > peakHoldMax[bar]) {
        peakHoldMax[bar] = val + 1; // +1 is very important!
      }

      /* DRAW BARS SECTION
       *************************************************/
      for (int x = 0; x < barLimit; x++) {
        uint16_t color = (FFT_UseWheel) ? rainbow(bar * rainbowSteps) : FFT_FFTBarColor;

        // draw bars
        if (x < pastVal) {
          im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightVisible, (FFT_FFTSegmentHeight == 0) ? color : (x % (FFT_FFTSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
          im.drawFastVLine(posX + x, posY - bar * barHeightTotal + barHeightVisible, barHeightTotal - barHeightVisible, FFT_DisplayBackColor); // clear gap
        } else {
          if (!FFT_PeakHold && x > 10 /*ShowFromPoint*/ && x >= fallingCounter[bar] && x < fallingCounter[bar] + FFT_FFTPeakHeight) im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightVisible, FFT_FFTPeakColor); // peaks
          else im.drawFastVLine(posX + x, posY - bar * barHeightTotal, barHeightTotal, FFT_DisplayBackColor); // clear
        }
      }
    }
  }

  // draw peak graph
  if (FFT_PeakHold) {
    for (uint16_t b = 0; b < barCount - 1; b++) {
      im.drawLine(posX + peakHoldMax[b], posY - (b * barHeightTotal) + (barHeightTotal / 2), posX + peakHoldMax[b + 1], posY - ((b + 1) * barHeightTotal) + (barHeightTotal / 2), FFT_FFTPeakColor);
    }
  }
}

/// <summary>
/// draw left bar
/// </summary>
/// <param name="reset"></param>
/// <returns>bar length</returns>
uint16_t drawLeftBarFFT(bool reset) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static float dBPre = 0.0f;
  static uint16_t pastVal = 0, holdCounter = 0, fallingCounter = 0, peakHoldMax = 0;

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) peakHoldMax = 0;

  if ((FFT_LevelBarMode == 0 /*PEAK*/) ? peak1.available() : rms1.available()) {
    // read RMS or PEAK, calculate dB & scale dB range to bar length
    uint16_t barVal = (FFT_LevelBarMode == 0 /*PEAK*/) ? map(peakAmplitudeTodB(peak1.read(), 0), FFT_dBLow, dBHigh, 0, 275) : map(rmsAmplitudeTodB(rms1.read(), 0), FFT_dBLow, dBHigh, 0, 275);

    // reset maxhold counter
    if (barVal > 0) clearMaxHold = 0;

    // get previous bar data
    uint16_t valTmp = pastVal;

    // ballistics
    if (FFT_LevelBarMode == 0 /*PEAK*/) {
      if (barVal < valTmp - FFT_PEAKBarRelease) barVal = valTmp - FFT_PEAKBarRelease;
      if (valTmp < barVal - FFT_PEAKBarAttack) barVal = valTmp + FFT_PEAKBarAttack;
      if (++holdCounter > FFT_PEAKPeakHoldTime && fallingCounter > FFT_PEAKPeakRelease) fallingCounter -= FFT_PEAKPeakRelease; // peak release
    } else {
      if (barVal < valTmp - FFT_VUBarRelease) barVal = valTmp - FFT_VUBarRelease;
      if (valTmp < barVal - FFT_VUBarAttack) barVal = valTmp + FFT_VUBarAttack;
      if (++holdCounter > FFT_VUPeakHoldTime && fallingCounter > FFT_VUPeakRelease) fallingCounter -= FFT_VUPeakRelease; // peak release
    }

    // store bar data
    pastVal = barVal;

    // store new max level and reset the hold counter
    if (barVal > fallingCounter) {
      fallingCounter = barVal + 1; // +1 is very important!
      holdCounter = 0;
    }

    // store new max level for peakhold
    if (barVal > peakHoldMax) {
      peakHoldMax = barVal + 1; // +1 is very important!
    }

    // draw bars and peaks
    for (uint16_t y = 0; y < 275; y++) {
      float dB = roundf(map((float)y, 0, 275, FFT_dBLow, 6.0f));

      // colors
      uint16_t color = FFT_VUBarColorNormal;
      if (dB >= 0.0f) color = FFT_VUBarColorOver;
      else if (dB >= -5.0f) color = FFT_VUBarColorMid;

      // bars
      if (y < pastVal) {
        im.drawFastHLine(214, 315 - y, 4, (FFT_VUSegmentHeight == 0) ? color : (y % (FFT_VUSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
      } else {
        if (FFT_PeakHold) {
          im.drawFastHLine(214, 315 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + FFT_VUPeakHeight) ? FFT_VUPeakColor : FFT_VUBarsBackColor);
        } else {
          im.drawFastHLine(214, 315 - y, 4, (y > 10 && y >= fallingCounter && y < fallingCounter + FFT_VUPeakHeight) ? FFT_VUPeakColor : FFT_VUBarsBackColor);
        }
      }

      // markers
      if (dB != dBPre) {
        if (dB == 6.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 5.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 4.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 3.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 2.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 1.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == 0.0f) {
          im.drawFastHLine(214, 315 - y, 4, RGB565_Red);
        }
        if (dB == -5.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -10.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -15.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -20.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -25.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -30.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -35.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -40.0f) {
          im.drawFastHLine(214, 315 - y, 4, FFT_VUMarkerColor);
        }
        dBPre = dB;
      }
    }
    return barVal;
  }
  return 0;
}

/// <summary>
/// draw right bar
/// </summary>
/// <param name="reset"></param>
/// <returns>bar length</returns>
uint16_t drawRightBarFFT(bool reset) {
  // static vars
  static elapsedMillis clearMaxHold = 0;
  static float dBPre = 0.0f;
  static uint16_t pastVal = 0, holdCounter = 0, fallingCounter = 0, peakHoldMax = 0;

  // clear peak hold max
  if (reset || (FFT_WorkMode > 7 && clearMaxHold > 4000)) peakHoldMax = 0;

  if ((FFT_LevelBarMode == 0 /*PEAK*/) ? peak2.available() : rms2.available()) {
    // read RMS or PEAK, calculate dB & scale dB range to bar length
    uint16_t barVal = (FFT_LevelBarMode == 0 /*PEAK*/) ? map(peakAmplitudeTodB(peak2.read(), 0), FFT_dBLow, dBHigh, 0, 275) : map(rmsAmplitudeTodB(rms2.read(), 0), FFT_dBLow, dBHigh, 0, 275);

    // reset maxhold counter
    if (barVal > 0) clearMaxHold = 0;

    // get previous bar data
    uint16_t valTmp = pastVal;

    // ballistics
    if (FFT_LevelBarMode == 0 /*PEAK*/) {
      if (barVal < valTmp - FFT_PEAKBarRelease) barVal = valTmp - FFT_PEAKBarRelease;
      if (valTmp < barVal - FFT_PEAKBarAttack) barVal = valTmp + FFT_PEAKBarAttack;
      if (++holdCounter > FFT_PEAKPeakHoldTime && fallingCounter > FFT_PEAKPeakRelease) fallingCounter -= FFT_PEAKPeakRelease; // peak release
    } else {
      if (barVal < valTmp - FFT_VUBarRelease) barVal = valTmp - FFT_VUBarRelease;
      if (valTmp < barVal - FFT_VUBarAttack) barVal = valTmp + FFT_VUBarAttack;
      if (++holdCounter > FFT_VUPeakHoldTime && fallingCounter > FFT_VUPeakRelease) fallingCounter -= FFT_VUPeakRelease; // peak release
    }

    // store bar data
    pastVal = barVal;

    // store new max level and reset the hold counter
    if (barVal > fallingCounter) {
      fallingCounter = barVal + 1; // +1 is very important!
      holdCounter = 0;
    }

    // store new max level for peakhold
    if (barVal > peakHoldMax) {
      peakHoldMax = barVal + 1; // +1 is very important!
    }

    // draw bars and peaks
    for (uint16_t y = 0; y < 275; y++) {
      float dB = roundf(map((float)y, 0, 275, FFT_dBLow, 6.0f));

      // colors
      uint16_t color = FFT_VUBarColorNormal;
      if (dB >= 0.0f) color = FFT_VUBarColorOver;
      else if (dB >= -5.0f) color = FFT_VUBarColorMid;

      // bars
      if (y < pastVal) {
        im.drawFastHLine(233, 315 - y, 4, (FFT_VUSegmentHeight == 0) ? color : (y % (FFT_VUSegmentHeight + 1) == 0) ? FFT_DisplayBackColor : color); // bars
      } else {
        if (FFT_PeakHold) {
          im.drawFastHLine(233, 315 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + FFT_VUPeakHeight) ? FFT_VUPeakColor : FFT_VUBarsBackColor);
        } else {
          im.drawFastHLine(233, 315 - y, 4, (y > 10 && y >= fallingCounter && y < fallingCounter + FFT_VUPeakHeight) ? FFT_VUPeakColor : FFT_VUBarsBackColor);
        }
      }

      // markers
      if (dB != dBPre) {
        if (dB == 6.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 5.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 4.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 3.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 2.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 1.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == 0.0f) {
          im.drawFastHLine(233, 315 - y, 4, RGB565_Red);
        }
        if (dB == -5.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -10.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -15.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -20.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -25.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -30.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -35.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        if (dB == -40.0f) {
          im.drawFastHLine(233, 315 - y, 4, FFT_VUMarkerColor);
        }
        dBPre = dB;
      }
    }
    return barVal;
  }
  return 0;
}
