#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>

#define ADDRESS     "tcp://mqtt.localhost:1883"
#define CLIENTID    "C_Client"
#define TOPIC       "test/topic"
#define PAYLOAD     "Hello MQTT"
#define QOS         1
#define TIMEOUT     10000L

void delivered(void *context, MQTTClient_deliveryToken dt) {
    printf("Message with token %d delivered.\n", dt);
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("Message arrived on topic %s: %s\n", topicName, (char *)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause) {
    printf("Connection lost: %s\n", cause);
}

int main() {
    MQTTClient client;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to connect to MQTT broker.\n");
        return 1;
    }

    printf("Connected to MQTT broker.\n");

    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;

    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Message published to topic: %s\n", TOPIC);

    MQTTClient_subscribe(client, TOPIC, QOS);

    sleep(5); // Wait to receive messages

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return 0;
}
