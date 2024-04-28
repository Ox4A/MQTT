#pragma warning(disable:4996)
#include<iostream>
#include <stdlib.h>
#include <string>
#include<cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "MQTTClient.h" //包含MQTT客户端库头文件
using namespace std;
MQTTClient client;

int MessageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message) {  //回调函数
    /*cout << "Message arrived:" << endl;
    cout << "Topic: " << topicName << endl;*/
    string m=(char*)message->payload;

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void Connect_Lost(void* context, char* cause) {   //连接意外终止处理函数
    
}

void MQTT_Subscribe(const string& topic, int Qos) {  //订阅
    MQTTClient_subscribe(client, topic.c_str(), Qos);
}

void MQTT_Connect(const string& user_name, const string& password, const string& client_id, const string& ip, const string& port) {  //建立连接
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = user_name.c_str();
    conn_opts.password = password.c_str();
    conn_opts.keepAliveInterval = 5; // 设置心跳包发送间隔为 20 秒
    string url = string("tcp://") + ip;
    url.push_back(':');
    url += port;

    MQTTClient_create(&client, url.c_str(), client_id.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_setCallbacks(client, NULL, Connect_Lost, MessageArrived, NULL);
    MQTTClient_connect(client, &conn_opts);
}

void MQTT_Publish(const string& topic, const string& payload, int Qos) {  //发布主题
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    pubmsg.payload = malloc(payload.size() + 1);
    strcpy((char*)pubmsg.payload, payload.c_str());
    pubmsg.payloadlen = payload.size();
    pubmsg.qos = Qos;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, topic.c_str(), &pubmsg, &token);
    free(pubmsg.payload);
}

void MQTT_Quit() {
    MQTTClient_disconnect(client, 1000 * 5);
    MQTTClient_destroy(&client);
}