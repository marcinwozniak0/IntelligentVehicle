#pragma once

#include <gmock/gmock.h>

#include "Vehicle.hpp"

class VehicleMock : public Vehicle
{
public:
    MOCK_METHOD0(startVehicle, void());
    MOCK_METHOD0(stopVehicle, void());
    MOCK_METHOD0(switchToAutomaticMode, void());
    MOCK_METHOD1(applyNewConfiguration, void(const Messages::CoordinateSystem&));
    MOCK_METHOD0(getVehicleState, VehicleState());
};
