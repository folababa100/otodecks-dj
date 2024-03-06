#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "LookandFeels.h"

//==============================================================================
/*
*/
class DJPanel : public Component,
    public Slider::Listener,
    public Button::Listener,
    public ModifierKeys
{
public:

    DJPanel(DJAudioPlayer* _player, TooltipWindow* _tooltipWindow);
    ~DJPanel() override;

    void paint(Graphics& g) override;
    void resized() override;

    // Set button properties
    void setButtonProperties(TextButton& button, double x, double y, double width, double height, Colour colour);

    // Implements Slider::Listener, pointer to the slider whose value changed
    void sliderValueChanged(Slider* slider) override;
    // Implement Button::Listener,pointer to the button that is clicked
    void buttonClicked(Button* button) override;

    // Handle button click
    void handleButtonClick(Button* button, double& hcPos);

    // Check if CTRL key is pressed
    bool isCommandDown() const noexcept;

private:
    Label volume, speed, loop, hotCue;

    LookandFeels v1;

    Label label;

    // Sliders
    Slider volSlider;
    Slider speedSlider;
    Slider loopSlider;

    //Hot Cue Buttons
    TextButton hcBtn1{ "1" };
    TextButton hcBtn2{ "2" };
    TextButton hcBtn3{ "3" };
    TextButton hcBtn4{ "4" };

    double hcPos1;
    double hcPos2;
    double hcPos3;
    double hcPos4;
    int experienceLevel;

    DJAudioPlayer* player;
    TooltipWindow* tooltipWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJPanel)
};