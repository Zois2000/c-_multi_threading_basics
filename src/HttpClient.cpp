#include "HttpClient.h"
#include <curl/curl.h>
#include <stdexcept>

size_t HttpClient::write_callback(void* contents, size_t size, size_t nmemb, std::string* output) 
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

std::string HttpClient::url_encode(void* curl_handler, const std::string& value)
{
    CURL* curl = static_cast<CURL*>(curl_handler);
    char* encoded = curl_easy_escape(curl, value.c_str(), static_cast<int>(value.length()));

    if (!encoded)
    {
        throw std::runtime_error("URL-Encoding fehlgeschlagen");
    }

    std::string result = encoded;
    curl_free(encoded);
    return result;
}

std::string HttpClient::post_form(const std::string& url, const std::map<std::string, std::string>& formFields) const 
{
    CURL* curl = curl_easy_init();

    if (!curl) {
        throw std::runtime_error("curl_easy_init() fehlgeschlagen");
    }

    std::string response;
    std::string post_fields;

    for (auto it = formFields.begin(); it != formFields.end(); ++it) {
        if (it != formFields.begin()) {
            post_fields += "&";
        }

        post_fields += url_encode(curl, it->first);
        post_fields += "=";
        post_fields += url_encode(curl, it->second);
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/sparql-results+json");
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpClient::write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "cpu-thread-query/0.1");

    CURLcode result = curl_easy_perform(curl);

    curl_slist_free_all(headers);

    if (result != CURLE_OK) {
        std::string error = curl_easy_strerror(result);
        curl_easy_cleanup(curl);
        throw std::runtime_error("HTTP-Request fehlgeschlagen: " + error);
    }

    curl_easy_cleanup(curl);

    return response;
}
