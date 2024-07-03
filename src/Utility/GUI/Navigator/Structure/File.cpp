#include "File.h"

#include <algorithm>
#include <iostream>


namespace utl::gui::navigator{

const ImGuiTableSortSpecs* File::current_sort_specs = nullptr;

bool File::compare_with_specs(const utl::gui::navigator::Item& a, const utl::gui::navigator::Item& b){
  //---------------------------

  // Check if either path is ".." and handle it as a special case
  if(a.name == ".."){
    return true;
  }else if(b.name == ".."){
    return false;
  }

  for(int n = 0; n < current_sort_specs->SpecsCount; n++){
    const ImGuiTableColumnSortSpecs* sort_spec = &current_sort_specs->Specs[n];
    int delta = 0;
    switch (sort_spec->ColumnUserID){
      case utl::gui::navigator::NAME: delta = a.name.compare(b.name); break;
      case utl::gui::navigator::WEIGHT: delta = (a.weight > b.weight) ? 1 : (a.weight < b.weight) ? -1 : 0; break;
      case utl::gui::navigator::FORMAT: delta = a.format.compare(b.format); break;
      default: std::cerr << "Unhandled column ID: " << sort_spec->ColumnUserID << std::endl; break;
    }
    if(delta > 0)
      return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? false : true;
    if(delta < 0)
      return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? true : false;
  }

  //---------------------------
  return false;
}
void File::sort_file_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<utl::gui::navigator::Item>& vec_item){
  //---------------------------

  current_sort_specs = sort_specs;
  if(vec_item.size() > 1){
    std::sort(vec_item.begin(), vec_item.end(), compare_with_specs);
  }
  current_sort_specs = nullptr;

  //---------------------------
}

}
