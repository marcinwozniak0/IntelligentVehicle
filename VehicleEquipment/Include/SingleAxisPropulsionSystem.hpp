#pragma once

#include <array>

#include "PropulsionSystem.hpp"

class Engine;
class EngineDriver;

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(Engine&, Engine&, const EngineDriver&);

     void transferCharacteristicValues(const std::vector<uint8_t>&) override;

private:
    Engine& _rightEngine;
    Engine& _leftEngine;
    const EngineDriver& _engineDriver;
};
