// 2020-07-25

#ifndef WRAPIDJSON_HANDLER_HANDLER_H_
#define WRAPIDJSON_HANDLER_HANDLER_H_

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

#include "wrapidjson/checker/checker.h"
#include "wrapidjson/3rdparty/rapidjson/include/rapidjson/document.h"
#include "wrapidjson/3rdparty/rapidjson/include/rapidjson/filereadstream.h"
#include "wrapidjson/3rdparty/rapidjson/include/rapidjson/stringbuffer.h"
#include "wrapidjson/3rdparty/rapidjson/include/rapidjson/writer.h"


namespace wrapidjson {
namespace handler {


inline auto json_obj_init(const bool if_auto_init=true) -> rapidjson::Document {
  rapidjson::Document json_obj;
  if (if_auto_init) {
    json_obj.SetObject();
  }
  return json_obj;
}


inline std::string json_obj2string(const rapidjson::Document& target_json_obj) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  target_json_obj.Accept(writer);
  
  return buffer.GetString();
}


template <typename NUM_TYPE>
inline auto json_insert_num(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const NUM_TYPE target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (checker::json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "num") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  val = (NUM_TYPE)target_val;
  if (if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "num") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


inline auto json_insert_str(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::string& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (checker::json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "string") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  val.SetString(target_val.c_str(), target_allocator);
  if (if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "num") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


template <typename VAL_ITEM_TYPE>
inline auto json_insert_num_array(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::vector<VAL_ITEM_TYPE>& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (checker::json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "array") != 2) { return 2; }

  // Interval vars
  rapidjson::Value key;
  rapidjson::Value val(rapidjson::kArrayType);
  rapidjson::Value element_val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  for (const VAL_ITEM_TYPE& item : target_val) {
    element_val = item;
    val.PushBack(element_val, target_allocator);
  }
  if (if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "array") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


inline auto json_insert_str_array(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::vector<std::string>& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (checker::json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "array") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val(rapidjson::kArrayType);
  rapidjson::Value element_val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  for (const std::string& item : target_val) {
    element_val.SetString(item.c_str(), target_allocator);
    val.PushBack(element_val, target_allocator);
  }
  if (if_overwrite && checker::json_obj_kv_checker(target_json_obj, target_key, "array") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


} // namespace handler
} // namespace wrapidjson

#endif
