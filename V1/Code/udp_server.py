import socket
from playsound import playsound

REMOTE_IP = '0.0.0.0'
REMOTE_PORT = 2000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
print(sock)
sock.bind((REMOTE_IP, REMOTE_PORT));

print("UDP server up and running.");
print(sock)

while True:
    
    data, addr = sock.recvfrom(24);
    print(data);
    if(data == b'\x01'):
        print("Yellow Button Pressed.")
        playsound("C:/Users/User/OneDrive/Dokumente/GameShowSystem/esp_v1/Belleville.mp3");
    if(data == b'\x02'):
        print("Red Button Pressed.")
        playsound("C:/Users/User/OneDrive/Dokumente/GameShowSystem/esp_v1/Mowbray.mp3")
    if(data == b'\x03'):
        print("Blue Button Pressed.")
        playsound("C:/Users/User/OneDrive/Dokumente/GameShowSystem/esp_v1/Wynberg.mp3")
    if(data == b'\x04'):
        print("Green Button Pressed.")
        playsound("C:/Users/User/OneDrive/Dokumente/GameShowSystem/esp_v1/Cape_Town.mp3")

