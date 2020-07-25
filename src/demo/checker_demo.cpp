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
  const std::string case0_var0 = "{\"project\":\"rapidjson\",\"stars\":10, \"fake_1\":\"哈哈\"}";
  rapidjson::Document case0_var1;
  int32_t case0_var2;
  int32_t case0_var3;
  int32_t case0_var4;
  case0_var1.Parse(case0_var0.c_str());
  case0_var2 = wrapidjson::checker::json_obj_basic_checker(case0_var1);
  case0_var3 = wrapidjson::checker::json_obj_field_checker(case0_var1, "project", "string");
  case0_var4 = wrapidjson::checker::json_obj_field_checker(case0_var1, "stars", "int");
  std::cout << "case0_var2=" << case0_var2 
      << ", case0_var3=" << case0_var3 << ", case0_var4=" << case0_var4 << std::endl;
  return 0;
}


int main(int argc, char *argv[]) {
  checker_demo();
  return 0;
}
