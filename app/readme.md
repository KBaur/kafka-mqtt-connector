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

Future implementations will have a monitoring interface with prometheus and an automatic build that can be pulled from docker hub.
Currently only the unencrypted communication is supported (without SSL/TLS) I will fix this as well in the future versions.
 
## Usage samples

#### Basic usage
```c++
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

int main() 
{
   
}

```

## Documentation

Doxygen documentation will be generated

---


