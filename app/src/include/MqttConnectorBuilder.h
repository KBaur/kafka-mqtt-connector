#ifndef __MQTTCONNECTORBUILDER_H__
#define __MQTTCONNECTORBUILDER_H__

#include <memory>
#include <string>

#include "MqttConnector.h"

#include "IFetchEnvironment.h"

namespace kb{
    namespace mqtt{
        /**
         * @class MqttConnectorBuilder
         * @details MqttConnectorBuilder
         * @date 2022
         * @author baurk
         */
        class MqttConnectorBuilder: public kb::IFetchEnvironment{
        public:
            MqttConnectorBuilder();
            std::shared_ptr<MqttConnector> BuildConnector();
        private:
            std::uint8_t m_mqttQos;
            std::string m_mqttHost;
            std::uint32_t m_mqttPort;
            std::shared_ptr<MqttConnector> m_mqttConnector;
        };
    }
}

#endif