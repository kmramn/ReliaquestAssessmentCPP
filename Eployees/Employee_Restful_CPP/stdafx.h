#pragma once

#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <codecvt>
#include <string>

#include <mutex>
#include <chrono>
#include <iomanip>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/http_msg.h>
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include "nlohmann/json.hpp"
using njson = nlohmann::json;

#include "Util.h"
#include "logger.h"
#include "EmployeeManager.h"
#include "EmployeeHandler.h"