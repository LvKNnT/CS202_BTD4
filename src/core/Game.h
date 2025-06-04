#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    ~Game();

    void LoadContent();
    void UnloadContent();

    void initialize();
    void render();
    void update(float deltaTime);
private:

};

#endif // GAME_H