#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Visuals  : public LookAndFeel_V4
{
public:

    Visuals();

    // Customise slider thumb appearance
    void drawRoundThumb(Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness);

    void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
                               float sliderPos, float minSliderPos, float maxSliderPos,
                               const Slider::SliderStyle style, Slider& slider) override;

    // Customise slider appearance
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const Slider::SliderStyle style, Slider& slider) override;

    // Customise slider background
    void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
                                    float, // sliderPos
                                    float, // minSliderPos
                                    float, // maxSliderPos
                                    const Slider::SliderStyle, //style
                                    Slider& slider) override;
                            };
