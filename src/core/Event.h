#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    enum class Type {
        None, 
/*---------------------------------------------------------UI ONLY------------------------------------------------------------------------*/ 
        MoveNext,
        MovePrevious,
        
        // Music
        HigherSound,
        LowerSound,
        HigherMusic,
        LowerMusic,
        
        // State
        ToOptions, 
        ToAreYouSure, 
        ToGameState,
        CancelCurrentState,
        ToMapSelection, 
        ToSpecificModeSelection, 
        
        // Game State 
        HoveringInfo,
        NextPriority, 
        PreviousPriority,
        
        // Mode
        HoveringReverseMode, 
        HoveringAlternateBloonsMode,
        HoveringApopalyseMode,
        
        //UI towers
        //Hovering
        HoveringChooseBomb,
        
        //Clicked
        
        /*-------------------------------------------------------------LOGIC------------------------------------------------------------------*/
        // Options (later)
        NewGame, // Begin a new game without save
        Continue, // Continue save game
        Exit, // Exit game, so when player clicks here, we should save the game 
        StartGame, // Start the round 
        BackHome, // Pause the game to back home
        Resume, // Unpause the game, we will back to the game immediately
        
        // TargetPriority - choose TargetPriority for the current tower
        Priority_First, 
        Priority_Last, 
        Priority_Close, 
        Priority_Strong, 
        
        // Difficulty - choose (Easy-Medium-Hard-Impoppable) Difficulty
        ToEasyModeSelection, 
        ToMediumModeSelection, 
        ToHardModeSelection,
        ToImpoppableModeSelection,
        
        // Mode - choose game modes
        StandardMode, 
        AlternateBloonsMode,
        ReverseMode, 
        ApopalyseMode,
        
        // Map - choose maps
        ToMonkeyLane,
        ToJungleLane, 
        
        // Settings
        AutoNextRound, // We should auto next round
        UnAutoNextRound, // We should unauto next round
        TickFastForward, // We should FastForward the game
        UntickFastForward, // We should Stop FastForward the game
        
        // Tower - handle tower placing
        // Clicked the button
        ClickedChooseBomb, // player begins to place Tower, we should know the valid points on the map
    };

};

#endif // EVENT_H