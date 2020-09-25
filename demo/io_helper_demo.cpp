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

#include "wrapidjson/io_helper/io_helper.h"
#include "wrapidjson/handler/handler.h"
#include "wrapidjson/type_register/type_register.h"


int32_t io_helper_demo() {
  std::cout << "=======io_helper_demo=======" << std::endl;
  std::cout << "--------case0-------" << std::endl;
  std::string case0_demo_json_file = "../test_data/json_file_demo.json";
  wrapidjson::Document case0_json_obj = wrapidjson::json_obj_init(true);
  wrapidjson::json_file2json_obj(case0_json_obj, case0_demo_json_file);
  std::cout << wrapidjson::json_obj2string(case0_json_obj) << std::endl;
  return 0;
}


int main(int argc, char *argv[]) {
  io_helper_demo();
  return 0;
}
