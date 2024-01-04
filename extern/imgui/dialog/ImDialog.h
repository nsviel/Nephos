#pragma once


// file style enum for file display (color, icon, font)
typedef int IGFD_FileStyleFlags;  // -> enum IGFD_FileStyleFlags_
enum IGFD_FileStyleFlags_         // by evaluation / priority order
{
    IGFD_FileStyle_None = 0,               // define none style
    IGFD_FileStyleByTypeFile = (1 << 0),   // define style for all files
    IGFD_FileStyleByTypeDir = (1 << 1),    // define style for all dir
    IGFD_FileStyleByTypeLink = (1 << 2),   // define style for all link
    IGFD_FileStyleByExtention = (1 << 3),  // define style by extention, for files or links
    IGFD_FileStyleByFullName = (1 << 4),   // define style for particular file/dir/link full name (filename + extention)
    IGFD_FileStyleByContainedInFullName =
        (1 << 5),  // define style for file/dir/link when criteria is contained in full name
};
typedef int ImGuiFileDialogFlags;  // -> enum ImGuiFileDialogFlags_
enum ImGuiFileDialogFlags_ {
    ImGuiFileDialogFlags_None = 0,                                 // define none default flag
    ImGuiFileDialogFlags_ConfirmOverwrite = (1 << 0),              // show confirm to overwrite dialog
    ImGuiFileDialogFlags_DontShowHiddenFiles = (1 << 1),           // dont show hidden file (file starting with a .)
    ImGuiFileDialogFlags_DisableCreateDirectoryButton = (1 << 2),  // disable the create directory button
    ImGuiFileDialogFlags_HideColumnType = (1 << 3),                // hide column file type
    ImGuiFileDialogFlags_HideColumnSize = (1 << 4),                // hide column file size
    ImGuiFileDialogFlags_HideColumnDate = (1 << 5),                // hide column file date
    ImGuiFileDialogFlags_NoDialog = (1 << 6),  // let the dialog embedded in your own imgui begin / end scope
    ImGuiFileDialogFlags_ReadOnlyFileNameField =
        (1 << 7),  // don't let user type in filename field for file open style dialogs
    ImGuiFileDialogFlags_CaseInsensitiveExtention =
        (1 << 8),                           // the file extentions treatments will not take into account the case
    ImGuiFileDialogFlags_Modal = (1 << 9),  // modal
    ImGuiFileDialogFlags_DisableThumbnailMode = (1 << 10),       // disable the thumbnail mode
    ImGuiFileDialogFlags_DisableBookmarkMode = (1 << 11),        // disable the bookmark mode
    ImGuiFileDialogFlags_DisableQuickPathSelection = (1 << 12),  // disable the quick path selection

    // default behavior when no flags is defined. seems to be the more common cases
    ImGuiFileDialogFlags_Default = ImGuiFileDialogFlags_ConfirmOverwrite |  //
                                   ImGuiFileDialogFlags_Modal |             //
                                   ImGuiFileDialogFlags_HideColumnType
};
// flags used for GetFilePathName(flag) or GetSelection(flag)
typedef int IGFD_ResultMode;  // -> enum IGFD_ResultMode_
enum IGFD_ResultMode_ {
    // IGFD_ResultMode_AddIfNoFileExt
    // add the file ext only if there is no file ext
    //   filter {.cpp,.h} with file :
    //     toto.h => toto.h
    //     toto.a.h => toto.a.h
    //     toto.a. => toto.a.cpp
    //     toto. => toto.cpp
    //     toto => toto.cpp
    //   filter {.z,.a.b} with file :
    //     toto.a.h => toto.a.h
    //     toto. => toto.z
    //     toto => toto.z
    //   filter {.g.z,.a} with file :
    //     toto.a.h => toto.a.h
    //     toto. => toto.g.z
    //     toto => toto.g.z
    IGFD_ResultMode_AddIfNoFileExt = 0,

    // IGFD_ResultMode_OverwriteFileExt
    // Overwrite the file extention by the current filter :
    //   filter {.cpp,.h} with file :
    //     toto.h => toto.cpp
    //     toto.a.h => toto.a.cpp
    //     toto.a. => toto.a.cpp
    //     toto.a.h.t => toto.a.h.cpp
    //     toto. => toto.cpp
    //     toto => toto.cpp
    //   filter {.z,.a.b} with file :
    //     toto.a.h => toto.z
    //     toto.a.h.t => toto.a.z
    //     toto. => toto.z
    //     toto => toto.z
    //   filter {.g.z,.a} with file :
    //     toto.a.h => toto.g.z
    //     toto.a.h.y => toto.a.g.z
    //     toto.a. => toto.g.z
    //     toto. => toto.g.z
    //     toto => toto.g.z
    IGFD_ResultMode_OverwriteFileExt = 1,  // behavior pre IGFD v0.6.6

    // IGFD_ResultMode_KeepInputFile
    // keep the input file => no modification :
    //   filter {.cpp,.h} with file :
    //      toto.h => toto.h
    //      toto. => toto.
    //      toto => toto
    //   filter {.z,.a.b} with file :
    //      toto.a.h => toto.a.h
    //      toto. => toto.
    //      toto => toto
    //   filter {.g.z,.a} with file :
    //      toto.a.h => toto.a.h
    //      toto. => toto.
    //      toto => toto
    IGFD_ResultMode_KeepInputFile = 2
};


#ifdef __cplusplus
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../core/imgui.h"
#include <set>
#include <map>
#include <list>
#include <regex>
#include <array>
#include <mutex>
#include <thread>
#include <cfloat>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <functional>
#include <unordered_map>


// Define attributes of all API symbols declarations (e.g. for DLL under Windows)
// Using ImDialog via a shared library is not recommended, because we don't guarantee
// backward nor forward ABI compatibility and also function call overhead. If you
// do use ImDialog as a DLL, be sure to call SetImGuiContext (see Miscellanous section).

#define IGFD_API
#define MAX_FILE_DIALOG_NAME_BUFFER 1024
#define MAX_PATH_BUFFER_SIZE 1024
#define EXT_MAX_LEVEL 10U
#define defaultSortField FIELD_FILENAME
#define defaultSortOrderFilename true
#define defaultSortOrderType true
#define defaultSortOrderSize true
#define defaultSortOrderDate true
#define defaultSortOrderThumbnails true


namespace IGFD {
  
typedef void* UserDatas;
typedef std::function<void(const char*, UserDatas, bool*)> PaneFun;  // side pane function binding

template <typename T>
class SearchableVector {
private:
    std::unordered_map<T, size_t> m_Dico;
    std::vector<T> m_Array;

public:
    void clear() {
        m_Dico.clear();
        m_Array.clear();
    }

    bool empty() const { return m_Array.empty(); }
    size_t size() const { return m_Array.size(); }
    T& operator[](const size_t& vIdx) { return m_Array[vIdx]; }
    T& at(const size_t& vIdx) { return m_Array.at(vIdx); }
    typename std::vector<T>::iterator begin() { return m_Array.begin(); }
    typename std::vector<T>::const_iterator begin() const { return m_Array.begin(); }
    typename std::vector<T>::iterator end() { return m_Array.end(); }
    typename std::vector<T>::const_iterator end() const { return m_Array.end(); }

    bool try_add(T vKey) {
        if (!exist(vKey)) {
            m_Dico[vKey] = m_Array.size();
            m_Array.push_back(vKey);
            return true;
        }
        return false;
    }

    bool try_set_existing(T vKey) {
        if (exist(vKey)) {
            auto row = m_Dico.at(vKey);
            m_Array[row] = vKey;
            return true;
        }
        return false;
    }

    bool exist(const std::string& vKey) const { return (m_Dico.find(vKey) != m_Dico.end()); }
};

class IGFD_API Utils {
public:
    struct IGFD_API PathStruct {
        std::string path;
        std::string name;
        std::string ext;
        bool isOk = false;
    };

public:
    static bool ImSplitter(bool split_vertically,
        float thickness,
        float* size1,
        float* size2,
        float min_size1,
        float min_size2,
        float splitter_long_axis_size = -1.0f);
    static bool ReplaceString(
        std::string& str, const std::string& oldStr, const std::string& newStr, const size_t& vMaxRecursion = 10U);
    static bool IsDirectoryCanBeOpened(const std::string& name);  // by ex protected dirs (not user rights)
    static bool IsDirectoryExist(const std::string& name);
    static bool CreateDirectoryIfNotExist(const std::string& name);
    static PathStruct ParsePathFileName(const std::string& vPathFileName);
    static void AppendToBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr);
    static void ResetBuffer(char* vBuffer);
    static void SetBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr);
    static std::string UTF8Encode(const std::wstring& wstr);
    static std::wstring UTF8Decode(const std::string& str);
    static std::vector<std::string> SplitStringToVector(
        const std::string& vText, const char& vDelimiter, const bool& vPushEmpty);
    static std::vector<std::string> GetDrivesList();
    static std::string LowerCaseString(const std::string& vString);  // turn all text in lower case for search facilitie
    static size_t GetCharCountInString(const std::string& vString, const char& vChar);
    static size_t GetLastCharPosWithMinCharCount(
        const std::string& vString, const char& vChar, const size_t& vMinCharCount);
};
class IGFD_API FileInfos;
class IGFD_API FileStyle {
public:
    typedef std::function<bool(const FileInfos&, FileStyle&)> FileStyleFunctor;

public:
    ImVec4 color = ImVec4(0, 0, 0, 0);
    std::string icon;
    ImFont* font = nullptr;
    IGFD_FileStyleFlags flags = 0;

public:
    FileStyle();
    FileStyle(const FileStyle& vStyle);
    FileStyle(const ImVec4& vColor, const std::string& vIcon = "", ImFont* vFont = nullptr);
};
class IGFD_API FileDialogInternal;
class IGFD_API SearchManager {
public:
    std::string puSearchTag;
    char puSearchBuffer[MAX_FILE_DIALOG_NAME_BUFFER] = "";
    bool puSearchInputIsActive = false;

public:
    void Clear();                                                 // clear datas
    void DrawSearchBar(FileDialogInternal& vFileDialogInternal);  // draw the search bar
};
class IGFD_API FilterInfos {
private:
    // just for return a default const std::string& in getFirstFilter.
    // cannot be const, because FilterInfos must be affected to an another FilterInfos
    // must stay empty alla time
    std::string empty_string;

public:
    std::string title;                                // displayed filter.can be different than rela filter
    SearchableVector<std::string> filters;            // filters
    SearchableVector<std::string> filters_optimized;  // optimized filters for case insensitive search
    std::vector<std::regex> filters_regex;            // collection of regex filter type
    size_t count_dots = 0U;                           // the max count dot the max per filter of all filters

public:
    void clear();                                                                // clear the datas
    bool empty() const;                                                          // is filter empty
    const std::string& getFirstFilter() const;                                   // get the first filter
    bool regexExist(const std::string& vFilter) const;                           // is regex filter exist
    bool exist(const FileInfos& vFileInfos, bool vIsCaseInsensitive) const;      // is filter exist
    void setCollectionTitle(const std::string& vTitle);                          // set the collection title
    void addFilter(const std::string& vFilter, const bool& vIsRegex);            // add a filter
    void addCollectionFilter(const std::string& vFilter, const bool& vIsRegex);  // add a filter in collection
    std::string transformAsteriskBasedFilterToRegex(
        const std::string& vFilter);  // will transform a filter who contain * to a regex
};
class IGFD_API FileInfos;
class IGFD_API FilterManager{
private:
  std::vector<FilterInfos> prParsedFilters;
  std::unordered_map<IGFD_FileStyleFlags, std::unordered_map<std::string, std::shared_ptr<FileStyle>>>
      prFilesStyle;                                               // file infos for file extention only
  std::vector<FileStyle::FileStyleFunctor> prFilesStyleFunctors;  // file style via lambda function
  FilterInfos prSelectedFilter;

public:
  std::string puDLGFilters;
  std::string puDLGdefaultExt;

public:
  const FilterInfos& GetSelectedFilter() const;
  void ParseFilters(const char* vFilters);  // Parse filter syntax, detect and parse filter collection
  void SetSelectedFilterWithExt(const std::string& vFilter);          // Select filter
  bool prFillFileStyle(std::shared_ptr<FileInfos> vFileInfos) const;  // fill with the good style
  void SetFileStyle(const IGFD_FileStyleFlags& vFlags, const char* vCriteria, const FileStyle& vInfos);  // Set FileStyle
  void SetFileStyle(const IGFD_FileStyleFlags& vFlags,const char* vCriteria,const ImVec4& vColor,const std::string& vIcon, ImFont* vFont);                                       // link file style to Color and Icon and Font
  void SetFileStyle(FileStyle::FileStyleFunctor vFunctor);  // lambda functor for set file style.
  bool GetFileStyle(const IGFD_FileStyleFlags& vFlags,const std::string& vCriteria,ImVec4* vOutColor,std::string* vOutIcon,ImFont** vOutFont);  // Get Color and Icon for Filter
  void ClearFilesStyle();  // clear prFileStyle
  bool IsCoveredByFilters(const FileInfos& vFileInfos, bool vIsCaseInsensitive)const;  // check if current file extention (vExt) is covered by current filter, or by regex (vNameExt)
  float GetFilterComboBoxWidth() const;  // will return the current combo box widget width
  bool DrawFilterComboBox(FileDialogInternal& vFileDialogInternal);  // draw the filter combobox 	// get the current selected filter
  std::string ReplaceExtentionWithCurrentFilterIfNeeded(const std::string& vFileName,IGFD_ResultMode vFlag) const;     // replace the extention of the current file by the selected filter
  void SetDefaultFilterIfNotDefined();  // define the first filter if no filter is selected
};
class IGFD_API FileType {
public:
  enum class ContentType {
    // The ordering will be used during sort.
    Invalid = -1,
    Directory = 0,
    File = 1,
    LinkToUnknown = 2,  // link to something that is not a regular file or directory.
  };

private:
  ContentType m_Content = ContentType::Invalid;
  bool m_Symlink = false;

public:
  FileType();
  FileType(const ContentType& vContentType, const bool& vIsSymlink);

  void SetContent(const ContentType& vContentType);
  void SetSymLink(const bool& vIsSymlink);

  bool isValid() const;
  bool isDir() const;
  bool isFile() const;
  bool isLinkToUnknown() const;
  bool isSymLink() const;

  // Comparisons only care about the content type, ignoring whether it's a symlink or not.
  bool operator==(const FileType& rhs) const;
  bool operator!=(const FileType& rhs) const;
  bool operator<(const FileType& rhs) const;
  bool operator>(const FileType& rhs) const;
};
class IGFD_API FileInfos {
public:
  // extention of the file, the array is the levels of ext, by ex : .a.b.c, will be save in {.a.b.c, .b.c, .c}
  // 10 level max are sufficient i guess. the others levels will be checked if countExtDot > 1
  std::array<std::string, EXT_MAX_LEVEL> fileExtLevels;
  std::array<std::string, EXT_MAX_LEVEL> fileExtLevels_optimized;  // optimized for search => insensitivecase
  size_t countExtDot = 0U;  // count dots in file extention. this count will give the levels in fileExtLevels
  FileType fileType;        // fileType
  std::string filePath;     // path of the file
  std::string fileNameExt;  // filename of the file (file name + extention) (but no pat
  std::string fileNameExt_optimized;               // optimized for search => insensitivecase
  size_t fileSize = 0U;                            // for sorting operations
  std::string formatedFileSize;                    // file size formated (10 o, 10 ko, 10 mo, 10 go)
  std::string fileModifDate;                       // file user defined format of the date (data + time by default)
  std::shared_ptr<FileStyle> fileStyle = nullptr;  // style of the file                               // USE_THUMBNAILS

public:
  bool SearchForTag(const std::string& vTag) const;  // will search a tag in fileNameExt and fileNameExt_optimized
  bool SearchForExt(const std::string& vExt, const bool& vIsCaseInsensitive, const size_t& vMaxLevel = EXT_MAX_LEVEL)const;  // will check the fileExtLevels levels for vExt, until vMaxLevel
  bool SearchForExts(const std::string& vComaSepExts, const bool& vIsCaseInsensitive, const size_t& vMaxLevel = EXT_MAX_LEVEL)const;  // will check the fileExtLevels levels for vExts (ext are coma separated), until vMaxLevel
  bool FinalizeFileTypeParsing(const size_t& vMaxDotToExtract);  // finalize the parsing the file (only a file or link to file. no dir)
};
class IGFD_API FileManager {
public:                            // types
  enum class SortingFieldEnum {  // sorting for filetering of the file lsit
    FIELD_NONE = 0,            // no sorting preference, result indetermined haha..
    FIELD_FILENAME,            // sorted by filename
    FIELD_TYPE,                // sorted by filetype
    FIELD_SIZE,                // sorted by filesize (formated file size)
    FIELD_DATE,                // sorted by filedate
    FIELD_THUMBNAILS,          // sorted by thumbnails (comparaison by width then by height)
  };

private:
  std::string prCurrentPath;  // current path (to be decomposed in prCurrentPathDecomposition
  std::vector<std::string> prCurrentPathDecomposition;         // part words
  std::vector<std::shared_ptr<FileInfos>> prFileList;          // base container
  std::vector<std::shared_ptr<FileInfos>> prFilteredFileList;  // filtered container (search, sorting, etc..)
  std::vector<std::shared_ptr<FileInfos>> prPathList;          // base container for path selection
  std::vector<std::shared_ptr<FileInfos>> prFilteredPathList;  // filtered container for path selection (search,
  std::vector<std::string>::iterator prPopupComposedPath;  // iterator on prCurrentPathDecomposition for Current Path
  std::string prLastSelectedFileName;                      // for shift multi selection
  std::set<std::string> prSelectedFileNames;               // the user selection of FilePathNames
  bool prCreateDirectoryMode = false;                      // for create directory widget

public:
  bool puInputPathActivated = false;  // show input for path edition
  bool puDrivesClicked = false;       // event when a drive button is clicked
  bool puPathClicked = false;         // event when a path button was clicked
  char puInputPathBuffer[MAX_PATH_BUFFER_SIZE] = "";
  char puVariadicBuffer[MAX_FILE_DIALOG_NAME_BUFFER] = "";  // called by prSelectableItem
  char puFileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER] = "";  // file name buffer in footer for imgui widget input text
  char puDirectoryNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER] ="";  // directory name buffer in footer for imgui widget input text (when is directory mode)
  std::string puHeaderFileName;  // detail view name of column file
  std::string puHeaderFileType;  // detail view name of column type
  std::string puHeaderFileSize;  // detail view name of column size
  std::string puHeaderFileDate;  // detail view name of column date + time
  bool puSortingDirection[4] = {  // true => Ascending, false => Descending
      defaultSortOrderFilename, defaultSortOrderType, defaultSortOrderSize, defaultSortOrderDate};
  SortingFieldEnum puSortingField = SortingFieldEnum::FIELD_FILENAME;  // detail view sorting column
  bool puShowDrives = false;                                           // drives are shown (only on os windows)
  std::string puDLGpath;             // base path set by user when OpenDialog was called
  std::string puDLGDefaultFileName;  // base default file path name set by user when OpenDialog was called
  size_t puDLGcountSelectionMax =1U;  // 0 for infinite				// base max selection count set by user when OpenDialog was called
  bool puDLGDirectoryMode = false;  // is directory mode (defiend like : puDLGDirectoryMode = (filters.empty()))
  std::string puFsRoot;

private:
  static std::string prRoundNumber(double vvalue, int n);  // custom rounding number
  static std::string prFormatFileSize(size_t vByteSize);   // format file size field
  static void prCompleteFileInfos(const std::shared_ptr<FileInfos>& FileInfos);  // set time and date infos of a file (detail view mode)
  void prRemoveFileNameInSelection(const std::string& vFileName);  // selection : remove a file name
  void prAddFileNameInSelection(const std::string& vFileName, bool vSetLastSelectionFileName);  // selection : add a file name
  void AddFile(const FileDialogInternal& vFileDialogInternal,
      const std::string& vPath,
      const std::string& vFileName,const FileType& vFileType);  // add file called by scandir
  void AddPath(const FileDialogInternal& vFileDialogInternal,const std::string& vPath, const std::string& vFileName, const FileType& vFileType);  // add file called by scandir
  void ScanDirForPathSelection(const FileDialogInternal& vFileDialogInternal,const std::string& vPath);  // scan the directory for retrieve the path list
  void OpenPathPopup(const FileDialogInternal& vFileDialogInternal,std::vector<std::string>::iterator vPathIter);  // open the popup list of paths
  void SetCurrentPath(std::vector<std::string>::iterator vPathIter);  // set the current path, update the path bar
  void ApplyFilteringOnFileList(const FileDialogInternal& vFileDialogInternal,
      std::vector<std::shared_ptr<FileInfos>>& vFileInfosList,
      std::vector<std::shared_ptr<FileInfos>>& vFileInfosFilteredList);
  void SortFields(const FileDialogInternal& vFileDialogInternal,std::vector<std::shared_ptr<FileInfos>>& vFileInfosList,std::vector<std::shared_ptr<FileInfos>>& vFileInfosFilteredList);  // will sort a column

public:
  FileManager();
  bool IsComposerEmpty();
  size_t GetComposerSize();
  bool IsFileListEmpty();
  bool IsPathListEmpty();
  bool IsFilteredListEmpty();
  bool IsPathFilteredListEmpty();
  size_t GetFullFileListSize();
  std::shared_ptr<FileInfos> GetFullFileAt(size_t vIdx);
  size_t GetFilteredListSize();
  size_t GetPathFilteredListSize();
  std::shared_ptr<FileInfos> GetFilteredFileAt(size_t vIdx);
  std::shared_ptr<FileInfos> GetFilteredPathAt(size_t vIdx);
  std::vector<std::string>::iterator GetCurrentPopupComposedPath();
  bool IsFileNameSelected(const std::string& vFileName);
  std::string GetBack();
  void ClearComposer();
  void ClearFileLists();  // clear file list, will destroy thumbnail textures
  void ClearPathLists();  // clear path list, will destroy thumbnail textures
  void ClearAll();
  void ApplyFilteringOnFileList(const FileDialogInternal& vFileDialogInternal);
  void SortFields(const FileDialogInternal& vFileDialogInternal);       // will sort a column
  void OpenCurrentPath(const FileDialogInternal& vFileDialogInternal);  // set the path of the dialog, will launch the
  bool GetDrives();                                                     // list drives on windows platform
  bool CreateDir(const std::string& vPath);                             // create a directory on the file system
  std::string ComposeNewPath(std::vector<std::string>::iterator vIter);         // compose a path from the compose path widget
  bool SetPathOnParentDirectoryIfAny();                  // compose paht on parent directory
  std::string GetCurrentPath();                          // get the current path
  void SetCurrentPath(const std::string& vCurrentPath);  // set the current path
  static bool IsFileExist(const std::string& vFile);
  void SetDefaultFileName(const std::string& vFileName);
  bool SelectDirectory(const std::shared_ptr<FileInfos>& vInfos);  // enter directory
  void SelectFileName(const FileDialogInternal& vFileDialogInternal,  const std::shared_ptr<FileInfos>& vInfos);  // select filename
  void SetCurrentDir(const std::string& vPath);   // define current directory for scan
  void ScanDir(const FileDialogInternal& vFileDialogInternal,const std::string& vPath);  // scan the directory for retrieve the file list

public:
  std::string GetResultingPath();
  std::string GetResultingFileName(FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag);
  std::string GetResultingFilePathName(FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag);
  std::map<std::string, std::string> GetResultingSelection(
      FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag);

public:
  void DrawDirectoryCreation(const FileDialogInternal& vFileDialogInternal);  // draw directory creation widget
  void DrawPathComposer(const FileDialogInternal& vFileDialogInternal);       // draw path composer widget
};
class IGFD_API FileDialogInternal {
public:
  FileManager puFileManager;      // the file manager
  FilterManager puFilterManager;  // the filter manager
  SearchManager puSearchManager;  // the search manager

public:
  std::string puName;                                           // the internal dialog name (title + ##word)
  bool puShowDialog = false;                                    // the dialog is shown
  ImVec2 puDialogCenterPos = ImVec2(0, 0);                      // center pos for display the confirm overwrite dialog
  int puLastImGuiFrameCount = 0;                                // to be sure than only one dialog displayed per frame
  float puFooterHeight = 0.0f;                                  // footer height
  bool puCanWeContinue = true;                                  // events
  bool puOkResultToConfirm = false;                             // to confim if ok for OverWrite
  bool puIsOk = false;                                          // is dialog ok button click
  bool puFileInputIsActive = false;                             // when input text for file or directory is active
  bool puFileListViewIsActive = false;                          // when list view is active
  std::string puDLGkey;                                         // the dialog key
  std::string puDLGtitle;                                       // the dialog title
  ImGuiFileDialogFlags puDLGflags = ImGuiFileDialogFlags_None;  // default dialog flag
  UserDatas puDLGuserDatas = nullptr;                           // the user datas passed to a dialog
  PaneFun puDLGoptionsPane = nullptr;                           // the user side pane
  float puDLGoptionsPaneWidth = 0.0f;                           // the user side pane width
  bool puNeedToExitDialog = false;                              // we need to exit the dialog
  bool puUseCustomLocale = false;                               // custom user locale
  int puLocaleCategory = LC_ALL;                                // locale category to use
  std::string puLocaleBegin;  // the locale who will be applied at start of the display dialog
  std::string puLocaleEnd;    // the locale who will be applaied at end of the display dialog

public:
  void NewFrame();           // new frame, so maybe neded to do somethings, like reset events
  void EndFrame();           // end frame, so maybe neded to do somethings fater all
  void ResetForNewDialog();  // reset what is needed to reset for the openging of a new dialog
};
class IGFD_API ThumbnailFeature {
protected:
  ThumbnailFeature();
  ~ThumbnailFeature();

  void NewThumbnailFrame(FileDialogInternal& vFileDialogInternal);
  void EndThumbnailFrame(FileDialogInternal& vFileDialogInternal);
  void QuitThumbnailFrame(FileDialogInternal& vFileDialogInternal);

#ifdef USE_THUMBNAILS
protected:
  enum class DisplayModeEnum { FILE_LIST = 0, THUMBNAILS_LIST, THUMBNAILS_GRID };

private:
    uint32_t prCountFiles = 0U;
    bool prIsWorking = false;
    std::shared_ptr<std::thread> prThumbnailGenerationThread = nullptr;
    std::list<std::shared_ptr<FileInfos>> prThumbnailFileDatasToGet;  // base container
    std::mutex prThumbnailFileDatasToGetMutex;
    std::list<std::shared_ptr<FileInfos>> prThumbnailToCreate;  // base container
    std::mutex prThumbnailToCreateMutex;
    std::list<IGFD_Thumbnail_Info> prThumbnailToDestroy;  // base container
    std::mutex prThumbnailToDestroyMutex;

    CreateThumbnailFun prCreateThumbnailFun = nullptr;
    DestroyThumbnailFun prDestroyThumbnailFun = nullptr;

protected:
    DisplayModeEnum prDisplayMode = DisplayModeEnum::FILE_LIST;

private:
    void prVariadicProgressBar(float fraction, const ImVec2& size_arg, const char* fmt, ...);

protected:
    // will be call in cpu zone (imgui computations, will call a texture file retrieval thread)
    void prStartThumbnailFileDatasExtraction();       // start the thread who will get byte buffer from image files
    bool prStopThumbnailFileDatasExtraction();        // stop the thread who will get byte buffer from image files
    void prThreadThumbnailFileDatasExtractionFunc();  // the thread who will get byte buffer from image files
    void prDrawThumbnailGenerationProgress();         // a little progressbar who will display the texture gen status
    void prAddThumbnailToLoad(const std::shared_ptr<FileInfos>& vFileInfos);  // add texture to load in the thread
    void prAddThumbnailToCreate(const std::shared_ptr<FileInfos>& vFileInfos);
    void prAddThumbnailToDestroy(const IGFD_Thumbnail_Info& vIGFD_Thumbnail_Info);
    void prDrawDisplayModeToolBar();  // draw display mode toolbar (file list, thumbnails list, small thumbnails grid,
                                      // big thumbnails grid)
    void prClearThumbnails(FileDialogInternal& vFileDialogInternal);

public:
    void SetCreateThumbnailCallback(const CreateThumbnailFun& vCreateThumbnailFun);
    void SetDestroyThumbnailCallback(const DestroyThumbnailFun& vCreateThumbnailFun);

    // must be call in gpu zone (rendering, possibly one rendering thread)
    void ManageGPUThumbnails();  // in gpu rendering zone, whill create or destroy texture
#endif
};

class IGFD_API BookMarkFeature {
protected:
  BookMarkFeature();

private:
  struct BookmarkStruct {
    std::string name;  // name of the bookmark
    std::string path;  // absolute path of the bookmarked directory
    bool defined_by_code = false;  // defined by code, can be used for rpevent serialization / deserialization
  };

private:
  ImGuiListClipper prBookmarkClipper;
  std::vector<BookmarkStruct> prBookmarks;
  char prBookmarkEditBuffer[MAX_FILE_DIALOG_NAME_BUFFER] = "";

protected:
  float prBookmarkWidth = 200.0f;
  bool prBookmarkPaneShown = false;

protected:
  void prDrawBookmarkButton();                                                            // draw bookmark button
  bool prDrawBookmarkPane(FileDialogInternal& vFileDialogInternal, const ImVec2& vSize);  // draw bookmark Pane

public:
  std::string SerializeBookmarks(const bool& vDontSerializeCodeBasedBookmarks = true);  // for avoid serialization of bookmarks added by code
  void DeserializeBookmarks(const std::string& vBookmarks);     // bookmark buffer to load
  void AddBookmark(const std::string& vBookMarkName, const std::string& vBookMarkPath);  // bookmark path
  bool RemoveBookmark(const std::string& vBookMarkName);  // bookmark name to remove
};

// file localization by input chat // widget flashing
class IGFD_API KeyExplorerFeature {
protected:
  KeyExplorerFeature();
};

class IGFD_API FileDialog : public BookMarkFeature, public KeyExplorerFeature, public ThumbnailFeature {
protected:
    FileDialogInternal prFileDialogInternal;
    ImGuiListClipper prFileListClipper;
    ImGuiListClipper prPathListClipper;
    float prOkCancelButtonWidth = 0.0f;

public:
    // Singleton for easier accces form anywhere but only one dialog at a time
    // vCopy or vForce can be used for share a memory pointer in a new memory space like a dll module
    static FileDialog* Instance(FileDialog* vCopy = nullptr, bool vForce = false) {
        static FileDialog _instance;
        static FileDialog* _instance_copy = nullptr;
        if (vCopy || vForce) {
            _instance_copy = vCopy;
        }
        if (_instance_copy) {
            return _instance_copy;
        }
        return &_instance;
    }

public:
    FileDialog();  // ImDialog Constructor. can be used for have many dialog at same time (not possible with singleton)
    virtual ~FileDialog();  // ImDialog Destructor
    virtual // todo : need to refactor all theses function to maybe just one

    //  standard dialog
    void OpenDialog(                        // open simple dialog (path and fileName can be specified)
        const std::string& vKey,            // key dialog
        const std::string& vTitle,          // title
        const char* vFilters,               // filters
        const std::string& vPath,           // path
        const std::string& vFileName,       // defaut file name
        const int& vCountSelectionMax = 1,  // count selection max
        UserDatas vUserDatas = nullptr,     // user datas (can be retrieved in pane)
        ImGuiFileDialogFlags vFlags = 0);   // ImGuiFileDialogFlags

    void OpenDialog(                        // open simple dialog (path and filename are obtained from filePathName)
        const std::string& vKey,            // key dialog
        const std::string& vTitle,          // title
        const char* vFilters,               // filters
        const std::string& vFilePathName,   // file path name (will be decompsoed in path and fileName)
        const int& vCountSelectionMax = 1,  // count selection max
        UserDatas vUserDatas = nullptr,     // user datas (can be retrieved in pane)
        ImGuiFileDialogFlags vFlags = 0);   // ImGuiFileDialogFlags

    // with pane
    void OpenDialogWithPane(           // open dialog with custom right pane (path and fileName can be specified)
        const std::string& vKey,       // key dialog
        const std::string& vTitle,     // title
        const char* vFilters,          // filters
        const std::string& vPath,      // path
        const std::string& vFileName,  // defaut file name
        const PaneFun& vSidePane,      // side pane
        const float& vSidePaneWidth = 250.0f,  // side pane width
        const int& vCountSelectionMax = 1,     // count selection max
        UserDatas vUserDatas = nullptr,        // user datas (can be retrieved in pane)
        ImGuiFileDialogFlags vFlags = 0);      // ImGuiFileDialogFlags

    void OpenDialogWithPane(  // open dialog with custom right pane (path and filename are obtained from filePathName)
        const std::string& vKey,               // key dialog
        const std::string& vTitle,             // title
        const char* vFilters,                  // filters
        const std::string& vFilePathName,      // file path name (will be decompsoed in path and fileName)
        const PaneFun& vSidePane,              // side pane
        const float& vSidePaneWidth = 250.0f,  // side pane width
        const int& vCountSelectionMax = 1,     // count selection max
        UserDatas vUserDatas = nullptr,        // user datas (can be retrieved in pane)
        ImGuiFileDialogFlags vFlags = 0);      // ImGuiFileDialogFlags

    // Display / Close dialog form
    bool Display(                 // Display the dialog. return true if a result was obtained (Ok or not)
        const std::string& vKey,  // key dialog to display (if not the same key as defined by OpenDialog => no opening)
        ImGuiWindowFlags vFlags = ImGuiWindowFlags_NoCollapse,  // ImGuiWindowFlags
        ImVec2 vMinSize = ImVec2(0, 0),                         // mininmal size contraint for the ImGuiWindow
        ImVec2 vMaxSize = ImVec2(FLT_MAX, FLT_MAX));            // maximal size contraint for the ImGuiWindow
    void Close();                                               // close dialog

    // queries
    bool WasOpenedThisFrame(const std::string& vKey) const;  // say if the dialog key was already opened this frame
    bool WasOpenedThisFrame() const;                         // say if the dialog was already opened this frame
    bool IsOpened(const std::string& vKey) const;            // say if the key is opened
    bool IsOpened() const;                                   // say if the dialog is opened somewhere
    std::string GetOpenedKey() const;  // return the dialog key who is opened, return nothing if not opened

    // get result
    bool IsOk() const;  // true => Dialog Closed with Ok result / false : Dialog closed with cancel result
    std::map<std::string, std::string> GetSelection(
        IGFD_ResultMode vFlag = IGFD_ResultMode_KeepInputFile);  // Open File behavior : will return selection via a
                                                                 // map<FileName, FilePathName>
    std::string GetFilePathName(IGFD_ResultMode vFlag =IGFD_ResultMode_AddIfNoFileExt);  // Save File behavior : will return the current file path name
    std::string GetCurrentFileName(IGFD_ResultMode vFlag =IGFD_ResultMode_AddIfNoFileExt);  // Save File behavior : will return the content file name
    std::string GetCurrentPath();             // will return current file path
    std::string GetCurrentFilter();           // will return current filter
    UserDatas GetUserDatas() const;           // will return user datas send with Open Dialog

    // file style by extentions
    void SetFileStyle(                      // SetExtention datas for have custom display of particular file type
        const IGFD_FileStyleFlags& vFlags,  // file style
        const char* vCriteria,              // extention filter to tune
        const FileStyle& vInfos);  // Filter Extention Struct who contain Color and Icon/Text for the display of the
                                   // file with extention filter
    void SetFileStyle(             // SetExtention datas for have custom display of particular file type
        const IGFD_FileStyleFlags& vFlags,  // file style
        const char* vCriteria,              // extention filter to tune
        const ImVec4& vColor,               // wanted color for the display of the file with extention filter
        const std::string& vIcon = "",      // wanted text or icon of the file with extention filter
        ImFont* vFont = nullptr);           // wanted font
    void SetFileStyle(FileStyle::FileStyleFunctor vFunctor);  // set file style via lambda function
    bool GetFileStyle(                                        // GetExtention datas. return true is extention exist
        const IGFD_FileStyleFlags& vFlags,                    // file style
        const std::string& vCriteria,                         // extention filter (same as used in SetExtentionInfos)
        ImVec4* vOutColor,                                    // color to retrieve
        std::string* vOutIcon = nullptr,                      // icon or text to retrieve
        ImFont** vOutFont = nullptr);                         // font to retreive
    void ClearFilesStyle();                                   // clear extentions setttings

    void SetLocales(                      // set locales to use before and after the dialog display
        const int& vLocaleCategory,       // set local category
        const std::string& vLocaleBegin,  // locale to use at begining of the dialog display
        const std::string& vLocaleEnd);   // locale to use at the end of the dialog display

protected:
    void NewFrame();   // new frame just at begining of display
    void EndFrame();   // end frame just at end of display
    void QuitFrame();  // quit frame when qui quit the dialog

    // others
    bool prConfirm_Or_OpenOverWriteFileDialog_IfNeeded(bool vLastAction, ImGuiWindowFlags vFlags);  // treatment of the result, start the confirm to overwrite dialog// if needed (if defined with flag)

    // dialog parts
    virtual void prDrawHeader();   // draw header part of the dialog (bookmark btn, dir creation, path composer, search
    virtual void prDrawContent();  // draw content part of the dialog (bookmark pane, file list, side pane)
    virtual bool prDrawFooter();   // draw footer part of the dialog (file field, fitler combobox, ok/cancel btn's)

    // widgets components
    virtual void DisplayPathPopup(ImVec2 vSize);  // draw path popup when click on a \ or /
    virtual bool prDrawValidationButtons();       // draw validations btns, ok, cancel buttons
    virtual bool prDrawOkButton();                // draw ok button
    virtual bool prDrawCancelButton();            // draw cancel button
    virtual void prDrawSidePane(float vHeight);   // draw side pane
    virtual void prSelectableItem(int vidx,std::shared_ptr<FileInfos> vInfos,bool vSelected,const char* vFmt,...);                                       // draw a custom selectable behavior item
    virtual void prDrawFileListView(ImVec2 vSize);  // draw file list view (default mode)

    // to be called only by these function and theirs overrides
    // - prDrawFileListView
    // - prDrawThumbnailsListView
    // - prDrawThumbnailsGridView
    void prBeginFileColorIconStyle(std::shared_ptr<FileInfos> vFileInfos, bool& vOutShowColor, std::string& vOutStr, ImFont** vOutFont);  // begin style apply of filter with color an icon if any
    void prEndFileColorIconStyle(const bool& vShowColor, ImFont* vFont);  // end style apply of filter
};



}  // namespace IGFD



#endif  // __cplusplus


#include <stdint.h>
#define API __attribute__((__visibility__("default")))
#define IGFD_C_API extern "C" API
typedef IGFD::UserDatas IGFDUserDatas;
typedef IGFD::PaneFun IGFDPaneFun;
typedef IGFD::FileDialog ImDialog;
