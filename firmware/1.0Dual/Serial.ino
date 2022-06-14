/// <summary>
/// get data from serial input
/// input text in the form "123 456\n"
/// </summary>
void getFromSerial() {

    static int past_val1 = 99;
    static int past_val2 = 99;

    // room for 19 characters plus terminating null
    static char instring[20];
    // location in the array
    static int spos = 0;
    int val1 = 0;
    int val2 = 0;

    if (Serial.available()) {
        char* bita, * bitb;
        int c = Serial.read();
        switch (c) {
        case '\r': break; // ignore
        case '\n':
            spos = 0;
            bita = strtok(instring, " ");
            bitb = strtok(NULL, " ");
            if (bita && bitb) {
                val1 = atoi(bita);
                val2 = atoi(bitb);
            }
            break;
        default:
            if (spos < 18) {
                instring[spos++] = c;
                instring[spos] = 0;
            }
        }

        if (val1 != past_val1 || val2 != past_val2) {
            past_val1 = val1;
            past_val2 = val2;

            switch (val1) {
            case 1: // FlipScreen
                flipScreen = (bool)val2;
                initalizeDisplayFromModuleType(moduleType);
                break;

            case 3: // ShowCalibrationFrame
                showCalibrationFrame = (bool)val2;
                initalizeDisplayFromModuleType(moduleType);
                break;

            case 4: // offset DIGITAL
                DIGITAL_Offset = val2;
                tft.setScroll((flipScreen) ? 320 - DIGITAL_Offset : DIGITAL_Offset);
                break;

            case 6: // offset ANALOG
                ANALOG_Offset = val2;
                tft.setScroll((flipScreen) ? 320 - ANALOG_Offset : ANALOG_Offset);
                break;

            case 8: // offset SPECTRUMANALYZER
                FFT_Offset = val2;
                tft.setScroll((flipScreen) ? 320 - FFT_Offset : FFT_Offset);
                break;

            case 10: // offset GONIO
                GONIO_Offset = val2;
                tft.setScroll((flipScreen) ? 320 - GONIO_Offset : GONIO_Offset);
                break;

                //////////////////////////////////////

            case 20: // module type
                moduleType = val2;
                initalizeDisplayFromModuleType(moduleType);
                break;

                //////////////////////////////////////

            case 22: // calibration mode
                calibrate = val2;
                initalizeDisplayFromModuleType(moduleType);
                break;

                //////////////////////////////////////

            case 30: // ShowA700Frame DIGITAL
                DIGITAL_ShowA700Frame = (bool)val2;
                displayInitDigital(false);
                break;

            case 32: // ShowA700Frame ANALOG
                ANALOG_ShowA700Frame = (bool)val2;
                displayInitAnalog();
                break;

            case 34: // ShowA700Frame SPECTRUMANALYZER
                FFT_ShowA700Frame = (bool)val2;
                displayInitFFT(false);
                break;

            case 36: // ShowA700Frame GONIO
                GONIO_ShowA700Frame = (bool)val2;
                displayInitGonio(false);
                break;

                //////////////////////////////////////

            case 100: // up
                IR_Up = (uint32_t)val2;
                break;

            case 110: // left
                IR_Left = (uint32_t)val2;
                break;

            case 120: // right
                IR_Right = (uint32_t)val2;
                break;

            case 130: // down
                IR_Down = (uint32_t)val2;
                break;

            case 140: // play/stop
                IR_PlayStop = (uint32_t)val2;
                break;

            case 150: // menu
                IR_Menu = (uint32_t)val2;
                break;

            case 160: // remote control type
                rcType = val2;
                break;

                //////////////////////////////////////

            case 200: // RMS_Correction_Left
                RMSCorrectionLeft = val2;
                break;

            case 210: // RMS_Correction_Right
                RMSCorrectionRight = val2;
                break;

            case 220: // PPM_Correction_Left
                PPMCorrectionLeft = val2;
                break;

            case 230: // PPM_Correction_Right
                PPMCorrectionRight = val2;
                break;

                //////////////////////////////////////

            case 504: // WorkMode
                DIGITAL_WorkMode = (int16_t)val2;
                setMode(true);
                break;

            case 506: // UseWheel
                DIGITAL_UseWheel = (bool)val2;
                break;

            case 508: // ShowHeader
                DIGITAL_ShowHeader = (bool)val2;
                displayInitDigital(false);
                break;

            case 510: // ShowPeakBars
                DIGITAL_ShowPeakBars = (bool)val2;
                break;

                //////////////////////////////////////

            case 512: // VUBarAttack
                DIGITAL_VUBarAttack = val2;
                break;

            case 514: // VUBarRelease
                DIGITAL_VUBarRelease = val2;
                break;

            case 516: // VUPeakHoldTime
                DIGITAL_VUPeakHoldTime = val2;
                break;

            case 518: // VUPeakRelease
                DIGITAL_VUPeakRelease = val2;
                break;

            case 520: // PEAKBarAttack
                DIGITAL_PEAKBarAttack = val2;
                break;

            case 522: // PEAKBarRelease
                DIGITAL_PEAKBarRelease = val2;
                break;

            case 524: // PEAKPeakHoldTime
                DIGITAL_PEAKPeakHoldTime = val2;
                break;

            case 526: // PEAKPeakReleas
                DIGITAL_PEAKPeakRelease = val2;
                break;

                //////////////////////////////////////

            case 528: // VUPeakHeight
                DIGITAL_VUPeakHeight = val2;
                break;

            case 530: // VUSegmentHeight
                DIGITAL_VUSegmentHeight = val2;
                break;

            case 532: // PEAKPeakHeight
                DIGITAL_PEAKPeakHeight = val2;
                break;

            case 534: // PEAKSegmentHeigh
                DIGITAL_PEAKSegmentHeight = val2;
                break;

                //////////////////////////////////////

            case 536: // DisplayBackColor
                DIGITAL_DisplayBackColor = val2;
                displayInitDigital(false);
                break;

            case 538: // LRColor
                DIGITAL_LRColor = val2;
                displayInitDigital(false);
                break;

            case 540: // HeaderForeColor
                DIGITAL_HeaderForeColor = val2;
                displayInitDigital(false);
                break;

            case 542: // ScaleForeColor
                DIGITAL_ScaleForeColor = val2;
                displayInitDigital(false);
                break;

            case 544: // ScaleMarkerColor
                DIGITAL_ScaleMarkerColor = val2;
                displayInitDigital(false);
                break;

            case 546: // LineColor
                DIGITAL_LineColor = val2;
                displayInitDigital(false);
                break;

            case 548: // LineColor
                DIGITAL_VUNullDBMarkerColor = val2;
                break;

            case 550: // VUPeakColor
                DIGITAL_VUPeakColor = val2;
                break;

            case 552: // VUBarColorNormal
                DIGITAL_VUBarColorNormal = val2;
                break;

            case 554: // VUBarColorMid
                DIGITAL_VUBarColorMid = val2;
                break;

            case 556: // VUBarColorOver
                DIGITAL_VUBarColorOver = val2;
                break;

            case 558: // PEAKPeakColor
                DIGITAL_PEAKPeakColor = val2;
                break;

            case 560: // PEAKBarColor
                DIGITAL_PEAKBarColor = val2;
                break;

            case 562: // CorrelationTextColor
                DIGITAL_CorrelationTextColor = val2;
                displayInitDigital(false);
                break;

            case 564: // CorrelationMinusColor
                DIGITAL_CorrelationMinusColor = val2;
                break;

            case 566: // CorrelationNullColor
                DIGITAL_CorrelationNullColor = val2;
                break;

            case 568: // CorrelationPlusColor
                DIGITAL_CorrelationPlusColor = val2;
                break;

            case 570: // CorrelationBackgroundColor
                DIGITAL_CorrelationBackgroundColor = val2;
                break;

            case 572: // CorrelationMarkerColor
                DIGITAL_CorrelationMarkerColor = val2;
                displayInitDigital(false);
                break;

            case 574: // CorrelationHoldColor
                DIGITAL_CorrelationHoldColor = val2;
                break;

            case 576: // CorrelationHoldBackgroundColor
                DIGITAL_CorrelationHoldBackgroundColor = val2;
                break;

            case 578: // LineMarkerColor
                DIGITAL_LineMarkerColor = val2;
                displayInitDigital(false);
                break;

            case 590: // PeakAttenuation
                DIGITAL_PeakAttenuation = val2 / 1000.0f;
                break;

                //////////////////////////////////////

            case 604: // ScalaMode
                ANALOG_Mode = (int16_t)val2;
                displayInitAnalog();
                break;

            case 606: // NeedleAttack
                ANALOG_NeedleAttack = val2;
                break;

            case 608: // NeedleRelease
                ANALOG_NeedleRelease = val2;
                break;

            case 610: // PeakLEDdB
                ANALOG_PeakLEDdB = val2;
                break;

            case 612: // PeakLEDHoldTime
                ANALOG_PeakLEDHoldTime = val2;
                break;

            case 614: // PeakLEDColor
                ANALOG_PeakLEDColor = val2;
                break;

            case 616: // NeedleColor
                ANALOG_NeedleColor = val2;
                break;

                //////////////////////////////////////

            case 704: // BarMode
                FFT_BarMode = (int16_t)val2;
                displayInitFFT(false);
                break;

            case 706: // WorkMode
                FFT_WorkMode = (int16_t)val2;
                setMode(true);
                break;

            case 708: // UseWheel
                FFT_UseWheel = (bool)val2;
                break;

                //////////////////////////////////////

            case 710: // VUBarAttack
                FFT_VUBarAttack = val2;
                break;

            case 712: // VUBarRelease
                FFT_VUBarRelease = val2;
                break;

            case 714: // VUPeakHoldTime
                FFT_VUPeakHoldTime = val2;
                break;

            case 716: // VUPeakRelease
                FFT_VUPeakRelease = val2;
                break;

            case 718: // FFTBarAttack
                FFT_FFTBarAttack = val2;
                break;

            case 720: // FFTBarRelease
                FFT_FFTBarRelease = val2;
                break;

            case 722: // FFTPeakHoldTime
                FFT_FFTPeakHoldTime = val2;
                break;

            case 724: // FFTPeakRelease
                FFT_FFTPeakRelease = val2;
                break;

                // todo: sorting!
            case 770: // PEAKBarAttack
                FFT_PEAKBarAttack = val2;
                break;

            case 772: // PEAKBarRelease
                FFT_PEAKBarRelease = val2;
                break;

            case 774: // PEAKPeakHoldTime
                FFT_PEAKPeakHoldTime = val2;
                break;

            case 776: // PEAKPeakRelease
                FFT_PEAKPeakRelease = val2;
                break;

                //////////////////////////////////////

            case 726: // VUPeakHeight
                FFT_VUPeakHeight = val2;
                break;

            case 728: // VUSegmentHeight
                FFT_VUSegmentHeight = val2;
                break;

            case 730: // FFTPeakHeight
                FFT_FFTPeakHeight = val2;
                break;

            case 732: // FFTSegmentHeight
                FFT_FFTSegmentHeight = val2;
                break;

                //////////////////////////////////////

            case 734: // DisplayBackColor
                FFT_DisplayBackColor = val2;
                displayInitFFT(false);
                break;

            case 736: // VUBarsBackColor
                FFT_VUBarsBackColor = val2;
                displayInitFFT(false);
                break;

            case 738: // FFTBarColor
                FFT_FFTBarColor = val2;
                break;

            case 740: // VUBarColorNormal
                FFT_VUBarColorNormal = val2;
                break;

            case 742: // VUBarColorMid
                FFT_VUBarColorMid = val2;
                break;

            case 744: // VUBarColorOver
                FFT_VUBarColorOver = val2;
                break;

            case 746: // FFTPeakColor
                FFT_FFTPeakColor = val2;
                break;

            case 748: // VUPeakColor
                FFT_VUPeakColor = val2;
                break;

            case 750: // VUMarkerColor
                FFT_VUMarkerColor = val2;
                displayInitFFT(false);
                break;

            case 752: // LRColor
                FFT_LRColor = val2;
                displayInitFFT(false);
                break;

            case 754: // HeaderForeColor
                FFT_HeaderForeColor = val2;
                displayInitFFT(false);
                break;

            case 756: // ScaleForeColor
                FFT_ScaleForeColor = val2;
                displayInitFFT(false);
                break;

            case 758: // ScaleBackgroundColor
                FFT_ScaleBackgroundColor = val2;
                displayInitFFT(false);
                break;

            case 760: // LineColor
                FFT_LineColor = val2;
                displayInitFFT(false);
                break;

                //////////////////////////////////////

            case 790: // PeakAttenuation
                FFT_PeakAttenuation = val2 / 1000.0f;
                break;

                //////////////////////////////////////

            case 800: // ShowSamplesCount
                GONIO_ShowSamplesCount = (bool)val2;
                displayInitGonio(false);
                break;

            case 802: // Samples
                GONIO_Samples = val2;
                displayInitGonio(false);
                break;

            case 804: // DrawMode
                GONIO_DrawMode = (int16_t)val2;
                break;

            case 806: // WorkMode
                GONIO_WorkMode = (int16_t)val2;
                setMode(true);
                break;

            case 808: // SwapX
                GONIO_SwapX = (bool)val2;
                break;

            case 810: // SwapY
                GONIO_SwapY = (bool)val2;
                break;

                //////////////////////////////////////

            case 812: // VUBarAttack
                GONIO_VUBarAttack = val2;
                break;

            case 814: // VUBarRelease
                GONIO_VUBarRelease = val2;
                break;

            case 816: // PEAKBarAttack
                GONIO_PEAKBarAttack = val2;
                break;

            case 818: //PEAKBarRelease
                GONIO_PEAKBarRelease = val2;
                break;

            case 820: // VUPeakHoldTime
                GONIO_VUPeakHoldTime = val2;
                break;

            case 822: // PEAKPeakHoldTime
                GONIO_PEAKPeakHoldTime = val2;
                break;

            case 824: // VUPeakRelease
                GONIO_VUPeakRelease = val2;
                break;

            case 826: // PEAKPeakRelease
                GONIO_PEAKPeakRelease = val2;
                break;

                //////////////////////////////////////

            case 828: // PeakHeight
                GONIO_PeakHeight = val2;
                break;

            case 830: // SegmentHeight
                GONIO_SegmentHeight = val2;
                break;

                //////////////////////////////////////

            case 832: // DisplayBackColor
                GONIO_DisplayBackColor = val2;
                displayInitGonio(false);
                break;

            case 834: // LRColor
                GONIO_LRColor = val2;
                displayInitGonio(false);
                break;

            case 836: // HeaderForeColor
                GONIO_HeaderForeColor = val2;
                displayInitGonio(false);
                break;

            case 838: // ScaleForeColor
                GONIO_ScaleForeColor = val2;
                displayInitGonio(false);
                break;

            case 842: // MarkerColor
                GONIO_MarkerColor = val2;
                displayInitGonio(false);
                break;

            case 844: // PeakColor
                GONIO_PeakColor = val2;
                break;

            case 846: // BarColorNormal
                GONIO_BarColorNormal = val2;
                break;

            case 848: // BarColorMid
                GONIO_BarColorMid = val2;
                break;

            case 850: // BarColorOver
                GONIO_BarColorOver = val2;
                break;

            case 852: // BarsBackColor
                GONIO_BarsBackColor = val2;
                break;

            case 854: // GoniometerColor
                GONIO_GoniometerColor = val2;
                break;

            case 856: // CorrelationTextColor
                GONIO_CorrelationTextColor = val2;
                displayInitGonio(false);
                break;

            case 858: // CorrelationMinusColor
                GONIO_CorrelationMinusColor = val2;
                break;

            case 860: // CorrelationNullColor
                GONIO_CorrelationNullColor = val2;
                break;

            case 862: // CorrelationPlusColor
                GONIO_CorrelationPlusColor = val2;
                break;

            case 864: // CorrelationBackgroundColor
                GONIO_CorrelationBackgroundColor = val2;
                displayInitGonio(false);
                break;

            case 866: // CorrelationMarkerColor
                GONIO_CorrelationMarkerColor = val2;
                displayInitGonio(false);
                break;

            case 868: // CorrelationHoldColor
                GONIO_CorrelationHoldColor = val2;
                break;

            case 870: // CorrelationHoldBackgroundColor
                GONIO_CorrelationHoldBackgroundColor = val2;
                break;

            case 872: // CrossColor
                GONIO_CrossColor = val2;
                displayInitGonio(false);
                break;

            case 890: // PeakAttenuation
                GONIO_PeakAttenuation = val2 / 1000.0f;
                break;

                //////////////////////////////////////

            case 1000: // answer from Teensy awaiting
                if (val2 == 1000) {
                    getControllerInfos();
                }
                break;

                //////////////////////////////////////

            case 1008: // save DIGITAL settings
                if (val2 == 1008) {
                    writeGLOBALConfig();
                    writeDIGITALConfig();
                    Serial.print("{[success]Configuration for digital meter successfully saved.}");
                }
                break;

            case 1009: // save ANALOG settings
                if (val2 == 1009) {
                    writeGLOBALConfig();
                    writeANALOGConfig();
                    Serial.print("{[success]Configuration for analog gauges successfully saved.}");
                }
                break;

            case 1010: // save FFT settings
                if (val2 == 1010) {
                    writeGLOBALConfig();
                    writeFFTConfig();
                    Serial.print("{[success]Configuration for spectrum analyzer successfully saved.}");
                }
                break;

            case 1011: // save GONIO settings
                if (val2 == 1011) {
                    writeGLOBALConfig();
                    writeGONIOConfig();
                    Serial.print("{[success]Configuration for goniometer successfully saved.}");
                }
                break;

            case 1013: // save REMOTECONTROL settings
                if (val2 == 1013) {
                    writeREMOTECONTROLConfig();
                    Serial.print("{[success]Configuration for remote control successfully saved.}");
                }
                break;

            case 1014: // save dB correction settings
                if (val2 == 1014) {
                    writeDBCorrection();
                    Serial.print("{[success]Configuration for dB correction successfully saved.}");
                }
                break;

                //////////////////////////////////////

            case 6666: // get dB correction data
                if (val2 == 6666) {
                    getDBCorrectionData();
                }
                break;

            case 7777: // get configuration infos
                if (val2 == 7777) {
                    getConfigurationInfos();
                }
                break;

            case 8888: // take a screenShot from frontbuffer
                if (val2 == 8888) {
                    takeScreenshot();
                }
                break;
            }
        }
    }
  
}
