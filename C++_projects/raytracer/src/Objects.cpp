/*
** EPITECH PROJECT, 2023
** Objects.cpp
** File description:
** Object classes definitions
*/
#include "Objects.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace raytracer {
    namespace objects {
        Object::Object(
            Vector3<int> position,
            Vector3<int> rotation,
            Color color
        )
            : _position(position),
            _rotation(rotation),
            _color(color)
        {}

        void Object::setPosition(Vector3<int> position)
        {
            _position = position;
        }

        void Object::setRotation(Vector3<int> rotation)
        {
            _rotation = rotation;
        }

        void Object::setColor(Color color)
        {
            _color = color;
        }

        Vector3<int> Object::getPosition() const
        {
            return _position;
        }

        Vector3<int> Object::getRotation() const
        {
            return _rotation;
        }

        Color Object::getColor() const
        {
            return _color;
        }

        Sphere::Sphere(
            Vector3<int> position,
            Vector3<int> rotation,
            Color color,
            unsigned int radius
        )
            : Object(position, rotation, color), _radius(radius)
        {}

        void Sphere::setRadius(unsigned int radius)
        {
            _radius = radius;
        }

        unsigned int Sphere::getRadius() const
        {
            return _radius;
        }

        Plane::Plane(
            std::string axis,
            Vector3<int> position,
            Vector3<int> rotation,
            Color color,
            Vector2<int> size
        )
            : Object(position, rotation, color), _size(size), _axis(axis)
        {}

        Vector2<int> Plane::getSize() const
        {
            return _size;
        }

        Camera::Camera(
            Vector3<int> position,
            Vector3<int> rotation,
            Vector2<int> resolution,
            double fov
        )
            : Object(position, rotation, Color(0, 0, 0)),
            _resolution(resolution),
            _fov(fov)
        {}

        Vector2<int> Camera::getResolution() const
        {
            return _resolution;
        }

        double Camera::getFov() const
        {
            return _fov;
        }

        AmbientLight::AmbientLight(
            Vector3<int> position,
            Vector3<int> rotation,
            float intensity
        )
            : Object(position, rotation, Color(255, 255, 255)),
            _intensity(intensity)
        {}

        float AmbientLight::getIntensity() const
        {
            return _intensity;
        }

        DirectionalLight::DirectionalLight(
            Vector3<int> position,
            Vector3<int> rotation,
            float intensity
        )
            : Object(position, rotation, Color(255, 255, 255)),
            _intensity(intensity)
        {}

        float DirectionalLight::getIntensity() const
        {
            return _intensity;
        }

        Cylinder::Cylinder(
            Vector3<int> position,
            Vector3<int> rotation,
            Color color,
            unsigned int radius,
            unsigned int height
        )
            : Object(position, rotation, color), _radius(radius), _height(height)
        {}

        void Cylinder::setRadius(unsigned int radius)
        {
            _radius = radius;
        }

        unsigned int Cylinder::getRadius() const
        {
            return _radius;
        }

        void Cylinder::setHeight(unsigned int height)
        {
            _height = height;
        }

        unsigned int Cylinder::getHeight() const
        {
            return _height;
        }

        Cone::Cone(
            Vector3<int> position,
            Vector3<int> rotation,
            Color color,
            unsigned int radius,
            unsigned int height
        )
            : Object(position, rotation, color), _radius(radius), _height(height)
        {}

        void Cone::setRadius(unsigned int radius)
        {
            _radius = radius;
        }

        unsigned int Cone::getRadius() const
        {
            return _radius;
        }

        void Cone::setHeight(unsigned int height)
        {
            _height = height;
        }

        unsigned int Cone::getHeight() const
        {
            return _height;
        }
    }
}
