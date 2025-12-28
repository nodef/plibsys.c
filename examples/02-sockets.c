#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>

int main() {
    p_libsys_init();

    PSocketAddress *address = p_socket_address_new("127.0.0.1", 8080);
    PSocket *server = p_socket_new(P_SOCKET_FAMILY_INET, P_SOCKET_TYPE_STREAM, P_SOCKET_PROTOCOL_TCP, NULL);

    if (!p_socket_bind(server, address, TRUE, NULL)) {
        printf("Failed to bind server socket\n");
        p_socket_address_free(address);
        p_socket_free(server);
        p_libsys_shutdown();
        return 1;
    }

    PError *error = NULL;
    if (!p_socket_listen(server, &error)) {
        printf("Failed to listen on server socket: %s\n", error != NULL ? error->message : "Unknown error");
        p_error_free(error);
        p_socket_address_free(address);
        p_socket_free(server);
        p_libsys_shutdown();
        return 1;
    }

    printf("Server is listening on 127.0.0.1:8080\n");

    PSocket *client = p_socket_accept(server, NULL);
    if (client == NULL) {
        printf("Failed to accept client connection\n");
    } else {
        printf("Client connected!\n");
        p_socket_free(client);
    }

    p_socket_address_free(address);
    p_socket_free(server);
    p_libsys_shutdown();
    return 0;
}
