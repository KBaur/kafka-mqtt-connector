#ifndef __MQTTCONNECTOR_H__
#define __MQTTCONNECTOR_H__

#include <string>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <memory>
#include <regex>

#include <kafka/KafkaProducer.h>

#include <mosquittopp.h>

#define DEBUG


namespace kb{
namespace mqtt{
    /**
     * @class MqttConnector
     * @details MqttConnector build on a singleton pattern
     * @date 2022
     * @author baurk
     */
class MqttConnector : public mosqpp::mosquittopp{
public:
    static MqttConnector * GetInstance(const char *id=NULL, bool clean_session=true);
    std::string GetCurrentISO8601TimeUTC();
    void SetProducer(std::shared_ptr<::kafka::clients::KafkaProducer> p_producer);
    void SetQos(std::uint8_t p_qos);
    void SetTopicsToSubscribeTo(const std::multimap<std::string,std::string>& p_topics);
    void SetTraceContextFlag(bool p_flag);

    // names in the functions commented to prevent unused parameter warning
    virtual void on_connect(int /*rc*/);
    virtual void on_disconnect(int /*rc*/);
    virtual void on_publish(int /*mid*/);
    virtual void on_message(const struct mosquitto_message * /*message*/);
    virtual void on_subscribe(int /*mid*/, int /*qos_count*/, const int * /*granted_qos*/);
    virtual void on_unsubscribe(int /*mid*/);
    virtual void on_log(int /*level*/, const char * /*str*/);
    virtual void on_error();

private:
    std::optional<std::vector<kafka::Header>> AddTraceContext(const std::string& p_msg);
    void SubscribeToTopics();
    void UnsubscribeToTopics();
    void SendToKafka(const std::string & p_topic,const std::string& p_header, const std::string p_message);
    MqttConnector(const char *id, bool clean_session);
    std::shared_ptr<::kafka::clients::KafkaProducer> m_producer;
    std::uint8_t m_qos{0};
    std::multimap<std::string,std::string> m_topics;
    bool m_useTraceContext;
    bool m_connected{false};
    const std::string m_regexString{R"(\"(traceparent|tracestate)\"\s*:\s*\"(\w*)\")"};
};
}
}
#endif