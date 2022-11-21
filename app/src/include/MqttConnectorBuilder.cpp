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
            
            m_mqttConnector = std::shared_ptr<MqttConnector>( MqttConnector::GetInstance(mqttUuid.c_str(),true));
            m_mqttConnector->SetQos(m_mqttQos);
            InitializeMqttConnector();
        }

        void MqttConnectorBuilder::InitializeMqttConnector()
        {
            bool traceContext = static_cast<bool>(std::atoi(FetchEnvVariable("USE_TRACE_CONTEXT").c_str()));
            bool setupTls = static_cast<bool>(std::atoi(FetchEnvVariable("MQTT_TLS_AUTHENTICATION").c_str()));
            bool setupUserAuth = static_cast<bool>(std::atoi(FetchEnvVariable("MQTT_USER_AUTHENTICATION").c_str()));
            bool insecure = static_cast<bool>(std::atoi(FetchEnvVariable("MQTT_INSECURE").c_str()));
            if(setupTls)
            {
                m_mqttConnector->tls_set(FetchEnvVariable("MQTT_CA_PATH").c_str(),FetchEnvVariable("MQTT_CA_DIR_PATH").c_str(),FetchEnvVariable("MQTT_CERT_PATH").c_str(),FetchEnvVariable("MQTT_KEY_PATH").c_str());
                m_mqttConnector->tls_insecure_set(insecure);
                // int tls_psk_set(const char *psk, const char *identity, const char *ciphers=NULL);
            }else if(setupUserAuth)
            {
                m_mqttConnector->username_pw_set(FetchEnvVariable("MQTT_USER").c_str(), FetchEnvVariable("MQTT_PASSWORD").c_str());
            }
            m_mqttConnector->SetTraceContextFlag(traceContext);
        }

        std::shared_ptr<MqttConnector> MqttConnectorBuilder::BuildConnector()
        {
            m_mqttConnector->connect_async(m_mqttHost.c_str(),m_mqttPort);
            return m_mqttConnector;
        }
    }
}