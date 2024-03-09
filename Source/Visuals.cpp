#include <JuceHeader.h>
#include "Visuals.h"

// Reference: https://github.com/juce-framework/JUCE/blob/master/examples/GUI/LookAndFeelDemo.h

// ==============================================================================
Visuals::Visuals()
{
    //  In your constructor, you should add any child components, and
    //  initialise any special settings that your component needs.

}

// Slider
// Customise slider thumb appearance
void Visuals::drawRoundThumb(Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness)
{
    auto halfThickness = outlineThickness * 0.5f;

    Path p;
    p.addRoundedRectangle(x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness, 5.0f);

    DropShadow(Colours::mediumpurple, 1, {}).drawForPath(g, p);

    g.setColour(Colour::fromRGB(76, 104, 215));
    g.fillPath(p);
    g.strokePath(p, PathStrokeType(outlineThickness));
}


void Visuals::drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         const Slider::SliderStyle style, Slider& slider)
{
    auto sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

    auto isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());

    auto knobColour = slider.findColour(Slider::thumbColourId)
        .withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
        .withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f);

    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = (float)x + (float)width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = (float)y + (float)height * 0.5f;
        }

        auto outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

        drawRoundThumb(g,
            kx - sliderRadius,
            ky - sliderRadius,
            sliderRadius * 2.0f,
            knobColour, outlineThickness);
    }
    else
    {
        // Calling base class for demo
        LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

// Customise slider appearance
void Visuals::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                    const Slider::SliderStyle style, Slider& slider)
{
    g.fillAll(slider.findColour(Slider::backgroundColourId).withMultipliedBrightness(0.8f));

    if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
    {
        Path p;

        if (style == Slider::LinearBarVertical)
        {
            p.addRectangle((float)x, sliderPos, (float)width, 1.0f + (float)height - sliderPos);
        }
        else
        {
            p.addRectangle((float)x, (float)y, sliderPos - (float)x, (float)height);
        }
        auto baseColour = slider.findColour(Slider::rotarySliderFillColourId)
                                .withMultipliedSaturation(slider.isEnabled() ? 1.0f : 0.5f)
                                .withMultipliedAlpha(0.8f);

        g.setColour(baseColour);
        g.fillPath(p);

        auto lineThickness = jmin(15.0f, (float)jmin(width, height) * 0.45f) * 0.1f;
        g.drawRect(slider.getLocalBounds().toFloat(), lineThickness);
    }
    else
    {
        drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

// Customise slider background
void Visuals::drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
                                              float, // sliderPos
                                              float, // minSliderPos
                                              float, // maxSliderPos
                                              const Slider::SliderStyle, //style
                                              Slider& slider)
{
    auto sliderRadius = (float)getSliderThumbRadius(slider) - 5.0f;
    Path on, off;

    if (slider.isHorizontal())
    {
        auto iy = (float)y + (float)height * 0.5f - sliderRadius * 0.5f;
        Rectangle<float> r((float)x - sliderRadius * 0.5f, iy, (float)width + sliderRadius, sliderRadius);
        auto onWidth = r.getWidth() * ((float)slider.valueToProportionOfLength(slider.getValue()));

        on.addRectangle(r.removeFromLeft(onWidth));
        off.addRectangle(r);
    }
    else
    {
        auto ix = (float)x + (float)width * 0.5f - sliderRadius * 0.5f;
        Rectangle<float> r(ix, (float)y - sliderRadius * 0.5f, sliderRadius, (float)height + sliderRadius);
        auto onH = r.getHeight() * ((float)slider.valueToProportionOfLength(slider.getValue()));

        on.addRectangle(r.removeFromBottom(onH));
        off.addRectangle(r);
    }
    // Set slider background colour
    g.fillAll(Colour::fromRGBA(255, 183, 197, 255));
    // Set slider colour -> included portion
    g.setColour(Colour(0xff001dab));
    g.fillPath(on);

    g.setColour(slider.findColour(Slider::trackColourId));
    g.fillPath(off);
}
