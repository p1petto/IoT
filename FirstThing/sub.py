import time
import paho.mqtt.client as mqtt_client
import random
import serial

broker = "broker.emqx.io"

responses = {'d': 7,
             'u': 6}

port = "COM8" 
connection = serial.Serial(port, timeout=1)

def send_command(cmd: str,
                 response_len: int) -> str:
    str_resp = None
    connection.write(cmd.encode())
    if response_len != 0:
        # connection.in_waiting <-> available
        resp = connection.read(response_len)
        str_resp = resp.decode()
        return str_resp
    return ""

def on_message(client, userdata, message):
    data = str(message.payload.decode("utf-8"))
    print("received message =", data)
    if data == "u":
        print(send_command("u",responses['u']))
    if data == "d":
        print(send_command("d",responses['d']))




def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)


client = mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_message = on_message
client.on_connect = on_connect
client.connect(broker)
client.loop_start()
print("Subcribing")
client.subscribe("house/RED_ALERT2")
time.sleep(1800)
client.disconnect()
client.loop_stop()



