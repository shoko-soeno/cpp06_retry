#include <iostream>
#include "Serializer.h"

int main()
{
    Data *data = new Data;
    data->name = "test";
    data->value = 42;

    std::cout << "Original data - Address: " << data << ", Name: " << data->name << ", Value: " << data->value << std::endl;

    uintptr_t serialized = Serializer::serialize(data);
    std::cout << "Serialized: " << serialized << std::endl;

    Data *deserialized = Serializer::deserialize(serialized);
    std::cout << "Deserialized data - Address: " << deserialized << ", Name: " << deserialized->name << ", Value: " << deserialized->value << std::endl;

    std::cout << "Pointers are equal: " << (data == deserialized ? "true" : "false") << std::endl;

    delete data;

    Data d1 = {"foo", 123};
    Data d2 = {"bar", -999};
    Data d3 = {"", 0};

    Data* arr[] = {&d1, &d2, &d3, NULL};

    for (int i = 0; i < 4; ++i) {
        uintptr_t raw = Serializer::serialize(arr[i]);
        Data* restored = Serializer::deserialize(raw);
        std::cout << "Test " << i << ": ";
        if (arr[i] == NULL) {
            std::cout << (restored == NULL ? "nullptr OK" : "nullptr NG") << std::endl;
        } else {
            std::cout << "Addr: " << arr[i] << " <-> " << restored
                    << ", Name: " << restored->name
                    << ", Value: " << restored->value
                    << ", Equal: " << (arr[i] == restored ? "true" : "false") << std::endl;
        }
    }
    return 0;
}
