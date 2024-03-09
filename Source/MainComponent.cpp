#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify number of input and output channels to be opened
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(DJPanel1);
    addAndMakeVisible(DJPanel2);
    addAndMakeVisible(stereoReverbGUI);
    // Format the audio files
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // Shuts down audio device & clears the audio source
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

    stereoReverb.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    stereoReverb.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources().
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
    stereoReverb.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    deckGUI1.setBounds(0, getHeight() * 0.35, getWidth() * 0.35, getHeight() * 0.65);
    deckGUI2.setBounds(getWidth() * 0.65, getHeight() * 0.35, getWidth() * 0.35, getHeight() * 0.65);
    DJPanel1.setBounds(getWidth() * 0.35, getHeight() * 0.35, getWidth() * 0.15, getHeight() * 0.65);
    DJPanel2.setBounds(getWidth() * 0.50, getHeight() * 0.35, getWidth() * 0.15, getHeight() * 0.65);
    stereoReverbGUI.setBounds(0, 0, getWidth() * 1, getHeight() * 0.35);

}


