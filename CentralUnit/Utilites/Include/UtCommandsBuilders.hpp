#pragma once

#include <string>
#include <google/protobuf/any.pb.h>

namespace UTHelpers
{
const google::protobuf::Any createDeactivateCommand();
const google::protobuf::Any createUserCommandToStart();
const google::protobuf::Any createUserCommandToStop();
const google::protobuf::Any createUnknownCommand();
const google::protobuf::Any createUserCommandToRun(const int32_t, const int32_t);
}//UTHelpers
