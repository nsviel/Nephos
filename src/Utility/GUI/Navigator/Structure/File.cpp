#include "File.h"

#include <algorithm>
#include <iostream>


namespace utl::gui::navigator{

const ImGuiTableSortSpecs* File::current_sort_specs = nullptr;

bool File::compare_with_specs(const utl::gui::navigator::File& a, const utl::gui::navigator::File& b){
  //---------------------------

  // Check if either path is ".." and handle it as a special case
  if(a.item.name == ".."){
    return true;
  }else if(b.item.name == ".."){
    return false;
  }

  for(int n = 0; n < current_sort_specs->SpecsCount; n++){
    const ImGuiTableColumnSortSpecs* sort_spec = &current_sort_specs->Specs[n];
    int delta = 0;
    switch (sort_spec->ColumnUserID){
      case utl::gui::navigator::NAME: delta = a.item.name.compare(b.item.name); break;
      case utl::gui::navigator::WEIGHT: delta = (a.item.weight > b.item.weight) ? 1 : (a.item.weight < b.item.weight) ? -1 : 0; break;
      case utl::gui::navigator::FORMAT: delta = a.item.format.compare(b.item.format); break;
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
void File::sort_file_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<utl::gui::navigator::File>& vec_file){
  //---------------------------

  current_sort_specs = sort_specs;
  if(vec_file.size() > 1){
    std::sort(vec_file.begin(), vec_file.end(), compare_with_specs);
  }
  current_sort_specs = nullptr;

  //---------------------------
}

}
