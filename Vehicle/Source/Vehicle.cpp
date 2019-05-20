#include "Vehicle.hpp"

Vehicle::Vehicle(PropulsionSystem& propulsionSystem)
    : _propulsionSystem(propulsionSystem)
{
    _vehicleState = VehicleState::Idle;
}

void Vehicle::startVehicle()
{
    _vehicleState = VehicleState::Manual;
}

void Vehicle::stopVehicle()
{
    _vehicleState = VehicleState::Idle;
}

void Vehicle::switchToAutomaticMode()
{
    _vehicleState = VehicleState::Auto;
}

VehicleState Vehicle::getVehicleState()
{
    return _vehicleState;
}

void Vehicle::run(const USER_COMMAND_TO_DRIVE&& command)
{
    const auto& characteristicToSend = command._coordinateSystem;

    _propulsionSystem.transferCharacteristicValues(characteristicToSend);
}
