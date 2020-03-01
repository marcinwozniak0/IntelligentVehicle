#pragma once

#include <gmock/gmock.h>

#include "CommunicationSocket.hpp"

class CommunicationSocketMock : public CommunicationSocket
{
public:
    MOCK_METHOD(void, receiveCommand, ());
    MOCK_METHOD(void, sendCommand, (google::protobuf::Any&&));
    MOCK_METHOD(std::optional<const std::string>, takeMessageFromQueue, ());
};
