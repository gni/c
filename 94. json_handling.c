#include <stdio.h>
#include <jansson.h>

int main() {
    // Create JSON object
    json_t *root = json_object();
    json_object_set_new(root, "name", json_string("Alice"));
    json_object_set_new(root, "age", json_integer(25));

    // Write to string
    char *json_string = json_dumps(root, JSON_INDENT(4));
    printf("JSON Output:\n%s\n", json_string);

    // Free resources
    free(json_string);
    json_decref(root);

    return 0;
}
