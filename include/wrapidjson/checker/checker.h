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

#include <rapidjson/document.h>


namespace wrapidjson {


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



/**
 * @brief 
 * Checking if `rapidjson::Document` object is valid and has a valid certain type 
 * key-pair at same time. Different error code has different meaning, so very elastic. 
 *
 * @param target_json_obj Target checking `rapidjson::Document` object.
 * @param target_key Target checking key.
 * @param target_val_type Target checking key's correpondong value type.
 */
inline auto json_obj_kv_checker(const rapidjson::Document& target_json_obj, 
      const std::string& target_key, const std::string& target_val_type) -> int32_t {
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!target_json_obj.HasMember(target_key.c_str())) { return 2; }
  if (target_val_type == "string" && !target_json_obj[target_key.c_str()].IsString()) { return 3; }
  if (target_val_type == "int" && !target_json_obj[target_key.c_str()].IsInt()) { return 4; }
  if (target_val_type == "double" && !target_json_obj[target_key.c_str()].IsDouble()) { return 5; }
  if (target_val_type == "num" && !target_json_obj[target_key.c_str()].IsNumber()) { return 6; }
  if (target_val_type == "bool" && !target_json_obj[target_key.c_str()].IsBool()) { return 7; }

  if (target_val_type == "num_array") {
    if (!target_json_obj[target_key.c_str()].IsArray()) { return 80; }
    if (!target_json_obj[target_key.c_str()].Empty() 
        && !target_json_obj[target_key.c_str()].Begin()->IsNumber()) {
      return 81;
    }
  }
  return 0;
}


} // namespace wrapidjson

#endif
