/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#ifdef MODULE_API_EXPORTS
#define MODULE_API __declspec(dllexport)
#else
#define MODULE_API __declspec(dllimport)
#endif
#else
#define MODULE_API
#endif

MODULE_API bool ASNBufferToJSBuffer(const char* inBuffer, char* outBuffer, unsigned int bufferSize, char* errorBuff, unsigned int errorBuffSize);
MODULE_API bool ASNFileToJSFile(const char* inPath, const char* outPath, char* errorBuff, unsigned int errorBuffSize);

MODULE_API bool ASNBufferToCPPBuffer(const char* inBuffer, char* outBuffer, unsigned int bufferSize, char* errorBuff, unsigned int errorBuffSize);
MODULE_API bool ASNFileToCPPFile(const char* inPath, const char* outPath, char* errorBuff, unsigned int errorBuffSize);

#ifdef __cplusplus
}
#endif
