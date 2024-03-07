'''
EL4236 Perancangan Perangkat Lunak Jaringan 2023/2024
*Hari dan Tanggal : Rabu, 6 Maret 2024
*Nama (NIM) 1     : Karma Kunga (13220028)
*Nama (NIM) 2     : Bostang Palaguna (13220055)
*Nama File        : server.c
*Deskripsi        : sourcecode server untuk program komunikasi TCP socket
*Programmer       : Bostang Palaguna
'''
import sys
import socket

# HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
# HOST = '10.8.100.167'  # IPv4 dari server
PORT = 8081        # Port to listen on (non-privileged ports are > 1023)
MAX_BUFFER_SIZE = 80

def handle_connection(sockfd):
   """Handles communication with the server."""
   while True:
       try:
           data = input("Client: ").encode()
           sockfd.sendall(data)

           response = sockfd.recv(MAX_BUFFER_SIZE).decode()
           if response != "selesai":
            print("Server:", response)

           if response.startswith("selesai"):
               print("Memutus koneksi...")
               break

       except (ConnectionError, KeyboardInterrupt):
           print("Connection closed.")
           break

def main(HOST_IP):
   """Creates a client socket and connects to the server."""
   with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sockfd:
       try:
           sockfd.connect((HOST_IP, PORT))
           print("Connected to the server.")

           handle_connection(sockfd)

       except ConnectionRefusedError:
           print("Connection with the server failed.")

if __name__ == "__main__":
    if sys.argv[0] == 2:
        HOST_IP = sys.argv[1]
    else:
        HOST_IP = '127.0.0.1' # localhost
    print(len(sys.argv))
    main(HOST_IP)

# Referensi
    # https://github.com/RPKQ/CNS_HW2
    # https://medium.com/@evaGachirwa/running-python-script-with-arguments-in-the-command-line-93dfa5f10eff
# Improvement di versi 2
    # IP dari server dijadikan argumen terhadap fungsi python
   # karena IP dari server cenderung berubah-ubah.