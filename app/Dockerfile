FROM debian:latest

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get install -y build-essential gcc gdb make cmake libssl-dev libmosquitto-dev libmosquitto1 libcurlpp-dev libmosquittopp-dev libmosquittopp1 git librdkafka++1 librdkafka-dev librdkafka1 libboost-all-dev

ENV LIBRDKAFKA_ROOT="/usr"
ENV LIBRDKAFKA_INCLUDE_DIR="/usr/include"
ENV LIBRDKAFKA_LIBRARY_DIR="/usr/lib/x86_64-linux-gnu"

RUN useradd --user-group --create-home --shell /bin/false app_user
RUN mkdir /services && chown -R app_user /services && chmod 777 /services

ADD . /services
WORKDIR /services

# install modern cpp kafka
RUN git clone --depth=1 https://github.com/morganstanley/modern-cpp-kafka.git
WORKDIR ./modern-cpp-kafka
RUN sed -i "s/\${LIBRDKAFKA_LIBRARY_DIR}\/librdkafka.a/\/usr\/lib\/x86_64-linux-gnu\/librdkafka.so/g" CMakeLists.txt
RUN mkdir ./build
WORKDIR ./build 
RUN cmake -DCMAKE_BUILD_TYPE=Release -DCPPKAFKA_ENABLE_TESTS:BOOL="0" ..
RUN cmake --build ./ -j
RUN make install
WORKDIR /services
RUN rm -r ./modern-cpp-kafka

# install prometheus
RUN git clone --depth=1 --recurse-submodules https://github.com/jupp0r/prometheus-cpp.git
WORKDIR ./prometheus-cpp
RUN mkdir ./build
WORKDIR ./build
RUN cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="1" -DUSE_THIRDPARTY_LIBRARIES:BOOL="1" -DENABLE_PUSH:BOOL="1" -DENABLE_COMPRESSION:BOOL="0" ..
RUN cmake --build ./ -j
RUN make install
WORKDIR /services
RUN rm -r ./prometheus-cpp

ENV MQTT_HOST=mosquitto
ENV MQTT_PORT=1883
ENV MQTT_CLIENT_ID=mqtt-client-1
ENV MQTT_QOS=0
ENV MQTT_TLS_AUTHENTICATION=0
ENV MQTT_USER_AUTHENTICATION=0
ENV MQTT_CERT_PATH="/services/res/client.crt"
ENV MQTT_KEY_PATH="/services/res/client.key"
ENV MQTT_CA_PATH="/services/res/ca.crt"
ENV MQTT_CA_DIR_PATH="/services/res"
ENV MQTT_TLS_PSW=""
ENV MQTT_USER=""
ENV MQTT_INSECURE=1

# currently not implemented
ENV MQTT_PASSWORD=""

ENV KAFKA_HOST=kafka
ENV KAFKA_PORT=9092
ENV KAFKA_CLIENT_ID=testing-kafka-client
ENV KAFKA_TLS=1
ENV KAFKA_CERT_PATH="/services/res/client.crt"
ENV KAFKA_KEY_PATH="/services/res/client.key"
ENV KAFKA_CA_PATH="/services/res/ca.crt"

ENV USE_TRACE_CONTEXT=1
# Tracing ID to KAFKA TOPIC and VICE VERSA

ENV TOPIC_MAPPING=test1-mqtt>>test1-kafka;test2-mqtt<<test2-kafka

WORKDIR /services/src
RUN if [ ! -d ./build ]; then mkdir ./build; fi
WORKDIR /services/src/build
# RUN rm -r ./*
RUN ls -l
RUN cmake ..
RUN cmake --build ./ -j

CMD ./kafka-mqtt-connector
