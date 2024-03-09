#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& formatManager)
        : AudioAppComponent(),
          formatManager(formatManager),
          resampleSource(&transportSource, false, 2) {
    startTimer(500);
}

DJAudioPlayer::~DJAudioPlayer() {
    stopTimer();
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(const URL& audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) {
        auto newSource = std::make_unique<AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        justLoaded = true;
    } else {
        DBG("DJAudioPlayer::loadURL: Bad audio file!");
    }
}

void DJAudioPlayer::setGain(double gain) {
    gain = std::clamp(gain / 100, 0.0, 1.0);
    transportSource.setGain(gain);
}

void DJAudioPlayer::setSpeed(double ratio) {
    ratio = std::clamp(ratio, 0.0, MAX_SPEED_RATIO);
    resampleSource.setResamplingRatio(ratio);
}

void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    pos = std::clamp(pos, 0.0, 1.0);
    double posInSecs = transportSource.getLengthInSeconds() * pos;
    setPosition(posInSecs);
}

void DJAudioPlayer::setLoop(double seconds) {
    if (seconds > 0 && seconds <= MAX_LOOP_SECONDS) {
        loopIsActivated = true;
        loopSeconds = seconds;
        loopEnd = transportSource.getCurrentPosition();
        loopStart = loopEnd - seconds;
    } else {
        loopIsActivated = false;
    }
}

void DJAudioPlayer::timerCallback() {
    if (loopIsActivated && (transportSource.getCurrentPosition() >= loopEnd || loopSeconds == 0)) {
        transportSource.setPosition(loopStart);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
    justLoaded = false;
}

void DJAudioPlayer::pause() {
    transportSource.stop();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
    transportSource.setPosition(0);
}

double DJAudioPlayer::getPosInTrack() const {
    return transportSource.getCurrentPosition();
}

double DJAudioPlayer::getPositionRelative() const {
    auto lengthInSeconds = transportSource.getLengthInSeconds();
    return (lengthInSeconds > 0) ? (transportSource.getCurrentPosition() / lengthInSeconds) : 0.0;
}

bool DJAudioPlayer::fileJustLoaded() {
    bool wasJustLoaded = justLoaded;
    justLoaded = false;
    return wasJustLoaded;
}
