#pragma once

#include "Material.hpp"
#include <cmath>
#include <numeric>
#include <random>


class PerlinNoise2D {
private:
    std::vector<int> p;
    static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    static double lerp(double t, double a, double b) { return a + t * (b - a); }
    static double grad(int hash, double x, double y) {
        int h = hash & 7;
        double u = h < 4 ? x : y;
        double v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2 * v : 2 * v);
    }

public:
    PerlinNoise2D() {
        p.resize(256);
        std::iota(p.begin(), p.end(), 0);
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(p.begin(), p.end(), generator);
        p.insert(p.end(), p.begin(), p.end());
    }

    double noise(double x, double y) {
        int X = (int)floor(x) & 255;
        int Y = (int)floor(y) & 255;
        x -= floor(x);
        y -= floor(y);
        double u = fade(x);
        double v = fade(y);
        int A = p[X] + Y, AA = p[A], AB = p[A + 1],
            B = p[X + 1] + Y, BA = p[B], BB = p[B + 1];

        return lerp(v, lerp(u, grad(p[AA], x, y), grad(p[BA], x - 1, y)),
                       lerp(u, grad(p[AB], x, y - 1), grad(p[BB], x - 1, y - 1)));
    }
};

namespace RayTracer {
class PerlinNoiseMaterial : public Material {
public:
    PerlinNoiseMaterial(const Math::RGBA &color1,
                        const Math::RGBA &color2,
                        double scale = 1.0)
        : Material(1.0, 5)
        , color1(color1)
        , color2(color2)
        , scale(scale),
            perlinNoise(PerlinNoise2D())
    {
    }

    Math::RGBA getColor(double u, double v) override
    {
        double x = u / scale;
        double y = v / scale;
        double noise = perlinNoise.noise(x, y);
        double factor = (noise + 1.0) / 2.0;
        return Math::RGBA(color1.R * (1 - factor) + color2.R * factor,
                          color1.G * (1 - factor) + color2.G * factor,
                          color1.B * (1 - factor) + color2.B * factor,
                          color1.A * (1 - factor) + color2.A * factor);
    }

private:
    Math::RGBA color1;
    Math::RGBA color2;
    double scale;
    PerlinNoise2D perlinNoise;
};

} // namespace RayTracer
