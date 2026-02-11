#include "includes/AudioController.h"

AudioController* AudioController::s_instance = nullptr;

AudioController::AudioController(const char* name) : m_displayName{name}, m_sink{m_dataStream} {
    s_instance = this;
    m_config = m_dataStream.defaultConfig(TX_MODE);
    m_sink.set_avrc_rn_volumechange(volChangedCallback);
    m_sink.set_on_audio_state_changed(statChangeCallback);
}

AudioController::AudioController(const char* name, int outputPin, int wordSelect, int clock) : m_displayName{name}, m_sink{m_dataStream} {
    s_instance = this;
    m_config = m_dataStream.defaultConfig(TX_MODE);
    m_config.pin_data = outputPin;
    m_config.pin_ws = wordSelect;
    m_config.pin_bck = clock;
    m_sink.set_avrc_rn_volumechange(volChangedCallback);
    m_sink.set_on_audio_state_changed(statChangeCallback);
}

void AudioController::init() {
    m_dataStream.begin(m_config);
    m_sink.start(m_displayName.c_str());
}

void AudioController::controlVolume(int amt) {
    if (amt < 0) {
        m_currentVolume = m_currentVolume - abs(amt);
    } else {
        m_currentVolume = m_currentVolume + amt;
    }
    m_sink.set_volume(m_currentVolume);
}

void AudioController::mute() {
    m_sink.set_volume(0);
    delay(30);
    digitalWrite(16, LOW);
}

void AudioController::unmute() {
    digitalWrite(16, HIGH);
    delay(10);
    m_sink.set_volume(m_currentVolume);
}

void AudioController::avrcOperation(AvrcCommand command) {
    switch (command) {
    case AvrcCommand::NEXT:
        m_sink.next();
        break;
    case AvrcCommand::PREVIOUS:
        m_sink.previous();
        break;
    case AvrcCommand::PAUSE:
        m_sink.pause();
        break;
    case AvrcCommand::PLAY:
        m_sink.play();
        break;
    }
}

void AudioController::updateVolume(int val) {
    m_currentVolume = val;
}