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
#include "wrapidjson/querier/querier.h"
#include "wrapidjson/type_register/type_register.h"


int32_t handler_n_querier_demo() {
  std::cout << "=======handler_demo=======" << std::endl;
  std::cout << "-------case0-------" << std::endl;
  wrapidjson::Document case0_var0 = wrapidjson::json_obj_init(true);
  std::cout << wrapidjson::json_obj2string(case0_var0) << std::endl;

  std::cout << "-------case1-------" << std::endl;
  auto case1_var0 = wrapidjson::json_obj_init(true);
  wrapidjson::json_insert_num<float>(case1_var0, "fake0", 32.0, true);
  wrapidjson::json_insert_num<int32_t>(case1_var0, "fake1", 5, true);
  wrapidjson::json_insert_num<double>(case1_var0, "fake2", -124876.356, true);
  wrapidjson::json_insert_num<double>(case1_var0, "fake2", -12976.36, true);
  wrapidjson::json_insert_num<double>(case1_var0, "fake2", -2976.36, false);
  std::cout << wrapidjson::json_obj2string(case1_var0) << std::endl;
  wrapidjson::json_insert_str(case1_var0, "fake3", "I'm fake3", false);
  wrapidjson::json_insert_str(case1_var0, "fake4", "I'm fake4", false);
  wrapidjson::json_insert_str(case1_var0, "fake4", "I'm fake4.1", false);
  wrapidjson::json_insert_str(case1_var0, "fake4", "I'm fake4.2", true);
  std::cout << wrapidjson::json_obj2string(case1_var0) << std::endl;
  wrapidjson::json_insert_str_array(case1_var0, "fake5", {"a", "b", "c"}, true);
  wrapidjson::json_insert_str_array(case1_var0, "fake5", {"a1", "b1", "c1"}, false);
  wrapidjson::json_insert_str_array(case1_var0, "fake5", {"a2", "b2", "c2"}, true);
  std::cout << wrapidjson::json_obj2string(case1_var0) << std::endl;
  wrapidjson::json_insert_num_array<int32_t>(case1_var0, "fake6", {-1, 0, 1}, false);
  wrapidjson::json_insert_num_array<float>(case1_var0, "fake6", {-1.5, 0.5, 1.5}, false);
  wrapidjson::json_insert_num_array<float>(case1_var0, "fake6", {-1.25, 0.25, 1.25}, true);
  wrapidjson::json_insert_num_array<int32_t>(case1_var0, "fake3", {10, 50, 100}, true);
  std::cout << wrapidjson::json_obj2string(case1_var0) << std::endl;

  std::cout << "-------case2-------" << std::endl;
  std::vector<float> case2_var0;
  std::vector<int32_t> case2_var1;
  wrapidjson::json_num_array2std_vec<float>(case2_var0, case1_var0, "fake6");
  wrapidjson::json_num_array2std_vec<int32_t>(case2_var1, case1_var0, "fake6");
  for (int32_t i = 0; i < case2_var1.size(); ++i) {
    std::cout << case2_var0[i] << ", " << case2_var1[i] << std::endl;
  }

  std::cout << "-------case3-------" << std::endl;
  wrapidjson::Document case3_target_json_obj = wrapidjson::json_obj_init(true);
  wrapidjson::Document case3_test_json_obj = wrapidjson::json_obj_init(true);
  std::string case3_test_json_str = "{\"a\":[0.2, 0.3, 0.4]}";
  std::vector<wrapidjson::Document*> case3_input_doc_vec;

  case3_test_json_obj.Parse(case3_test_json_str.c_str());
  for (int32_t i = 0; i < 3; ++i) {
    std::cout << wrapidjson::json_obj2string(case3_test_json_obj) << std::endl;;
    case3_input_doc_vec.emplace_back(&case3_test_json_obj);
  }
  wrapidjson::json_insert_doc_array(case3_target_json_obj, "json_obj_array", case3_input_doc_vec, true);
  std::cout << wrapidjson::json_obj2string(case3_target_json_obj) << std::endl;

  std::cout << "-------case4-------" << std::endl;
  std::string case4_test_json_str = "{\"a\":[0.2, 0.3, 0.4]}";
  wrapidjson::Document case4_source_json_obj = wrapidjson::json_obj_init(true);
  wrapidjson::Document case4_target_json_obj;

  case4_source_json_obj.Parse(case4_test_json_str.c_str());

  std::cout << wrapidjson::json_obj2string(case4_target_json_obj) << std::endl;
  wrapidjson::doc_assign(&case4_target_json_obj, &case4_source_json_obj);
  std::cout << wrapidjson::json_obj2string(case4_target_json_obj) << std::endl;

  std::vector<wrapidjson::Document> case4_doc_vec;
  case4_doc_vec.resize(3);
  for (auto& x : case4_doc_vec) {
    wrapidjson::doc_assign(&x, &case4_source_json_obj);
    std::cout << "address: " << &x << ", value: " << wrapidjson::json_obj2string(x) << std::endl;
  }

  std::vector<wrapidjson::Document*> case4_doc_pointer_vec;
  case4_doc_pointer_vec.resize(5);
  for (auto pt : case4_doc_pointer_vec) {
    //wrapidjson::doc_assign(pt, &case4_source_json_obj);
    //std::cout << "pointer: " << case4_doc_pointer_vec[i] 
    //    << ", value: " << wrapidjson::json_obj2string(*(case4_doc_pointer_vec[i])) << std::endl;
  }

  return 0;
}


int main(int argc, char *argv[]) {
  handler_n_querier_demo();
  return 0;
}
