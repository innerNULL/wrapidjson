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
#include "wrapidjson/handler/handler.h"


int32_t handler_demo() {
  std::cout << "=======handler_demo=======" << std::endl;
  std::cout << "-------case0-------" << std::endl;
  rapidjson::Document case0_var0 = wrapidjson::handler::json_obj_init(true);
  std::cout << wrapidjson::handler::json_obj2string(case0_var0) << std::endl;

  std::cout << "-------case1-------" << std::endl;
  auto case1_var0 = wrapidjson::handler::json_obj_init(true);
  wrapidjson::handler::json_insert_num<float>(case1_var0, "fake0", 32.0, true);
  wrapidjson::handler::json_insert_num<int32_t>(case1_var0, "fake1", 5, true);
  wrapidjson::handler::json_insert_num<double>(case1_var0, "fake2", -124876.356, true);
  wrapidjson::handler::json_insert_num<double>(case1_var0, "fake2", -12976.36, true);
  wrapidjson::handler::json_insert_num<double>(case1_var0, "fake2", -2976.36, false);
  wrapidjson::handler::json_insert_str(case1_var0, "fake3", "I'm fake3", false);
  wrapidjson::handler::json_insert_str(case1_var0, "fake4", "I'm fake4", false);
  wrapidjson::handler::json_insert_str(case1_var0, "fake4", "I'm fake4.1", false);
  wrapidjson::handler::json_insert_str(case1_var0, "fake4", "I'm fake4.2", true);
  std::cout << wrapidjson::handler::json_obj2string(case1_var0) << std::endl;
  return 0;
}


int main(int argc, char *argv[]) {
  handler_demo();
  return 0;
}