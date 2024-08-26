#include "Selection.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>


namespace dat::gph{

//Constructor / Destructor
Selection::Selection(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->dat_graph = node_graph->get_gph_graph();
  this->gph_struct = node_graph->get_gph_struct();
  this->dat_set = node_element->get_dat_set();

  //---------------------------
}
Selection::~Selection(){}

//Main function
void Selection::select_element(std::shared_ptr<utl::base::Element> element){
  if(element->is_selectable == false) return;
  //----------------------------

  gph_struct->selection = element;

  //If an entity, make it active
  if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    dat_set->active_entity(entity->set_parent, entity);
  }

  //----------------------------
}
void Selection::select_next_element(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection.lock();
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  //----------------------------

  // Attempt to cast to dat::base::Set
  if (auto set = std::dynamic_pointer_cast<dat::base::Set>(element)) {
    // Handling selection within a set
    if(!set->list_entity.empty()){
      gph_struct->selection = *set->list_entity.begin(); // Select first entity in the set
      return;
    }else if(!set->list_subset.empty()){
      gph_struct->selection = *set->list_subset.begin(); // Select first subset in the set
      return;
    }else{
      // If no entities or subsets in the current set, move up the hierarchy
      std::shared_ptr<dat::base::Set> set_parent = set->set_parent;
      auto it = std::find(set_parent->list_subset.begin(), set_parent->list_subset.end(), set);
      if(it != set_parent->list_subset.end() && ++it != set_parent->list_subset.end()){
        // Select the next subset in the parent set
        gph_struct->selection = *it;
        return;
      }else{
        gph_struct->selection = set_graph; // Loop back to the root if no next element is found
        return;
      }
    }
  }
  // Attempt to cast to dat::base::Entity
  else if (auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)) {
    // Handling selection within an entity
    std::shared_ptr<dat::base::Set> set_parent = entity->set_parent;
    auto it = std::find(set_parent->list_entity.begin(), set_parent->list_entity.end(), entity);
    if(it != set_parent->list_entity.end() && ++it != set_parent->list_entity.end()){
      // Select the next entity in the parent set
      gph_struct->selection = *it;
      return;
    }else{
      // If no next entity in the parent set, move up the hierarchy
      if(set_parent->list_subset.size() > 0){
      gph_struct->selection = *set_parent->list_subset.begin();
      return;
      }

      gph_struct->selection = set_graph; // Loop back to the root if no next element is found
      return;
    }
  }

  //----------------------------
}

//Accesseur
std::shared_ptr<utl::base::Element>Selection::get_selected_element(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection;
  //---------------------------

  if(!element){
    this->select_next_element();
    return nullptr;
  }

 //---------------------------
  return element;
}
std::shared_ptr<dat::base::Entity>& Selection::get_selected_entity(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection;
  //---------------------------

  if(!element){
    this->select_next_element();
    return nullptr;
  }

  // Attempt to cast the element to a dat::base::Entity
  auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element);

  // If the cast fails, try to get the active entity from the set
  if (!entity) {
    auto set = std::dynamic_pointer_cast<dat::base::Set>(element);
    if (set) {
      entity = set->active_entity;
    }
  }

  //---------------------------
  return entity;
}
dat::base::Set* Selection::get_selected_set(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection;
  //---------------------------

  if (!element) {
      this->select_next_element();
      return nullptr;
  }

  // Try to cast to dat::base::Set
  auto set = std::dynamic_pointer_cast<dat::base::Set>(element);

  // If cast fails, try to cast to dat::base::Entity and get its set_parent
  if (!set) {
      auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element);
      if (entity) {
          set = entity->set_parent.lock().get();
      }
  }

  //---------------------------
  return set;
}

}
