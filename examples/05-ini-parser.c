#define PLIBSYS_IMPLEMENTATION
#include "plibsys.h"
#include <stdio.h>
#include <string.h>

int main() {
    p_libsys_init();

    PError *error = NULL;
    PIniFile *ini = p_ini_file_new("examples/aa-acme.ini");

    if (ini == NULL) {
        printf("Failed to create INI file object\n");
        p_libsys_shutdown();
        return 1;
    }

    if (!p_ini_file_parse(ini, &error)) {
        printf("Failed to parse INI file: %s\n", error ? error->message : "Unknown error");
        p_error_free(error);
        p_ini_file_free(ini);
        p_libsys_shutdown();
        return 1;
    }

    const char *value = p_ini_file_parameter_string(ini, "owner", "name", "default_value");
    if (value != NULL) {
        printf("Value for 'name' in 'owner': %s\n", value);
    } else {
        printf("Key not found\n");
    }

    p_ini_file_free(ini);
    p_libsys_shutdown();
    return 0;
}
