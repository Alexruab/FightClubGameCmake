#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <string>
#   include <optional>

template<typename T>
static std::optional<T> parser(const std::string& jsonStr)
{
    try
    {
        const auto json = nlohmann::json::parse(jsonStr);
        return json.get<T>();
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << "Parse error:" << e.what() << std::endl;
    }

    return std::nullopt;
}

struct ChuckResponse
{
    std::string value;
    std::string id;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChuckResponse, value, id)
};

int main() {

    auto response = cpr::Get(cpr::Url{"https://api.chucknorris.io/jokes/random"});

    if (response.status_code != 200)
    {
        return EXIT_FAILURE;
    }

    std::cout << response.status_code << std::endl;
    std::cout << response.header["content-type"] << std::endl;
    std::cout << response.text << std::endl;
    if (const auto chuckResponse = parser<ChuckResponse>(response.text))
    {
        std::cout << "==============================================" << std::endl;
        std::cout << chuckResponse->value << std::endl;
        std::cout << "id: " << chuckResponse->id << std::endl;
    }

    return EXIT_SUCCESS;
}