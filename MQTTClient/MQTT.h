#pragma once
#include<string>
using namespace std;
void MQTT_Subscribe(const string& topic, int Qos = 0);
void MQTT_Connect(const string& user_name, const string& password, const string& client_id, const string& ip, const string& port);
void MQTT_Publish(const string& topic, const string& payload, int Qos = 0);
void MQTT_Quit();