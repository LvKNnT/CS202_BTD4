#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include "State.h"

class OptionsState : public State {
public:
    OptionsState();
    void draw() const override;
    void update(Event::Type event) override;

private:
    std::shared_ptr<PanelElement> soundTexture[6];
    std::shared_ptr<PanelElement> musicTexture[6];
    
    void resetSoundTextures();
    void resetMusicTextures();
};

#endif // OPTIONS_STATE_H