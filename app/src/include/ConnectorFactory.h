#ifndef __CONNECTORFACTORY_H__
#define __CONNECTORFACTORY_H__

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <exception>
#include <memory>
#include <regex>

#include <boost/algorithm/string.hpp>

#include <kafka/KafkaProducer.h>

#include "KafkaConnectorBuilder.h"
#include "MqttConnectorBuilder.h"

namespace kb{
    /**
     * @class ConnectorFactory
     * @details Connector Factory for mqtt and kafka builder
     * @date 2022
     * @author baurk
     */
    class ConnectorFactory{
    public:
        std::string FetchEnvVariable(const std::string& p_name);
        void SetMappingString(const std::string & p_mappingString);
        void SetMap(const std::vector<std::string>& p_vector,std::multimap<std::string,std::string> & p_map, std::regex p_delimiter);
        std::shared_ptr<kb::kafka::KafkaConnectorBuilder> GetKafkaBuilder();
        std::shared_ptr<kb::mqtt::MqttConnectorBuilder> GetMqttBuilder();
    private:
        std::string m_mappingString;
        std::multimap<std::string,std::string> m_kafkaMapping;
        std::multimap<std::string,std::string> m_mqttMapping;
        std::shared_ptr<kb::mqtt::MqttConnectorBuilder> m_mqttConnectorBuilder;
        std::shared_ptr<kb::kafka::KafkaConnectorBuilder> m_kafkaConnectorBuilder;
    };
}

#endif