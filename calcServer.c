#include <stdio.h>      /* for snprintf */
#include "csapp.h"
#include "calc.h"
#include <stdbool.h>

/* buffer size for reading lines of input from user */
#define LINEBUF_SIZE 1024

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
    while (1) {
		ssize_t n = rio_readlineb(&in, linebuf, LINEBUF_SIZE);
		if (n <= 0) {
			/* error or end of input */
		} else if (strcmp(linebuf, "quit\n") == 0 || strcmp(linebuf, "quit\r\n") == 0) {
			/* quit command */
			return 1;
		} else if (strcmp(linebuf, "shutdown\n") == 0 || strcmp(linebuf, "shutdown\r\n") == 0){
            return 0;
        } else {
			/* process input line */
			int result;
			if (calc_eval(calc, linebuf, &result) == 0) {
				/* expression couldn't be evaluated */
				rio_writen(outfd, "Error\n", 6);
			} else {
				/* output result */
				int len = snprintf(linebuf, LINEBUF_SIZE, "%d\n", result);
				if (len < LINEBUF_SIZE) {
					rio_writen(outfd, linebuf, len);
				}
			}
		}
	}
    return 1;
}

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
    int listen = Open_listenfd(argv[1]);
    printf("Server created: %d\n", listen);
    if (listen < 0) {
        printf("Unable to open server\n");
        return 0;
    }


    //fd_set fdSet;
    //FD_ZERO(&fdSet);
    //FD_SET(listen, &fdSet);
    int exit = 1;
    int loopCounter = 0;
    while (exit) {
        int clientfd = Accept(listen, NULL, NULL);
        if (clientfd > 0) {
            exit = chat_with_client(calc, clientfd, clientfd);
            close(clientfd);
        }
        loopCounter++;
    }
    close(listen);
    calc_destroy(calc);

    

	return 0;
}

