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
            void InitializeMqttConnector();
            std::uint8_t m_mqttQos;
            std::string m_mqttHost;
            std::uint32_t m_mqttPort;
            std::string m_certPath;
            std::string m_keyPath;
            std::string m_caPath;
            std::string m_user;
            std::string m_password;
            std::shared_ptr<MqttConnector> m_mqttConnector;
        };
    }
}

#endif