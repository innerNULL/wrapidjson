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


inline std::string json_obj2string(const rapidjson::Document& target_json_obj) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  target_json_obj.Accept(writer);
  
  return buffer.GetString();
}


template <typename NUM_TYPE>
inline auto json_insert_str_key_num_val(rapidjson::Document& target_json_obj, 
    const std::string& target_field_name, const NUM_TYPE target_field_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (checker::json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && checker::json_obj_field_checker(target_json_obj, target_field_name, "num") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_field_name.c_str(), target_allocator);
  val = (NUM_TYPE)target_field_val;
  if (if_overwrite && checker::json_obj_field_checker(target_json_obj, target_field_name, "num") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


} // namespace handler
} // namespace wrapidjson

#endif
