cmake_minimum_required(VERSION 3.16)
project(kafka-mqtt-connector VERSION 0.1)
set (CMAKE_CXX_STANDARD 20)

include_directories(./include /usr/include /usr/local/include)

set(H_FILES
    include/MqttConnector.h
    include/MqttConnectorBuilder.h
    include/KafkaConnectorBuilder.h
    include/IFetchEnvironment.h
    include/ConnectorFactory.h
)

set(CPP_FILES
    include/MqttConnector.cpp
    include/MqttConnectorBuilder.cpp
    include/KafkaConnectorBuilder.cpp
    include/IFetchEnvironment.cpp
    include/ConnectorFactory.cpp
)

find_library(RDKAFKA rdkafka)
find_library(MOSQUITTO mosquittopp /usr/lib/x86_64-linux-gnu)
find_library(PTHREAD pthread)

add_library(kafka-mqtt-connector-lib ${H_FILES} ${CPP_FILES})

add_executable(kafka-mqtt-connector main.cpp)
#${BOOST}

find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams)
target_link_libraries(kafka-mqtt-connector PUBLIC kafka-mqtt-connector-lib ${MOSQUITTO} ${PTHREAD} ${RDKAFKA} Boost::date_time Boost::filesystem Boost::iostreams)

target_include_directories(kafka-mqtt-connector PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include"
                          )

install(TARGETS kafka-mqtt-connector-lib DESTINATION /usr/local/lib)
install(FILES ${H_FILES} DESTINATION /usr/local/include)
