#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>     
#include <string.h>     


#define MAX_MSG_LEN 1024

int sockfd;
pthread_t recv_thread, send_thread;

void *recv_msg(void *arg) {
    char buffer[MAX_MSG_LEN];
    while (1) {
        int len = recv(sockfd, buffer, MAX_MSG_LEN - 1, 0);
        if (len <= 0) {
            printf("\nConnection closed by peer.\n");
            kill(getppid(), SIGUSR1);
            exit(0);
        }
        buffer[len] = '\0';
        printf("\nPeer: %s\n", buffer);
        printf("You: ");
        fflush(stdout);
    }
    return NULL;
}

void *send_msg(void *arg) {
    char buffer[MAX_MSG_LEN];
    while (1) {
        printf("You: ");
        fflush(stdout);
        if (fgets(buffer, MAX_MSG_LEN, stdin) == NULL)
            continue;

        buffer[strcspn(buffer, "\n")] = '\0';  // Strip newline

        if (strcmp(buffer, "/exit") == 0) {
            printf("Ending chat...\n");
            shutdown(sockfd, SHUT_RDWR);
            close(sockfd);
            exit(0);
        }

        send(sockfd, buffer, strlen(buffer), 0);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fd>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sockfd = atoi(argv[1]);

    printf("Chat started. Type '/exit' to end chat.\n");

    // Start threads
    pthread_create(&recv_thread, NULL, recv_msg, NULL);
    pthread_create(&send_thread, NULL, send_msg, NULL);

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    close(sockfd);
    return 0;
}

