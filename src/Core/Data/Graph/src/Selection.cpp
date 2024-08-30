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
    dat_set->active_entity(entity->set_parent.lock(), entity);
  }

  //----------------------------
}
void Selection::select_next_element(){
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  std::shared_ptr<utl::base::Element> element = gph_struct->selection.lock();
  //----------------------------

  if(!element){
    gph_struct->selection = set_graph;
    return;
  }

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
      // Handling selection within a set
      if(!set->list_entity.empty()){
          gph_struct->selection = *set->list_entity.begin(); // Select first entity in the set
          return;
      }
      if(!set->list_subset.empty()){
          gph_struct->selection = *set->list_subset.begin(); // Select first subset in the set
          return;
      }
      // If no entities or subsets in the current set, move up the hierarchy
      if(auto set_parent = set->set_parent.lock()){
          auto it = std::find(set_parent->list_subset.begin(), set_parent->list_subset.end(), set);
          if(it != set_parent->list_subset.end()){
              ++it; // Move to the next subset
              if(it != set_parent->list_subset.end()){
                  gph_struct->selection = *it; // Select the next subset in the parent set
                  return;
              }
          }
          // If no next subset in the parent set, loop back to the root
          gph_struct->selection = set_graph;
          return;
      }
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
      // Handling selection within an entity
      if(auto set_parent = entity->set_parent.lock()){
          auto it = std::find(set_parent->list_entity.begin(), set_parent->list_entity.end(), entity);
          if(it != set_parent->list_entity.end()){
              ++it; // Move to the next entity
              if(it != set_parent->list_entity.end()){
                  gph_struct->selection = *it; // Select the next entity in the parent set
                  return;
              }
          }
          // If no next entity in the parent set, check subsets
          if(!set_parent->list_subset.empty()){
              gph_struct->selection = *set_parent->list_subset.begin(); // Select first subset in the parent set
              return;
          }
          // If no next entity or subset, loop back to the root
          gph_struct->selection = set_graph;
          return;
      }
  }

  //----------------------------
}

//Accesseur
std::shared_ptr<utl::base::Element>Selection::get_selected_element(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection.lock();
  //---------------------------

  if(!element){
    this->select_next_element();

    element = gph_struct->selection.lock();
    if(!element){
      return nullptr;
    }
  }

 //---------------------------
  return element;
}
std::shared_ptr<dat::base::Entity> Selection::get_selected_entity(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection.lock();
  //---------------------------

  if(!element){
    this->select_next_element();
  }

  // Attempt to cast the element to a dat::base::Entity
  auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element);

  // If the cast fails, try to get the active entity from the set
  if(!entity){
    auto set = std::dynamic_pointer_cast<dat::base::Set>(element);
    if(set){
      entity = set->active_entity.lock();
    }
  }

  //---------------------------
  return entity;
}
std::shared_ptr<dat::base::Set> Selection::get_selected_set(){
  std::shared_ptr<utl::base::Element> element = gph_struct->selection.lock();
  //---------------------------

  if(!element){
    this->select_next_element();
  }

  // Try to cast to dat::base::Set
  auto set = std::dynamic_pointer_cast<dat::base::Set>(element);

  // If cast fails, try to cast to dat::base::Entity and get its set_parent
  if(!set){
    auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element);
    if(entity){
      set = entity->set_parent.lock();
    }
  }

  //---------------------------
  return set;
}

}
