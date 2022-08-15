#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <exception>
#include <memory>

#include <boost/algorithm/string.hpp>
#include <kafka/KafkaProducer.h>

#include "ConnectorFactory.h"

int main(int argc, char ** argv)
{
    std::string line = std::getenv("TOPIC_MAPPING");    

    kb::ConnectorFactory connectorFactor;
    connectorFactor.SetMappingString(line);

    auto mqttBuilder = connectorFactor.GetMqttBuilder();
    auto kafkaBuilder = connectorFactor.GetKafkaBuilder();

    auto kafkaProducer = kafkaBuilder->BuildProducer();
    auto mqtt = mqttBuilder->BuildConnector();
    //auto threads = kafkaBuilder->BuildConsumerThreads();

    mqtt->SetProducer(kafkaProducer);
    mqtt->loop_start();
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mqtt->loop_stop();
    
    return EXIT_SUCCESS;
}
