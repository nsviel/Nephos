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
void Git::retrieve_last_tag(){
  //---------------------------

  git_repository *repo = NULL;
  git_strarray tag_names = {0};
  git_revwalk *walker = NULL;
  git_oid oid;
  const git_oid *commit_oid = NULL;

  // Open the local repository.
  if (git_repository_open(&repo, "path_to_your_local_repo") != 0) {
      fprintf(stderr, "Failed to open the repository.\n");
      git_libgit2_shutdown();
      return 1;
  }

  // Retrieve all tag names in the repository.
  if (git_tag_list(&tag_names, repo) != 0) {
      fprintf(stderr, "Failed to list tags.\n");
      git_repository_free(repo);
      git_libgit2_shutdown();
      return 1;
  }

  // Initialize a revwalk to iterate over commits.
  if (git_revwalk_new(&walker, repo) != 0) {
      fprintf(stderr, "Failed to initialize revwalk.\n");
      git_strarray_free(&tag_names);
      git_repository_free(repo);
      git_libgit2_shutdown();
      return 1;
  }

  // Iterate over tags to find the latest one.
  git_oid_fromstr(&oid, "0000000000000000000000000000000000000000"); // Initialize to a null OID
  for (size_t i = 0; i < tag_names.count; i++) {
      const char *tag_name = tag_names.strings[i];
      git_reference *ref = NULL;
      git_tag *tag = NULL;

      if (git_reference_dwim(&ref, repo, tag_name) == 0) {
          git_reference_peel(&commit_oid, ref, GIT_OBJ_COMMIT);
          if (git_oid_cmp(&oid, commit_oid) < 0) {
              git_oid_cpy(&oid, commit_oid);
          }
          git_reference_free(ref);
      }
  }

  // Print the latest tag.
  char latest_tag[GIT_OID_HEXSZ + 1];
  git_oid_fmt(latest_tag, &oid);
  latest_tag[GIT_OID_HEXSZ] = '\0';
  printf("Latest tag: %s\n", latest_tag);

  git_revwalk_free(walker);
  git_strarray_free(&tag_names);

  //---------------------------
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
