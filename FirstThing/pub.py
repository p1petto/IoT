import time
import paho.mqtt.client as mqtt_client
import random

broker="broker.emqx.io"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)


client= mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_connect = on_connect
client.connect(broker) 

for i in range(100000000):
    state = "u" if i%2 == 0 else "d"
    client.publish("house/RED_ALERT2", state)
    time.sleep(1)
    
client.disconnect()