import socket

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 8080        # Port to listen on (non-privileged ports are > 1023)
MAX_BUFFER_SIZE = 80

def handle_connection(sockfd):
   """Handles communication with the server."""
   while True:
       try:
           data = input("Enter the string: ").encode()
           sockfd.sendall(data)

           response = sockfd.recv(MAX_BUFFER_SIZE).decode()
           print("From Server:", response)

           if response.startswith("exit"):
               print("Client Exit...")
               break

       except (ConnectionError, KeyboardInterrupt):
           print("Connection closed.")
           break

def main():
   """Creates a client socket and connects to the server."""
   with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sockfd:
       try:
           sockfd.connect((HOST, PORT))
           print("Connected to the server.")

           handle_connection(sockfd)

       except ConnectionRefusedError:
           print("Connection with the server failed.")

if __name__ == "__main__":
   main()

# Referensi
    # https://github.com/RPKQ/CNS_HW2