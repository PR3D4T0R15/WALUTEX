#include "update_data.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int getDataFromServer()
{
    CURL* curl;
    CURLcode res;
    std::string buffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.nbp.pl/api/exchangerates/tables/C/?format=xml");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);
    }

    if (!updateArray(buffer))
    {
        return 1;
    }

    return 0;
}

int updateArray(std::string jsonInput)
{
    std::stringstream sstream;
    sstream << jsonInput;

    boost::property_tree::ptree xmldata;
    boost::property_tree::read_xml(sstream, xmldata);

    auto child = xmldata.get_child("ArrayOfExchangeRatesTable.ExchangeRatesTable.Rates");
    
    int counter = 0;
    BOOST_FOREACH(boost::property_tree::ptree::value_type & v, xmldata.get_child("ArrayOfExchangeRatesTable.ExchangeRatesTable.Rates"))
    {
        if (v.first == "Rate" && v.second.get("Code", "") != "XDR")
        {
            std::string val1 = v.second.get("Bid", "");
            currenciesData[counter].Bid = std::stod(val1);

            std::string val2 = v.second.get("Ask", "");
            currenciesData[counter].Ask = std::stod(val2);
        }
        counter++;
    }

    return 0;
}