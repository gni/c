#include <stdio.h>
#include <cjson/cJSON.h>

int main() {
    const char *json_string = "{\"name\": \"Alice\", \"age\": 25}";
    cJSON *json = cJSON_Parse(json_string);

    if (!json) {
        printf("Error parsing JSON.\n");
        return 1;
    }

    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *age = cJSON_GetObjectItem(json, "age");

    printf("Name: %s\n", name->valuestring);
    printf("Age: %d\n", age->valueint);

    cJSON_Delete(json);
    return 0;
}
