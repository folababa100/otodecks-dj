#pragma once

#include <JuceHeader.h>
#include "LookandFeels.h"

//==============================================================================
/*
*/
class Initiallise : public Component,
    public Slider::Listener,
    public Button::Listener,
    public ComboBox::Listener
{
public:
    Initiallise();

    // Initialise slider settings
    static void sliderOptions(Component* component, Slider* slider, Slider::Listener* listener,
                              Slider::SliderStyle style, Slider::TextEntryBoxPosition textPos,
                              bool readOnly, int textBoxW, int textBoxH, double rangeStart,
                              double rangeEnd, double increment, LookAndFeel* LookandFeels,
                              Slider::ColourIds colourid, Colour colour);

    // Initialise label settings
    static void labelOptions(Component* component, Label* label, String title,
                             NotificationType notiType, Justification justification,
                             float fontSize, Label::ColourIds colourid, Colour colour);

    // Initialise button settings
    static void buttonOptions(Component* component, Button* button,
                              Button::Listener* listener, bool toggleOn,
                              String tooltip, float alpha);
};
