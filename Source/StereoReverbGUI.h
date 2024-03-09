#pragma once

#include <JuceHeader.h>
#include "Stereo.h"
#include "Visuals.h"

//==============================================================================
/*
*/
class StereoReverbGUI  : public Component,
                         public Slider::Listener
{
public:
    StereoReverbGUI(Stereo* _stereoReverb);
    ~StereoReverbGUI() override;

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

    // Label for StereoReverbGUI
    Label label;

    // Info button
    ImageButton infoBtn;

    // Stereo reverb filter
    Stereo* stereoReverb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoReverbGUI)
};
