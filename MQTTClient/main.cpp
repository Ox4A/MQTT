#pragma warning(disable:4996)
#include<iostream>
#include <string>
#include "MQTTClient.h" //包含MQTT客户端库头文件
#include"MQTT.h"
using namespace std;
extern MQTTClient client;

int main() {
    string user_name, password,ip,port,topic,payload;
    cout << "please input your user_name:";
    cin >> user_name;
    cout << "please input your password:";
    cin >> password;
    cout << "please input server's ip:";
    cin >> ip;
    cout << "please input process's port:";
    cin >> port;
    MQTT_Connect(user_name, password, string("42"),ip, port);

    int mode;
    while (true) {
        MQTTClient_yield();  //定时发送心跳包维持链接
        cout << "***************Menu**************" << endl;
        cout << "1.publish" << endl;
        cout << "2.subscribe" << endl;
        cout << "3.unsubscribe" << endl;
        cout << "any other key to quit" << endl;
        cout << "tell me your choice:";
        cin >> mode;
        switch (mode) {
        case 1: {
            cout << "please input the topic you want to publish:";
            cin >> topic;
            cout << "please input the payload of the topic above:";
            cin.ignore();
            getline(cin, payload);
            MQTT_Publish(topic, payload);
            break;
        }
        case 2: {
            cout << "please input the topic you want to subscribe:";
            cin >> topic;
            MQTT_Subscribe(topic.c_str());
            break;
        }
        case 3: {
            cout << "please input the topic you want to unsubscribe:";
            cin >> topic;
            MQTTClient_unsubscribe(client, topic.c_str());
            break;
        }
        default: {
            MQTT_Quit();
            return 0;
        }
        }
    }

    return 0;
}