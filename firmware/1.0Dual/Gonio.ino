/// <summary>
/// initialize display
/// </summary>
/// <param name="reset"></param>
void displayInitGonio(bool reset) {
    // refresh: 200, frames: 100
    tft.setRefreshRate(200);
    tft.setVSyncSpacing(2);

    setMode(false);
    setSampleBlocks();
    queueStart();

    (flipScreen) ? tft.setRotation(2) : tft.setRotation(0);
    tft.setScroll((flipScreen) ? 320 - GONIO_Offset : GONIO_Offset);

    // fill screen
    bg.fillScreen(GONIO_ShowA700Frame ? RGB565_Black : GONIO_DisplayBackColor);

    // show the A700 frame
    if (GONIO_ShowA700Frame) bg.fillRoundRect(0, 26, 240, 294, 7, GONIO_DisplayBackColor);

    // cross
    bg.drawLine(116, 169, 200, 85, GONIO_CrossColor);
    bg.drawLine(104, 181, 20, 265, GONIO_CrossColor);
    bg.drawLine(104, 169, 20, 85, GONIO_CrossColor);
    bg.drawLine(116, 181, 200, 265, GONIO_CrossColor);

    // make cross dotted smart
    for (uint16_t y = 75; y < 275; y += 4)
        bg.fillRect(15, y, 195, 2, GONIO_DisplayBackColor);

    // labels
    bg.drawText("M", iVec2(104, 44), GONIO_HeaderForeColor, Arial_12_Bold, false);
    bg.drawText("L", iVec2(29, 64), GONIO_LRColor, Arial_16, false);
    bg.drawText("R", iVec2(175, 64), GONIO_LRColor, Arial_16, false);

    // samples count
    char buf[12];
    sprintf(buf, "%d SAMPLES", GONIO_SampleBlocks * 128);
    if (GONIO_ShowSamplesCount) drawTextCenterX(bg, buf, 61, 220, GONIO_HeaderForeColor, Arial_8);

    // show the calibration frame
    if (showCalibrationFrame) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Magenta);

    // send calibration data
    if (calibrate) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Red);

    // write descriptions over bars
    bg.drawText((GONIO_BarMode == 0 /*PPM*/) ? "PPM" : "RMS", (GONIO_BarMode == 0 /*PPM*/) ? iVec2(216, 36) : iVec2(215, 36), GONIO_HeaderForeColor, Arial_8, false);

    // write bar 'dB' description
    float dBPre = 0.0f;
    for (uint16_t y = 0; y < 275; y++) {
        float dB = roundf((float)map(y, 0, 275, GONIO_dBLow, 6.0f));
        if (dB != dBPre) {
            if (dB == 6) { bg.drawText("6", iVec2(223, 319 - y), RGB565_Red, Arial_8, false); }
            if (dB == 3) { bg.drawText("3", iVec2(223, 319 - y), RGB565_Red, Arial_8, false); }
            if (dB == 0) { bg.drawText("0", iVec2(223, 319 - y), RGB565_Red, Arial_8, false); }
            if (dB == -5) { bg.drawText("5", iVec2(223, 319 - y), GONIO_ScaleForeColor, Arial_8, false); }
            if (dB == -10) { bg.drawText("10", iVec2(220, 319 - y), GONIO_ScaleForeColor, Arial_8, false); }
            if (dB == -20) { bg.drawText("20", iVec2(220, 319 - y), GONIO_ScaleForeColor, Arial_8, false); }
            if (dB == -30) { bg.drawText("30", iVec2(220, 319 - y), GONIO_ScaleForeColor, Arial_8, false); }
            if (dB == -40) { bg.drawText("40", iVec2(220, 319 - y), GONIO_ScaleForeColor, Arial_8, false); }
            dBPre = dB;
        }
    }

    /* CORRELATION SECTION
     * *************************************************/
    drawTextCenterX(bg, "CORRELATION", 298, 220, GONIO_ScaleForeColor, Arial_8);

    // draw correlation backgrounds
    bg.fillRect(30, 304, 161, 8, GONIO_CorrelationBackgroundColor);
    bg.drawFastHLine(30, 316, 161, GONIO_CorrelationHoldBackgroundColor);

    // draw correlation frame marker
    bg.drawFastVLine(29, 304, 8, GONIO_CorrelationMarkerColor);
    bg.drawFastVLine(191, 304, 8, GONIO_CorrelationMarkerColor);
    bg.drawFastVLine(29, 315, 3, GONIO_CorrelationMarkerColor);
    bg.drawFastVLine(110, 315, 3, GONIO_CorrelationTextColor);
    bg.drawFastVLine(191, 315, 3, GONIO_CorrelationMarkerColor);

    // correlation -1/+1
    bg.drawText("-1", iVec2(13, 316), GONIO_CorrelationTextColor, Arial_10, false);
    bg.drawText("+1", iVec2(194, 316), GONIO_CorrelationTextColor, Arial_10, false);

    // draw middle marker
    bg.drawFastVLine(110, 304, 8, GONIO_CorrelationTextColor);
    bg.drawFastVLine(110, 315, 3, GONIO_CorrelationTextColor);

    // copy background to front
    memcpy(frontBuffer, backBuffer, 153600);
    drawGonio(reset);
    tft.update(frontBuffer, true);

Serial.print ("image kopied form frontbuffer in gonio = {\n");
for (int n=0;n<(320*240);n++){
  Serial.printf("0x%04x, ", frontBuffer[n]);
  if ((n+1)%16==0) {
    Serial.printf("  // 0x%04x  (%d) pixels\n",n+1,n+1);
  }
}
Serial.print ( "einde\n");




    
}

/// <summary>
/// all draws & update framebuffer
/// </summary>
/// <param name="reset"></param>
void drawGonio(bool reset) {
    getSamples(GONIO_SampleBlocks);
    drawGonioAndCorrelation(drawLeftBarGonio(reset) + drawRightBarGonio(reset), reset);
    tft.update(frontBuffer, false);
}

/// <summary>
/// draw left bar
/// </summary>
/// <param name="reset"></param>
/// <returns>bar length</returns>
uint16_t drawLeftBarGonio(bool reset) {
    // static vars
    static float dBPre = 0.0f;
    static uint16_t pastVal = 0, holdCounter = 0, fallingCounter = 0, peakHoldMax = 0;

    // clear hold max
    if (reset) peakHoldMax = 0;

    if ((GONIO_BarMode == 0 /*PEAK*/) ? peak1.available() : rms1.available()) {
        // read RMS or PEAK, calculate dB & scale dB range to bar length
        uint16_t barVal = (GONIO_BarMode == 0 /*PEAK*/) ? map(peakAmplitudeTodB(peak1.read(), 0), GONIO_dBLow, dBHigh, 0, 275) : map(rmsAmplitudeTodB(rms1.read(), 0), GONIO_dBLow, dBHigh, 0, 275);

        // get previous bar data
        uint16_t valTmp = pastVal;

        // ballistics
        if (GONIO_BarMode == 0 /*PEAK*/) {
            if (barVal < valTmp - GONIO_PEAKBarRelease) barVal = valTmp - GONIO_PEAKBarRelease;
            if (valTmp < barVal - GONIO_PEAKBarAttack) barVal = valTmp + GONIO_PEAKBarAttack;
            if (++holdCounter > GONIO_PEAKPeakHoldTime && fallingCounter > GONIO_PEAKPeakRelease) fallingCounter -= GONIO_PEAKPeakRelease; // peak release
        } else {
            if (barVal < valTmp - GONIO_VUBarRelease) barVal = valTmp - GONIO_VUBarRelease;
            if (valTmp < barVal - GONIO_VUBarAttack) barVal = valTmp + GONIO_VUBarAttack;
            if (++holdCounter > GONIO_VUPeakHoldTime && fallingCounter > GONIO_VUPeakRelease) fallingCounter -= GONIO_VUPeakRelease; // peak release
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
            float dB = roundf(map((float)y, 0, 275, GONIO_dBLow, 6.0f));

            uint16_t color = GONIO_BarColorNormal;
            if (dB >= 0.0f) color = GONIO_BarColorOver;
            else if (dB >= -5.0f) color = GONIO_BarColorMid;

            // draw bars
            if (y < pastVal) {
                im.drawFastHLine(214, 315 - y, 4, (GONIO_SegmentHeight == 0) ? color : (y % (GONIO_SegmentHeight + 1) == 0) ? GONIO_DisplayBackColor : color); // bars
            } else {
                if (GONIO_PeakHold) {
                    im.drawFastHLine(214, 315 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + GONIO_PeakHeight) ? GONIO_PeakColor : GONIO_BarsBackColor);
                } else {
                    im.drawFastHLine(214, 315 - y, 4, (y > 10 && y >= fallingCounter && y < fallingCounter + GONIO_PeakHeight) ? GONIO_PeakColor : GONIO_BarsBackColor);
                }
            }

            if (dB != dBPre) {
                if (dB == 6.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 5.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 4.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 3.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 2.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 1.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == 0.0f) { im.drawFastHLine(214, 315 - y, 4, RGB565_Red); }
                if (dB == -5.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -10.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -15.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -20.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -25.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -30.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -35.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -40.0f) { im.drawFastHLine(214, 315 - y, 4, GONIO_MarkerColor); }
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
uint16_t drawRightBarGonio(bool reset) {
    // static vars
    static float dBPre = 0.0f;
    static uint16_t pastVal = 0, holdCounter = 0, fallingCounter = 0, peakHoldMax = 0;

    // clear hold max
    if (reset) peakHoldMax = 0;

    if ((GONIO_BarMode == 0 /*PEAK*/) ? peak2.available() : rms2.available()) {
        // read RMS or PEAK, calculate dB & scale dB range to bar length
        uint16_t barVal = (GONIO_BarMode == 0 /*PEAK*/) ? map(peakAmplitudeTodB(peak2.read(), 0), GONIO_dBLow, dBHigh, 0, 275) : map(rmsAmplitudeTodB(rms2.read(), 0), GONIO_dBLow, dBHigh, 0, 275);

        // get previous bar data
        uint16_t valTmp = pastVal;

        // ballistics
        if (GONIO_BarMode == 0 /*PEAK*/) {
            if (barVal < valTmp - GONIO_PEAKBarRelease) barVal = valTmp - GONIO_PEAKBarRelease;
            if (valTmp < barVal - GONIO_PEAKBarAttack) barVal = valTmp + GONIO_PEAKBarAttack;
            if (++holdCounter > GONIO_PEAKPeakHoldTime && fallingCounter > GONIO_PEAKPeakRelease) fallingCounter -= GONIO_PEAKPeakRelease; // peak release
        } else {
            if (barVal < valTmp - GONIO_VUBarRelease) barVal = valTmp - GONIO_VUBarRelease;
            if (valTmp < barVal - GONIO_VUBarAttack) barVal = valTmp + GONIO_VUBarAttack;
            if (++holdCounter > GONIO_VUPeakHoldTime && fallingCounter > GONIO_VUPeakRelease) fallingCounter -= GONIO_VUPeakRelease; // peak release
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
            float dB = roundf(map((float)y, 0, 275, GONIO_dBLow, 6.0f));

            uint16_t color = GONIO_BarColorNormal;
            if (dB >= 0.0f) color = GONIO_BarColorOver;
            else if (dB >= -5.0f) color = GONIO_BarColorMid;

            // draw bars
            if (y < pastVal) {
                im.drawFastHLine(233, 315 - y, 4, (GONIO_SegmentHeight == 0) ? color : (y % (GONIO_SegmentHeight + 1) == 0) ? GONIO_DisplayBackColor : color); // bars
            } else {
                if (GONIO_PeakHold) {
                    im.drawFastHLine(233, 315 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + GONIO_PeakHeight) ? GONIO_PeakColor : GONIO_BarsBackColor);
                } else {
                    im.drawFastHLine(233, 315 - y, 4, (y > 10 && y >= fallingCounter && y < fallingCounter + GONIO_PeakHeight) ? GONIO_PeakColor : GONIO_BarsBackColor);
                }
            }

            if (dB != dBPre) {
                if (dB == 6.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 5.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 4.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 3.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 2.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 1.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == 0.0f) { im.drawFastHLine(233, 315 - y, 4, RGB565_Red); }
                if (dB == -5.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -10.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -15.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -20.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -25.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -30.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -35.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                if (dB == -40.0f) { im.drawFastHLine(233, 315 - y, 4, GONIO_MarkerColor); }
                dBPre = dB;
            }
        }
        return barVal;
    }
    return 0;
}

/// <summary>
/// draw gonio and correlation
/// </summary>
/// <param name="totalLength"></param>
/// <param name="reset"></param>
void drawGonioAndCorrelation(uint16_t totalLength, bool reset) {
    static uint16_t frame = 0, negativeMax = 0, negativeMaxHold = 0, positiveMax = 0, positiveMaxHold = 0, xPast = 0, yPast = 0;
    static float amp = 1.0f, avgPrev = 0.0f;

    // vars
    uint16_t x = 0, y = 0, corrPos = 0, corrBarLength = 0;
    float xL = 0.0f, xR = 0.0f, xNorm = 0.0f, yL = 0.0f, yR = 0.0f, yNorm = 0.0f, normL = 0.0f, normR = 0.0f, maxAmp = 0.0f, value = 0.0f, runningTotal = 0.0f, maxL = 0.0f, maxR = 0.0f, avg = 0.0f;

    // copy rectangle from back to front
    copyRect(frontBuffer, backBuffer, 0, 64, 213, 224);

    // loop through the samples
    for (uint16_t i = 0; i < GONIO_SampleBlocks * 128; i++) {
        normL = (samplesLeft[i] / 32767.0f) * amp;
        normR = (samplesRight[i] / 32767.0f) * amp;

        // correlation
        runningTotal += cosf((atan2f(normL, normR) - 0.78539816f) * 2.0f);

        // gonio
        xL = normL * 0.70710678f;
        yL = normL * 0.70710678f;

        xR = normR * 0.70710678f;
        yR = normR * 0.70710678f;

        xL *= 0.70710678f;
        yL *= 0.70710678f;
        xR *= 0.70710678f;
        yR *= 0.70710678f;

        xNorm = (xR - xL) / 1.41421356f;
        yNorm = (yR + yL) / 1.41421356f;

        // swap x/y if needed
        (GONIO_SwapX) ? x = 220 - (110 + (xNorm * 150)) : x = 110 + (xNorm * 150);
        (GONIO_SwapY) ? y = 350 - (175 - (yNorm * 150)) : y = 175 - (yNorm * 150);

        // draw lines or cloud pixels in range
        if (x < 213 && y > 64 && y < 288) {
            if (GONIO_DrawMode == 0) {
                im.drawPixel(x, y, GONIO_GoniometerColor);
            } else {
                if (xPast != 0 && yPast != 0) im.drawLine(xPast, yPast, x, y, GONIO_GoniometerColor);
            }

            // store x,y as past position
            xPast = x; yPast = y;
        }

        if (normL > maxL) maxL = normL;
        if (normR > maxR) maxR = normR;
    }

    // correlation avg
    avg = runningTotal / (float)(GONIO_SampleBlocks * 128);

    // autogain
    if (maxL > 1.0f || maxR > 1.0f) {
        maxAmp = maxL > maxR ? maxL : maxR;
        amp -= maxAmp - 1.0f;
    } else if (amp < 40.0f && maxL < 0.9f && maxR < 0.9f) {
        amp += 0.1f;
        if (amp > 40.0f) amp = 40.0f;
    }

    // bars avaiable -> reset clear trigger, not -> reset avg 
    if (totalLength > 0) frame = 0; else avg = 0.0f;

    // ballistics
    value = (abs(avg - avgPrev) > 0.01f) ? (avg > avgPrev) ? avgPrev + 0.01f : avgPrev - 0.01f : avg; avgPrev = value;

    // delimiter
    if (value > 1.0f) value = 1.0f;
    if (value < -1.0f) value = -1.0f;

    // set correlation box color from value and hysteresis
    corrPos = 110.0f + (80.0f * value);
    corrBarLength = abs(80.0f * value);

    // draw correlation background
    //im.fillRect(30, 304, 161, 8, GONIO_CorrelationBackgroundColor);

    // set colors for correlation rectangle and store min/max values for correlation maxhold view
    uint16_t corBox = GONIO_CorrelationNullColor;
    if (corrPos > 110) {
        if (corrPos > 112) corBox = GONIO_CorrelationPlusColor;
        if (corrBarLength > positiveMax) {
            positiveMax = corrBarLength;
            if (positiveMax > positiveMaxHold) positiveMaxHold = positiveMax;
        }
    } else if (corrPos < 110) {
        if (corrPos < 108) corBox = GONIO_CorrelationMinusColor;
        if (corrBarLength > negativeMax) {
            negativeMax = corrBarLength;
            if (negativeMax > negativeMaxHold) negativeMaxHold = negativeMax;
        }
    } else {
        corBox = GONIO_CorrelationNullColor;
    }

    // optical delimiter
    if (corrPos <= 30) corrPos = 30;
    else if (corrPos > 184) corrPos = 184;
    else corrPos -= 3;

    // reset maxhold values after 400 frames
    if ((++frame == 400 && !GONIO_PeakHold) || reset) {
        negativeMax = 0; positiveMax = 0; positiveMaxHold = 0; negativeMaxHold = 0;
        // copy background to front (from line 304 to 317)
        memcpy(frontBuffer + 72960, backBuffer + 72960, 6240);
    } else {
        // draw correlation box and middle marker
        im.fillRect(30, 304, 161, 8, GONIO_CorrelationBackgroundColor);
        im.drawFastVLine(110, 304, 8, GONIO_CorrelationTextColor);
        im.fillRect(corrPos, 304, 7, 8, corBox);
    }

    // draw negative hold correlation
    if (negativeMaxHold > 0) im.drawFastHLine(110 - negativeMaxHold, 316, negativeMaxHold, GONIO_CorrelationHoldColor);

    // draw positive hold correlation
    if (positiveMaxHold > 0) im.drawFastHLine(111, 316, positiveMaxHold, GONIO_CorrelationHoldColor);
}
