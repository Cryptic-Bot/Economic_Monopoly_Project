//
//  Properties.hpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/29/25.
//

#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include <string>

class Property {
private:
    std::string name;
    int value;
    // Other attributes such as color group, rent, mortgage value, etc.

public:
    Property(const std::string& name = "", int value = 0) : name(name), value(value) {}

    const std::string& getName() const { return name; }
    int getValue() const { return value; }

    // Add more property-specific methods and attributes as needed
};

#endif // PROPERTIES_HPP
