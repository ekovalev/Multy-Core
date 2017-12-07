/* Copyright 2017 by Multy.io
 * Licensed under Multy.io license.
 *
 * See LICENSE for details
 */

#ifndef UTILITY_H
#define UTILITY_H

#include "multy_core/common.h"
#include "multy_core/internal/utility.h"

#include <string>
#include <vector>

#define E(statement)                                                           \
    if ((statement) != 0)                                                      \
    {                                                                          \
        test_utility::throw_exception(#statement);                             \
    }

struct BinaryData;
struct ExtendedKey;

namespace test_utility
{
typedef std::vector<unsigned char> bytes;

bytes from_hex(const char* hex_str);
std::string to_hex(const bytes& bytes);
std::string to_hex(const BinaryData& data);
BinaryData to_binary_data(const bytes& data);
BinaryData to_binary_data(const char* data);
ExtendedKey make_dummy_extended_key();
wallet_core::internal::ExtendedKeyPtr make_dummy_extended_key_ptr();
EntropySource make_dummy_entropy_source();

template <typename T, size_t N>
BinaryData to_binary_data(const T (&data)[N])
{
    return BinaryData{
            reinterpret_cast<const unsigned char*>(data),
            N * sizeof(data[0])
    };
}

void throw_exception(const char* message);

} // test_utility

bool operator==(const BinaryData& lhs, const BinaryData& rhs);
bool operator==(const PublicKey& lhs, const PublicKey& rhs);
inline bool operator!=(const BinaryData& lhs, const BinaryData& rhs)
{
    return !(lhs == rhs);
}

#endif // UTILITY_H