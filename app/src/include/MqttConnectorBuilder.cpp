#include "MqttConnectorBuilder.h"
namespace kb{
    namespace mqtt{
        MqttConnectorBuilder::MqttConnectorBuilder()
        {
            // mqtt certificates
            // psw user
            std::string mqttUuid = FetchEnvVariable("MQTT_CLIENT_ID");
            m_mqttQos = std::stoi(FetchEnvVariable("MQTT_QOS"));
            m_mqttHost = FetchEnvVariable("MQTT_HOST");
            m_mqttPort = std::stoi(FetchEnvVariable("MQTT_PORT"));
            // int username_pw_set(const char *username, const char *password=NULL);
            // int tls_set(const char *cafile, const char *capath=NULL, const char *certfile=NULL, const char *keyfile=NULL, int (*pw_callback)(char *buf, int size, int rwflag, void *userdata)=NULL);
            // int tls_insecure_set(bool value);
            // int tls_psk_set(const char *psk, const char *identity, const char *ciphers=NULL);
            m_mqttConnector = std::shared_ptr<MqttConnector>( MqttConnector::GetInstance(mqttUuid.c_str(),true));
            m_mqttConnector->SetQos(m_mqttQos);
        }

        std::shared_ptr<MqttConnector> MqttConnectorBuilder::BuildConnector()
        {
            m_mqttConnector->connect_async(m_mqttHost.c_str(),m_mqttPort);
            return m_mqttConnector;
        }
    }
}