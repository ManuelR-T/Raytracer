/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"
#include "Shapes/IShape.hpp"

#include <memory>
#include <sys/types.h>
#include <tuple>

namespace RayTracer {

Camera::Camera(const Point3D &origin,
               const Vector3D &direction,
               const Vector3D &up)
    : origin(origin)
    , direction(direction.normalized())
    , up(up.normalized())
{
}

Ray Camera::ray(double u, double v, double fov, double aspectRatio) const
{
    Vector3D right = up.cross(direction).normalized();
    Vector3D adjustedUp = direction.cross(right).normalized();
    double scale = tan(fov * 0.5 * M_PI / 180);

    Vector3D rayDirection = (right * (u - 0.5) * scale * aspectRatio +
                             adjustedUp * (v - 0.5) * scale + direction)
                                .normalized();

    return Ray(origin, rayDirection);
}

static void applyDiffuseLight(Math::RGBA &loopColor,
                              const Math::RGBA &closestColor,
                              const Math::RGBA &lightColor,
                              double dot)
{
    loopColor.R = closestColor.R * lightColor.R * dot / 255.0;
    loopColor.G = closestColor.G * lightColor.G * dot / 255.0;
    loopColor.B = closestColor.B * lightColor.B * dot / 255.0;
}

static void applySpecularLight(
    Math::RGBA &loopColor,
    const Math::RGBA &lightColor,
    double dot,
    const Vector3D &viewDir,
    const Vector3D &lightDir,
    const Vector3D &normal,
    const std::vector<std::unique_ptr<IShape>>::const_iterator &closestShapeIt)
{
    double shininess = (*closestShapeIt)->getMaterial().shininess;
    if (shininess == 0)
        return;
    Vector3D reflectDir = (2 * dot * normal - lightDir).normalized();
    double spec = std::pow(std::max(viewDir.dot(reflectDir), .0), shininess);
    loopColor += lightColor * spec;
}

static std::tuple<double,
                  Math::RGBA,
                  Point3D,
                  std::vector<std::unique_ptr<IShape>>::const_iterator>
getClosestShapeInfo(const Ray &ray, const Scene &scene)
{
    double minDist = std::numeric_limits<double>::infinity();
    Math::RGBA closestColor = Math::RGBA{0, 0, 0, 0};
    Point3D hitPoint;
    auto closestShapeIt = scene.shapes.end();

    for (auto it = scene.shapes.begin(); it != scene.shapes.end(); ++it) {
        double dist;
        Math::RGBA hitColor;
        if ((*it)->hits(ray, hitColor, dist) && dist < minDist && dist > 0) {
            minDist = dist;
            closestColor = hitColor;
            closestShapeIt = it;
            hitPoint = ray.m_origin + ray.m_direction * dist;
        }
    }
    return std::make_tuple(minDist, closestColor, hitPoint, closestShapeIt);
}

static void applyLight(
    const Scene &scene,
    const std::vector<std::unique_ptr<IShape>>::const_iterator &closestShapeIt,
    const Math::RGBA &closestColor,
    const Point3D &hitPoint,
    Math::RGBA &finalColor,
    const Vector3D &viewDir
)
{
    for (const auto &light : scene.lights) {
        Math::RGBA loopColor = Math::RGBA{0, 0, 0, 1};
        Vector3D lightDir = light->getDirectionToPoint(hitPoint).normalized();

        Ray lightRay(hitPoint, lightDir * (-1));
        double currShapeToLight = lightDir.length();
        bool isCollision = false;
        for (auto &obj: scene.shapes) {
            if (*closestShapeIt == obj)
                continue;
            Math::RGBA color;
            double distance = 0.f;
            if (obj->hits(lightRay, color, distance) == true && distance < currShapeToLight) {
                isCollision = true;
                break;
            }
        }
        // if (isCollision)
        //     continue;

        Math::RGBA lightColor = light->getIntensityAt(hitPoint);
        Vector3D normal = (*closestShapeIt)->getNormal(hitPoint) * -1;
        double dot = std::max(lightDir.dot(normal), 0.0);

        if (dot > 0)
            applyDiffuseLight(loopColor, closestColor, lightColor, dot);
        applySpecularLight(loopColor,
                           lightColor,
                           dot,
                           viewDir,
                           lightDir,
                           normal,
                           closestShapeIt);
        finalColor += loopColor * (0.8 * currShapeToLight);
    }
}

Math::RGBA Camera::traceRay(const Ray &ray, const Scene &scene) const
{
    double minDist;
    Math::RGBA closestColor;
    Point3D hitPoint;
    std::vector<std::unique_ptr<IShape>>::const_iterator closestShapeIt;

    std::tie(minDist, closestColor, hitPoint, closestShapeIt) =
        getClosestShapeInfo(ray, scene);

    if (closestShapeIt != scene.shapes.end()) {
        Math::RGBA finalColor = scene.ambientLight * closestColor;

        applyLight(scene,
                   closestShapeIt,
                   closestColor,
                   hitPoint,
                   finalColor,
                   (ray.m_direction).normalized());
        return finalColor.clamp();
    }
    return closestColor;
}
} // namespace RayTracer
