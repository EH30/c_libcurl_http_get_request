#include <stdio.h>
#include "libcurl/include/curl/curl.h"

int main(void) {
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if (!curl) {
        printf("error: (%d)\n", curl);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "www.google.com");
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
