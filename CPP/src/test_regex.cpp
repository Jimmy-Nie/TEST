#include <iostream>
#include <string>
#include <regex>
#include <iomanip>

bool testRegex(std::string text) {
    std::regex pattern("^[0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2}");
    if (std::regex_match(text, pattern)) {
        std::cout << "The string " << text << " matches the pattern." << std::endl;
    } else {
        std::cout << "The string " << text << " DONOT matches the pattern." << std::endl;
    }

    return 0;
}
    
int main() {
    // testRegex("v1.2.3");
    // testRegex("1.2.3");
    // testRegex("11.2.3");
    // testRegex("1.12.3");
    // testRegex("1.2.13");
    // testRegex("1.2.345");
    // testRegex("1.x.3");
    // testRegex("1.2.3.4.5.6");

    float angle = 523.153;
    angle = ((int)angle % 360) + (angle - (int)angle);  // 角度保证在 (-360°, 360°)
    std::cout << "The angle: " << angle << std::endl;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << angle << std::endl;;
    std::cout << "The ss: " << ss.str();

    ss >> angle;
    std::cout << "The angle: " << angle << std::endl;

    return 0;
}