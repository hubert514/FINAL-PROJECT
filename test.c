#include <stdio.h>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;

    hubert
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/completions");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "prompt=你好，世界！");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Authorization: Bearer YOUR_API_KEY");
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() 失败：%s\n", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
    }
    
    return 0;
}
