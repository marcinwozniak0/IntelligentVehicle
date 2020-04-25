#include <google/protobuf/stubs/common.h>
#include <grpc++/grpc++.h>

#include "VehiclePoolControler.hpp"
#include "GrpcCommandSender.hpp"
#include "GrpcCommandReceiver.hpp"
#include "InternalVehiclePool.hpp"
#include "VehicleFactoryFacade.hpp"
#include "ThreeWheeledVehicleFactory.hpp"

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ThreeWheeledVehicleFactory threeWheeledVehicleFactory;

    VehicleFactoryFacade vehicleFactoryFacade(threeWheeledVehicleFactory);

    GrpcCommandReceiver commandReceiver("127.0.0.1:5000");

    GrpcCommandSender commandSender(std::make_shared<Router::Stub>(
        grpc::CreateChannel("127.0.0.1:3000", grpc::InsecureChannelCredentials())));

    InternalVehiclePool vehiclePool(vehicleFactoryFacade);

    VehiclePoolControler vehiclePoolControler(commandReceiver,
                                              commandSender,
                                              vehiclePool);

    try
    {
        vehiclePoolControler.controlVehiclePool();
    }
    catch(const std::exception& unhandledException)
    {
        std::cerr << unhandledException.what() << std::endl;
        vehiclePoolControler.vehiclePoolEmergencyStop();
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
