#include <thread>
#include <chrono>

#include "VehicleControler.hpp"
#include "Commands.hpp"

VehicleControler::VehicleControler(CommandReceiver& commandReceiver,
                                   Vehicle& vehicle)
    : _commandReceiver(commandReceiver)
    , _commandsQueue(_commandReceiver.shareCommandsQueue())
    , _vehicle(vehicle)
{
    _isControlerActive = true;
}

void VehicleControler::controlVehicle()
{
    //think about receiving commands
    while(_isControlerActive)
    {
        _commandReceiver.receiveCommand(); //temporary solution
        if (const auto command = getCommandToExecute())
        {
            executeCommand(command.value());
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void VehicleControler::vehicleEmergencyStop()
{
    //TODO execute emergency command
}

std::optional<std::string> VehicleControler::getCommandToExecute()
{
    if (not _commandsQueue->empty())
    {
        const auto command = _commandsQueue->front();
        _commandsQueue->pop();
        return command;
    }
    else
    {
        return {};
    }
}

namespace
{
bool startsWith(const std::string& str, const std::string& pattern)
{
    return str.rfind(pattern, 0) ? false : true; //return 0 on succes
}

std::string getFieldFromCommand(const std::string& command, const uint8_t fieldNumber)
{
    uint8_t acctualPossition = 0;
    for (uint8_t i = 0; i <= fieldNumber; i++)
    {
        acctualPossition = command.find('|', acctualPossition);
        ++acctualPossition;
    }

    uint8_t endMarker = command.find('|', acctualPossition);

    return std::string(command.begin() + acctualPossition, command.begin() + endMarker);
}
}//namespace

void VehicleControler::executeCommand(const std::string& command)
{
    //TODO komenda do wybrania manula czy auto
    //komendy strignowe do jakiegos namesapce
    //pomyslec o tym xmlu
    //moze cos w stylu START|MANUAL ?
    if("START" == command)
    {
        _vehicle.startVehicle();
    }
    else if("STOP" == command)
    {
        _vehicle.stopVehicle();
    }
    else if(startsWith(command, "DRIVE"))
    {
        //TODO jak obslugiwac i pobierac te mesgi
        //TODO moze jakies xml czy coś do tych mesgow
        //TODO musi byc w stanie != IDLE zeby przyjac takiego mesga
        constexpr uint8_t xCoordinationField = 0;
        constexpr uint8_t yCoordinationField = 1;
        const auto direction = static_cast<int16_t>(std::stoi(getFieldFromCommand(command, xCoordinationField)));
        const auto speed = static_cast<int16_t>(std::stoi(getFieldFromCommand(command, yCoordinationField)));

        _vehicle.run(USER_COMMAND_TO_DRIVE{direction, speed});
    }
    else if("DEACTIVATE")
    {
        _isControlerActive = false;
    }
}
