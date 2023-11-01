#include "Git.h"


//Constructor / Destructor
Git::Git(){
  //---------------------------

  this->open_repository();

  //---------------------------
}
Git::~Git(){
  //---------------------------

  this->close_repository();

  //---------------------------
}

//Main function
void Git::open_repository(){
  //---------------------------

  git_libgit2_init();

  this->repo = nullptr;
  int error = git_repository_open(&repo, "..");
  if (error != 0) {
    std::cerr << "Failed to open the repository: " << giterr_last()->message << std::endl;
    return;
  }

  this->retrieve_all_branch();

  //---------------------------
}
void Git::close_repository(){
  //---------------------------

  git_repository_free(repo);
  git_libgit2_shutdown();

  //---------------------------
}

//Git function
void Git::retrieve_all_branch(){
  //---------------------------

  git_branch_iterator *it;
  if (!git_branch_iterator_new(&it, repo, GIT_BRANCH_ALL)) {
    git_reference *ref;
    git_branch_t type;
    while (!git_branch_next(&ref, &type, it)) {
      // Do something with 'ref' and 'type'.
      const char* branch_name = git_reference_name(ref);
      // Do something with 'branch_name'
      vec_branch.push_back(branch_name);
      git_reference_free(ref);
    }
    git_branch_iterator_free(it);
  }

  //---------------------------
  this->format_branch();
}

//Subfunction
void Git::format_branch(){
  //---------------------------

  for(int i=0; i<vec_branch.size(); i++){
    string& branch = vec_branch[i];

    //Local branch
    string local = "refs/heads";
    string remote = "refs/remotes";
    if(branch.find(local) != std::string::npos){
      string name = branch.substr(local.length()+1, branch.length()-1);
      pair<string, string> format;
      format.first = "local";
      format.second = name;
      vec_branch_format.push_back(format);
    }
    //Remote branch
    else if(branch.find(remote) != std::string::npos){
      string name = branch.substr(remote.length()+1, branch.length()-1);
      pair<string, string> format;
      format.first = "remote";
      format.second = name;
      vec_branch_format.push_back(format);
    }
  }

  //---------------------------
}
