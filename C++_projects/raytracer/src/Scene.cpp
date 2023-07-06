/*
** EPITECH PROJECT, 2023
** Scene.cpp
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Objects.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "libconfig.h++"

#include <cstdlib>
#include <libconfig.h++>
#include <memory>

using std::cerr;
using std::endl;

namespace raytracer {
    Scene::Scene(std::string &filename)
        : _ambientLight(
            Vector3<int>(0, 0, 0),
            Vector3<int>(0, 0, 0),
            0.1
        ),
        _camera(
            Vector3<int>(0, 0, 0),
            Vector3<int>(0, 0, 0),
            Vector2<int>(500, 500),
            90.0
        )
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(filename.c_str());
        }
        catch(const libconfig::FileIOException &fioex) {
            cerr << "[!] I/O error while reading file." << endl;
            exit(EXIT_ERROR);
        }
        catch(const libconfig::ParseException &pex) {
            cerr << "[!] Parse error at ";
            cerr << pex.getFile();
            cerr << ":" << pex.getLine();
            cerr << " - " << pex.getError() << endl;
            exit(EXIT_ERROR);
        }
        try {
            const libconfig::Setting& root = cfg.getRoot();
            const libconfig::Setting &camera = root["camera"];
            Vector2<int> resolution(
                camera["resolution"]["width"],
                camera["resolution"]["height"]
            );
            Vector3<int> position(
                camera["position"]["x"],
                camera["position"]["y"],
                camera["position"]["z"]
            );
            Vector3<int> rotation(
                camera["rotation"]["x"],
                camera["rotation"]["y"],
                camera["rotation"]["z"]
            );
            double fov = camera["fieldOfView"];

            _camera = raytracer::objects::Camera(
                position,
                rotation,
                resolution,
                fov
            );

            const libconfig::Setting &primitives = root["primitives"];

            const libconfig::Setting &spheres = primitives["spheres"];
            for(int c = 0; c < spheres.getLength(); c++) {
                const libconfig::Setting &sphere = spheres[c];
                Vector3<int> spherePosition(
                    sphere["x"],
                    sphere["y"],
                    sphere["z"]
                );
                Vector3<int> sphereRotation(0, 0, 0);
                Color sphereColor(
                    static_cast<int>(sphere["color"]["r"]),
                    static_cast<int>(sphere["color"]["g"]),
                    static_cast<int>(sphere["color"]["b"])
                );
                unsigned int sphereRadius = sphere["r"];

                _spheres.push_back(
                    objects::Sphere(
                        spherePosition,
                        sphereRotation,
                        sphereColor,
                        sphereRadius
                    )
                );
            }

            const libconfig::Setting &planes = primitives["planes"];

            for(int c = 0; c < planes.getLength(); c++) {
                const libconfig::Setting &plane = planes[c];
                std::string planeAxis = plane["axis"];
                Vector3<int> planePosition(0, 0, 0);
                if (planeAxis == "x" || planeAxis == "X")
                    Vector3<int> planePosition(plane["position"], 0, 0);
                else if (planeAxis == "y" || planeAxis == "Y")
                    Vector3<int> planePosition(0, plane["position"], 0);
                else if (planeAxis == "z" || planeAxis == "Z")
                    Vector3<int> planePosition(0, 0, plane["position"]);
                else {
                    cerr << "[!] Invalid plane axis." << endl;
                    exit(EXIT_ERROR);
                }
                Vector3<int> planeRotation(0, 0, 0);
                Vector2<int> planeSize(0, 0);
                Color planeColor(
                    static_cast<int>(plane["color"]["r"]),
                    static_cast<int>(plane["color"]["g"]),
                    static_cast<int>(plane["color"]["b"])
                );

                _planes.push_back(
                    objects::Plane(
                        planeAxis,
                        planePosition,
                        planeRotation,
                        planeColor,
                        planeSize
                    )
                );
            }

            const libconfig::Setting &lights = root["lights"];
            double ambient = lights["ambient"];
            double diffuse = lights["diffuse"];

            _ambientLight = objects::AmbientLight(
                Vector3<int>(0, 0, 0),
                Vector3<int>(0, 0, 0),
                ambient
            );

            const libconfig::Setting &directionals = lights["directional"];

            for(int i = 0; i < directionals.getLength(); ++i) {
                const libconfig::Setting &directional = directionals[i];
                Vector3<int> directionalLightPosition(
                        directional["x"],
                        directional["y"],
                        directional["z"]
                );
                Vector3<int> directionalLightRotation(0, 0, 0);
                float directionalLightIntensity = directional["intensity"];
                _directionalLights.push_back(
                    objects::DirectionalLight(
                        directionalLightPosition,
                        directionalLightRotation,
                        directionalLightIntensity
                    )
                );
            }
        }
        catch(const libconfig::SettingNotFoundException &nfex) {
            cerr << "[!] No '" << nfex.getPath() << "' setting in configuration file." << endl;
            exit(EXIT_ERROR);
        }
    }

    std::vector<objects::Sphere> &Scene::getSpheres()
    {
        return _spheres;
    }

    std::vector<objects::Plane> &Scene::getPlanes()
    {
        return _planes;
    }

    std::vector<objects::DirectionalLight> &Scene::getDirectionalLights()
    {
        return _directionalLights;
    }

    objects::AmbientLight &Scene::getAmbientLight()
    {
        return _ambientLight;
    }

    objects::Camera &Scene::getCamera()
    {
        return _camera;
    }
}
