#ifndef SHARPSHOTS_H
#define SHARPSHOTS_H

#include "../../Upgrade.h"
#include "../../../../core/Game.h"
#include "../../../../interfaces/Drawable.h"

class SharpShots : public Upgrade {
public:
    SharpShots();
    SharpShots(const SharpShots& other);
    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture();

    // SharpShots does not need to be drawn, but we need to implement it
    void draw() const override;
    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // SHARPSHOTS_H