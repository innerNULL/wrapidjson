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

#include "../checker/checker.h"
#include "../3rdparty/rapidjson/include/rapidjson/document.h"
#include "../3rdparty/rapidjson/include/rapidjson/filereadstream.h"
#include "../3rdparty/rapidjson/include/rapidjson/stringbuffer.h"
#include "../3rdparty/rapidjson/include/rapidjson/writer.h"


namespace wrapidjson {


/**
 * @brief
 * Initialing a `rapidjson::Document` object which could be used without any 
 * extra handling.
 *
 * @param if_auto_init If automatically execute some usual-and-necessary handlings.
 */
inline auto json_obj_init(const bool if_auto_init=true) -> rapidjson::Document {
  rapidjson::Document json_obj;
  if (if_auto_init) {
    json_obj.SetObject();
  }
  return json_obj;
}


/**
 * @brief
 * Convert a `rapidjson::Document` object to `std::string`. 
 *
 * @param target_json_obj The target `rapidjson::Document` object, which should be 
 *     called `SetObject()` method.
 */
inline std::string json_obj2string(const rapidjson::Document& target_json_obj) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  target_json_obj.Accept(writer);
  
  return buffer.GetString();
}


/**
 * @brief 
 * Insert a numeric key-value pair to a `rapidjson::Document` object.
 *
 * @t_param NUM_TYPE Target inserting key's coppesponding numerical value type.
 * @param target_json_obj Target `rapidjson::Document` object.
 * @param target_key Target inserting key's name.
 * @param target_val Target inserting key's correponding value.
 * @param if_overwrite If overwrite the key-value pair already existing in `target_json_obj`, 
 *     which key name is same with the `target_key`.
 */
template <typename NUM_TYPE>
inline auto json_insert_num(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const NUM_TYPE target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "num") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  val = (NUM_TYPE)target_val;
  if (if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "num") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


/**
 * @brief
 * Insert a string key-value pair to a `rapidjson::Document` object. 
 * The parameters is almost same meaning with `json_insert_num`. 
 */
inline auto json_insert_str(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::string& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "string") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  val.SetString(target_val.c_str(), target_allocator);
  if (if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "num") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


/**
 * @brief
 * Similiar with `json_insert_num`, but this time, the purpose is inserting a 
 * numerical `std::vector` object. 
 */
template <typename VAL_ITEM_TYPE>
inline auto json_insert_num_array(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::vector<VAL_ITEM_TYPE>& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) { return 2; }

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
  if (if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


/**
 * @brief
 * Similiar with `json_insert_str`, but this time, the purpose is inserting a 
 * `std::vector<std::string>` object. 
 */
inline auto json_insert_str_array(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::vector<std::string>& target_val, const bool if_overwrite=true) -> int32_t {
  // Check
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) { return 2; }

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
  if (if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


/**
 * @brief
 * Similiar with `json_insert_str_array`, insert a vector of json object(Document) into a json object(Document).
 * 
 * @note
 * The reason let `target_val` as `const std::vector<rapidjson::Document*>&` but not 
 * `const std::vector<rapidjson::Document>&` is, 
 *    1. Let each element in `std::vector` be a `rapidjson::Document` full copy is memory ineffective。
 *    2. It's wierd, insert a `rapidjson::Document` element into a `std::vector<rapidjson::Document>` 
 *       always retures error, for example following codes:
 *       ```
 *       std::vector<rapidjson::Document> json_obj_vec;
 *       rapidjson::Document test_json_obj = wrapidjson::json_obj_init(true);
 *       for (int32_t i = 0; i < 3; ++i) { json_obj_vec.emplace_back(test_json_obj); }
 *       ```
 *       but it is ok for 
 *       ```
 *       std::vector<rapidjson::Document*> json_obj_vec;
 *       rapidjson::Document test_json_obj = wrapidjson::json_obj_init(true);
 *       for (int32_t i = 0; i < 3; ++i) { json_obj_vec.emplace_back(&test_json_obj); }
 *       ```
 */
inline int32_t json_insert_doc_array(rapidjson::Document& target_json_obj, 
    const std::string& target_key, const std::vector<rapidjson::Document*>& target_val, const bool if_overwrite=true) {
  // Check
  if (json_obj_basic_checker(target_json_obj) != 0) { return 1; }
  if (!if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) { return 2; }

  // Internal vars
  rapidjson::Value key;
  rapidjson::Value val(rapidjson::kArrayType);
  rapidjson::Value element_val;
  rapidjson::Document::AllocatorType& target_allocator = target_json_obj.GetAllocator();

  // Process
  key.SetString(target_key.c_str(), target_allocator);
  for (const rapidjson::Document* item : target_val) {
    element_val = rapidjson::Value(*item, target_allocator);
    val.PushBack(element_val, target_allocator);
  }
  if (if_overwrite && json_obj_kv_checker(target_json_obj, target_key, "array") != 2) {
    target_json_obj.RemoveMember(key);
  }
  target_json_obj.AddMember(key, val, target_allocator);

  return 0;
}


} // namespace wrapidjson

#endif
