/* * ******************************************** * ******************************************** * Process Sequence Panel Events * ******************************************** * ******************************************** */void xLightsFrame::OnButton_PlaySelectionClick(wxCommandEvent& event){    SetPlayMode(play_seqpartial);}void xLightsFrame::OnButton_PlayAllClick(wxCommandEvent& event){    PlayerDlg->MediaCtrl->Play();    SetPlayMode(play_seqall);}void xLightsFrame::OnButton_PlayEffectClick(wxCommandEvent& event){    SetPlayMode(play_effect);}void xLightsFrame::OnButton_PresetsClick(wxCommandEvent& event){    EffectListDialog dialog(this);    wxString name;    for(wxXmlNode* e=EffectsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {        if (e->GetName() == wxT("effect")) {            name=e->GetAttribute(wxT("name"));            if (!name.IsEmpty()) {                dialog.ListBox1->Append(name,e);            }        }    }    dialog.ShowModal();    UpdateEffectsList();    PresetsSelect();}void xLightsFrame::SetChoicebook(wxChoicebook* cb, wxString& PageName)
{
    for(size_t i=0; i<cb->GetPageCount(); i++) {
        if (cb->GetPageText(i) == PageName) {
            cb->SetSelection(i);
            return;
        }
    }
}

void xLightsFrame::SetEffectControls(wxXmlNode* x)
{
    long TempLong;
    wxColour color;
    for (wxXmlAttribute *a=x->GetAttributes(); a!=NULL; a=a->GetNext()) {
        wxString name=a->GetName();
        wxString value=a->GetValue();
        if (!name.StartsWith(wxT("ID_"))) continue;
        wxWindow *CtrlWin=wxWindow::FindWindowByName(name);
        if (CtrlWin==NULL) continue;
        if (name.StartsWith(wxT("ID_SLIDER"))) {
            wxSlider* ctrl=(wxSlider*)CtrlWin;
            if (value.ToLong(&TempLong)) ctrl->SetValue(TempLong);
        } else if (name.StartsWith(wxT("ID_TEXTCTRL"))) {
            wxTextCtrl* ctrl=(wxTextCtrl*)CtrlWin;
            ctrl->SetValue(value);
        } else if (name.StartsWith(wxT("ID_CHOICEBOOK"))) {
            SetChoicebook((wxChoicebook*)CtrlWin,value);
        } else if (name.StartsWith(wxT("ID_CHOICE"))) {
            wxChoice* ctrl=(wxChoice*)CtrlWin;
            ctrl->SetStringSelection(value);
        } else if (name.StartsWith(wxT("ID_BUTTON"))) {
            color.Set(value);
            CtrlWin->SetBackgroundColour(color);
        } else if (name.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)CtrlWin;
            if (value.ToLong(&TempLong)) ctrl->SetValue(TempLong!=0);
        }
    }
    PaletteChanged=true;
    MixTypeChanged=true;
}

void xLightsFrame::PresetsSelect(){    int NameIdx=Choice_Presets->GetSelection();    if (NameIdx != wxNOT_FOUND) {        wxXmlNode* x=(wxXmlNode*)Choice_Presets->GetClientData(NameIdx);        SetEffectControls(x);    }}void xLightsFrame::OnChoice_PresetsSelect(wxCommandEvent& event){    PresetsSelect();}void xLightsFrame::OnButton_PresetAddClick(wxCommandEvent& event){    wxTextEntryDialog dialog(this,_("Enter preset name"),_("Add New Preset"));
    int DlgResult;
    bool ok;
    wxString name;
    do {
        ok=true;
        DlgResult=dialog.ShowModal();
        if (DlgResult == wxID_OK) {
            // validate inputs
            name=dialog.GetValue();
            name.Trim();
            if (name.IsEmpty()) {
                ok=false;
                wxMessageBox(_("A preset name cannot be empty"), _("ERROR"));
            } else if (Choice_Presets->FindString(name) != wxNOT_FOUND) {
                ok=false;
                wxMessageBox(_("That name is already in use"), _("ERROR"));
            }
        }
    } while (DlgResult == wxID_OK && !ok);
    if (DlgResult != wxID_OK) return;

    // update Choice_Presets
    EffectsNode->AddChild(CreateEffectNode(name));
    UpdateEffectsList();
    Choice_Presets->SetStringSelection(name);
}wxXmlNode* xLightsFrame::CreateEffectNode(wxString& name)
{
    int PageIdx1=Choicebook1->GetSelection();
    int PageIdx2=Choicebook2->GetSelection();
    wxXmlNode* NewXml=new wxXmlNode(wxXML_ELEMENT_NODE, wxT("effect"));
    NewXml->AddAttribute(wxT("name"), name);
    NewXml->AddAttribute(wxT("ID_CHOICEBOOK1"), Choicebook1->GetPageText(PageIdx1));
    NewXml->AddAttribute(wxT("ID_CHOICEBOOK2"), Choicebook2->GetPageText(PageIdx2));
    NewXml->AddAttribute(wxT("ID_CHOICE_LayerMethod"), Choice_LayerMethod->GetStringSelection());
    NewXml->AddAttribute(wxT("ID_SLIDER_SparkleFrequency"), wxString::Format(wxT("%d"),Slider_SparkleFrequency->GetValue()));
    NewXml->AddAttribute(wxT("ID_SLIDER_Speed1"), wxString::Format(wxT("%d"),Slider_Speed1->GetValue()));
    NewXml->AddAttribute(wxT("ID_SLIDER_Speed2"), wxString::Format(wxT("%d"),Slider_Speed2->GetValue()));
    LoadPageControlsToAttr(Choicebook1->GetPage(PageIdx1),NewXml);
    LoadSizerControlsToAttr(FlexGridSizer_Palette1, NewXml);
    LoadPageControlsToAttr(Choicebook2->GetPage(PageIdx2),NewXml);
    LoadSizerControlsToAttr(FlexGridSizer_Palette2, NewXml);
    return NewXml;
}

void xLightsFrame::OnButton_PresetUpdateClick(wxCommandEvent& event){    int NameIdx=Choice_Presets->GetSelection();
    if (NameIdx == wxNOT_FOUND) {
        wxMessageBox(_("No preset name is selected"), _("ERROR"));
    } else {
        // delete old xml entry
        wxXmlNode* OldXml=(wxXmlNode*)Choice_Presets->GetClientData(NameIdx);
        EffectsNode->RemoveChild(OldXml);
        delete OldXml;

        wxString name=Choice_Presets->GetString(NameIdx);
        EffectsNode->AddChild(CreateEffectNode(name));
        UpdateEffectsList();
        Choice_Presets->SetStringSelection(name);
    }
}void xLightsFrame::OnChoice_LayerMethodSelect(wxCommandEvent& event){    MixTypeChanged=true;}void xLightsFrame::OnButton_SaveEffectsClick(wxCommandEvent& event){    SaveEffectsFile();
}void xLightsFrame::OnButton_ModelsClick(wxCommandEvent& event){    ModelListDialog dialog(this);    wxString name;    wxXmlNode* e;    for(e=ModelsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {        if (e->GetName() == wxT("model")) {            name=e->GetAttribute(wxT("name"));            if (!name.IsEmpty()) {                dialog.ListBox1->Append(name,e);            }        }    }    dialog.HtmlEasyPrint=HtmlEasyPrint;    dialog.ShowModal();    // append any new models to the main xml structure    for(size_t i=0; i<dialog.ListBox1->GetCount(); i++) {        e=(wxXmlNode*)dialog.ListBox1->GetClientData(i);        if (!e->GetParent()) {            ModelsNode->AddChild(e);        }    }    UpdateModelsList();}void xLightsFrame::OnCheckBox_PaletteClick(wxCommandEvent& event){    PaletteChanged=true;}// displays color chooser and updates the button's background color with the return valuevoid xLightsFrame::OnButton_ColorClick(wxCommandEvent& event){    wxWindow* w=(wxWindow*)event.GetEventObject();    if (ColourDialog1->ShowModal() == wxID_OK) {        wxColourData retData = ColourDialog1->GetColourData();        wxColour color = retData.GetColour();        w->SetBackgroundColour(color);        PaletteChanged=true;    }}void xLightsFrame::UpdateEffectsList(){    wxString name;    wxString SelectedStr=Choice_Presets->GetStringSelection();    Choice_Presets->Clear();    for(wxXmlNode* e=EffectsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {        if (e->GetName() == wxT("effect")) {            name=e->GetAttribute(wxT("name"));            if (!name.IsEmpty()) {                Choice_Presets->Append(name,e);            }        }    }    // select a preset if one exists    if (Choice_Presets->GetCount() > 0) {        if (SelectedStr.IsEmpty() || !Choice_Presets->SetStringSelection(SelectedStr)) {            Choice_Presets->SetSelection(0);        }    }}void xLightsFrame::UpdateModelsList(){    wxString name;    wxString SelectedStr=Choice_Models->GetStringSelection();    Choice_Models->Clear();    for(wxXmlNode* e=ModelsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {        if (e->GetName() == wxT("model")) {            name=e->GetAttribute(wxT("name"));            if (!name.IsEmpty()) {                Choice_Models->Append(name,e);            }        }    }    // select a model if one exists    if (Choice_Models->GetCount() > 0) {        if (SelectedStr.IsEmpty() || !Choice_Models->SetStringSelection(SelectedStr)) {            Choice_Models->SetSelection(0);        }        Button_PlayEffect->Enable(play_mode == play_off);
    }}void xLightsFrame::LoadPageControlsToAttr(wxWindow* page,wxXmlNode* x)
{
    wxWindowList &ChildList = page->GetChildren();
    //wxString msg=_("Children of ")+page->GetName();
    for ( wxWindowList::Node *node = ChildList.GetFirst(); node; node = node->GetNext() )
    {
        wxWindow *ChildWin = (wxWindow *)node->GetData();
        wxString ChildName=ChildWin->GetName();
        if (ChildName.StartsWith(wxT("ID_SLIDER"))) {
            wxSlider* ctrl=(wxSlider*)ChildWin;
            x->AddAttribute(ChildName, wxString::Format(wxT("%d"),ctrl->GetValue()));
        } else if (ChildName.StartsWith(wxT("ID_TEXTCTRL"))) {
            wxTextCtrl* ctrl=(wxTextCtrl*)ChildWin;
            x->AddAttribute(ChildName, ctrl->GetValue());
        } else if (ChildName.StartsWith(wxT("ID_CHOICE"))) {
            wxChoice* ctrl=(wxChoice*)ChildWin;
            x->AddAttribute(ChildName, ctrl->GetStringSelection());
        } else if (ChildName.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)ChildWin;
            wxString v=(ctrl->IsChecked()) ? wxT("1") : wxT("0");
            x->AddAttribute(ChildName, v);
        }
        //msg+=wxT("\n")+ChildName;
    }
    //wxMessageBox(msg);
}

// used to save palette
void xLightsFrame::LoadSizerControlsToAttr(wxSizer* sizer,wxXmlNode* x)
{
    wxSizerItemList &ChildList = sizer->GetChildren();
    for ( wxSizerItemList::iterator it = ChildList.begin(); it != ChildList.end(); ++it )
    {
        if (!(*it)->IsWindow()) continue;
        wxWindow *ChildWin = (*it)->GetWindow();
        wxString ChildName=ChildWin->GetName();
        if (ChildName.StartsWith(wxT("ID_BUTTON"))) {
            wxColour color=ChildWin->GetBackgroundColour();
            x->AddAttribute(ChildName, color.GetAsString(wxC2S_HTML_SYNTAX));
        } else if (ChildName.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)ChildWin;
            wxString v=(ctrl->IsChecked()) ? wxT("1") : wxT("0");
            x->AddAttribute(ChildName, v);
        }
    }
}

void xLightsFrame::CreateDefaultEffectsXml(){    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xrgb") );    EffectsXml.SetRoot( root );}// returns true on successvoid xLightsFrame::LoadEffectsFile(){    //wxMessageBox(Slider_Meteors1_Type->GetName());    wxFileName effectsFile;    effectsFile.AssignDir( CurrentDir );    effectsFile.SetFullName(_(XLIGHTS_RGBEFFECTS_FILE));    if (!effectsFile.FileExists()) {        // file does not exist, so create an empty xml doc        CreateDefaultEffectsXml();    } else if (!EffectsXml.Load( effectsFile.GetFullPath() )) {        wxMessageBox(_("Unable to load RGB effects file"), _("Error"));        CreateDefaultEffectsXml();    }    wxXmlNode* root=EffectsXml.GetRoot();    if (root->GetName() != wxT("xrgb")) {        wxMessageBox(_("Invalid RGB effects file. Press Save File button to start a new file."), _("Error"));        CreateDefaultEffectsXml();    }    for(wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {        if (e->GetName() == wxT("models")) ModelsNode=e;        if (e->GetName() == wxT("effects")) EffectsNode=e;    }    if (ModelsNode == 0) {        ModelsNode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("models") );        root->AddChild( ModelsNode );    }    if (EffectsNode == 0) {        EffectsNode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("effects") );        root->AddChild( EffectsNode );    }    UpdateModelsList();    UpdateEffectsList();}// returns true on successbool xLightsFrame::SaveEffectsFile(){    wxFileName effectsFile;    effectsFile.AssignDir( CurrentDir );    effectsFile.SetFullName(_(XLIGHTS_RGBEFFECTS_FILE));    if (!EffectsXml.Save( effectsFile.GetFullPath() )) {        wxMessageBox(_("Unable to save RGB effects file"), _("Error"));        return false;    }    UnsavedChanges=false;    return true;}void xLightsFrame::UpdateBufferPalette()
{
    wxColourVector newcolors;

    // effect 1
    if (CheckBox_Palette1_1->IsChecked()) newcolors.push_back(Button_Palette1_1->GetBackgroundColour());
    if (CheckBox_Palette1_2->IsChecked()) newcolors.push_back(Button_Palette1_2->GetBackgroundColour());
    if (CheckBox_Palette1_3->IsChecked()) newcolors.push_back(Button_Palette1_3->GetBackgroundColour());
    if (CheckBox_Palette1_4->IsChecked()) newcolors.push_back(Button_Palette1_4->GetBackgroundColour());
    if (CheckBox_Palette1_5->IsChecked()) newcolors.push_back(Button_Palette1_5->GetBackgroundColour());
    if (CheckBox_Palette1_6->IsChecked()) newcolors.push_back(Button_Palette1_6->GetBackgroundColour());
    buffer.SetPalette(0,newcolors);

    // effect 2
    newcolors.clear();
    if (CheckBox_Palette2_1->IsChecked()) newcolors.push_back(Button_Palette2_1->GetBackgroundColour());
    if (CheckBox_Palette2_2->IsChecked()) newcolors.push_back(Button_Palette2_2->GetBackgroundColour());
    if (CheckBox_Palette2_3->IsChecked()) newcolors.push_back(Button_Palette2_3->GetBackgroundColour());
    if (CheckBox_Palette2_4->IsChecked()) newcolors.push_back(Button_Palette2_4->GetBackgroundColour());
    if (CheckBox_Palette2_5->IsChecked()) newcolors.push_back(Button_Palette2_5->GetBackgroundColour());
    if (CheckBox_Palette2_6->IsChecked()) newcolors.push_back(Button_Palette2_6->GetBackgroundColour());
    buffer.SetPalette(1,newcolors);
}

void xLightsFrame::TimerEffect()
{
    wxString line1,line2,s;
    buffer.Clear();

    // update SparkleFrequency
    int freq=Slider_SparkleFrequency->GetValue();
    if (freq == Slider_SparkleFrequency->GetMax()) freq=0;
    buffer.SetSparkle(freq);

    if (PaletteChanged) {
        UpdateBufferPalette();
        PaletteChanged=false;
    }
    if (MixTypeChanged) {
        s=Choice_LayerMethod->GetStringSelection();
        buffer.SetMixType(s);
        MixTypeChanged=false;
    }

    // render effect 1
    buffer.SetSpeed(Slider_Speed1->GetValue());
    switch (Choicebook1->GetSelection())
    {
        case 0: break;   // none
        case 1:
            buffer.RenderBars(0, Slider_Bars1_BarCount->GetValue(),
                              Choice_Bars1_Direction->GetSelection(),
                              CheckBox_Bars1_Highlight->GetValue(),
                              CheckBox_Bars1_3D->GetValue());
            break;
        case 2:
            buffer.RenderButterfly(0, Choice_Butterfly1_Colors->GetSelection(),
                                   Slider_Butterfly1_Style->GetValue(),
                                   Slider_Butterfly1_Chunks->GetValue(),
                                   Slider_Butterfly1_Skip->GetValue());
            break;
        case 3:
            buffer.RenderColorWash(0,CheckBox_ColorWash1_HFade->GetValue(),
                                   CheckBox_ColorWash1_VFade->GetValue());
            break;
        case 4:
            buffer.RenderFire(0);
            break;
        case 5:
            buffer.RenderGarlands(0,Slider_Garlands1_Type->GetValue(),
                                  Slider_Garlands1_Spacing->GetValue());
            break;
        case 6:
            buffer.RenderLife(0,Slider_Life1_Count->GetValue(),
                              Slider_Life1_Seed->GetValue());
            break;
        case 7:
            buffer.RenderMeteors(0,Choice_Meteors1_Type->GetSelection(),
                                 Slider_Meteors1_Count->GetValue(),
                                 Slider_Meteors1_Length->GetValue());
            break;
        case 8:
            buffer.RenderPictures(0);
            break;
        case 9:
            buffer.RenderSnowflakes(0);
            break;
        case 10:
            buffer.RenderSnowstorm(0,Slider_Snowstorm1_Count->GetValue(),
                                   Slider_Snowstorm1_Length->GetValue());
            break;
        case 11:
            buffer.RenderSpirals(0,Slider_Spirals1_Count->GetValue(),
                                 Slider_Spirals1_Direction->GetValue(),
                                 Slider_Spirals1_Rotation->GetValue(),
                                 Slider_Spirals1_Thickness->GetValue(),
                                 CheckBox_Spirals1_Blend->GetValue(),
                                 CheckBox_Spirals1_3D->GetValue());
            break;
        case 12:
            line1=TextCtrl_Text1_Line1->GetValue();
            line2=TextCtrl_Text1_Line2->GetValue();
            buffer.RenderText(0,Slider_Text1_Top->GetValue(),line1,line2);
            break;
    }

    // render effect 2
    buffer.SetSpeed(Slider_Speed2->GetValue());
    switch (Choicebook2->GetSelection())
    {
        case 0: break;   // none
        case 1:
            buffer.RenderBars(1, Slider_Bars2_BarCount->GetValue(),
                              Choice_Bars2_Direction->GetSelection(),
                              CheckBox_Bars2_Highlight->GetValue(),
                              CheckBox_Bars2_3D->GetValue());
            break;
        case 2:
            buffer.RenderButterfly(1, Choice_Butterfly2_Colors->GetSelection(),
                                   Slider_Butterfly2_Style->GetValue(),
                                   Slider_Butterfly2_Chunks->GetValue(),
                                   Slider_Butterfly2_Skip->GetValue());
            break;
        case 3:
            buffer.RenderColorWash(1,CheckBox_ColorWash2_HFade->GetValue(),
                                   CheckBox_ColorWash2_VFade->GetValue());
            break;
        case 4:
            buffer.RenderFire(1);
            break;
        case 5:
            buffer.RenderGarlands(1,Slider_Garlands2_Type->GetValue(),
                                  Slider_Garlands2_Spacing->GetValue());
            break;
        case 6:
            buffer.RenderLife(1,Slider_Life2_Count->GetValue(),
                              Slider_Life2_Seed->GetValue());
            break;
        case 7:
            buffer.RenderMeteors(1,Choice_Meteors2_Type->GetSelection(),
                                 Slider_Meteors2_Count->GetValue(),
                                 Slider_Meteors2_Length->GetValue());
            break;
        case 8:
            buffer.RenderPictures(1);
            break;
        case 9:
            buffer.RenderSnowflakes(1);
            break;
        case 10:
            buffer.RenderSnowstorm(1,Slider_Snowstorm2_Count->GetValue(),
                                   Slider_Snowstorm2_Length->GetValue());
            break;
        case 11:
            buffer.RenderSpirals(1,Slider_Spirals2_Count->GetValue(),
                                 Slider_Spirals2_Direction->GetValue(),
                                 Slider_Spirals2_Rotation->GetValue(),
                                 Slider_Spirals2_Thickness->GetValue(),
                                 CheckBox_Spirals2_Blend->GetValue(),
                                 CheckBox_Spirals2_3D->GetValue());
            break;
        case 12:
            line1=TextCtrl_Text2_Line1->GetValue();
            line2=TextCtrl_Text2_Line2->GetValue();
            buffer.RenderText(1,Slider_Text2_Top->GetValue(),line1,line2);
            break;
    }
    buffer.DisplayOutput();
    if (CheckBoxLightOutput->IsChecked() && xout) {
        size_t ChannelNum=buffer.StartChannel-1;
        size_t NodeCnt=buffer.GetNodeCount();
        for(size_t i=0; i<NodeCnt; i++) {
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(0));
            ChannelNum++;
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(1));
            ChannelNum++;
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(2));
            ChannelNum++;
        }
    }
}

void xLightsFrame::TimerSeqPartial()
{
}

void xLightsFrame::TimerSeqAll()
{
}

