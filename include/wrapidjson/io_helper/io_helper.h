// 2020-07-25

#ifndef WRAPIDJSON_IO_HELPER_IO_HELPER_H_
#define WRAPIDJSON_IO_HELPER_IO_HELPER_H_

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

#include "../3rdparty/rapidjson/include/rapidjson/document.h"
#include "../3rdparty/rapidjson/include/rapidjson/filereadstream.h"
#include "../3rdparty/rapidjson/include/rapidjson/stringbuffer.h"
#include "../3rdparty/rapidjson/include/rapidjson/writer.h"


namespace wrapidjson {


inline int32_t json_file2json_obj(
    rapidjson::Document& result_json_obj, const std::string& json_records_path) {
  FILE* json_fp = fopen(json_records_path.c_str(), "r"); 
  char readBuffer[65536];

  rapidjson::FileReadStream json_in_stream(json_fp, readBuffer, sizeof(readBuffer));
  result_json_obj.ParseStream(json_in_stream);
  //assert(result_json_obj.IsObject());
  return 0;
}


} // namespace wrapidjson

#endif
