#include "Enemy.h"
#include "../../core/Game.h"

Enemy::Enemy(Vector2 position, Vector2 size, float rotation, BloonType type, int health, int speed, int reward, int livesLost)
    : GameObject(position, size, rotation, "Enemy"), type(type), health(health), speed(speed), reward(reward), livesLost(livesLost), trackIndex(0), pathIndex(0), properties(BloonProperties()), debuff(BloonDebuff()), regrowLimit(type), regrowTimer(0.0f), enemyId(-1) {
    // Constructor implementation can be extended if needed

}

int Enemy::getId() const {
    return enemyId;
}

int Enemy::getSpeed() const {
    return speed;
}

Vector2 Enemy::getPosition() const {
    return position;
}

BloonProperties Enemy::getProperties() const {
    return properties;
}

BloonType Enemy::getType() const {
    return type;
}

void Enemy::updateEffect() {
    if(tag.empty()) return;    
    // Stun effect
    if(debuff.stunDuration > 0.0f) {
        Texture texture = Game::Instance().getTextureManager().getTexture(tag);
        if(effects.stunEffect.isAnimationPlaying() == false) {
            effects.stunEffect = Animation("stun", texture.height / 1.5f, texture.width / 1.5f, 4, 0.1, true);
            effects.stunEffect.start();
        }
        effects.stunEffect.setPosition((Vector2) {position.x - texture.width / 3.0f, position.y - texture.height / 1.5f});
    } else effects.stunEffect.stop();
 
    // Freeze effect
    if(debuff.freezeDuration > 0.0f) {
        Texture texture = Game::Instance().getTextureManager().getTexture(tag);
        if(effects.freezeEffect.isAnimationPlaying() == false) {
            effects.freezeEffect = Animation("freeze", texture.height, texture.width, 1, debuff.freezeDuration, false);
            effects.freezeEffect.start();
        }
        effects.freezeEffect.setPosition((Vector2) {position.x - texture.width / 2.0f, position.y - texture.height / 2.0f});
    } else effects.freezeEffect.stop();

    // Slow effect
    if(debuff.slowDuration > 0.0f) {
        effects.colorTint = effects.slowColor;
    } else effects.colorTint = effects.normalColor;
    effects.update();
}
    
void Enemy::drawEffect() const {
    //if(!isActiveFlag) return;
    effects.draw();
}

void Enemy::drawDeadEffect() {
    Texture texture = Game::Instance().getTextureManager().getTexture(tag);
    effects.deadEffect = Animation("starburst", (Vector2) {position.x - texture.width / 2, position.y - texture.height / 2}, 0.0f, texture.height, texture.width, 4, 0.0125);
    effects.deadEffect.start();
    Game::Instance().getAnimationManager().addAnimation(effects.deadEffect);
}
