# Kafka-Mqtt-Connector

A lightweigth Kafka to MQTT Connector which was written in C++.
It includes the paho-mqtt library and the modern-cpp-kafka library to communicate via kafka.
The container is designed to be bi-directional. So topics can be sent via kafka to mqtt and vice versa.

## Install 

#### Compile the static library
```console
$ git clone https://github.com/KBaur/Kafka-Mqtt-Connector.git
$ cd ./Kafka-Mqtt-Connector
$ docker-compose run
```

## Platforms
 * Linux
 * Windows
 * macOS
 * ...

## Features
* Translate MQTT messages to kafka streams and vice versa via the TOPIC_MAPPING env variable:
```
TOPIC_MAPPING=test1-mqtt>>test1-kafka;test2-mqtt<<test2-kafka
```
That translates into:
```
test1-mqtt topic -> to kafka topic test1-kafka 
```
```
test2-kafka topic -> to mqtt topic test2-mqtt 
```
* Use modern features like the tracecontext, a [trace context](https://w3c.github.io/trace-context-mqtt/) for MQTT

---

#### TOPIC: 
```
test-topic/device1
```
#### PAYLOAD:
```json
{
    "msg": { ... },
    "traceparent": "00-0af7651916cd43dd8448eb211c80319c-b7ad6b7169203331-01",
    "tracestate": "ot=BleGNlZWRzIHRohbCBwbGVhc3VyZS4"
}
```

---

translates into kafka

---

##### KEY: 
```
test-topic/device1
```
##### HEADER: 
```
traceparent:00-0af7651916cd43dd8448eb211c80319c-b7ad6b7169203331-01
tracestate:ot=BleGNlZWRzIHRohbCBwbGVhc3VyZS4
```
##### VALUE:
```json
{
    "msg": { ... },
    "traceparent": "00-0af7651916cd43dd8448eb211c80319c-b7ad6b7169203331-01",
    "tracestate": "ot=BleGNlZWRzIHRohbCBwbGVhc3VyZS4"
}
```
---

### Future
Future implementations will have a 
* monitoring interface with prometheus
 
## Usage samples

## Documentation

Doxygen documentation will be generated

---


