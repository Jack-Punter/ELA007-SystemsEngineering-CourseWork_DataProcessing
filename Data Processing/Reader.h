#pragma once
#include <ostream>
#include <fstream>
#include <vector>
#include <array>
#include "helpers.h"
#include "Vec2.h"

std::vector<fileData> Reader(const std::string file);

std::ostream& operator<< (std::ostream& cout, const fileData& data);