#pragma once

#include <Utility/Specific/common.h>


enum ColumnID{
  //---------------------------

  ColumnID_name,
  ColumnID_weight,
  ColumnID_format

  //---------------------------
};

struct Item{
  //---------------------------

  //Item stuff
  string name;
  string type;
  string format;
  string size;
  string icon;
  ImVec4 color_icon;
  ImVec4 color_text;
  float weight;
  int ID;

  //Sorting stuff
  static const ImGuiTableSortSpecs* s_current_sort_specs;
  static bool CompareWithSortSpecs(const Item& a, const Item& b);
  static void SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, std::vector<Item>& vec_item);

  //---------------------------
};
