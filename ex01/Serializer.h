#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <stdint.h>
#include "Data.h"

class Serializer
{
private:
    Serializer();
    Serializer(const Serializer &src);
    Serializer &operator=(const Serializer &other);
    ~Serializer();

public:
    static uintptr_t serialize(Data *data);
    static Data *deserialize(uintptr_t raw);
};

#endif
