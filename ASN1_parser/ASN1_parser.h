/*
 * Copyright (c) 2016, 2017 Alexandre SZYDLOWSKI <alexandre.szydlowski@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to GPL-V3 license.
 */
#pragma once

#if defined DLLCOMPIL
#define DLLSPEC __declspec(dllexport)
#else
#define DLLSPEC __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLLSPEC bool ASNBufferToJSBuffer(const char* inBuffer, char* outBuffer, unsigned int bufferSize, char* errorBuff, unsigned int errorBuffSize);
DLLSPEC bool ASNFileToJSFile(const char* inPath, const char* outPath, char* errorBuff, unsigned int errorBuffSize);

DLLSPEC bool ASNBufferToCPPBuffer(const char* inBuffer, char* outBuffer, unsigned int bufferSize, char* errorBuff, unsigned int errorBuffSize);
DLLSPEC bool ASNFileToCPPFile(const char* inPath, const char* outPath, char* errorBuff, unsigned int errorBuffSize);

}
