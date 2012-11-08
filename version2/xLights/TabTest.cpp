/*
 * ********************************************
 * ********************************************
 * Process Test Panel Events
 * ********************************************
 * ********************************************
 */

void xLightsFrame::SetTestCheckboxes(bool NewValue)
{
    int ChCount = CheckListBoxTestChannels->GetCount();
    for (int i=0; i < ChCount; i++) {
        CheckListBoxTestChannels->Check(i,NewValue);
    }
    CheckChannelList = true;
}

void xLightsFrame::OnButtonTestSelectAllClick(wxCommandEvent& event)
{
    SetTestCheckboxes(true);
}

void xLightsFrame::OnButtonTestClearClick(wxCommandEvent& event)
{
    SetTestCheckboxes(false);
}

void xLightsFrame::OnCheckListBoxTestChannelsToggled(wxCommandEvent& event)
{
    int ChCount = CheckListBoxTestChannels->GetCount();
    int row=event.GetInt();
    bool newval=CheckListBoxTestChannels->IsChecked(row);

    if (CheckListBoxTestChannels->IsSelected(row)) {
        for (int i=0; i < ChCount; i++) {
            if (CheckListBoxTestChannels->IsSelected(i)) CheckListBoxTestChannels->Check(i,newval);
        }
    }

    CheckChannelList = true;
}

void xLightsFrame::GetCheckedItems(wxArrayInt& chArray)
{
    chArray.Clear();
    int maxch = CheckListBoxTestChannels->GetCount();
    for (int ch=0; ch < maxch; ch++) {
        if (CheckListBoxTestChannels->IsChecked(ch)) {
            chArray.Add(ch);
        }
    }
}

void xLightsFrame::TestButtonsOff()
{
    RadioButtonOff->SetValue(true);
    RadioButtonChase->SetValue(false);
    RadioButtonChase3->SetValue(false);
    RadioButtonChase4->SetValue(false);
    RadioButtonChase5->SetValue(false);
    RadioButtonAlt->SetValue(false);
    RadioButtonTwinkle05->SetValue(false);
    RadioButtonTwinkle10->SetValue(false);
    RadioButtonTwinkle25->SetValue(false);
    RadioButtonTwinkle50->SetValue(false);
    RadioButtonShimmer->SetValue(false);
    RadioButtonDim->SetValue(false);

    RadioButtonRgbChaseOff->SetValue(true);
    RadioButtonRgbChase->SetValue(false);
    RadioButtonRgbChase3->SetValue(false);
    RadioButtonRgbChase4->SetValue(false);
    RadioButtonRgbChase5->SetValue(false);
    RadioButtonRgbAlt->SetValue(false);
    RadioButtonRgbTwinkle05->SetValue(false);
    RadioButtonRgbTwinkle10->SetValue(false);
    RadioButtonRgbTwinkle25->SetValue(false);
    RadioButtonRgbTwinkle50->SetValue(false);
    RadioButtonRgbShimmer->SetValue(false);
    RadioButtonRgbDim->SetValue(false);

    RadioButtonRgbCycleOff->SetValue(true);
    RadioButtonRgbCycle3->SetValue(false);
    RadioButtonRgbCycle4->SetValue(false);
    RadioButtonRgbCycle5->SetValue(false);
    RadioButtonRgbCycleMixed->SetValue(false);

    TestFunc=OFF;
}

void xLightsFrame::OnButtonTestLoadClick(wxCommandEvent& event)
{
}

void xLightsFrame::OnButtonTestSaveClick(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonOffSelect(wxCommandEvent& event)
{
    TestFunc=OFF;
}

void xLightsFrame::OnRadioButtonChaseSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=std::numeric_limits<int>::max();
}

void xLightsFrame::OnRadioButtonChase3Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=3;
}

void xLightsFrame::OnRadioButtonChase4Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=4;
}

void xLightsFrame::OnRadioButtonChase5Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=5;
}

void xLightsFrame::OnRadioButtonAltSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=2;
}

void xLightsFrame::OnRadioButtonTwinkle05Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=20;
}

void xLightsFrame::OnRadioButtonTwinkle10Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=10;
}

void xLightsFrame::OnRadioButtonTwinkle25Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=4;
}

void xLightsFrame::OnRadioButtonTwinkle50Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=2;
}

void xLightsFrame::OnRadioButtonShimmerSelect(wxCommandEvent& event)
{
    TestFunc=SHIMMER;
}

void xLightsFrame::OnRadioButtonDimSelect(wxCommandEvent& event)
{
    TestFunc=DIM;
}

// called on each Timer tick while Test dialog is open
void xLightsFrame::OnTimerTest()
{
    static int LastNotebookSelection = -1;
    static int LastBgIntensity,LastFgIntensity,LastBgColor[3],LastFgColor[3],*ShimColor,ShimIntensity;
    static int LastSequenceSpeed;
    static int LastAutomatedTest;
    static long NextSequenceStart = -1;
    static TestFunctions LastFunc = OFF;
    static unsigned int interval, rgbCycle, TestSeqIdx;
    static wxArrayInt chArray,TwinkleState;
    static float frequency;
    int v,BgIntensity,FgIntensity,BgColor[3],FgColor[3];
    unsigned int i;
    bool ColorChange;

    if (!xout) {
        StatusBar1->SetStatusText(_("Testing disabled - Output to Lights is not checked"));
        return;
    }
    wxDateTime TimerStartTime = wxDateTime::UNow();
    wxTimeSpan ts = TimerStartTime - starttime;
    long curtime = ts.GetMilliseconds().ToLong();
    xout->TimerStart(curtime);
    int NotebookSelection = NotebookTest->GetSelection();
    if (NotebookSelection != LastNotebookSelection) {
        LastNotebookSelection = NotebookSelection;
        CheckChannelList = true;
        TestSeqIdx=0;
        TestButtonsOff();
    }
    if (TestFunc != LastFunc) {
        LastFunc = TestFunc;
        rgbCycle=0;
        CheckChannelList = true;
    }

    if (CheckChannelList) {
        // get list of checked channels
        xout->alloff();
        GetCheckedItems(chArray);
        LastSequenceSpeed=-1;
        LastBgIntensity=-1;
        LastFgIntensity=-1;
        LastAutomatedTest=-1;
        for (i=0; i < 3; i++) {
            LastBgColor[i] = -1;
            LastFgColor[i] = -1;
        }
        if (TestFunc == OFF) {
            StatusBar1->SetStatusText(_("All lights off"));
        } else {
            StatusBar1->SetStatusText(wxString::Format(_("Testing %ld channels"),static_cast<long>(chArray.Count())));
        }
        CheckChannelList = false;
    }

    if (TestFunc != OFF && chArray.Count() > 0) switch (NotebookSelection) {
        case 0:
            // standard tests
            v=SliderChaseSpeed->GetValue();  // 0-100
            BgIntensity = SliderBgIntensity->GetValue();
            FgIntensity = SliderFgIntensity->GetValue();
            ColorChange = BgIntensity != LastBgIntensity || FgIntensity != LastFgIntensity;
            LastBgIntensity = BgIntensity;
            LastFgIntensity = FgIntensity;
            interval = 1600 - v*15;

            switch (TestFunc) {
                case DIM:
                    if (ColorChange) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(chArray[i], BgIntensity);
                        }
                    }
                    break;

                case TWINKLE:
                    if (LastSequenceSpeed < 0) {
                        LastSequenceSpeed=0;
                        TwinkleState.Clear();
                        for (i=0; i < chArray.Count(); i++) {
                            TestSeqIdx = static_cast<int>(rand01()*TwinkleRatio);
                            TwinkleState.Add(TestSeqIdx == 0 ? -1 : 1);
                        }
                    }
                    for (i=0; i < TwinkleState.Count(); i++) {
                        if (TwinkleState[i] < -1) {
                            // background
                            TwinkleState[i]++;
                        } else if (TwinkleState[i] > 1) {
                            // highlight
                            TwinkleState[i]--;
                        } else if (TwinkleState[i] == -1) {
                            // was background, now highlight for random period
                            TwinkleState[i]=static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL;
                            xout->SetIntensity(chArray[i], FgIntensity);
                        } else {
                            // was on, now go to bg color for random period
                            TwinkleState[i]=-static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL * (TwinkleRatio - 1);
                            xout->SetIntensity(chArray[i], BgIntensity);
                        }
                    }
                    break;

                case SHIMMER:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        ShimIntensity = (ShimIntensity == FgIntensity) ? BgIntensity : FgIntensity;
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(chArray[i], ShimIntensity);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval/2;
                    }
                    break;

                case CHASE:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        for (i=0; i < chArray.Count(); i++) {
                            v = (i % ChaseGrouping) == TestSeqIdx ? FgIntensity : BgIntensity;
                            xout->SetIntensity(chArray[i], v);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval;
                        TestSeqIdx = (TestSeqIdx + 1) % ChaseGrouping;
                        if (TestSeqIdx >= chArray.Count()) TestSeqIdx=0;
                    }
                    break;
                default: break;
            }
            break;

        case 1:
            // RGB tests
            v=SliderRgbChaseSpeed->GetValue();  // 0-100
            BgColor[0] = SliderBgColorA->GetValue();
            BgColor[1] = SliderBgColorB->GetValue();
            BgColor[2] = SliderBgColorC->GetValue();
            FgColor[0] = SliderFgColorA->GetValue();
            FgColor[1] = SliderFgColorB->GetValue();
            FgColor[2] = SliderFgColorC->GetValue();

            interval = 1600 - v*15;
            for (ColorChange=false,i=0; i < 3; i++) {
                ColorChange |= (BgColor[i] != LastBgColor[i]);
                ColorChange |= (FgColor[i] != LastFgColor[i]);
                LastBgColor[i] = BgColor[i];
                LastFgColor[i] = FgColor[i];
            }
            switch (TestFunc) {
                case DIM:
                    if (ColorChange) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(chArray[i], BgColor[i % 3]);
                        }
                    }
                    break;

                case TWINKLE:
                    if (LastSequenceSpeed < 0) {
                        LastSequenceSpeed=0;
                        TwinkleState.Clear();
                        for (i=0; i < chArray.Count()-2; i+=3) {
                            TestSeqIdx = static_cast<int>(rand01()*TwinkleRatio);
                            TwinkleState.Add(TestSeqIdx == 0 ? -1 : 1);
                        }
                    }
                    for (i=0; i < TwinkleState.Count(); i++) {
                        if (TwinkleState[i] < -1) {
                            // background
                            TwinkleState[i]++;
                        } else if (TwinkleState[i] > 1) {
                            // highlight
                            TwinkleState[i]--;
                        } else if (TwinkleState[i] == -1) {
                            // was background, now highlight for random period
                            TwinkleState[i]=static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL;
                            TestSeqIdx = i * 3;
                            xout->SetIntensity(chArray[TestSeqIdx], FgColor[0]);
                            xout->SetIntensity(chArray[TestSeqIdx+1], FgColor[1]);
                            xout->SetIntensity(chArray[TestSeqIdx+2], FgColor[2]);
                        } else {
                            // was on, now go to bg color for random period
                            TwinkleState[i]=-static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL * (TwinkleRatio - 1);
                            TestSeqIdx = i * 3;
                            xout->SetIntensity(chArray[TestSeqIdx], BgColor[0]);
                            xout->SetIntensity(chArray[TestSeqIdx+1], BgColor[1]);
                            xout->SetIntensity(chArray[TestSeqIdx+2], BgColor[2]);
                        }
                    }
                    break;
                case SHIMMER:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        ShimColor = (ShimColor == FgColor) ? BgColor : FgColor;
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(chArray[i], ShimColor[i % 3]);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval/2;
                    }
                    break;
                case CHASE:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        for (i=0; i < chArray.Count(); i++) {
                            v = (i / 3 % ChaseGrouping) == TestSeqIdx ? FgColor[i % 3] : BgColor[i % 3];
                            xout->SetIntensity(chArray[i], v);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval;
                        TestSeqIdx = (TestSeqIdx + 1) % ChaseGrouping;
                        if (TestSeqIdx >= (chArray.Count()+2) / 3) TestSeqIdx=0;
                    }
                    break;
                default: break;
            }
            break;

        case 2:
            // RGB Cycle
            v=SliderRgbCycleSpeed->GetValue();  // 0-100
            if (TestFunc == DIM) {
                // color mixing
                if (v != LastSequenceSpeed) {
                    frequency=v/1000.0 + 0.05;
                    LastSequenceSpeed = v;
                }
                BgColor[0] = sin(frequency*TestSeqIdx + 0.0) * 127 + 128;
                BgColor[1] = sin(frequency*TestSeqIdx + 2.0) * 127 + 128;
                BgColor[2] = sin(frequency*TestSeqIdx + 4.0) * 127 + 128;
                TestSeqIdx++;
                for (i=0; i < chArray.Count(); i++) {
                    xout->SetIntensity(chArray[i], BgColor[i % 3]);
                }
            } else {
                // RGB cycle
                if (v != LastSequenceSpeed) {
                    interval = (101-v)*50;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                }
                if (curtime >= NextSequenceStart) {
                    for (i=0; i < chArray.Count(); i++) {
                        switch (rgbCycle) {
                            case 3: v=255; break;
                            default: v = (i % 3) == rgbCycle ? 255 : 0; break;
                        }
                        xout->SetIntensity(chArray[i], v);
                    }
                    rgbCycle=(rgbCycle + 1) % ChaseGrouping;
                    NextSequenceStart += interval;
                }
            }
            break;
    }
    xout->TimerEnd();
    ts = wxDateTime::UNow() - TimerStartTime;
    curtime = ts.GetMilliseconds().ToLong();
    StatusBar1->SetStatusText(wxString::Format(_("Timer took %ld msec"),curtime));
    //wxLogTrace(wxT("xout"),wxT("Ending OnTimer"));
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}