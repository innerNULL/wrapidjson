// 2020-07-25

#ifndef WRAPIDJSON_QUERIER_QUERIER_H_
#define WRAPIDJSON_QUERIER_QUERIER_H_

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
 * Query a numeric vector from a json object and put the results into an predefined 
 * numeric `std::vector` object.
 *
 * @t_param NUM_TYPE The target numerical type.
 * @param destination The target numeric `std::vector` object to hold json querying output.
 * @param target_json_obj Target querying json object.
 * @param target_field Target querying field name from json.
 */
template<typename NUM_TYPE>
int32_t json_num_array2std_vec(std::vector<NUM_TYPE>& destination, 
    const rapidjson::Document& target_json_obj, const std::string target_field) {
  destination.clear();
  if (wrapidjson::json_obj_kv_checker(target_json_obj, target_field, "num_array") != 0) { return 1; }
  
  for (auto& v : target_json_obj[target_field.c_str()].GetArray()) {
    destination.emplace_back(v.GetDouble());
  }
  return 0;
}


} // namespace wrapidjson

#endif
