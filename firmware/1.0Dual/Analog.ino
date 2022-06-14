/// <summary>
/// initialize display
/// </summary>
void displayInitAnalog() {
  int cnt7 = millis();

  // refresh: 240, frames: 120
  tft.setRefreshRate(240);
  tft.setVSyncSpacing(2);

  // queue not needed
  queueStop();

  dBPPML = -100;
  dBPPMR = -100;

  // set rotation
  (flipScreen) ? tft.setRotation(2) : tft.setRotation(0);
  tft.setScroll((flipScreen) ? 320 - ANALOG_Offset : ANALOG_Offset);

  // get color from middle of the backgound picture
  uint16_t bgColor = getBackgroundColor(ANALOG_Mode);

  // fill display with black, white or warm color
  bg.fillScreen((ANALOG_ShowA700Frame) ? RGB565_Black : bgColor);

  // copy background image to backbuffer and set backgroundcolor
  if (ANALOG_Mode == 0) memcpy(backBuffer, analog_black, 153600);
  if (ANALOG_Mode == 1) memcpy(backBuffer, analog_white, 153600);
  if (ANALOG_Mode == 2) memcpy(backBuffer, analog_warm, 153600);

  // A700 frame
  if (ANALOG_ShowA700Frame) {
    bg.fillRect(0, 0, 240, 26 + 7, RGB565_Black);
    bg.fillRect(0, 320 - 7, 240, 7, RGB565_Black);
    fillRoundRect(bg, 0, 26, 240, 294, 7, bgColor, false);
  }

  // show the calibration frame
  if (showCalibrationFrame) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Magenta);

  // send Calibration data
  if (calibrate) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Red);

  // copy background to front
  memcpy(frontBuffer, backBuffer, 153600);

  // initialize Needles
  drawAnalog(true);


  cnt7 = millis();
  Serial.printf("time passed:%d\n", cnt7 - millis());
}

/// <summary>
/// draw needles and update framebuffer
/// </summary>
void drawAnalog(boolean init) {
  // copy background from line 54 to 234 and bring to front
  memcpy(frontBuffer + 12960, backBuffer + 12960, 112320);

  //while(1);
  drawNeedleLeft(init);
  drawNeedleRight(init);
  tft.update(frontBuffer, false);

}

/// <summary>
/// draw left Side
/// </summary>
/// <param name="init"></param>
void drawNeedleLeft(boolean init) {
  static elapsedMillis peakLEDTime = 0;
  static bool peakLEDTrigger = false;
  static float pastData = 0.0f;

  // handle peak LED
  if (peakLEDTime <= 500 && peakLEDTrigger) {
    im.drawSpot(iVec2(20, 153 + 19), 7.0f, ANALOG_PeakLEDColor, 1.0f);
  } else {
    peakLEDTrigger = false;
  }

  // init?
  if (init && (pastData < 1.0f || pastData > 2.15f)) pastData = 1.1f;

  // if RMS & PPM available or init
  if (rms1.available() || init) {
    // read RMS, convert to dB, convert dB to radians (rotate arc for left side)
    float arc = PI - dBToRAD(rmsAmplitudeTodB(rms1.read(), 0), -40.0f, 7.0f);

    // peak LED ON
    if ((20.0f * log10f(peak1.read() * 2.0f) + 3.0f) >= (float)ANALOG_PeakLEDdB) {
      peakLEDTrigger = true;
      peakLEDTime = 0;
    }

    // ballistic
    float pastArc = pastData; (pastData - arc < 0) ? arc = pastArc + (ANALOG_NeedleAttack / 1000.0f) : arc = pastArc - (ANALOG_NeedleRelease / 1000.0f); pastData = arc;

    // draw needle
    if (arc != pastArc) {
      float x1 = -115.0f + 193.0f * sinf(arc);
      float y1 = (160.0f + 14.0f) + 193.0f * cosf(arc);
      float yEdge = (160.0f + 13.0f) + 115.0f * cosf(arc);
      im.drawWedgeLine(0.0f, yEdge, x1, y1, 3.0f, 3.0f, ANALOG_NeedleColor, 1.0f);
    }
  }
}

/// <summary>
/// draw right side
/// </summary>
/// <param name="init"></param>
void drawNeedleRight(boolean init) {
  static elapsedMillis peakLEDTime = 0;
  static bool peakLEDTrigger = false;
  static float pastData = 0.0f;

  // handle peak LED
  if (peakLEDTime <= 500 && peakLEDTrigger) {
    im.drawSpot(iVec2(220, 153 + 19), 7.0f, ANALOG_PeakLEDColor, 1.0f);
  } else {
    peakLEDTrigger = false;
  }

  // init?
  if (init && (pastData < 1.0f || pastData > 2.15f)) pastData = 2.16f;

  // if RMS & PPM available or init
  if (rms2.available() || init) {
    // read RMS, convert to dB, convert dB to radians
    float arc = dBToRAD(rmsAmplitudeTodB(rms2.read(), 1), -40.0f, 7.0f);

    // peak LED ON
    if (20.0f * log10f(peak2.read() * 2.0f) + 3.0f >= (float)ANALOG_PeakLEDdB) {
      peakLEDTrigger = true;
      peakLEDTime = 0;
    }

    // ballistic
    float pastArc = pastData; (pastData - arc < 0) ? arc = pastArc + (ANALOG_NeedleRelease / 1000.0f) : arc = pastArc - (ANALOG_NeedleAttack / 1000.0f); pastData = arc;

    // draw needle
    if (arc != pastArc) {
      float x1 = 355.0f - 193.0f * sinf(arc);
      float y1 = (160.0f + 13.0f) - 193.0f * cosf(arc);
      float yEdge = (160.0f + 13.0f) - 115.0f * cosf(arc);
      im.drawWedgeLine(240.0f, yEdge, x1, y1, 3.0f, 3.0f, ANALOG_NeedleColor, 1.0f);
    }
  }
}

//*******************************************



void display2InitAnalog() {

  // refresh: 240, frames: 120
  tft1.setRefreshRate(240);
  tft1.setVSyncSpacing(2);

  dBPPML = -100;
  dBPPMR = -100;

  // set rotation
  (flipScreen) ? tft1.setRotation(2) : tft1.setRotation(0);
  tft1.setScroll((flipScreen) ? 320 - ANALOG_Offset : ANALOG_Offset);

  // get color from middle of the backgound picture
  uint16_t bgColor = getBackgroundColor(ANALOG_Mode);

  // fill display with black, white or warm color
  bg1.fillScreen((ANALOG_ShowA700Frame) ? RGB565_Black : bgColor);

  // copy background image to backbuffer and set backgroundcolor
  if (ANALOG_Mode == 0) memcpy(backBuffer1, analog_black, 153600);
  if (ANALOG_Mode == 1) memcpy(backBuffer1, analog_white, 153600);
  if (ANALOG_Mode == 2) memcpy(backBuffer1, analog_warm, 153600);

  // A700 frame
  if (ANALOG_ShowA700Frame) {
    bg1.fillRect(0, 0, 240, 26 + 7, RGB565_Black);
    bg1.fillRect(0, 320 - 7, 240, 7, RGB565_Black);
    fillRoundRect(bg1, 0, 26, 240, 294, 7, bgColor, false);
  }

  // show the calibration frame
  if (showCalibrationFrame) bg1.drawRoundRect(0, 26, 240, 294, 7, RGB565_Magenta);

  // send Calibration data
  if (calibrate) bg1.drawRoundRect(0, 26, 240, 294, 7, RGB565_Red);

  // copy background to front
  memcpy(frontBuffer1, backBuffer1, 153600);

  // initialize Needles
  drawAnalog2(true);

}



/// <summary>
/// draw needles and update framebuffer
/// </summary>
void drawAnalog2(boolean init) {
  // copy background from line 54 to 234 and bring to front
  //   memcpy(frontBuffer1 , analog_black_back , 153600);
  memcpy(frontBuffer1 + 12960, backBuffer1 + 12960, 112320);
  drawNeedleLeft2(init);
  drawNeedleRight2(init);
  tft1.update(frontBuffer1, false);
}

/// <summary>
/// draw left Side
/// </summary>
/// <param name="init"></param>
void drawNeedleLeft2(boolean init) {
  static elapsedMillis peakLEDTime = 0;
  static bool peakLEDTrigger = false;
  static float pastData = 0.0f;

  // handle peak LED
  if (peakLEDTime <= 500 && peakLEDTrigger) {
    im1.drawSpot(iVec2(20, 153 + 19), 7.0f, ANALOG_PeakLEDColor, 1.0f);
  } else {
    peakLEDTrigger = false;
  }

  // init?
  if (init && (pastData < 1.0f || pastData > 2.15f)) pastData = 1.1f;

  // if RMS & PPM available or init
  if (rms1.available() || init) {
    // read RMS, convert to dB, convert dB to radians (rotate arc for left side)
    float arc = PI - dBToRAD(rmsAmplitudeTodB(rms1.read(), 0), -40.0f, 7.0f);

    // peak LED ON
    if ((20.0f * log10f(peak1.read() * 2.0f) + 3.0f) >= (float)ANALOG_PeakLEDdB) {
      peakLEDTrigger = true;
      peakLEDTime = 0;
    }

    // ballistic
    float pastArc = pastData; (pastData - arc < 0) ? arc = pastArc + (ANALOG_NeedleAttack / 1000.0f) : arc = pastArc - (ANALOG_NeedleRelease / 1000.0f); pastData = arc;

    // draw needle
    if (arc != pastArc) {
      float x1 = -115.0f + 193.0f * sinf(arc);
      float y1 = (160.0f + 14.0f) + 193.0f * cosf(arc);
      float yEdge = (160.0f + 13.0f) + 115.0f * cosf(arc);
      im1.drawWedgeLine(0.0f, yEdge, x1, y1, 3.0f, 3.0f, ANALOG_NeedleColor, 1.0f);
    }
  }
}

/// <summary>
/// draw right side
/// </summary>
/// <param name="init"></param>
void drawNeedleRight2(boolean init) {
  static elapsedMillis peakLEDTime = 0;
  static bool peakLEDTrigger = false;
  static float pastData = 0.0f;

  // handle peak LED
  if (peakLEDTime <= 500 && peakLEDTrigger) {
    im1.drawSpot(iVec2(220, 153 + 19), 7.0f, ANALOG_PeakLEDColor, 1.0f);
  } else {
    peakLEDTrigger = false;
  }

  // init?
  if (init && (pastData < 1.0f || pastData > 2.15f)) pastData = 2.16f;

  // if RMS & PPM available or init
  if (rms2.available() || init) {
    // read RMS, convert to dB, convert dB to radians
    float arc = dBToRAD(rmsAmplitudeTodB(rms2.read(), 1), -40.0f, 7.0f);

    // peak LED ON
    if (20.0f * log10f(peak2.read() * 2.0f) + 3.0f >= (float)ANALOG_PeakLEDdB) {
      peakLEDTrigger = true;
      peakLEDTime = 0;
    }

    // ballistic
    float pastArc = pastData; (pastData - arc < 0) ? arc = pastArc + (ANALOG_NeedleRelease / 1000.0f) : arc = pastArc - (ANALOG_NeedleAttack / 1000.0f); pastData = arc;

    // draw needle
    if (arc != pastArc) {
      float x1 = 355.0f - 193.0f * sinf(arc);
      float y1 = (160.0f + 13.0f) - 193.0f * cosf(arc);
      float yEdge = (160.0f + 13.0f) - 115.0f * cosf(arc);
      im1.drawWedgeLine(240.0f, yEdge, x1, y1, 3.0f, 3.0f, ANALOG_NeedleColor, 1.0f);
    }
  }
}
