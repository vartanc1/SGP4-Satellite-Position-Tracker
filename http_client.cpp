//Fetches raw text from the CelesTrak website
#include "http_client.h"
#include <curl/curl.h>
#include <string>

//curl fetches data from the URL, and as the data arrives it calls write_func multiple times beacause the data arrives sequentially and each time write_func is called it write data the chunk into the response string

//append is used here in the buffer because curl sends the data in multiple buffers and if we used the equal sign the previous data would be lost


//// size is how big each chunk of bytes
//nmemb how many chunks of data so x*y = total_size here
//"N elements, each of size X bytes"

//void *clientp is used so you can point to a string, array, int etc
//but we clarify what the buffer is by using static_cast<std::string*>
//letting the compiler know the cast


//What were the two bugs in the original error handling code?
//line 47 had a bug issues where if the result wasnt OK, there was no
//throw command to stop the program, throw will not let the program continue
//on its own

static size_t write_func(char *data, size_t size, size_t nmemb, void *clientp){
    size_t total_size = size*nmemb;
    std::string* buffer = static_cast<std::string*>(clientp);

    buffer->append(static_cast<char*>(data),total_size);
    return total_size;
}


std::string fetch_url(const std::string& url){
    CURL* curl = curl_easy_init();
    CURLcode result;
    if(!curl){
        throw std::runtime_error("failed to init curl");

    }
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&response);

    //send request
    result = curl_easy_perform(curl);

    if(result!=CURLE_OK){
        curl_easy_cleanup(curl);
        throw std::runtime_error("send request failed, CURLE_OK failure");
    }
    curl_easy_cleanup(curl);
    return response;

    
}