#include <curl/curl.h>
#include "json.hpp"
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <algorithm>
struct Median
{
    double sum;
    std::vector<double> vector;
};
static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string* html)
{
    int result = 0;
    if (buffer != NULL)
    {
        html->append(buffer, size * nmemb);
        result = size * nmemb;
    }
    return result;
}
void foo(char &symbol)
{
    symbol=getchar();
}
int main()
{
    std::map<std::string, Median> map;
    int count = 0;
    nlohmann::json j;
    std::string str;
    char symbol = 0;
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::thread th(foo, std::ref(symbol));
    if (curl)
    {
        while (symbol==0)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
            res = curl_easy_perform(curl);
            j = nlohmann::json::parse(str);
          
            auto it = j.begin();
            std::cout << *it << ':' << std::endl;
            advance(it, 4);
            auto end = (*it).end();
            it = (*it).begin();
            for (; it != end; ++it)
            {
                auto it2 = (*it).begin();
                std::string strtemp;
                strtemp = *it2;
                advance(it2, 3);
                double tempvalue = (double)1 / *it2;
                tempvalue /= *it2;
                advance(it2, 3);
                tempvalue *= (double)*it2;
                if (count == 0)
                {
                    Median tempM;
                    tempM.sum=tempvalue;
                    tempM.vector.push_back(tempvalue);
                    map.emplace(strtemp, tempM);
                }
                else
                {
                    map.at(strtemp).vector.push_back(tempvalue);
                    map.at(strtemp).sum += tempvalue;
                }
                std::cout << strtemp << "   " << tempvalue << std::endl;
            }
            count++;
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
            str.clear();
        }
    }
    curl_easy_cleanup(curl);
    std::cout << std::endl;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        auto tempit = it->second.vector.begin();
        advance(tempit, count/2);
        std::nth_element(it->second.vector.begin(), tempit, it->second.vector.end());
        std::cout << it->first << "   " << (double)it->second.sum / count << "   " << it->second.vector[count / 2] << std::endl;
    }
    getchar();
    th.detach();
    return 0;
}