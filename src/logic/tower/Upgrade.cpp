#include "Upgrade.h"
#include "../../core/Game.h"

Upgrade::Upgrade(const std::string& name, int cost, const std::string& description)
    : name(name), cost(cost), description(description), tag("NoUpgrade") {
    nextUpgrade = nullptr;
}

// default state mean no upgrade avaiable

Upgrade::Upgrade(const Upgrade& other)
    : name(other.name), cost(other.cost), description(other.description), tag(other.tag) {
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Upgrade::clone() const {
    return std::make_unique<Upgrade>(*this);
}

void Upgrade::loadTexture() {
    Game::Instance().getTextureManager().loadTexture(tag, "assets/tower/NoUpgradeIcon.png");
}

void Upgrade::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    // Should do nothin
    std::cerr << "Update NoUpgrade\n";
}

std::unique_ptr<Upgrade> Upgrade::buy() {
    // Should do nothin
    std::cerr << "Buy NoUpgrade\n";
    return nullptr;
}

const std::string& Upgrade::getName() const {
    return name;
}

int Upgrade::getCost() const {
    return cost;
}

const std::string& Upgrade::getDescription() {
    return description;
}

void Upgrade::setCost(int newCost) {
    cost = newCost;
}