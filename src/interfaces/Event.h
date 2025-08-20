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
        MuteSound,
        UnmuteSound, 
        MuteMusic,
        UnmuteMusic,
        TickJiggle,
        UntickJiggle,
        
        // State
        ToOptions, 
        ToAreYouSure, 
        ToGameState,
        CancelCurrentState,
        ToMapSelection, 
        ToSpecificModeSelection, 
        ToGameOver,
        ToVictory, 
        ToHeroSelection,

        // Game State
        UpgradeTowerLeft,
        UpgradeTowerMiddle,
        UpgradeTowerRight,
        HoveringInfo,
        NextPriority, 
        PreviousPriority,
        SellTower,
        Replay,
        
        // Mode
        HoveringStandardMode,
        HoveringReverseMode, 
        HoveringAlternateBloonsMode,
        HoveringApopalyseMode,
        
        //UI towers
        //Hovering
        HoveringChooseDartMonkey,
        HoveringChooseBomb,
        HoveringChooseNinjaMonkey,
        HoveringChooseSniperMonkey,
        HoveringChooseIceMonkey,
        HoveringChooseMonkeySub,

        //Clicked
        ClickedChooseBomb, // player begins to place Tower, we should know the valid points on the map
        ClickedChooseDartMonkey, 
        ClickedChooseNinjaMonkey,
        ClickedChooseSniperMonkey,
        ClickedChooseIceMonkey,
        ClickedChooseMonkeySub,

        // Bullets idk
        HoveringChooseSpike,
        HoveringChoosePineapple,

        ClickedChooseSpike,
        ClickedChoosePineapple,

//----------------------------------------------------------------------LOGIC------------------------------------------------------------------
        // Options (later)
        NewGame, // Begin a new game without save
        Continue, // Continue save game
        Exit, // Exit game, so when player clicks here, we should save the game 
        StartRound, // Start the round 
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
        ToRinkRevenge,
        ToDuneSea,
        ToAttackOnBloon,
        
        // Settings
        AutoNextRound, // We should auto next round
        UnAutoNextRound, // We should unauto next round
        TickFastForward, // We should FastForward the game
        UntickFastForward, // We should Stop FastForward the game
        
        // Heros
        HoveringQuincy,
        ClickedQuincy,
        HoveringBenjamin,
        ClickedBenjamin,
        HoveringRosalia,
        ClickedRosalia,
        HoveringEtienne,
        ClickedEtienne,
    };

};

#endif // EVENT_H