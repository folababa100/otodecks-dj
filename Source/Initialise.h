#pragma once

#include <JuceHeader.h>
#include "LookandFeels.h"

class Initialise : public Component,
    public Slider::Listener,
    public Button::Listener,
    public ComboBox::Listener
{
public:
    Initialise();

    static void sliderOptions(Component* component, Slider* slider, Slider::Listener* listener,
                              Slider::SliderStyle style, Slider::TextEntryBoxPosition textPos,
                              bool readOnly, int textBoxW, int textBoxH, double rangeStart,
                              double rangeEnd, double increment, LookAndFeel* LookandFeels,
                              Slider::ColourIds colourid, Colour colour);

    static void labelOptions(Component* component, Label* label, String title,
                             NotificationType notiType, Justification justification,
                             float fontSize, Label::ColourIds colourid, Colour colour);

    static void buttonOptions(Component* component, Button* button,
                              Button::Listener* listener, bool toggleOn,
                              String tooltip, float alpha);
};
