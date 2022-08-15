#include "ConnectorFactory.h"

namespace kb{

    void ConnectorFactory::SetMap(const std::vector<std::string>& p_vector,std::multimap<std::string,std::string> & p_map, std::regex p_delimiter)
    {
        std::stringstream ss;
        std::smatch sm;
        for(auto elem : p_vector)
        {
            if( elem.size()>2 && std::regex_search(elem,sm,p_delimiter))
            {
                std::string key(elem.begin(),elem.begin()+sm.position());
                std::string value(elem.begin()+sm.position()+sm.length(),elem.end());
        #ifdef DEBUG
                std::cout << "[ " << key << " ] =>  " << value << std::endl;
        #endif
                if( key.size()>1 && value.size()>1)
                {
                    p_map.insert(std::pair<std::string,std::string>(key,value));
                }
            }
        }
    }
    
    void ConnectorFactory::SetMappingString(const std::string & p_mappingString)
    {
        m_mappingString = p_mappingString;
        std::vector<std::string> strs;

        boost::split(strs,m_mappingString,boost::is_any_of(";"));
        SetMap(strs,m_mqttMapping,std::regex(R"(>>)"));
        SetMap(strs,m_kafkaMapping,std::regex(R"(<<)"));
    }

    std::shared_ptr<kb::kafka::KafkaConnectorBuilder> ConnectorFactory::GetKafkaBuilder()
    {
        m_kafkaConnectorBuilder= std::make_shared<kb::kafka::KafkaConnectorBuilder>();
        m_kafkaConnectorBuilder->TopicsToSubscribeTo(m_kafkaMapping);
        return m_kafkaConnectorBuilder;
    }
    
    std::shared_ptr<kb::mqtt::MqttConnectorBuilder> ConnectorFactory::GetMqttBuilder()
    {
        m_mqttConnectorBuilder = std::make_shared<kb::mqtt::MqttConnectorBuilder>();
        auto connector = m_mqttConnectorBuilder->BuildConnector();
        connector->SetTopicsToSubscribeTo(m_mqttMapping);
        return m_mqttConnectorBuilder;
    }

}