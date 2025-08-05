#include "Hitbox.h"

static float dotProduct(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

static Vector2 rotatePoint(Vector2 point, Vector2 origin, float angleDegrees) {
    float angle = angleDegrees * DEG2RAD;
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    Vector2 result;
    point.x -= origin.x;
    point.y -= origin.y;
    result.x = point.x * cosA - point.y * sinA + origin.x;
    result.y = point.x * sinA + point.y * cosA + origin.y;
    return result;
}

std::vector<Vector2> RectShape::getCorners() const {
    Vector2 half = { width / 2, height / 2 };
    std::vector<Vector2> corners = {
        { center.x - half.x, center.y - half.y },
        { center.x + half.x, center.y - half.y },
        { center.x + half.x, center.y + half.y },
        { center.x - half.x, center.y + half.y }
    };
    for (auto& pt : corners) {
        pt = rotatePoint(pt, center, rotation);
    }
    return corners;
}

static bool pointInCircle(Vector2 p, Vector2 c, float r) {
    float dx = p.x - c.x, dy = p.y - c.y;
    return dx * dx + dy * dy <= r * r;
}

static bool polygonsIntersect(const std::vector<Vector2>& a, const std::vector<Vector2>& b) {
    auto project = [](const std::vector<Vector2>& verts, Vector2 axis) {
        float min = dotProduct(verts[0], axis);
        float max = min;
        for (const auto& v : verts) {
            float proj = dotProduct(v, axis);
            if (proj < min) min = proj;
            if (proj > max) max = proj;
        }
        return std::make_pair(min, max);
    };

    auto overlap = [](std::pair<float, float> a, std::pair<float, float> b) {
        return a.second >= b.first && b.second >= a.first;
    };

    std::vector<Vector2> edges;
    for (size_t i = 0; i < a.size(); ++i) {
        Vector2 edge = { a[(i+1)%a.size()].x - a[i].x, a[(i+1)%a.size()].y - a[i].y };
        Vector2 axis = { -edge.y, edge.x }; // perpendicular
        edges.push_back(axis);
    }
    for (size_t i = 0; i < b.size(); ++i) {
        Vector2 edge = { b[(i+1)%b.size()].x - b[i].x, b[(i+1)%b.size()].y - b[i].y };
        Vector2 axis = { -edge.y, edge.x };
        edges.push_back(axis);
    }

    for (const auto& axis : edges) {
        if (!overlap(project(a, axis), project(b, axis)))
            return false;
    }
    return true;
}

bool CircleShape::collidesWith(const Shape& other) const {
    if (const auto* circle = dynamic_cast<const CircleShape*>(&other)) {
        float dx = center.x - circle->center.x;
        float dy = center.y - circle->center.y;
        float distSq = dx * dx + dy * dy;
        float rSum = radius + circle->radius;
        return distSq <= rSum * rSum;
    }
    if (const auto* rect = dynamic_cast<const RectShape*>(&other)) {
        std::vector<Vector2> corners = rect->getCorners();
        for (auto& pt : corners) {
            if (pointInCircle(pt, center, radius))
                return true;
        }
        return false; // approximation: we skip edge/corner projection
    }
    return false;
}

bool RectShape::collidesWith(const Shape& other) const {
    if (const auto* rect = dynamic_cast<const RectShape*>(&other)) {
        return polygonsIntersect(this->getCorners(), rect->getCorners());
    }
    if (const auto* circle = dynamic_cast<const CircleShape*>(&other)) {
        return circle->collidesWith(*this);
    }
    return false;
}
