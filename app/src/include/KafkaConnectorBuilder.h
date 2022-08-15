#ifndef __KAFKACONNECTORBUILDER_H__
#define __KAFKACONNECTORBUILDER_H__

#include <thread>

#include <kafka/KafkaProducer.h>
#include <kafka/KafkaConsumer.h>

#include <MqttConnector.h>
#include <IFetchEnvironment.h>

namespace kb{
    namespace kafka{
        /**
         * @class KafkaConnectorBuilder
         * @details KafkaConnectorBuilder
         * @date 2022
         * @author baurk
         */
        class KafkaConnectorBuilder : public kb::IFetchEnvironment {
        public:
            KafkaConnectorBuilder();
            ~KafkaConnectorBuilder();
            std::shared_ptr<::kafka::clients::KafkaProducer> BuildProducer();
            std::shared_ptr<std::vector<std::thread>> BuildConsumerThreads();
            void TopicsToSubscribeTo(const std::multimap<std::string,std::string>& p_topicsToSubscribeTo);
        private:
            ::kafka::Properties m_propertiesProducer;
            ::kafka::Properties m_propertiesConsumer;
            std::shared_ptr<::kafka::clients::KafkaProducer> m_producer{nullptr};
            std::shared_ptr<std::vector<std::thread>> m_consumerThreads;
            std::multimap<std::string,std::string> m_topicsToSubscribeTo;
            std::string m_clientId;
            std::string m_user;
            std::string m_password;
            std::string m_certificates;
            std::atomic<bool> m_threadFlag;
        };
    }
}
#endif