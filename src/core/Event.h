#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    enum class Type {
        None, 
        // UI
        MainMenuToMapSelection, 
        CancelMapSelection,
        Exit,
        MoveNext,
        MovePrevious,
        MapSelectionToMonkeyLane
        // Logic

    };
};

#endif // EVENT_H