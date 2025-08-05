#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"
#include <vector>
#include <memory>
#include <cmath>

class Shape {
public:
    float rotation; // degrees

    Shape(float rotation = 0.0f) : rotation(rotation) {}
    virtual ~Shape() = default;
    virtual bool collidesWith(const Shape& other) const = 0;
};

class CircleShape : public Shape {
public:
    Vector2 center;
    float radius;

    CircleShape(Vector2 center, float radius, float rotation = 0.0f)
        : Shape(rotation), center(center), radius(radius) {}

    bool collidesWith(const Shape& other) const override;
};

class RectShape : public Shape {
public:
    Vector2 center;
    float width, height;

    RectShape(Vector2 center, float width, float height, float rotation = 0.0f)
        : Shape(rotation), center(center), width(width), height(height) {}

    bool collidesWith(const Shape& other) const override;

    std::vector<Vector2> getCorners() const;
};

class Hitbox {
private:
    std::vector<std::shared_ptr<Shape>> shapes;

public:
    void addCircle(Vector2 center, float radius, float rotation = 0.0f) {
        shapes.push_back(std::make_shared<CircleShape>(center, radius, rotation));
    }

    void addRect(Vector2 center, float width, float height, float rotation = 0.0f) {
        shapes.push_back(std::make_shared<RectShape>(center, width, height, rotation));
    }

    bool checkCollisionWith(const Hitbox& other) const {
        for (const auto& s1 : shapes)
            for (const auto& s2 : other.shapes)
                if (s1->collidesWith(*s2))
                    return true;
        return false;
    }
};

#endif
