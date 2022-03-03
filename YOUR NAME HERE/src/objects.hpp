#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/entityComponentSystem.hpp"
#include "systems.hpp"
#include "components.hpp"

struct Actor { Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect); };