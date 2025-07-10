#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    enum class Type {
        None, 
        // UI
        ToMapSelection, 
        ToOptions, 
        CancelCurrentState,
        Exit,
        MoveNext,
        MovePrevious,
        ToMonkeyLane,
        HigherSound,
        LowerSound,
        HigherMusic,
        LowerMusic,
        ToAreYouSure,
        BackHome,
        ToEasyModeSelection,
        ToMediumModeSelection, 
        ToHardModeSelection,
        ToEasyStandardMode, 
        ToEasyPrimaryOnlyMode, 
        ToEasyDeflationdMode, 
        ToEasySandboxMode, 

        //UI towers
        //Hovering
        HoveringChooseBomb,
        //Clicked
        ClickedChooseBomb
        // Logic

    };

};

#endif // EVENT_H