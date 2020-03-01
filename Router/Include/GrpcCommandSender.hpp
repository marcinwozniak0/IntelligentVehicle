#pragma once

#include <grpc++/grpc++.h>
#include <memory>

#include <Client.grpc.pb.h>

#include "CommandSender.hpp"

class GrpcCommandSender : public CommandSender
{
public:
    GrpcCommandSender(std::shared_ptr<Router::StubInterface>);

    void sendCommand(google::protobuf::Any&&) override;

private:
    std::string connectWithServer() const;
    
    std::shared_ptr<Router::StubInterface> _stub;
};