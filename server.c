/*
EL4236 Perancangan Perangkat Lunak Jaringan 2023/2024
*Hari dan Tanggal : Rabu, 6 Maret 2024
*Nama (NIM) 1     : Karma Kunga (13220028)
*Nama (NIM) 2     : Bostang Palaguna (13220055)
*Nama File        : server.c
*Deskripsi        : sourcecode server untuk program komunikasi TCP socket
*Programmer       : Bostang Palaguna
*/

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#define MAX 80 
#define PORT 8081 
#define SA struct sockaddr 

// DEKLARASI KONSTANTA
const char nama1[MAX]="Karma Kunga";
const char nama2[MAX]="Bostang Palaguna";
const char NIM1[MAX]="13220028";
const char NIM2[MAX]="13220055";

// REALISASI FUNGSI

// Fungsi yang didesain untuk interaksi antara server dengan client
void func(int connfd) 
{ 
	char buff[MAX];  // buffer untuk pesan
	int n; 

	// infinite loop sampai server mengirim 'selesai'
	for (;;)
    {
        // mengosongkan buffer
		bzero(buff, MAX); 

        // membaca pesan dari client dan menyimpan ke buffer
		read(connfd, buff, sizeof(buff)); 

        // mencetak buffer yang berisi pesan dari client
        printf("client: %s\n", buff); 
		// bzero(buff, MAX); // mengosongkan kembali buffer
	
        // jika buffer berisi 'nama1', maka server mengembalikan pesan 'Karma Kunga' ke client
        if (strncmp("nama1", buff, 5) == 0)
        {
            strcpy(buff,nama1);
        }

        // jika buffer berisi 'nama2', maka server mengembalikan pesan 'Bostang Palaguna' ke client
        else if (strncmp("nama2", buff, 5) == 0)
        {
            strcpy(buff,nama2);
        }

        // jika buffer berisi 'NIM1', maka server mengembalikan pesan 'Bostang Palaguna' ke client
        else if (strncmp("NIM1", buff, 5) == 0)
        {
            strcpy(buff,NIM1);
        }

        // jika buffer berisi 'NIM2', maka server mengembalikan pesan 'Bostang Palaguna' ke client
        else if (strncmp("NIM2", buff, 5) == 0)
        {
            strcpy(buff,NIM2);
        }

        // jika buffer berisi 'NIM2', maka server mengembalikan pesan 'Bostang Palaguna' ke client
        else if (strncmp("selesai", buff, 5) == 0)
        {
            strcpy(buff,"selesai");
            // break;
        }

        // selain isi buffer di atas, maka akan ditampilkan pesan error 
        else
        {
            strcpy(buff,"Perintah tidak diketahui");
        }

		// mengirimkan buffer (isi pesan dari server) ke client
		write(connfd, buff, sizeof(buff)); 

        // break apabila pesan 'selesai' telah dikirim ke client
        if (strncmp("selesai", buff, 5) == 0)
        {
            break;
        }
	} 
}

// ALGORITMA UTAMA
    // Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server accept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server accept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
}

// Referensi :
    // https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/