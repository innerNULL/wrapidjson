// 2020-07-25

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

#include "wrapidjson/checker/checker.h"


int32_t checker_demo() {
  std::cout << "=======checker_demo=======" << std::endl;
  std::cout << "--------case0-------" << std::endl;
  const std::string case0_var0 = "{\"project\":\"rapidjson\",\"stars\":10, \"fake_1\":\"哈哈\", \"fake_2\":[1,2,3], \"fake_3\":[\"a\",\"b\"]}";
  rapidjson::Document case0_var1;
  case0_var1.Parse(case0_var0.c_str());
  int32_t case0_var2 = wrapidjson::json_obj_basic_checker(case0_var1);
  int32_t case0_var3 = wrapidjson::json_obj_kv_checker(case0_var1, "project", "string");
  int32_t case0_var4 = wrapidjson::json_obj_kv_checker(case0_var1, "stars", "int");
  int32_t case0_var5 = wrapidjson::json_obj_kv_checker(case0_var1, "fake_1", "string");
  int32_t case0_var6 = wrapidjson::json_obj_kv_checker(case0_var1, "fake_2", "num_array");
  int32_t case0_var7 = wrapidjson::json_obj_kv_checker(case0_var1, "fake_3", "num_array");
  std::cout << "case0_var2=" << case0_var2 << ", case0_var3=" << case0_var3 << ", case0_var4=" << case0_var4 
      << ", case0_var5=" << case0_var5 << ", case0_var6=" << case0_var6 << ", case0_var7=" << case0_var7
      << std::endl;
  return 0;
}


int main(int argc, char *argv[]) {
  checker_demo();
  return 0;
}
