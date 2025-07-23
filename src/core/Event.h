#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    enum class Type {
        None, 
        // UI
        Exit,
        NewGame,
        Continue,
        MoveNext,
        MovePrevious,
        
        // Music
        HigherSound,
        LowerSound,
        HigherMusic,
        LowerMusic,
        
        // State
        ToOptions, 
        ToMonkeyLane,
        CancelCurrentState,
        ToMapSelection, 
        ToAreYouSure,
        BackHome,
        ToSpecificModeSelection, 
        ToEasyModeSelection,
        ToMediumModeSelection, 
        ToHardModeSelection,
        ToImpoppableModeSelection,
        ToGameState,

        // Game State 
        HoveringInfo,
        NextPriority, 
        PreviousPriority,
        Priority_First,
        Priority_Last, 
        Priority_Close, 
        Priority_Strong,

        // Mode
        AutoNextRound,
        UnAutoNextRound,
        TickFastForward,
        UntickFastForward,

        StandardMode, 
        AlternateBloonsMode,
        ReverseMode, 
        ApopalyseMode,
        HoveringReverseMode, 
        HoveringAlternateBloonsMode,
        HoveringApopalyseMode,

        //UI towers
        //Hovering
        HoveringChooseBomb,
        
        //Clicked
        ClickedChooseBomb
        // Logic

    };

};

#endif // EVENT_H