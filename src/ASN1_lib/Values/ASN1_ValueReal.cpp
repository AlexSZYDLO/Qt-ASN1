/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */

/*
 Part of this code copied from here: https://github.com/vlm/asn1c/blob/master/skeletons/REAL.c
*/

#include <cmath>
#include "ASN1_Value_Nodes.h"

using namespace Utils;

namespace Value {

  double hexstr2double(const ByteArray& hexstr) {
    union {
      unsigned long long i;
      double d;
    } value;

    value.i = std::stoull(hexstr.GetString(), nullptr, 16);
    return value.d;
  }

  ByteArray double2hexstr(double x) {
    union {
      unsigned long long i;
      double d;
    } value;

    value.d = x;
    char buf[17];
    snprintf(buf, sizeof(buf), "%016llx", value.i);
    buf[16] = 0; //make sure it is null terminated.
    return ByteArray(buf);
  }

  void ASN1_ValueReal::RealToHex(const double& input, ByteArray& output, std::string& error) {
    error.clear();
    ByteArray result;

    std::string realAsBinary = HexAsBinary8Padded(double2hexstr(input));
    char sign = (char)std::stoi(realAsBinary.substr(0, 1), nullptr, 2);
    //int ex = std::stoi(realAsBinary.substr(1, 11), nullptr, 2);
    //unsigned long long man = std::stoll(realAsBinary.substr(12), nullptr, 2);

    if(std::isnan(input)) {
      result.Append(ByteArray("42")); // NaN
    } else if(!std::isfinite(input)) {
      if(sign == 0) {
        result.Append(ByteArray("40")); // + infinity
      } else {
        result.Append(ByteArray("41")); // - infinity
      }
    } else if(input == 0) {
      if(sign == 0) {
        return; // zero
      } else {
        result.Append(ByteArray("43")); // minus zero
      }
    }

    if(result.Size() == 1) {
      output = result;
      return;
    }

    unsigned int LE = 1;
    unsigned char littleEndian = *reinterpret_cast<unsigned char*>(&LE);

    unsigned char dscr[sizeof(double)];
    unsigned char* mstop = nullptr; /* Last byte of mantissa */
    unsigned char bmsign; /* binary mask with sign */

    if(littleEndian) {
      const unsigned char* s = (reinterpret_cast<const unsigned char*>(&input)) + sizeof(input) - 2;
      const unsigned char* start = (reinterpret_cast<const unsigned char*>(&input));
      unsigned char* d;

      bmsign = 0x80 | ((s[1] >> 1) & 0x40); //sets binary encoding (b8=1) and sign (b7)
      for(mstop = d = dscr; s >= start; d++, s--) {
        *d = *s;
        if(*d) mstop = d;
      }
    }

    /* Remove parts of the exponent, leave mantissa and explicit 1. */
    dscr[0] = 0x10 | (dscr[0] & 0x0f);

    /* Adjust exponent in a very unobvious way */
    int expval = ilogb(input);
    expval -= 8 * ((int)(mstop - dscr) + 1) - 4;

    /* This loop ensures DER conformance by forcing mantissa odd: 11.3.1 */
    unsigned char mval = *mstop; /* Value of the last byte of mantissa */
    if(mval && !(mval & 1)) {
      unsigned char shift_count = 1;
      unsigned char ishift;
      unsigned char* mptr;
      unsigned char accum;

      // Figure out what needs to be done to make mantissa odd.
      if(!(mval & 0x0f)) /* Speed-up a little */
        shift_count = 4;
      while(((mval >> shift_count) & 1) == 0)
        shift_count++;

      ishift = 8 - shift_count;
      accum = 0;

      /* Go over the buffer, shifting it shift_count bits right. */
      for(mptr = dscr; mptr <= mstop; mptr++) {
        mval = *mptr;
        *mptr = accum | (mval >> shift_count);
        accum = mval << ishift;
      }

      /* Adjust exponent appropriately. */
      expval += shift_count;
    }

    unsigned char buf[16]; /* More than enough for 8-byte dbl_value */
    unsigned char* ptr = buf;

    if(expval < 0) {
      if((expval >> 7) == -1) {
        *ptr++ = bmsign | 0x00;
        *ptr++ = (char)expval;
      } else if((expval >> 15) == -1) {
        *ptr++ = bmsign | 0x01;
        *ptr++ = (char)expval >> 8;
        *ptr++ = (char)expval;
      } else {
        *ptr++ = bmsign | 0x02;
        *ptr++ = (char)expval >> 16;
        *ptr++ = (char)expval >> 8;
        *ptr++ = (char)expval;
      }
    } else if(expval <= 0x7f) {
      *ptr++ = bmsign | 0x00;
      *ptr++ = (char)expval;
    } else if(expval <= 0x7fff) {
      *ptr++ = bmsign | 0x01;
      *ptr++ = (char)expval >> 8;
      *ptr++ = (char)expval;
    } else {
      *ptr++ = bmsign | 0x02;
      *ptr++ = (char)expval >> 16;
      *ptr++ = (char)expval >> 8;
      *ptr++ = (char)expval;
    }

    unsigned int buflen = (int)(mstop - dscr) + 1;
    memcpy(ptr, dscr, buflen);
    ptr += buflen;
    buflen = (int)(ptr - buf);
    *ptr = 0;

    for(unsigned char* c = buf; c < buf + buflen; c++)
      result.Append(IntAsHex(*c));

    output = result;
  }

  void ASN1_ValueReal::HexToReal(const ByteArray& input, double& output, std::string& error) {
    error.clear();
    const std::string strHexReal = input.GetString();

    if(strHexReal == "") {
      output = 0.0;
      return;
    }

    unsigned int octv;
    //if (strHexReal.size() > 1)
    octv = std::stoul(strHexReal.substr(0, 2), nullptr, 16);
    //else return false;

    switch(octv & 0xC0) {
      case 0x40: /* X.690: 8.5.6 a) => 8.5.9 */
        if(octv == 0x40)
          output = INFINITY; /* 01000000: PLUS-INFINITY */
        else if(octv == 0x41)
          output = -INFINITY; /* 01000001: MINUS-INFINITY */
        else if(octv == 0x42)
          output = NAN; /* 01000010: NOT-A-NUMBER */
        else if(octv == 0x43)
          output = -0.0; /* 01000011: minus zero */
        else
          error = "Double special value not recognized";
        return;

      case 0x00:
        /* Decimal. NR{1,2,3} format from ISO 6093.  X.690: 8.5.7
      * NR1: [ ]*[+-]?[0-9]+
      * NR2: [ ]*[+-]?([0-9]+\.[0-9]*|[0-9]*\.[0-9]+)
      * NR3: [ ]*[+-]?([0-9]+\.[0-9]*|[0-9]*\.[0-9]+)[Ee][+-]?[0-9]+  */

        if(octv == 0 || (octv & 0x3C)) {
          error = "ISO 6093 - Remaining values of bits 6 to 1 are Reserved";
          return;
        }

        std::string RealAsString = Utils::HexToString(input);

        for(unsigned int i(0); i < RealAsString.size(); ++i)
          if(RealAsString[i] == ',') RealAsString[i] = '.';

        char* endptr;
        double d = std::strtod(RealAsString.c_str() + 1, &endptr); // +1 to skip the format coding byte

        if(*endptr != '\0') {
          error = "Format is not consistent with ISO 6093";
          return;
        }

        output = d;
        return;
    }

    // ------- Binary representation.

    unsigned int baseF;
    switch((octv & 0x30) >> 4) {
      case 0x00:
        baseF = 1;
        break; /* base 2 */
      case 0x01:
        baseF = 3;
        break; /* base 8 */
      case 0x02:
        baseF = 4;
        break; /* base 16 */
      default:
        error = "Base not recognized";
        return;
    }

    int sign = (octv & 0x40); /* bit 7 */
    unsigned int scaleF = (octv & 0x0C) >> 2; /* bits 4 to 3 */

    if(strHexReal.size() <= (unsigned int)(1 + (octv & 0x03))) {
      error = "Double incorrect encoding";
      return;
    }

    // get exponent length
    char expIdx;
    unsigned char elen = (octv & 0x03); /* bits 2 to 1; 8.5.6.4 */
    if(elen == 0x03) { /* bits 2 to 1 = 11; 8.5.6.4, case d) */
      elen = (unsigned char)std::stoul(strHexReal.substr(2, 2), nullptr, 16);
      if(elen == 0 || strHexReal.size() <= (unsigned char)(2 + elen)) {
        error = "Double incorrect encoding";
        return;
      }
      expIdx = 2;
    } else {
      expIdx = 1;
      elen++;
    }

    /* Fetch the multibyte exponent */
    int expval = 0;
    for(int i = expIdx + elen - 1; i > expIdx - 1; i--) {
      char c = (char)HexAsInt(ByteArray(strHexReal.substr(i * 2, 2).c_str()));
      expval += (expval * 256) + c;
    }

    /* Okay, the exponent is here. Now, what about mantissa? */
    double m = 0.0; /* Initial mantissa value */
    char mIdx = expIdx + elen;
    unsigned int mlen = (unsigned int)strHexReal.size() / 2 - mIdx;
    for(unsigned int i = mIdx; i < mIdx + mlen; i++) {
      unsigned char byte = (unsigned char)HexAsInt(ByteArray(strHexReal.substr(i * 2, 2).c_str()));
      m = ldexp(m, 8) + byte;
    }

    /* (S * N * 2^F) * B^E
    * Essentially:
    m = ldexp(m, scaleF) * pow(pow(2, base), expval); */

    m = ldexp(m, expval * baseF + scaleF);
    output = sign ? -m : m;
  }

} // namespace Value
