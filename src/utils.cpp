#include "utils.h"
#include <regex>


std::string preProcessUrl(std::string url)
{
    std::regex e {"https?:\\/\\/"};
    return std::regex_replace(url, e, "");
}

std::string shortenUrl(std::string input)
{
    vector<base64::byte> data(begin(input), end(input));
    std::string encoded = base64::encode(data);
    return encoded;
}