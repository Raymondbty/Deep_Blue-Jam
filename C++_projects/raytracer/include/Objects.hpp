/*
** EPITECH PROJECT, 2023
** Objects.hpp
** File description:
** Object class
*/
#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Color.hpp"
#include <iostream>

namespace raytracer {
    namespace objects {
        class IObject {
        public:
            virtual void setPosition(Vector3<int> position) = 0;
            virtual void setRotation(Vector3<int> position) = 0;
            virtual void setColor(Color color) = 0;
            virtual Vector3<int> getPosition() const = 0;
            virtual Vector3<int> getRotation() const = 0;
            virtual Color getColor() const = 0;
        };

        class Object : public IObject {
        public:
            Object(
                Vector3<int> position,
                Vector3<int> rotation,
                Color color
            );
            ~Object() = default;

            void setPosition(Vector3<int> position) override;
            void setRotation(Vector3<int> position) override;
            void setColor(Color color) override;

            Vector3<int> getPosition() const override;
            Vector3<int> getRotation() const override;
            Color getColor() const override;
        protected:
            Vector3<int> _position;
            Vector3<int> _rotation;
            Color _color;
        };

        class Sphere : public Object {
        public:
            Sphere(
                Vector3<int> position,
                Vector3<int> rotation,
                Color color,
                unsigned int radius
            );
            ~Sphere() = default;

            void setRadius(unsigned int radius);
            unsigned int getRadius() const;

            bool isIntersect(Vector3<int> position) const;
        private:
            unsigned int _radius;
        };

        class Plane : public Object {
        public:
            Plane(
                std::string axis,
                Vector3<int> position,
                Vector3<int> rotation,
                Color color,
                Vector2<int> size
            );
            ~Plane() = default;

            Vector2<int> getSize() const;
            std::string getAxis() const;

            bool isIntersect(Vector3<int> position) const;
        private:
            Vector2<int> _size;
            std::string _axis;
        };

        class Camera : public Object {
        public:
            Camera(
                Vector3<int> position,
                Vector3<int> rotation,
                Vector2<int> resolution,
                double fov
            );
            ~Camera() = default;

            Vector2<int> getResolution() const;
            double getFov() const;
        private:
            Vector2<int> _resolution;
            double _fov;
        };

        class AmbientLight : public Object {
        public:
            AmbientLight(
                Vector3<int> position,
                Vector3<int> rotation,
                float intensity
            );
            ~AmbientLight() = default;

            float getIntensity() const;
        private:
            float _intensity;
        };

        class DirectionalLight : public Object {
        public:
            DirectionalLight(
                Vector3<int> position,
                Vector3<int> rotation,
                float intensity
            );
            ~DirectionalLight() = default;

            float getIntensity() const;
        private:
            float _intensity;
        };

        class Cylinder : public Object {
        public:
            Cylinder(
                Vector3<int> position,
                Vector3<int> rotation,
                Color color,
                unsigned int radius,
                unsigned int height
            );
            ~Cylinder() = default;

            void setRadius(unsigned int radius);
            unsigned int getRadius() const;

            void setHeight(unsigned int height);
            unsigned int getHeight() const;
        private:
            unsigned int _radius;
            unsigned int _height;
        };

        class Cone : public Object {
        public:
            Cone(
                Vector3<int> position,
                Vector3<int> rotation,
                Color color,
                unsigned int radius,
                unsigned int height
            );
            ~Cone() = default;

            void setRadius(unsigned int radius);
            unsigned int getRadius() const;

            void setHeight(unsigned int height);
            unsigned int getHeight() const;
        private:
            unsigned int _radius;
            unsigned int _height;
        };
    }
}