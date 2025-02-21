#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <clover.h>

std::string ToHex(uintptr_t value);

uintptr_t GetBaseModuleAddress(const char* ModuleName);

uintptr_t ResolveAddress(uintptr_t Address, const std::vector<uintptr_t>& offsets);

//uintptr_t CheckGameVersion();

void CheckKeyState();

void Features();

#endif // UTILS_H

