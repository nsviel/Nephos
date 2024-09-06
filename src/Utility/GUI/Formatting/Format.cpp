#include "Format.h"

#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <sstream>


namespace utl::gui{

std::string format_title(const std::string& name, int totalWidth){
  //---------------------------

  // Get the length of the name
   int nameLength = static_cast<int>(name.length());

   // Calculate available width for dashes
   int availableWidth = totalWidth - nameLength - 2; // Subtract spaces around the name

   // Ensure the available width is non-negative
   if (availableWidth < 0){
       return name;  // If not enough width, return the name itself
   }

   // Calculate the number of dashes on each side
   int dashLength = availableWidth / 2;

   // Construct the title string
   std::ostringstream ss;
   ss << std::string(dashLength, '-') << " " << name << " " << std::string(dashLength, '-');

   // Ensure the final length matches the totalWidth
   std::string result = ss.str();
   int resultLength = static_cast<int>(result.length());

   if (resultLength < totalWidth){
       result += std::string(totalWidth - resultLength, '-');
   }


  //---------------------------
  return ss.str();
}

}
