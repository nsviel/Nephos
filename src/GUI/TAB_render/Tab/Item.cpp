#include "Item.h"


const ImGuiTableSortSpecs* Item::s_current_sort_specs = nullptr;

bool Item::CompareWithSortSpecs(const Item& a, const Item& b){
  //---------------------------

  for (int n = 0; n < s_current_sort_specs->SpecsCount; n++) {
    const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
    int delta = 0;
    switch (sort_spec->ColumnUserID) {
      case ColumnID_name: delta = a.name.compare(b.name); break;
      case ColumnID_weight: delta = (a.weight > b.weight) ? 1 : (a.weight < b.weight) ? -1 : 0; break;
      case ColumnID_format: delta = a.format.compare(b.format); break;
      default: std::cerr << "Unhandled column ID: " << sort_spec->ColumnUserID << std::endl; break;
    }
    if (delta > 0)
      return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? false : true;
    if (delta < 0)
      return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? true : false;
  }

  //---------------------------
  return false;
}
void Item::SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, std::vector<Item>& vec_item) {
  //---------------------------

  s_current_sort_specs = sort_specs;
  if (vec_item.size() > 1){
    std::sort(vec_item.begin(), vec_item.end(), CompareWithSortSpecs);
  }
  s_current_sort_specs = nullptr;

  //---------------------------
}
