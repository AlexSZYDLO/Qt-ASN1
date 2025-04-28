/*
* Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
* Redistribution and modifications are permitted subject to GPL-V3 license.
*/
#pragma once
#include "../ASN1_Value.h"


namespace Value
{

template<Utils::eNodeType type> struct UnderlyingType {};
template<> struct UnderlyingType<Utils::cBitString>  { using T = std::string; };
template<> struct UnderlyingType<Utils::cBoolean>    { using T = bool; };
template<> struct UnderlyingType<Utils::cEnumerated> { using T = int; };
template<> struct UnderlyingType<Utils::cIA5String>  { using T = std::string; };
template<> struct UnderlyingType<Utils::cInteger>    { using T = int; };
template<> struct UnderlyingType<Utils::cNull>       { using T = bool; };
template<> struct UnderlyingType<Utils::cObjectID>   { using T = std::string; };
template<> struct UnderlyingType<Utils::cOctetString>{ using T = ByteArray; };
template<> struct UnderlyingType<Utils::cReal>       { using T = double; };
template<> struct UnderlyingType<Utils::cUTCTime>    { using T = std::string; };
template<> struct UnderlyingType<Utils::cUTF8String> { using T = std::string; };

template <Utils::eNodeType T> class ASN1_ValueDer;

} // namespace Value
