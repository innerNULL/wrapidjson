// 2020-07-25

#ifndef WRAPIDJSON_CHECKER_CHECKER_H_
#define WRAPIDJSON_CHECKER_CHECKER_H_

#include <algorithm>    
#include <random>      
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <chrono>
#include <cassert>
#include <locale>
#include <codecvt>
#include <any>
#include <utility>
#include <set>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>

#include "wrapidjson/3rdparty/rapidjson/include/rapidjson/document.h"


namespace wrapidjson {
namespace checker {


/**
 * @brief 
 * Basic checking for `rapidjson::Document` object. Usually, the `rapidjson::Document` object 
 * should be called `SetObject` method first before doing some handling.
 *
 * @param target_json_obj Target checking `rapidjson::Document` object.
 */
inline auto json_obj_basic_checker(const rapidjson::Document& target_json_obj) -> int32_t {
  if (!target_json_obj.IsObject()) { return 1; }
  return 0;
}


inline auto json_obj_field_checker(const rapidjson::Document& target_json_obj, 
      const std::string& target_field_name, const std::string& target_field_type) -> int32_t {
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!target_json_obj.HasMember(target_field_name.c_str())) { return 2; }
  if (target_field_type == "string" && !target_json_obj[target_field_name.c_str()].IsString()) { return 3; }
  if (target_field_type == "int" && !target_json_obj[target_field_name.c_str()].IsInt()) { return 4; }
  if (target_field_type == "double" && !target_json_obj[target_field_name.c_str()].IsDouble()) { return 5; }
  if (target_field_type == "num" && !target_json_obj[target_field_name.c_str()].IsNumber()) { return 6; }
  if (target_field_type == "bool" && !target_json_obj[target_field_name.c_str()].IsBool()) { return 7; }
  return 0;
}


} // namespace checker
} // namespace wrapidjson

#endif
