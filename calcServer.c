#include <stdio.h>      /* for snprintf */
#include "csapp.h"
#include "calc.h"
#include <stdbool.h>

/* buffer size for reading lines of input from user */
#define LINEBUF_SIZE 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }
    struct Calc *calc = calc_create();
	int port = atoi(argv[1]);
    if (port < 1024) {
        printf("Not a free port\n");
        return 0;
    }
    int listen = Open_listenfd(port);
    if (listen < 0) {
        printf("Unable to open server\n");
        return 0;
    }

    int clientfd;
    struct sockaddr serv_addr;
    struct hostent *host_name;
    char *ip_address;

    bool exit = false;
    while (!exit) {
        socklen_t length = sizeof(serv_addr);
        clientfd = Accept(listen, NULL, NULL);
        int test = chat_with_client(calc, clientfd, clientfd);
        if (test == 0) {
            exit = true;
        }
    }
    calc_destroy(calc);

    

	return 0;
}

int chat_with_client(struct Calc *calc, int infd, int outfd) {
	rio_t in;
	char linebuf[LINEBUF_SIZE];

	/* wrap standard input (which is file descriptor 0) */
	rio_readinitb(&in, infd);

	/*
	 * Read lines of input, evaluate them as calculator expressions,
	 * and (if evaluation was successful) print the result of each
	 * expression.  Quit when "quit" command is received.
	 */
	int done = 0;
	while (!done) {
		ssize_t n = rio_readlineb(&in, linebuf, LINEBUF_SIZE);
		if (n <= 0) {
			printf("No input found. Enter new input:\n");
			return 1;
		} else if (strcmp(linebuf, "quit\n") == 0 || strcmp(linebuf, "quit\r\n") == 0) {
			/* quit command */
			return 0;
		} else {
			/* process input line */
			int result;
			if (calc_eval(calc, linebuf, &result) == 0) {
				rio_writen(outfd, "Error\n", 6);
                return 1;
			} else {
				/* output result */
				int len = snprintf(linebuf, LINEBUF_SIZE, "%d\n", result);
				if (len < LINEBUF_SIZE) {
					rio_writen(outfd, linebuf, len);
                    return 1;
				}
			}
		}
	}
    return 1;
}
