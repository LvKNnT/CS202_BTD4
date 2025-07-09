#ifndef ARE_YOU_SURE_STATE_H
#define ARE_YOU_SURE_STATE_H

#include "State.h"

class AreYouSureState: public State {
public:
    AreYouSureState();
    void draw() const override;
    void update(Event::Type event) override;
};
 
#endif // ARE_YOU_SURE_STATE_H