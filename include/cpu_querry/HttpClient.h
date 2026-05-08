#pragma

#include <map>
#include <string>

class HttpClient {
    public:
    std::string post_form(const std::string& url, const std::map<std::string, std::string>& form_fields) const;

    private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output);

    static std::string url_encode(void* curl_handle, const std::string& value);
};