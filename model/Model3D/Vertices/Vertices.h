#pragma once
#include <vector>
#include "../../math_core/Vec3.h"


namespace s21 {
    
    struct Vertices {
        std::vector<Vec3> vrts;

        double getMaxDeltaX() const;
        double getMaxDeltaY() const;
        double getMaxDeltaZ() const;

        double getCenterX() const;
        double getCenterY() const;
        double getCenterZ() const;

    };  //struct Vertices
}  // namespace s21