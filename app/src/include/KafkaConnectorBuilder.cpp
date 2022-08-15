#include "KafkaConnectorBuilder.h"

namespace kb{
    namespace kafka{

        KafkaConnectorBuilder::KafkaConnectorBuilder()
        {
            // certificates ?
            // psw user ?
            
            std::string kafkaClientId = FetchEnvVariable("KAFKA_CLIENT_ID");
            std::string kafkaHost = FetchEnvVariable("KAFKA_HOST");
            std::string kafkaPort = FetchEnvVariable("KAFKA_PORT");

            std::stringstream ss;
            ss << kafkaHost << ":" << kafkaPort;

            // "security.protocol"
            // "acks"

            // Create configuration object
            m_propertiesProducer = ::kafka::Properties({
                {"bootstrap.servers",  ss.str()},
                {"enable.idempotence", "true"},
                {"client.id",kafkaClientId}
            });
            m_propertiesConsumer = ::kafka::Properties({
                {"bootstrap.servers",  ss.str()},
                {"enable.auto.commit", "true"},
                {"client.id",kafkaClientId}
            });
        }

        KafkaConnectorBuilder::~KafkaConnectorBuilder()
        {
            m_threadFlag=true;
            for(auto & val : *m_consumerThreads.get())
            {
                if(val.joinable())
                {
                    val.join();
                }
            }
        }

        void KafkaConnectorBuilder::TopicsToSubscribeTo(const std::multimap<std::string,std::string>& p_topicsToSubscribeTo)
        {
            m_topicsToSubscribeTo=p_topicsToSubscribeTo;
        }

        std::shared_ptr<::kafka::clients::KafkaProducer> KafkaConnectorBuilder::BuildProducer()
        {
            if(m_producer==nullptr)
            {
                m_producer = std::shared_ptr<::kafka::clients::KafkaProducer>{ new ::kafka::clients::KafkaProducer(m_propertiesProducer)};
            }
            return m_producer;
        }

        std::shared_ptr<std::vector<std::thread>> KafkaConnectorBuilder::BuildConsumerThreads()
        {
            if(m_consumerThreads==nullptr)
            {

                m_consumerThreads = std::make_shared<std::vector<std::thread>>();
                m_consumerThreads->reserve(m_topicsToSubscribeTo.size());

                for(auto pair:m_topicsToSubscribeTo)
                {
                    auto function = [](::kafka::Properties propertiesConsumer,std::pair<const std::string, std::string> pair, std::atomic<bool>* stopFlag){
                    try 
                    {

                        // Create a consumer instance
                        ::kafka::clients::KafkaConsumer consumer(propertiesConsumer);

                        // Subscribe to topics
                        consumer.subscribe({pair.second});
                        kb::mqtt::MqttConnector * mqtt = kb::mqtt::MqttConnector::GetInstance();
                        // Read messages from the topic
#ifdef DEBUG
                        std::cout << "% Reading messages from topic: " << pair.second << std::endl;
#endif
                        while (stopFlag!=nullptr&&*stopFlag!=true) {
                            auto records = consumer.poll(std::chrono::milliseconds(100));
                            for (const auto& record: records) {
                                // In this example, quit on empty message
                                if (record.value().size() == 0) return;
                                std::string payload = record.value().toString();
                                if (!record.error()) {
#ifdef DEBUG
                                    std::cout << "% Got a new message..." << std::endl;
                                    std::cout << "    Topic    : " << record.topic() << std::endl;
                                    std::cout << "    Partition: " << record.partition() << std::endl;
                                    std::cout << "    Offset   : " << record.offset() << std::endl;
                                    std::cout << "    Timestamp: " << record.timestamp().toString() << std::endl;
                                    std::cout << "    Headers  : " << ::kafka::toString(record.headers()) << std::endl;
                                    std::cout << "    Key   [" << record.key().toString() << "]" << std::endl;
                                    std::cout << "    Value [" << payload << "]" << std::endl;
#endif
                                    mqtt->publish(0,pair.first.c_str(),payload.size(),(void *)payload.c_str());
                                } else {
                                    std::cerr << record.toString() << std::endl;
                                }
                            }
                        }
                    } catch (const ::kafka::KafkaException& e) {
                        std::cerr << "% Unexpected exception caught: " << e.what() << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    };

                    m_consumerThreads->push_back(std::thread(function,this->m_propertiesConsumer,pair, &this->m_threadFlag));
                }
            }
            return m_consumerThreads;
        }

    }
}