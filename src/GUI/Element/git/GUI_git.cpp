#include "GUI_git.h"

#include <GUI.h>
#include <git2.h>


//Constructor / Destructor
GUI_git::GUI_git(GUI* gui){
  //---------------------------


  //---------------------------
}
GUI_git::~GUI_git(){}

//Main function
void GUI_git::retrieve_all_branch(){
  //---------------------------

  git_libgit2_init();

  // Open the repository
  git_repository* repo = nullptr;
  int error = git_repository_open(&repo, "..");
  if (error != 0) {
    std::cerr << "Failed to open the repository: " << giterr_last()->message << std::endl;
    return;
  }

  git_branch_iterator *it;
  if (!git_branch_iterator_new(&it, repo, GIT_BRANCH_ALL)) {
    git_reference *ref;
    git_branch_t type;
    while (!git_branch_next(&ref, &type, it)) {
      // Do something with 'ref' and 'type'.
      const char* branch_name = git_reference_name(ref);
       // Do something with 'branch_name'
       say(branch_name);
      git_reference_free(ref);
    }
    git_branch_iterator_free(it);
  }


  git_repository_free(repo);

  git_libgit2_shutdown();

  //---------------------------
}

//Subfunction
