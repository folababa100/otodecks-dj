#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "DJPanel.h"
#include "Track.h"
#include "StereoGUI.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    // For left
    DJAudioPlayer player1{ formatManager };
    Colour blueDeckColour{ Colour::fromRGBA(1, 30, 254, 255) };
    DeckGUI deckGUI1{ &player1, formatManager, thumbCache, blueDeckColour, &tip };
    DJPanel DJPanel1{ &player1, &tip };

    // For right
    DJAudioPlayer player2{ formatManager };
    Colour purpleDeckColour{ Colour::fromRGBA(201, 0, 255, 255) };
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache, purpleDeckColour, &tip };
    DJPanel DJPanel2{ &player2, &tip};

    // Take in 2 audio sources
    MixerAudioSource mixerSource;

    TooltipWindow tip{ this, 700 };

    // Stereo Reverb GUI
    StereoGUI stereoReverbGUI{&stereoReverb};
    // Stereo Reverb
    Stereo stereoReverb{&mixerSource};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
