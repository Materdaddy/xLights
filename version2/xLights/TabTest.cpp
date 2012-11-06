/*
 * ********************************************
 * ********************************************
 * Process Test Panel Events
 * ********************************************
 * ********************************************
 */

void xLightsFrame::SetAllCheckboxes(bool NewValue)
{
    int ChCount = CheckListBoxTestChannels->GetCount();
    for (int i=0; i < ChCount; i++) {
        CheckListBoxTestChannels->Check(i,NewValue);
    }
    CheckChannelList = true;
}

void xLightsFrame::OnButtonTestSelectAllClick(wxCommandEvent& event)
{
    SetAllCheckboxes(true);
}

void xLightsFrame::OnButtonTestClearClick(wxCommandEvent& event)
{
    SetAllCheckboxes(false);
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

void xLightsFrame::OnButtonTestLoadClick(wxCommandEvent& event)
{
}

void xLightsFrame::OnButtonTestSaveClick(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonOffSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonChaseSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonChase3Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonChase4Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonChase5Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonAltSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonTwinkle05Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonTwinkle10Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonTwinkle25Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonTwinkle50Select(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonShimmerSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonDimSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonRgbChaseOffSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonRgbChaseSelect(wxCommandEvent& event)
{
}

void xLightsFrame::OnRadioButtonRgbChase3Select(wxCommandEvent& event)
{
}
