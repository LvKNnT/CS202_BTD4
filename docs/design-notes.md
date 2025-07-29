# UML Diagram Explanation
***
I’m not sure if I wrote this correctly, but I will try to explain everything based on the diagram.
This UML is specified for C++ and the external library **Raylib**.
***

## Interface Classes
These interface classes are designed for future expansion and modularity.

- Drawable: Defines objects that can be drawn on the screen.
- Updatable: Defines objects that update themselves during each game frame.

### Drawable
This interface ensures that all visual elements can be rendered on the screen.

```mermaid
classDiagram 
    %% Interfaces
    class Drawable {
        <<interface>>
        +draw()
    }

    %% Interfaces relationships
    Drawable <|-- Screen
    Drawable <|-- Panel
    Drawable <|-- PanelElement
    Drawable <|-- GameObject
```
**Explanation:** 
- *Screen*: Represents different game screens, such as the main menu or gameplay.
- *Panel*: UI components within screens (e.g., settings panels, menus).
- *PanelElement*: Smaller UI elements like buttons and text fields.
- *GameObject*: Core objects in the game world (towers, enemies, bullets, etc.).

### Updatable
This interface allows game objects to update their state every frame.

```mermaid
classDiagram
    class Updatable {
        <<interface>>
        +update()
    }

    %% Interfaces relationships
    Updatable <|-- Screen
    Updatable <|-- Panel
    Updatable <|-- PanelElement
    Updatable <|-- GameLogic
    Updatable <|-- GameObject
```
**Explanation:**
- *Screen*: Can update animations or handle screen transitions.
- *Panel*: Updates UI logic such as hover effects or panel animations.
- *PanelElement*: Updates for interactive elements (like buttons changing state).
- *GameLogic*: Updates core game logic (spawning, scoring, etc.).
- *GameObject*: Updates game world objects (movement, collisions, etc.).
***

## Core Classes
### Game
The main entry point of the game. It manages high-level systems:

- *GameLogic*: Core gameplay rules (towers, enemies, bullets).
- *InputManager*: Handles user input (mouse, keyboard).
- *SoundManager*: Controls sound and music.
- *ScreenManager*: Controls which screen is currently visible.
- *SpriteManager*: Manages loading and drawing of game sprites.
- *ScreenList*: Holds all available screens.

```mermaid
classDiagram 
    class Game {
        -gameLogic: GameLogic
        -inputManager: InputManager
        -soundManager: SoundManager
        -screenManager: ScreenManager
        -spriteManager: SpriteManager
        -screenList: vector~Screen~

        +Game()
        +LoadContent()
        +Initialize()
        +UnloadContent()
        +render()
        +update()
    }

    %% Game Relationships
    Game -- FileManager
    Game -- GameLogic
    Game -- InputManager
    Game -- SoundManager
    Game -- ScreenManager
    Game -- SpriteManager
    Game -- Screen
```
***

## Game Logic Subsystem
### GameLogic
Controls the main gameplay, including:

- *Levels*: Manages game levels.
- *Settings*: Game options such as resolution and sound.
- *LogicManager*: Manages specific game object types.

```mermaid
classDiagram
    class GameLogic {
        -levels: Levels
        -settings: Settings
        -logicManager: LogicManager

        +GetDrawable()
        +Init()
        +Update()
    }

    GameLogic -- Map
    GameLogic -- Settings
    GameLogic -- Levels
    GameLogic -- LogicManager
```

### LogicManager 
Handles the update and draw logic for different groups of game objects:

- *BulletManager*: Controls bullets.
- *EffectManager*: Manages effects like explosions.
- *EnemyManager*: Controls enemy movement and health.
- *TowerManager*: Handles towers and their behavior.

Each of these managers has its own list of objects (e.g., a vector\<Bullet\> for bullets).

```mermaid
classDiagram
    class LogicManager {
        +GetDrawable()
        +Update()
    }

    LogicManager <|-- BulletManager
    LogicManager <|-- EffectManager
    LogicManager <|-- EnemyManager
    LogicManager <|-- TowerManager

    class BulletManager {
        -bulletList: vector~Bullet~

        +BulletManager()
        +addBullet(Bullet)
        +removeBullet(Bullet)
        +update()
    }

    BulletManager -- Bullet

    class EffectManager {
        -effectList: vector~Effect~

        +EffectManager()
        +addEffect(Effect)
        +removeEffect(Effect)
        +update()
    }

    EffectManager -- Effect

    class EnemyManager {
        -enemyList: vector~Enemy~

        +EnemyManager()
        +addEnemy(Enemy)
        +removeEnemy(Enemy)
        +update()
    }

    EnemyManager -- Enemy

    class TowerManager {
        -towerList: vector~Tower~

        +TowerManager()
        +addTower(Tower)
        +removeTower(Tower)
        +update()
    }

    TowerManager -- Tower
```
***

## Game Objects
### GameObject
Base class for all objects in the game world:

- *Bullet*: Fired from towers, moves toward enemies.
- *Effect*: Visuals like explosions.
- *Enemy*: The creeps that towers must destroy.
- *Tower*: The player's main defense structures.

Each subclass has its own attributes and methods:

- Bullets have damage, velocity, and hit()/miss() logic.
- Enemies have hp, reward, and die() logic.
- Towers can attack() enemies and upgrade().

```mermaid
classDiagram
    class GameObject {
        -name: string
        -position: Vector2

        +GameObject(name, position)
        +draw()
        +update()
    }

    GameObject <|-- Bullet
    GameObject <|-- Effect
    GameObject <|-- Enemy
    GameObject <|-- Tower

    class Bullet {
        -type: enum
        -velocity: Vector2
        -damage: int
        -timeFired: int

        +Bullet(type, position, velocity, damage, timeFired)
        +hit()
        +miss()
        +remove()
    }

    class Effect {
        -startFrame: int
        -animSpeed: int

        +Effect()
        +play()
        +stop()
        +remove()
    }

    class Enemy {
        -type: enum
        -velocity: Vector2
        -hp: int
        -reward: int

        +Enemy(type, position, velocity, hp, reward)
        +run()
        +hit()
        +die()
        +remove()
    }

    class Tower {
        -type: enum
        -position: Vector2
        -range: int
        -damage: int
        -fireRate: int
        -cost: int
        -tier: int

        +Tower(type, position, range, damage, fireRate, cost)
        +attack(Enemy)
        +upgrade()
        +checkRange()
        +remove()
    }
```
***

## User Interface System
### Screen
- Represents a full-screen UI, such as a menu or gameplay screen.
- Each Screen contains:
  - One or more Panels for organizing UI elements.
  - Panels contain PanelElements (buttons, text fields, input fields).

```mermaid
classDiagram
    class Screen {
        -height: int
        -width: int
        -background: Texture

        +Screen()
        +onButtonClick(Button)
        +draw()
        +update()
    }

    Screen *-- Panel
    Screen <|-- MainMenuScreen
    Screen <|-- OptionsScreen
    Screen <|-- GameScreen
    Screen <|-- MapScreen

    class MainMenuScreen {
        -mainMenu: Panel

        +MainMenuScreen()
    }

    class OptionsScreen {
        -optionsPanel: Panel

        +OptionsScreen()
    }

    class GameScreen {
        -gamePanel: Panel

        +GameScreen()
    }

    class MapScreen {
        -mapPanel: Panel

        +MapScreen()
    }

    class Panel {
        -elements: vector~PanelElement~
        -height: int
        -width: int
        -title: string
        -position: Vector2

        +Panel()
        +addPanelElement(PanelElement)
        +removePanelElement(PanelElement)
        +draw()
        +update()
    }

    Panel o-- PanelElement
```

### PanelElement
Base class for UI components:

- *Button*: A clickable button.
- *TextureField*: Displays textures or images.
- *TextField*: Displays text.
- *InputField*: Lets players enter text.

```mermaid
classDiagram
    class PanelElement {
        -index: int
        -height: int
        -width: int
        -position: Vector2

        +PanelElement()
        +draw()
    }

    PanelElement <|-- Button
    PanelElement <|-- TextureField
    PanelElement <|-- TextField
    PanelElement <|-- InputField

    class Button {
        -texture: Texture
        -title: string

        +Button(title)
        +onClick()
    }

    class TextureField {
        -textureList: vector~Texture~
        -height: int
        -width: int
        -position: Vector2

        +TextureField()
        +addTexture(Texture)
        +removeTexture(Texture)
    }

    class TextField {
        -text: string
        -font: Font
        -color: Color
        -height: int
        -width: int
        -position: Vector2

        +TextField()
        +setText()
    }

    class InputField {
        -maxLength: int 
        -text: string
        -height: int
        -width: int
        -position: Vector2

        +InputField()
        +setText(string)
        +getText()
    }
```
***

## Managers
### InputManager
Handles keyboard and mouse input:

- Tracks mouse position, clicks, and key presses.

```mermaid
classDiagram
    class InputManager {
        -mouseState: int
        -keyboardState: int
        -mousePosition: Vector2

        +getMouseState()
        +getKeyboardState()
        +getMousePosition()
    }
```

### SoundManager
Controls sound playback:

- Can play, stop, or mute sounds.
- Uses SoundChannels for categories (e.g., music, effects).

```mermaid
classDiagram
    class SoundManager {
        -volume: float
        -isMuted: bool
        -sounds: map~soundType, SoundChannel~

        +SoundManager()
        +setVolume(volume)
        +toggleMute()
        +playSound(soundType, soundName)
    }

    SoundManager -- SoundChannel
    SoundChannel -- Sound

    class SoundChannel {
        -volume: float
        -isMuted: bool
        -soundList: vector~Sound~

        +SoundChannel()
        +setVolume(volume)
        +toggleMute()
        +playSound(soundName)
    }

    class Sound {
        -file: file

        +start()
        +stop()
    }
```

### FileManager
- Handles file import/export.
- Extended by EnemyImport, TowerImport, and MapImport to load specific game data.

```mermaid
classDiagram
    class FileManager {
        +importFile(filePath)
        +exportFile(filePath)
    }

    FileManager <|-- EnemyImport
    FileManager <|-- TowerImport
    FileManager <|-- MapImport
```
***

# Summary
This UML diagram outlines a modular architecture for a Tower Defense game:

- Interfaces define common behavior.
- Managers organize game components.
- The GameObject hierarchy handles core game logic.
- The UI system manages user interaction.

