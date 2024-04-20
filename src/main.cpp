#include <Arduino.h>
#include <WiFi.h>
#include <H4.h>
#include <H4AsyncMQTT.h>

H4 h4(PROJ_BAUD_RATE);

#define WIFI_SSID "XXXXXXXX"
#define WIFI_PASS "XXXXXXXX"


H4AsyncMQTT mqttClient;

// #define MQTT_URL "broker.emqx.com:1883"
#define MQTT_URL "192.168.100.4:1883"

std::string TOPIC_LEVEL = "";
// std::string TOPIC_LEVEL = "SPECIALTIPIC"; // Don't append the separator slash '/'


std::string prependTopicLevel(const std::string& topic) {
	if (TOPIC_LEVEL.length()) {
		return TOPIC_LEVEL.append("/").append(topic);
	}
	return topic;
}

// If using MQTT server authentication, fill in next two fields!
const char *mqAuth = "example";
const char *mqPass = "pangolin";

#define START_WITH_CLEAN_SESSION true

void onMqttError(int e, int i)
{
	if (e < H4AMC_ERROR_BASE)
	{
		Serial.printf("H4ASYNC ERROR %d [%s] info=%d[%p]\n", e, H4AsyncClient::errorstring(e).data(), i, i);
	}
	else
	{
		if (e < H4AMC_ERROR_MAX)
		{
			Serial.printf("H4AsyncMQTT ERROR %d [%s] info=%d[%p]\n", e, H4AsyncMQTT::errorstring(e).data(), i, i);
		}
		else
			Serial.printf("UNKNOWN ERROR: %u extra info %d[%p]\n", e, i, i);
	}
}
H4_TIMER sender;

void onMqttConnect(H4AMC_ConnackParam params)
{
	Serial.printf("USER: Connected as %s MP=%d\n", mqttClient.getClientId().data(), getMaxPayloadSize());

	// Serial.println("USER: Subscribing at QoS 2");
	// mqttClient.subscribe(prependTopicLevel("test").c_str(), 2);

	sender = h4.every(5000, []
					  {
						int value = analogRead(35);
						float value_f = value;
						Serial.printf("T=%u Publish value %d\n", millis(), value);
						mqttClient.xPublish(prependTopicLevel("analog").c_str(), std::to_string(value));
						mqttClient.xPublish(prependTopicLevel("analog_f").c_str(), std::to_string(value_f));

						mqttClient.publish("raw_topic", "Hello World");
						// mqttClient.publish(prependTopicLevel("analog").c_str(), value, "%u");
					});
}

void onMqttMessage(const char *topic, const uint8_t *payload, size_t len, H4AMC_MessageOptions opts)
{
	Serial.printf("Receive: H=%u Message %s qos%d dup=%d retain=%d len=%d\n", _HAL_freeHeap(), topic, opts.qos, opts.dup, opts.retain, len);
}

void onMqttDisconnect()
{
	Serial.printf("USER: Disconnected from MQTT\n");
	h4.cancel(sender);
}

void h4setup()
{
	Serial.printf("\nH4AsyncMQTT v%s running @ debug level %d heap=%u\n", H4AMC_VERSION, H4AMC_DEBUG, _HAL_freeHeap());

	mqttClient.onError(onMqttError);
	mqttClient.onConnect(onMqttConnect);
	mqttClient.onDisconnect(onMqttDisconnect);
	mqttClient.onMessage(onMqttMessage);
	mqttClient.setWill("DIED", 2, "probably still some bugs", false);
	//  mqttClient.setKeepAlive(RECONNECT_DELAY_M *3); // very rarely need to change this (if ever)
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(1000);
	}

	Serial.printf("WIFI CONNECTED IP=%s\n", WiFi.localIP().toString().c_str());

	mqttClient.connect(MQTT_URL, mqAuth, mqPass);
}