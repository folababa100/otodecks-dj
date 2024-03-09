#include <JuceHeader.h>
#include "Initialise.h"

Initialise::Initialise()
{

}

void Initialise::sliderOptions(Component* component, Slider* slider, Slider::Listener* listener,
                                Slider::SliderStyle style, Slider::TextEntryBoxPosition textPos,
                                bool readOnly, int textBoxW, int textBoxH, double rangeStart,
                                double rangeEnd, double increment, LookAndFeel* Visuals,
                                Slider::ColourIds colourid, Colour colour)
{
    component->addAndMakeVisible(slider);
    slider->addListener(listener);
    slider->setSliderStyle(style);
    slider->setTextBoxStyle(textPos, readOnly, textBoxW, textBoxH);
    slider->setColour(slider->textBoxOutlineColourId, Colours::transparentWhite);
    slider->setRange(rangeStart, rangeEnd, increment);
    slider->setLookAndFeel(Visuals);
    slider->setColour(colourid, colour);
}

void Initialise::labelOptions(Component* component, Label* label, String title,
                               NotificationType notiType, Justification justification,
                               float fontSize, Label::ColourIds colourid, Colour colour)
{
    component->addAndMakeVisible(label);
    label->setText(title, notiType);
    label->setJustificationType(justification);
    label->setFont(fontSize);
    label->setColour(colourid, colour);
}

void Initialise::buttonOptions(Component* component, Button* button,
                                Button::Listener* listener, bool toggleOn,
                                String tooltip, float alpha)
{
    component->addAndMakeVisible(button);
    button->addListener(listener);
    button->setClickingTogglesState(toggleOn);
    button->setTooltip(tooltip);
    button->setAlpha(alpha);
}
