import time
import paho.mqtt.client as client
import random

broker = "broker.emqx.io"

client = client.Client('isu10012300')

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")

flag = True
start_second = 20
duration = 20


for _ in range(10):
    if duration < 10:
        duration = 20
    # лампочка загорается на 20 секунде
    time.sleep(start_second)
    state = "u"
    print(f"state is {state}")
    client.publish("esp8266-fc6f10/command", state)
    time.sleep(duration)
    duration -= 1

    #по истечении времени погасает
    state = "d"
    print(f"state is {state}")
    client.publish("esp8266-fc6f10/command", state)
    #Времени до конца минуты
    time.sleep(60 - duration - start_second)

client.disconnect()
client.loop_stop()