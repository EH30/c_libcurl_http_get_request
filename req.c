#include <stdio.h>
#include "libcurl/include/curl/curl.h"


size_t got_data(char *buffer, size_t itemsize, size_t nitems, void* ignorethis) {
    size_t bytes = itemsize * nitems;
    for (int i = 0; i < bytes; i++) {
        printf("%c", buffer[i]);
    }
    return bytes;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if (!curl) {
        printf("error: (%d)\n", curl);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        printf("error: [%d]\n", res);
        return 1;
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    printf("\nResponse Code: [%ld]\n", response_code);

    curl_easy_cleanup(curl);
    return 0;
}
