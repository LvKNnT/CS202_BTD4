#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    enum class Type {
        None, 
        // UI
        MainMenuToMapSelection, 
        CancleMapSelection,
        Exit,
        // Logic

    };
};

#endif // EVENT_H