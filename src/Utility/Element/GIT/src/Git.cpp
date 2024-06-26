#include "Git.h"


namespace utl::element{

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
  if(error != 0){
    std::cerr << "Failed to open the repository: " << giterr_last()->message << std::endl;
    return;
  }

  this->retrieve_all_branch();
  this->retrieve_last_tag();

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
  if(!git_branch_iterator_new(&it, repo, GIT_BRANCH_ALL)){
    git_reference *ref;
    git_branch_t type;
    while(!git_branch_next(&ref, &type, it)){
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
void Git::retrieve_last_tag(){
  //---------------------------

  git_strarray tag_names = {0};
  git_oid latest_tag_oid;

  // Retrieve all tag names in the repository.
  if(git_tag_list(&tag_names, repo) != 0){
    fprintf(stderr, "Failed to list tags.\n");
    git_repository_free(repo);
    git_libgit2_shutdown();
    return;
  }

  this->last_tag = tag_names.strings[tag_names.count-1];

  git_strarray_free(&tag_names);

  //---------------------------
}
void Git::up_tag_version(){
  //---------------------------

  //Update tag version
  float tag = stof(last_tag);
  tag += 0.001;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << tag;
  std::string new_tag = ss.str();

  // Resolve the HEAD reference to a commit
  git_reference *head_ref = NULL;
  int error = git_reference_lookup(&head_ref, repo, "HEAD");
  if(error < 0){
      git_repository_free(repo);
      git_libgit2_shutdown();
      return;
  }

  // Create a new tag
  git_oid tag_oid;
  git_signature *tagger;

  error = git_signature_now(&tagger, "Your Name", "your.email@example.com");
  if(error < 0){
    git_reference_free(head_ref);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return;
  }

  // Use git_reference_peel to get the commit object
  git_object *target_commit = NULL;
  error = git_reference_peel(&target_commit, head_ref, GIT_OBJ_COMMIT);
  if(error < 0){
    git_reference_free(head_ref);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return;
  }

  error = git_tag_create(&tag_oid, repo, new_tag.c_str(), target_commit, tagger, "Tagging version 1.1", 0);
  if(error < 0){
    git_signature_free(tagger);
    git_object_free(target_commit);
    git_reference_free(head_ref);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return;
  }

  // Clean up
  git_signature_free(tagger);
  git_object_free(target_commit);
  git_reference_free(head_ref);

  //---------------------------
  this->retrieve_last_tag();
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

}
