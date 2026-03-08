#include <string>
#include "AudioTools.h"
#include "BluetoothA2DP.h"

class AudioController {

public:
    enum class AvrcCommand {NEXT, PREVIOUS, PAUSE, PLAY};
    AudioController(const char* name, int enable);
    AudioController(const char* name, int outputPin, int wordSelect, int clock, int enable);
    ~AudioController();
    void init();
    void controlVolume(int amt);
    void mute();
    void unmute();
    void avrcOperation(AvrcCommand command);
    void loop();
private:
    void updateVolume(int val);
    inline static void volChangedCallback(int vol) {
        s_instance->updateVolume(vol);
    }
    static void statChangeCallback(esp_a2d_audio_state_t state, void* ptr) {
        switch (state)
        {
        case ESP_A2D_AUDIO_STATE_STARTED:
            s_instance->unmute();
            break;
        case ESP_A2D_AUDIO_STATE_STOPPED:
            s_instance->mute();
            break;
        case ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND:
            s_instance->mute();
            break;
        }
    }
private:
    I2SStream m_dataStream;
    I2SConfig m_config;
    BluetoothA2DPSink m_sink;
    std::string m_displayName;
    unsigned int m_currentVolume;
    static AudioController* s_instance;
    int m_enable;
};