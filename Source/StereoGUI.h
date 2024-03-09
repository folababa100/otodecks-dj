#pragma once

#include <JuceHeader.h>
#include "Stereo.h"
#include "Visuals.h"

//==============================================================================
/*
*/
class StereoGUI  : public Component,
                         public Slider::Listener
{
public:
    StereoGUI(Stereo* _stereoReverb);
    ~StereoGUI() override;

    void paint(Graphics&) override;
    void resized() override;

    // Get parameters value from respective sliders -> implement Slider::Listener
    void sliderValueChanged(Slider* slider) override;

private:
    // 6 slider values for 6 reverb parameters
    Slider roomSizeSlider;
    Slider dampingSlider;
    Slider wetLevelSlider;
    Slider dryLevelSlider;
    Slider widthSlider;
    Slider freezeModeSlider;

    // Labels for all the parameters
    Label roomSize, damping, wetLevel, dryLevel, width, freezeMode;

    // Customise slider appearance
    Visuals v1;

    // Label for StereoGUI
    Label label;

    // Info button
    ImageButton infoBtn;

    // Stereo reverb filter
    Stereo* stereoReverb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoGUI)
};
