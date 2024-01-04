#include "ImDialog.h"

#include <cfloat>
#include <cstring>  // stricmp / strcasecmp
#include <cstdarg>  // variadic
#include <sstream>
#include <iomanip>
#include <ctime>
#include <sys/stat.h>
#include <cstdio>
#include <cerrno>
#include <filesystem>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cctype>

#include "ImDialog_config.h"
#include "../core/imgui.h"
#include "../core/imgui_internal.h"
#include "../../image/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../image/stb_image_resize.h"


#define _IGFD_UNIX_
#define stricmp strcasecmp

#define IS_FLOAT_DIFFERENT(a, b) (fabs((a) - (b)) > FLT_EPSILON)
#define IS_FLOAT_EQUAL(a, b) (fabs((a) - (b)) < FLT_EPSILON)





class IGFDException : public std::exception {
private:
    std::string m_Message;
public:
    IGFDException(const std::string& vMessage) : m_Message(vMessage) {}
    const char* what() { return m_Message.c_str(); }
};


inline int inAlphaSort(const struct dirent** a, const struct dirent** b) { return strcoll((*a)->d_name, (*b)->d_name); }

//Utils
bool IGFD::Utils::ImSplitter(bool split_vertically,
    float thickness,
    float* size1,
    float* size2,
    float min_size1,
    float min_size2,
    float splitter_long_axis_size) {
    using namespace ImGui;
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    ImGuiID id = window->GetID("##Splitter");
    ImRect bb;
    bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
    bb.Max = bb.Min + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size)
                                                    : ImVec2(splitter_long_axis_size, thickness),
                          0.0f, 0.0f);
    return SplitterBehavior(
        bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 1.0f);
}
bool IGFD::Utils::ReplaceString(std::string& str, const ::std::string& oldStr, const ::std::string& newStr, const size_t& vMaxRecursion) {
    if (!str.empty() && oldStr != newStr) {
        bool res = false;
        size_t pos = 0;
        bool found = false;
        size_t max_recursion = vMaxRecursion;
        do {
            pos = str.find(oldStr, pos);
            if (pos != std::string::npos) {
                found = res = true;
                str.replace(pos, oldStr.length(), newStr);
                pos += newStr.length();
            } else if (found && max_recursion > 0) {  // recursion loop
                found = false;
                pos = 0;
                --max_recursion;
            }
        } while (pos != std::string::npos);
        return res;
    }
    return false;
}
bool IGFD::Utils::IsDirectoryCanBeOpened(const std::string& name) {
  bool bExists = false;
  //---------------------------

  if (!name.empty()) {
    namespace fs = std::filesystem;
    fs::path pathName = fs::path(name);
    try {
        // interesting, in the case of a protected dir or for any reason the dir cant be opened
        // this func will work but will say nothing more . not like the dirent version
        bExists = fs::is_directory(pathName);
        // test if can be opened, this function can thrown an exception if there is an issue with this dir
        // here, the dir_iter is need else not exception is thrown..
        const auto dir_iter = std::filesystem::directory_iterator(pathName);
        (void)dir_iter;  // for avoid unused warnings
    } catch (const std::exception& /*ex*/) {
        // fail so this dir cant be opened
        bExists = false;
    }
    DIR* pDir = nullptr;
    // interesting, in the case of a protected dir or for any reason the dir cant be opened
    // this func will fail
    pDir = opendir(name.c_str());
    if (pDir != nullptr) {
        bExists = true;
        (void)closedir(pDir);
    }
  }

  //---------------------------
  return bExists;  // this is not a directory!
}
bool IGFD::Utils::IsDirectoryExist(const std::string& name) {
    bool bExists = false;

    if (!name.empty()) {
        namespace fs = std::filesystem;
        fs::path pathName = fs::path(name);
        bExists = fs::is_directory(pathName);
    }

    return bExists;  // this is not a directory!
}
bool IGFD::Utils::CreateDirectoryIfNotExist(const std::string& name) {
    bool res = false;

    if (!name.empty()) {
        if (!IsDirectoryExist(name)) {
            char buffer[PATH_MAX] = {};
            snprintf(buffer, PATH_MAX, "mkdir -p \"%s\"", name.c_str());
            const int dir_err = std::system(buffer);
            if (dir_err != -1) {
                res = true;
            }
            if (!res) {
                std::cout << "Error creating directory " << name << std::endl;
            }
        }
    }

    return res;
}
void IGFD::Utils::AppendToBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr) {
    std::string st = vStr;
    size_t len = vBufferLen - 1u;
    size_t slen = strlen(vBuffer);

    if (!st.empty() && st != "\n") {
        IGFD::Utils::ReplaceString(st, "\n", "");
        IGFD::Utils::ReplaceString(st, "\r", "");
    }
    vBuffer[slen] = '\0';
    std::string str = std::string(vBuffer);
    // if (!str.empty()) str += "\n";
    str += vStr;
    if (len > str.size()) {
        len = str.size();
    }
}
void IGFD::Utils::ResetBuffer(char* vBuffer) { vBuffer[0] = '\0'; }
void IGFD::Utils::SetBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr) {
    ResetBuffer(vBuffer);
    AppendToBuffer(vBuffer, vBufferLen, vStr);
}
size_t IGFD::Utils::GetCharCountInString(const std::string& vString, const char& vChar) {
    size_t res = 0U;
    for (const auto& c : vString) {
        if (c == vChar) {
            ++res;
        }
    }
    return res;
}
size_t IGFD::Utils::GetLastCharPosWithMinCharCount(
    const std::string& vString, const char& vChar, const size_t& vMinCharCount) {
    if (vMinCharCount) {
        size_t last_dot_pos = vString.size() + 1U;
        size_t count_dots = vMinCharCount;
        while (count_dots > 0U && last_dot_pos > 0U && last_dot_pos != std::string::npos) {
            auto new_dot = vString.rfind(vChar, last_dot_pos - 1U);
            if (new_dot != std::string::npos) {
                last_dot_pos = new_dot;
                --count_dots;
            } else {
                break;
            }
        }
        return last_dot_pos;
    }
    return std::string::npos;
}
std::string IGFD::Utils::LowerCaseString(const std::string& vString) {
    auto str = vString;

    // convert to lower case
    for (char& c : str) {
        c = (char)std::tolower(c);
    }

    return str;
}
std::vector<std::string> IGFD::Utils::SplitStringToVector(
    const std::string& vText, const char& vDelimiter, const bool& vPushEmpty) {
    std::vector<std::string> arr;
    if (!vText.empty()) {
        size_t start = 0;
        size_t end = vText.find(vDelimiter, start);
        while (end != std::string::npos) {
            auto token = vText.substr(start, end - start);
            if (!token.empty() || (token.empty() && vPushEmpty)) {  //-V728
                arr.push_back(token);
            }
            start = end + 1;
            end = vText.find(vDelimiter, start);
        }
        auto token = vText.substr(start);
        if (!token.empty() || (token.empty() && vPushEmpty)) {  //-V728
            arr.push_back(token);
        }
    }
    return arr;
}
std::vector<std::string> IGFD::Utils::GetDrivesList() {
    std::vector<std::string> res;
    //---------------------------

    //---------------------------
    return res;
}
IGFD::Utils::PathStruct IGFD::Utils::ParsePathFileName(const std::string& vPathFileName){
  PathStruct res;
  //---------------------------

  if (!vPathFileName.empty()) {
    std::string pfn = vPathFileName;
    std::string separator(1u, '/');
    IGFD::Utils::ReplaceString(pfn, "\\", separator);
    IGFD::Utils::ReplaceString(pfn, "/", separator);

    size_t lastSlash = pfn.find_last_of(separator);
    if (lastSlash != std::string::npos) {
      res.name = pfn.substr(lastSlash + 1);
      res.path = pfn.substr(0, lastSlash);
      res.isOk = true;
    }

    size_t lastPoint = pfn.find_last_of('.');
    if (lastPoint != std::string::npos) {
      if (!res.isOk) {
        res.name = pfn;
        res.isOk = true;
      }
      res.ext = pfn.substr(lastPoint + 1);
      IGFD::Utils::ReplaceString(res.name, "." + res.ext, "");
    }

    if (!res.isOk) {
      res.name = std::move(pfn);
      res.isOk = true;
    }
  }

  //---------------------------
  return res;
}

//Style
IGFD::FileStyle::FileStyle() : color(0, 0, 0, 0) {}
IGFD::FileStyle::FileStyle(const FileStyle& vStyle) {
    color = vStyle.color;
    icon = vStyle.icon;
    font = vStyle.font;
    flags = vStyle.flags;
}
IGFD::FileStyle::FileStyle(const ImVec4& vColor, const std::string& vIcon, ImFont* vFont) : color(vColor), icon(vIcon), font(vFont) {}

//Search
void IGFD::SearchManager::Clear() {
    puSearchTag.clear();
    IGFD::Utils::ResetBuffer(puSearchBuffer);
}
void IGFD::SearchManager::DrawSearchBar(FileDialogInternal& vFileDialogInternal) {
    // search field
    if (ImGui::Button(resetButtonString "##BtnImGuiFileDialogSearchField")) {
        Clear();
        vFileDialogInternal.puFileManager.ApplyFilteringOnFileList(vFileDialogInternal);
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(buttonResetSearchString);
    ImGui::SameLine();
    ImGui::Text(searchString);
    ImGui::SameLine();
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
    bool edited = ImGui::InputText("##InputImGuiFileDialogSearchField", puSearchBuffer, MAX_FILE_DIALOG_NAME_BUFFER);
    if (ImGui::GetItemID() == ImGui::GetActiveID())
        puSearchInputIsActive = true;
    ImGui::PopItemWidth();
    if (edited) {
        puSearchTag = puSearchBuffer;
        vFileDialogInternal.puFileManager.ApplyFilteringOnFileList(vFileDialogInternal);
    }
}

//Filter info
void IGFD::FilterInfos::setCollectionTitle(const std::string& vTitle) { title = vTitle; }
void IGFD::FilterInfos::addFilter(const std::string& vFilter, const bool& vIsRegex) {
    setCollectionTitle(vFilter);
    addCollectionFilter(vFilter, vIsRegex);
}
void IGFD::FilterInfos::addCollectionFilter(const std::string& vFilter, const bool& vIsRegex) {
    if (!vIsRegex) {
        if (vFilter.find('*') != std::string::npos) {
            const auto& regex_string = transformAsteriskBasedFilterToRegex(vFilter);
            addCollectionFilter(regex_string, true);
            return;
        }
        filters.try_add(vFilter);
        filters_optimized.try_add(Utils::LowerCaseString(vFilter));
        auto _count_dots = Utils::GetCharCountInString(vFilter, '.');
        if (_count_dots > count_dots) {
            count_dots = _count_dots;
        }
    } else {
        try {
            auto rx = std::regex(vFilter);
            filters.try_add(vFilter);
            filters_regex.emplace_back(rx);
        } catch (std::exception&) {
            assert(0);  // YOUR REGEX FILTER IS INVALID
        }
    }
}
void IGFD::FilterInfos::clear() {
    title.clear();
    filters.clear();
    filters_optimized.clear();
    filters_regex.clear();
}
bool IGFD::FilterInfos::empty() const { return filters.empty() || filters.begin()->empty(); }
bool IGFD::FilterInfos::exist(const FileInfos& vFileInfos, bool vIsCaseInsensitive) const {
    for (const auto& filter : filters) {
        if (vFileInfos.SearchForExt(filter, vIsCaseInsensitive, count_dots)) {
            return true;
        }
    }
    return false;
}
bool IGFD::FilterInfos::regexExist(const std::string& vFilter) const {
    for (auto regex : filters_regex) {
        if (std::regex_search(vFilter, regex)) {
            return true;
        }
    }
    return false;
}
bool IGFD::FileInfos::SearchForTag(const std::string& vTag) const {
    if (!vTag.empty()) {
        if (fileNameExt_optimized == "..")
            return true;

        return fileNameExt_optimized.find(vTag) != std::string::npos ||  // first try without case and accents
               fileNameExt.find(vTag) != std::string::npos;              // second if searched with case and accents
    }

    // if tag is empty => its a special case but all is found
    return true;
}
bool IGFD::FileInfos::SearchForExt(const std::string& vExt, const bool& vIsCaseInsensitive, const size_t& vMaxLevel) const {
    if (!vExt.empty()) {
        const auto& ext_to_check = vIsCaseInsensitive ? Utils::LowerCaseString(vExt) : vExt;
        const auto& ext_levels = vIsCaseInsensitive ? fileExtLevels_optimized : fileExtLevels;
        if (vMaxLevel >= 1 && countExtDot >= vMaxLevel) {
            for (const auto& ext : ext_levels) {
                if (!ext.empty() && ext == ext_to_check) {
                    return true;
                }
            }
        } else {
            return (fileExtLevels[0] == vExt);
        }
    }
    return false;
}
bool IGFD::FileInfos::SearchForExts(const std::string& vComaSepExts, const bool& vIsCaseInsensitive, const size_t& vMaxLevel) const {
    if (!vComaSepExts.empty()) {
        const auto& arr = Utils::SplitStringToVector(vComaSepExts, ',', false);
        for (const auto& a : arr) {
            if (SearchForExt(a, vIsCaseInsensitive, vMaxLevel)) {
                return true;
            }
        }
    }
    return false;
}
bool IGFD::FileInfos::FinalizeFileTypeParsing(const size_t& vMaxDotToExtract) {
    if (fileType.isFile() || fileType.isLinkToUnknown()) {  // link can have the same extention of a file
        countExtDot = Utils::GetCharCountInString(fileNameExt, '.');
        size_t lpt = 0U;
        if (countExtDot > 1U) {  // multi layer ext
            size_t max_dot_to_extract = vMaxDotToExtract;
            if (max_dot_to_extract > countExtDot) {
                max_dot_to_extract = countExtDot;
            }
            lpt = Utils::GetLastCharPosWithMinCharCount(fileNameExt, '.', max_dot_to_extract);
        } else {
            lpt = fileNameExt.find_first_of('.');
        }
        if (lpt != std::string::npos) {
            size_t lvl = 0U;
            fileExtLevels[lvl] = fileNameExt.substr(lpt);
            fileExtLevels_optimized[lvl] = Utils::LowerCaseString(fileExtLevels[lvl]);
            if (countExtDot > 1U) {  // multi layer ext
                auto count = countExtDot;
                while (count > 0 && lpt != std::string::npos && lvl < fileExtLevels.size()) {
                    ++lpt, ++lvl;
                    if (fileNameExt.size() > lpt) {
                        lpt = fileNameExt.find_first_of('.', lpt);
                        if (lpt != std::string::npos) {
                            fileExtLevels[lvl] = fileNameExt.substr(lpt);
                            fileExtLevels_optimized[lvl] = Utils::LowerCaseString(fileExtLevels[lvl]);
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}
std::string IGFD::FilterInfos::transformAsteriskBasedFilterToRegex(const std::string& vFilter) {
    std::string res;
    if (!vFilter.empty() && vFilter.find('*') != std::string::npos) {
        res = "((";
        for (const auto& c : vFilter) {
            if (c == '.') {
                res += "[.]";  // [.] => a dot
            } else if (c == '*') {
                res += ".*";  // .* => any char zero or many
            } else {
                res += c;  // other chars
            }
        }
        res += "$))";  // $ => end fo the string
    }
    return res;
}
const std::string& IGFD::FilterInfos::getFirstFilter() const {
    if (!filters.empty()) {
        return *filters.begin();
    }
    return empty_string;
}
const IGFD::FilterInfos& IGFD::FilterManager::GetSelectedFilter() const { return prSelectedFilter; }

//Filter manager
void IGFD::FilterManager::ParseFilters(const char* vFilters) {
    prParsedFilters.clear();

    if (vFilters) {
        puDLGFilters = vFilters;  // file mode
    } else {
        puDLGFilters.clear();  // directory mode
    }

    if (!puDLGFilters.empty()) {
        /* Rules
        0) a filter must have 2 chars mini and the first must be a .
        1) a regex must be in (( and ))
        2) a , will separate filters except if between a ( and )
        3) name{filter1, filter2} is a spetial form for collection filters
        3.1) the name can be composed of what you want except { and }
        3.2) the filter can be a regex
        4) the filters cannot integrate these chars '(' ')' '{' '}' ' ' except for a regex with respect to rule 1)
        5) the filters cannot integrate a ','
        */

        bool current_filter_found = false;
        bool started = false;
        bool regex_started = false;
        bool parenthesis_started = false;

        std::string word;
        std::string filter_name;

        char last_split_char = 0;
        for (char c : puDLGFilters) {
            if (c == '{') {
                if (regex_started) {
                    word += c;
                } else {
                    started = true;
                    prParsedFilters.emplace_back();
                    prParsedFilters.back().setCollectionTitle(filter_name);
                    filter_name.clear();
                    word.clear();
                }
                last_split_char = c;
            } else if (c == '}') {
                if (regex_started) {
                    word += c;
                } else {
                    if (started) {
                        if (word.size() > 1U && word[0] == '.') {
                            if (prParsedFilters.empty()) {
                                prParsedFilters.emplace_back();
                            }
                            prParsedFilters.back().addCollectionFilter(word, false);
                        }
                        word.clear();
                        filter_name.clear();
                        started = false;
                    }
                }
                last_split_char = c;
            } else if (c == '(') {
                word += c;
                if (last_split_char == '(') {
                    regex_started = true;
                }
                parenthesis_started = true;
                if (!started) {
                    filter_name += c;
                }
                last_split_char = c;
            } else if (c == ')') {
                word += c;
                if (last_split_char == ')') {
                    if (regex_started) {
                        if (started) {
                            prParsedFilters.back().addCollectionFilter(word, true);
                        } else {
                            prParsedFilters.emplace_back();
                            prParsedFilters.back().addFilter(word, true);
                        }
                        word.clear();
                        filter_name.clear();
                        regex_started = false;
                    } else {
                        if (!started) {
                            if (!prParsedFilters.empty()) {
                                prParsedFilters.erase(prParsedFilters.begin() + prParsedFilters.size() - 1U);
                            } else {
                                prParsedFilters.clear();
                            }
                        }
                        word.clear();
                        filter_name.clear();
                    }
                }
                parenthesis_started = false;
                if (!started) {
                    filter_name += c;
                }
                last_split_char = c;
            } else if (c == '.') {
                word += c;
                if (!started) {
                    filter_name += c;
                }
                last_split_char = c;
            } else if (c == ',') {
                if (regex_started) {
                    regex_started = false;
                    word.clear();
                    filter_name.clear();
                } else {
                    if (started) {
                        if (word.size() > 1U && word[0] == '.') {
                            prParsedFilters.back().addCollectionFilter(word, false);
                            word.clear();
                            filter_name.clear();
                        }
                    } else {
                        if (word.size() > 1U && word[0] == '.') {
                            prParsedFilters.emplace_back();
                            prParsedFilters.back().addFilter(word, false);
                            word.clear();
                            filter_name.clear();
                        }
                        if (parenthesis_started) {
                            filter_name += c;
                        }
                    }
                }
            } else {
                if (c != ' ') {
                    word += c;
                }
                if (!started) {
                    filter_name += c;
                }
            }
        }

        if (started) {
            if (!prParsedFilters.empty()) {
                prParsedFilters.erase(prParsedFilters.begin() + prParsedFilters.size() - 1U);
            } else {
                prParsedFilters.clear();
            }
        } else if (word.size() > 1U && word[0] == '.') {
            prParsedFilters.emplace_back();
            prParsedFilters.back().addFilter(word, false);
            word.clear();
        }

        for (const auto& it : prParsedFilters) {
            if (it.title == prSelectedFilter.title) {
                prSelectedFilter = it;
                current_filter_found = true;
                break;
            }
        }

        if (!current_filter_found) {
            if (!prParsedFilters.empty()) {
                prSelectedFilter = *prParsedFilters.begin();
            }
        }
    }
}
void IGFD::FilterManager::SetSelectedFilterWithExt(const std::string& vFilter) {
    if (!prParsedFilters.empty()) {
        if (!vFilter.empty()) {
            for (const auto& infos : prParsedFilters) {
                for (const auto& filter : infos.filters) {
                    if (vFilter == filter) {
                        prSelectedFilter = infos;
                    }
                }
            }
        }

        if (prSelectedFilter.empty()) {
            prSelectedFilter = *prParsedFilters.begin();
        }
    }
}
void IGFD::FilterManager::SetFileStyle(
    const IGFD_FileStyleFlags& vFlags, const char* vCriteria, const FileStyle& vInfos) {
    std::string _criteria = (vCriteria != nullptr) ? std::string(vCriteria) : "";
    prFilesStyle[vFlags][_criteria] = std::make_shared<FileStyle>(vInfos);
    prFilesStyle[vFlags][_criteria]->flags = vFlags;
}
bool IGFD::FilterManager::prFillFileStyle(std::shared_ptr<FileInfos> vFileInfos) const {
    // todo : better system to found regarding what style to priorize regarding other
    // maybe with a lambda fucntion for let the user use his style
    // according to his use case
    if (vFileInfos.use_count() && !prFilesStyle.empty()) {
        for (const auto& _flag : prFilesStyle) {
            for (const auto& _file : _flag.second) {
                if ((_flag.first & IGFD_FileStyleByTypeDir && _flag.first & IGFD_FileStyleByTypeLink &&
                        vFileInfos->fileType.isDir() && vFileInfos->fileType.isSymLink()) ||
                    (_flag.first & IGFD_FileStyleByTypeFile && _flag.first & IGFD_FileStyleByTypeLink &&
                        vFileInfos->fileType.isFile() && vFileInfos->fileType.isSymLink()) ||
                    (_flag.first & IGFD_FileStyleByTypeLink && vFileInfos->fileType.isSymLink()) ||
                    (_flag.first & IGFD_FileStyleByTypeDir && vFileInfos->fileType.isDir()) ||
                    (_flag.first & IGFD_FileStyleByTypeFile && vFileInfos->fileType.isFile())) {
                    if (_file.first.empty()) {  // for all links
                        vFileInfos->fileStyle = _file.second;
                    } else if (_file.first.find("((") != std::string::npos &&
                               std::regex_search(vFileInfos->fileNameExt,
                                   std::regex(_file.first))) {  // for links who are equal to style criteria
                        vFileInfos->fileStyle = _file.second;
                    } else if (_file.first == vFileInfos->fileNameExt) {  // for links who are equal to style criteria
                        vFileInfos->fileStyle = _file.second;
                    }
                }

                if (_flag.first & IGFD_FileStyleByExtention) {
                    if (_file.first.find("((") != std::string::npos &&
                        std::regex_search(vFileInfos->fileExtLevels[0], std::regex(_file.first))) {
                        vFileInfos->fileStyle = _file.second;
                    } else if (vFileInfos->SearchForExt(_file.first, false)) {
                        vFileInfos->fileStyle = _file.second;
                    }
                }

                if (_flag.first & IGFD_FileStyleByFullName) {
                    if (_file.first.find("((") != std::string::npos &&
                        std::regex_search(vFileInfos->fileNameExt, std::regex(_file.first))) {
                        vFileInfos->fileStyle = _file.second;
                    } else if (_file.first == vFileInfos->fileNameExt) {
                        vFileInfos->fileStyle = _file.second;
                    }
                }

                if (_flag.first & IGFD_FileStyleByContainedInFullName) {
                    if (_file.first.find("((") != std::string::npos &&
                        std::regex_search(vFileInfos->fileNameExt, std::regex(_file.first))) {
                        vFileInfos->fileStyle = _file.second;
                    } else if (vFileInfos->fileNameExt.find(_file.first) != std::string::npos) {
                        vFileInfos->fileStyle = _file.second;
                    }
                }

                for (auto& functor : prFilesStyleFunctors) {
                    if (functor) {
                        FileStyle result;
                        if (functor(*(vFileInfos.get()), result)) {
                            vFileInfos->fileStyle = std::make_shared<FileStyle>(std::move(result));
                        }
                    }
                }

                if (vFileInfos->fileStyle.use_count()) {
                    return true;
                }
            }
        }
    }

    return false;
}
void IGFD::FilterManager::SetFileStyle(const IGFD_FileStyleFlags& vFlags,
    const char* vCriteria,
    const ImVec4& vColor,
    const std::string& vIcon,
    ImFont* vFont) {
    std::string _criteria;
    if (vCriteria)
        _criteria = std::string(vCriteria);
    prFilesStyle[vFlags][_criteria] = std::make_shared<FileStyle>(vColor, vIcon, vFont);
    prFilesStyle[vFlags][_criteria]->flags = vFlags;
}
void IGFD::FilterManager::SetFileStyle(FileStyle::FileStyleFunctor vFunctor) {
    if (vFunctor) {
        prFilesStyleFunctors.push_back(vFunctor);
    }
}
bool IGFD::FilterManager::GetFileStyle(const IGFD_FileStyleFlags& vFlags,
    const std::string& vCriteria,
    ImVec4* vOutColor,
    std::string* vOutIcon,
    ImFont** vOutFont) {
    if (vOutColor) {
        if (!prFilesStyle.empty()) {
            if (prFilesStyle.find(vFlags) != prFilesStyle.end()) {  // found
                if (vFlags & IGFD_FileStyleByContainedInFullName) {
                    // search for vCriteria who are containing the criteria
                    for (const auto& _file : prFilesStyle.at(vFlags)) {
                        if (vCriteria.find(_file.first) != std::string::npos) {
                            if (_file.second.use_count()) {
                                *vOutColor = _file.second->color;
                                if (vOutIcon)
                                    *vOutIcon = _file.second->icon;
                                if (vOutFont)
                                    *vOutFont = _file.second->font;
                                return true;
                            }
                        }
                    }
                } else {
                    if (prFilesStyle.at(vFlags).find(vCriteria) != prFilesStyle.at(vFlags).end()) {  // found
                        *vOutColor = prFilesStyle[vFlags][vCriteria]->color;
                        if (vOutIcon)
                            *vOutIcon = prFilesStyle[vFlags][vCriteria]->icon;
                        if (vOutFont)
                            *vOutFont = prFilesStyle[vFlags][vCriteria]->font;
                        return true;
                    }
                }
            } else {
                // search for flag composition
                for (const auto& _flag : prFilesStyle) {
                    if (_flag.first & vFlags) {
                        if (_flag.first & IGFD_FileStyleByContainedInFullName) {
                            // search for vCriteria who are containing the criteria
                            for (const auto& _file : prFilesStyle.at(_flag.first)) {
                                if (vCriteria.find(_file.first) != std::string::npos) {
                                    if (_file.second.use_count()) {
                                        *vOutColor = _file.second->color;
                                        if (vOutIcon)
                                            *vOutIcon = _file.second->icon;
                                        if (vOutFont)
                                            *vOutFont = _file.second->font;
                                        return true;
                                    }
                                }
                            }
                        } else {
                            if (prFilesStyle.at(_flag.first).find(vCriteria) !=
                                prFilesStyle.at(_flag.first).end()) {  // found
                                *vOutColor = prFilesStyle[_flag.first][vCriteria]->color;
                                if (vOutIcon)
                                    *vOutIcon = prFilesStyle[_flag.first][vCriteria]->icon;
                                if (vOutFont)
                                    *vOutFont = prFilesStyle[_flag.first][vCriteria]->font;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool IGFD::FilterManager::IsCoveredByFilters(const FileInfos& vFileInfos, bool vIsCaseInsensitive) const {
    if (!puDLGFilters.empty() && !prSelectedFilter.empty()) {
        return (prSelectedFilter.exist(vFileInfos, vIsCaseInsensitive) ||
                prSelectedFilter.regexExist(vFileInfos.fileNameExt));
    }

    return false;
}
float IGFD::FilterManager::GetFilterComboBoxWidth() const {

    const auto& combo_width = ImGui::CalcTextSize(prSelectedFilter.title.c_str()).x + ImGui::GetFrameHeight() +
                              ImGui::GetStyle().ItemInnerSpacing.x;
    return ImMax(combo_width, 150.0f);

}
bool IGFD::FilterManager::DrawFilterComboBox(FileDialogInternal& vFileDialogInternal) {
    if (!puDLGFilters.empty()) {
        ImGui::SameLine();
        bool needToApllyNewFilter = false;
        ImGui::PushItemWidth(GetFilterComboBoxWidth());
        if (ImGui::BeginCombo("##Filters", prSelectedFilter.title.c_str(), ImGuiComboFlags_None)) {
            intptr_t i = 0;
            for (const auto& filter : prParsedFilters) {
                const bool item_selected = (filter.title == prSelectedFilter.title);
                ImGui::PushID((void*)(intptr_t)i++);
                if (ImGui::Selectable(filter.title.c_str(), item_selected)) {
                    prSelectedFilter = filter;
                    needToApllyNewFilter = true;
                }
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();
        if (needToApllyNewFilter) {
            vFileDialogInternal.puFileManager.OpenCurrentPath(vFileDialogInternal);
        }
        return needToApllyNewFilter;
    }
    return false;
}
std::string IGFD::FilterManager::ReplaceExtentionWithCurrentFilterIfNeeded(const std::string& vFileName, IGFD_ResultMode vFlag) const {
    auto result = vFileName;
    if (!result.empty()) {
        const auto& current_filter = prSelectedFilter.getFirstFilter();
        if (!current_filter.empty()) {
            Utils::ReplaceString(result, "..", ".");

            // is a regex => no change
            if (current_filter.find("((") != std::string::npos) {
                return result;
            }

            // contain .* => no change
            if (current_filter.find(".*") != std::string::npos) {
                return result;
            }

            switch (vFlag) {
                case IGFD_ResultMode_KeepInputFile: {
                    return vFileName;
                }
                case IGFD_ResultMode_OverwriteFileExt: {
                    const auto& count_dots = Utils::GetCharCountInString(vFileName, '.');
                    const auto& min_dots = ImMin<size_t>(count_dots, prSelectedFilter.count_dots);
                    const auto& lp = Utils::GetLastCharPosWithMinCharCount(vFileName, '.', min_dots);
                    if (lp != std::string::npos) {  // there is a user extention
                        const auto& file_name_without_user_ext = vFileName.substr(0, lp);
                        result = file_name_without_user_ext + current_filter;
                    } else {  // add extention
                        result = vFileName + current_filter;
                    }
                    break;
                }
                case IGFD_ResultMode_AddIfNoFileExt: {
                    const auto& count_dots = Utils::GetCharCountInString(vFileName, '.');
                    const auto& min_dots = ImMin<size_t>(count_dots, prSelectedFilter.count_dots);
                    const auto& lp = Utils::GetLastCharPosWithMinCharCount(vFileName, '.', min_dots);
                    if (lp == std::string::npos ||  // there is no user extention
                        lp == (vFileName.size() -
                                  1U)) {  // or this pos is also the last char => considered like no user extention
                        const auto& file_name_without_user_ext = vFileName.substr(0, lp);
                        result = file_name_without_user_ext + current_filter;
                    }
                    break;
                }
            }

            Utils::ReplaceString(result, "..", ".");
        }
    }
    return result;
}

IGFD::FileManager::FileManager() { puFsRoot = std::string(1u, '/'); }


size_t IGFD::FileManager::GetComposerSize() { return prCurrentPathDecomposition.size(); }
size_t IGFD::FileManager::GetFullFileListSize() { return prFileList.size(); }
size_t IGFD::FileManager::GetFilteredListSize() { return prFilteredFileList.size(); }
size_t IGFD::FileManager::GetPathFilteredListSize() { return prFilteredPathList.size(); }
std::shared_ptr<IGFD::FileInfos> IGFD::FileManager::GetFullFileAt(size_t vIdx) {
    if (vIdx < prFileList.size())
        return prFileList[vIdx];
    return nullptr;
}
std::shared_ptr<IGFD::FileInfos> IGFD::FileManager::GetFilteredFileAt(size_t vIdx) {
    if (vIdx < prFilteredFileList.size())
        return prFilteredFileList[vIdx];
    return nullptr;
}
std::shared_ptr<IGFD::FileInfos> IGFD::FileManager::GetFilteredPathAt(size_t vIdx) {
    if (vIdx < prFilteredPathList.size())
        return prFilteredPathList[vIdx];
    return nullptr;
}
std::vector<std::string>::iterator IGFD::FileManager::GetCurrentPopupComposedPath() {
    return prPopupComposedPath;
}

void IGFD::FilterManager::ClearFilesStyle() { prFilesStyle.clear(); }
void IGFD::FilterManager::SetDefaultFilterIfNotDefined() {
    if (prSelectedFilter.empty() &&                   // no filter selected
        !prParsedFilters.empty()) {                   // filter exist
        prSelectedFilter = *prParsedFilters.begin();  // we take the first filter
    }
}
void IGFD::FileManager::OpenCurrentPath(const FileDialogInternal& vFileDialogInternal) {
    puShowDrives = false;
    ClearComposer();
    ClearFileLists();
    if (puDLGDirectoryMode) {  // directory mode
        SetDefaultFileName(".");
    } else {
        SetDefaultFileName(puDLGDefaultFileName);
    }
    ScanDir(vFileDialogInternal, GetCurrentPath());
}
void IGFD::FileManager::SortFields(const FileDialogInternal& vFileDialogInternal) {
    SortFields(vFileDialogInternal, prFileList, prFilteredFileList);
}
void IGFD::FileManager::SortFields(const FileDialogInternal& vFileDialogInternal,
    std::vector<std::shared_ptr<FileInfos>>& vFileInfosList,
    std::vector<std::shared_ptr<FileInfos>>& vFileInfosFilteredList) {
    if (puSortingField != SortingFieldEnum::FIELD_NONE) {
        puHeaderFileName = tableHeaderFileNameString;
        puHeaderFileType = tableHeaderFileTypeString;
        puHeaderFileSize = tableHeaderFileSizeString;
        puHeaderFileDate = tableHeaderFileDateString;
#ifdef USE_THUMBNAILS
        puHeaderFileThumbnails = tableHeaderFileThumbnailsString;
#endif  // #ifdef USE_THUMBNAILS
    }
    if (puSortingField == SortingFieldEnum::FIELD_FILENAME) {
        if (puSortingDirection[0]) {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileName = tableHeaderAscendingIcon + puHeaderFileName;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    // tofix : this code fail in c:\\Users with the link "All users". got a invalid comparator
                    /*
                    // use code from
                    https://github.com/jackm97/ImDialog/commit/bf40515f5a1de3043e60562dc1a494ee7ecd3571
                    // strict ordering for file/directory types beginning in '.'
                    // common on _IGFD_WIN_ platforms
                    if (a->fileNameExt[0] == '.' && b->fileNameExt[0] != '.')
                        return false;
                    if (a->fileNameExt[0] != '.' && b->fileNameExt[0] == '.')
                        return true;
                    if (a->fileNameExt[0] == '.' && b->fileNameExt[0] == '.')
                    {
                        return (stricmp(a->fileNameExt.c_str(), b->fileNameExt.c_str()) < 0); // sort in insensitive
                    case
                    }
                    */
                    if (a->fileType != b->fileType)
                        return (a->fileType < b->fileType);                                // directories first
                    return (stricmp(a->fileNameExt.c_str(), b->fileNameExt.c_str()) < 0);  // sort in insensitive case
                });
        } else {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileName = tableHeaderDescendingIcon + puHeaderFileName;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    // tofix : this code fail in c:\\Users with the link "All users". got a invalid comparator
                    /*
                    // use code from
                    https://github.com/jackm97/ImDialog/commit/bf40515f5a1de3043e60562dc1a494ee7ecd3571
                    // strict ordering for file/directory types beginning in '.'
                    // common on _IGFD_WIN_ platforms
                    if (a->fileNameExt[0] == '.' && b->fileNameExt[0] != '.')
                        return false;
                    if (a->fileNameExt[0] != '.' && b->fileNameExt[0] == '.')
                        return true;
                    if (a->fileNameExt[0] == '.' && b->fileNameExt[0] == '.')
                    {
                        return (stricmp(a->fileNameExt.c_str(), b->fileNameExt.c_str()) > 0); // sort in insensitive
                    case
                    }
                    */
                    if (a->fileType != b->fileType)
                        return (a->fileType > b->fileType);                                // directories last
                    return (stricmp(a->fileNameExt.c_str(), b->fileNameExt.c_str()) > 0);  // sort in insensitive case
                });
        }
    } else if (puSortingField == SortingFieldEnum::FIELD_TYPE) {
        if (puSortingDirection[1]) {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileType = tableHeaderAscendingIcon + puHeaderFileType;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType < b->fileType);              // directory in first
                    return (a->fileExtLevels[0] < b->fileExtLevels[0]);  // else
                });
        } else {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileType = tableHeaderDescendingIcon + puHeaderFileType;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType > b->fileType);              // directory in last
                    return (a->fileExtLevels[0] > b->fileExtLevels[0]);  // else
                });
        }
    } else if (puSortingField == SortingFieldEnum::FIELD_SIZE) {
        if (puSortingDirection[2]) {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileSize = tableHeaderAscendingIcon + puHeaderFileSize;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType < b->fileType);  // directory in first
                    return (a->fileSize < b->fileSize);      // else
                });
        } else {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileSize = tableHeaderDescendingIcon + puHeaderFileSize;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType > b->fileType);  // directory in last
                    return (a->fileSize > b->fileSize);      // else
                });
        }
    } else if (puSortingField == SortingFieldEnum::FIELD_DATE) {
        if (puSortingDirection[3]) {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileDate = tableHeaderAscendingIcon + puHeaderFileDate;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType < b->fileType);        // directory in first
                    return (a->fileModifDate < b->fileModifDate);  // else
                });
        } else {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileDate = tableHeaderDescendingIcon + puHeaderFileDate;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType > b->fileType);        // directory in last
                    return (a->fileModifDate > b->fileModifDate);  // else
                });
        }
    }
#ifdef USE_THUMBNAILS
    else if (puSortingField == SortingFieldEnum::FIELD_THUMBNAILS) {
        // we will compare thumbnails by :
        // 1) width
        // 2) height

        if (puSortingDirection[4]) {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileThumbnails = tableHeaderAscendingIcon + puHeaderFileThumbnails;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (a->fileType.isDir());  // directory in first
                    if (a->thumbnailInfo.textureWidth == b->thumbnailInfo.textureWidth)
                        return (a->thumbnailInfo.textureHeight < b->thumbnailInfo.textureHeight);
                    return (a->thumbnailInfo.textureWidth < b->thumbnailInfo.textureWidth);
                });
        }

        else {
#ifdef USE_CUSTOM_SORTING_ICON
            puHeaderFileThumbnails = tableHeaderDescendingIcon + puHeaderFileThumbnails;
#endif  // USE_CUSTOM_SORTING_ICON
            std::sort(vFileInfosList.begin(), vFileInfosList.end(),
                [](const std::shared_ptr<FileInfos>& a, const std::shared_ptr<FileInfos>& b) -> bool {
                    if (!a.use_count() || !b.use_count())
                        return false;
                    if (a->fileType != b->fileType)
                        return (!a->fileType.isDir());  // directory in last
                    if (a->thumbnailInfo.textureWidth == b->thumbnailInfo.textureWidth)
                        return (a->thumbnailInfo.textureHeight > b->thumbnailInfo.textureHeight);
                    return (a->thumbnailInfo.textureWidth > b->thumbnailInfo.textureWidth);
                });
        }
    }
#endif  // USE_THUMBNAILS

    ApplyFilteringOnFileList(vFileDialogInternal, vFileInfosList, vFileInfosFilteredList);
}
void IGFD::FileManager::ClearFileLists() {
    prFilteredFileList.clear();
    prFileList.clear();
}
void IGFD::FileManager::ClearPathLists() {
    prFilteredPathList.clear();
    prPathList.clear();
}
void IGFD::FileManager::AddFile(const FileDialogInternal& vFileDialogInternal,
    const std::string& vPath,
    const std::string& vFileName,
    const FileType& vFileType) {
    auto infos = std::make_shared<FileInfos>();

    infos->filePath = vPath;
    infos->fileNameExt = vFileName;
    infos->fileNameExt_optimized = Utils::LowerCaseString(infos->fileNameExt);
    infos->fileType = vFileType;

    if (infos->fileNameExt.empty() ||
        (infos->fileNameExt == "." && !vFileDialogInternal.puFilterManager.puDLGFilters
                                           .empty())) {  // filename empty or filename is the current dir '.' //-V807
        return;
    }

    if (infos->fileNameExt != ".." && (vFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DontShowHiddenFiles) &&
        infos->fileNameExt[0] == '.') {  // dont show hidden files
        if (!vFileDialogInternal.puFilterManager.puDLGFilters.empty() ||
            (vFileDialogInternal.puFilterManager.puDLGFilters.empty() &&
                infos->fileNameExt != ".")) {  // except "." if in directory mode //-V728
            return;
        }
    }

    if (infos->FinalizeFileTypeParsing(vFileDialogInternal.puFilterManager.GetSelectedFilter().count_dots)) {
        if (!vFileDialogInternal.puFilterManager.IsCoveredByFilters(
                *infos.get(), (vFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_CaseInsensitiveExtention) != 0)) {
            return;
        }
    }

    vFileDialogInternal.puFilterManager.prFillFileStyle(infos);

    prCompleteFileInfos(infos);
    prFileList.push_back(infos);
}
void IGFD::FileManager::AddPath(const FileDialogInternal& vFileDialogInternal,const std::string& vPath,const std::string& vFileName,const FileType& vFileType) {
  if (!vFileType.isDir()) return;
  //---------------------------

  auto infos = std::make_shared<FileInfos>();

  infos->filePath = vPath;
  infos->fileNameExt = vFileName;
  infos->fileNameExt_optimized = Utils::LowerCaseString(infos->fileNameExt);
  infos->fileType = vFileType;

  if (infos->fileNameExt.empty() || (infos->fileNameExt == "." && !vFileDialogInternal.puFilterManager.puDLGFilters.empty())) {
    return;
  }

  if (infos->fileNameExt != ".." && (vFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DontShowHiddenFiles) &&
    infos->fileNameExt[0] == '.') {  // dont show hidden files
    if (!vFileDialogInternal.puFilterManager.puDLGFilters.empty() || (vFileDialogInternal.puFilterManager.puDLGFilters.empty() && infos->fileNameExt != ".")) {
      return;
    }
  }

  vFileDialogInternal.puFilterManager.prFillFileStyle(infos);

  prCompleteFileInfos(infos);
  prPathList.push_back(infos);

  //---------------------------
}
void IGFD::FileManager::ScanDir(const FileDialogInternal& vFileDialogInternal, const std::string& vPath) {
    std::string path = vPath;

    if (prCurrentPathDecomposition.empty()) {
        set_current_dir(path);
    }

    if (!prCurrentPathDecomposition.empty()) {

        ClearFileLists();

#ifdef USE_STD_FILESYSTEM
        try {
            const std::filesystem::path fspath(path);
            const auto dir_iter = std::filesystem::directory_iterator(fspath);
            FileType fstype = FileType(
                FileType::ContentType::Directory, std::filesystem::is_symlink(std::filesystem::status(fspath)));
            AddFile(vFileDialogInternal, path, "..", fstype);
            for (const auto& file : dir_iter) {
                FileType fileType;
                if (file.is_symlink()) {
                    fileType.SetSymLink(file.is_symlink());
                    fileType.SetContent(FileType::ContentType::LinkToUnknown);
                }

                if (file.is_directory()) {
                    fileType.SetContent(FileType::ContentType::Directory);
                }  // directory or symlink to directory
                else if (file.is_regular_file()) {
                    fileType.SetContent(FileType::ContentType::File);
                }

                if (fileType.isValid()) {
                    auto fileNameExt = file.path().filename().string();
                    AddFile(vFileDialogInternal, path, fileNameExt, fileType);
                }
            }
        } catch (const std::exception& ex) {
            printf("%s", ex.what());
        }
#else  // dirent
        struct dirent** files = nullptr;
        size_t n = scandir(path.c_str(), &files, nullptr, inAlphaSort);
        if (n && files) {
            size_t i;

            for (i = 0; i < n; i++) {
                struct dirent* ent = files[i];

                FileType fileType;
                switch (ent->d_type) {
                    case DT_DIR: fileType.SetContent(FileType::ContentType::Directory); break;
                    case DT_REG: fileType.SetContent(FileType::ContentType::File); break;
#if defined(_IGFD_UNIX_) || (DT_LNK != DT_UNKNOWN)
                    case DT_LNK:
#endif
                    case DT_UNKNOWN: {
                        struct stat sb = {};
                        auto filePath = path + std::string(1u, '/') + ent->d_name;

                        if (!stat(filePath.c_str(), &sb)) {
                            if (sb.st_mode & S_IFLNK) {
                                fileType.SetSymLink(true);
                                fileType.SetContent(
                                    FileType::ContentType::LinkToUnknown);  // by default if we can't figure out the
                                                                            // target type.
                            }
                            if (sb.st_mode & S_IFREG) {
                                fileType.SetContent(FileType::ContentType::File);
                                break;
                            } else if (sb.st_mode & S_IFDIR) {
                                fileType.SetContent(FileType::ContentType::Directory);
                                break;
                            }
                        }
                        break;
                    }
                    default: break;  // leave it invalid (devices, etc.)
                }

                if (fileType.isValid()) {
                    AddFile(vFileDialogInternal, path, ent->d_name, fileType);
                }
            }

            for (i = 0; i < n; i++) {
                free(files[i]);
            }

            free(files);
        }
#endif  // USE_STD_FILESYSTEM

        SortFields(vFileDialogInternal, prFileList, prFilteredFileList);
    }
}
void IGFD::FileManager::ScanDirForPathSelection(
    const FileDialogInternal& vFileDialogInternal, const std::string& vPath) {
    std::string path = vPath;

    if (!path.empty()) {

        ClearPathLists();

#ifdef USE_STD_FILESYSTEM
        const std::filesystem::path fspath(path);
        const auto dir_iter = std::filesystem::directory_iterator(fspath);
        FileType fstype =
            FileType(FileType::ContentType::Directory, std::filesystem::is_symlink(std::filesystem::status(fspath)));
        AddPath(vFileDialogInternal, path, "..", fstype);
        for (const auto& file : dir_iter) {
            FileType fileType;
            if (file.is_symlink()) {
                fileType.SetSymLink(file.is_symlink());
                fileType.SetContent(FileType::ContentType::LinkToUnknown);
            }
            if (file.is_directory()) {
                fileType.SetContent(FileType::ContentType::Directory);
                auto fileNameExt = file.path().filename().string();
                AddPath(vFileDialogInternal, path, fileNameExt, fileType);
            }
        }
#else  // dirent
        struct dirent** files = nullptr;
        size_t n = scandir(path.c_str(), &files, nullptr, inAlphaSort);
        if (n) {
            size_t i;

            for (i = 0; i < n; i++) {
                struct dirent* ent = files[i];
                struct stat sb = {};
                int result = 0;
                if (ent->d_type == DT_UNKNOWN) {
                    auto filePath = path + std::string(1u, '/') + ent->d_name;

                    result = stat(filePath.c_str(), &sb);
                }

                if (ent->d_type == DT_DIR || (ent->d_type == DT_UNKNOWN && result == 0 && sb.st_mode & S_IFDIR)) {
                    AddPath(vFileDialogInternal, path, ent->d_name, FileType(FileType::ContentType::Directory, false));
                }
            }

            for (i = 0; i < n; i++) {
                free(files[i]);
            }

            free(files);
        }
#endif  // USE_STD_FILESYSTEM

        SortFields(vFileDialogInternal, prPathList, prFilteredPathList);
    }
}
void IGFD::FileManager::OpenPathPopup(
    const FileDialogInternal& vFileDialogInternal, std::vector<std::string>::iterator vPathIter) {
    const auto path = ComposeNewPath(vPathIter);
    ScanDirForPathSelection(vFileDialogInternal, path);
    prPopupComposedPath = vPathIter;
    ImGui::OpenPopup("IGFD_Path_Popup");
}
void IGFD::FileManager::ClearComposer() { prCurrentPathDecomposition.clear(); }
void IGFD::FileManager::ClearAll() {
    ClearComposer();
    ClearFileLists();
    ClearPathLists();
}
void IGFD::FileManager::ApplyFilteringOnFileList(const FileDialogInternal& vFileDialogInternal) {
    ApplyFilteringOnFileList(vFileDialogInternal, prFileList, prFilteredFileList);
}
void IGFD::FileManager::ApplyFilteringOnFileList(const FileDialogInternal& vFileDialogInternal,
    std::vector<std::shared_ptr<FileInfos>>& vFileInfosList,
    std::vector<std::shared_ptr<FileInfos>>& vFileInfosFilteredList) {
    vFileInfosFilteredList.clear();
    for (const auto& file : vFileInfosList) {
        if (!file.use_count())
            continue;
        bool show = true;
        if (!file->SearchForTag(vFileDialogInternal.puSearchManager.puSearchTag))  // if search tag
            show = false;
        if (puDLGDirectoryMode && !file->fileType.isDir())
            show = false;
        if (show)
            vFileInfosFilteredList.push_back(file);
    }
}
void IGFD::FileManager::prCompleteFileInfos(const std::shared_ptr<FileInfos>& vInfos) {
    if (!vInfos.use_count())
        return;

    if (vInfos->fileNameExt != "." && vInfos->fileNameExt != "..") {
        // _stat struct :
        // dev_t     st_dev;     /* ID of device containing file */
        // ino_t     st_ino;     /* inode number */
        // mode_t    st_mode;    /* protection */
        // nlink_t   st_nlink;   /* number of hard links */
        // uid_t     st_uid;     /* user ID of owner */
        // gid_t     st_gid;     /* group ID of owner */
        // dev_t     st_rdev;    /* device ID (if special file) */
        // off_t     st_size;    /* total size, in bytes */
        // blksize_t st_blksize; /* blocksize for file system I/O */
        // blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
        // time_t    st_atime;   /* time of last access - not sure out of ntfs */
        // time_t    st_mtime;   /* time of last modification - not sure out of ntfs */
        // time_t    st_ctime;   /* time of last status change - not sure out of ntfs */

        std::string fpn;

        // FIXME: so the condition is always true?
        if (vInfos->fileType.isFile() || vInfos->fileType.isLinkToUnknown() || vInfos->fileType.isDir())
            fpn = vInfos->filePath + std::string(1u, '/') + vInfos->fileNameExt;

        struct stat statInfos = {};
        char timebuf[100];
        int result = stat(fpn.c_str(), &statInfos);
        if (!result) {
            if (!vInfos->fileType.isDir()) {
                vInfos->fileSize = (size_t)statInfos.st_size;
                vInfos->formatedFileSize = prFormatFileSize(vInfos->fileSize);
            }

            size_t len = 0;
            if (len) {
                vInfos->fileModifDate = std::string(timebuf, len);
            }
        }
    }
}
void IGFD::FileManager::prRemoveFileNameInSelection(const std::string& vFileName) {
    prSelectedFileNames.erase(vFileName);

    if (prSelectedFileNames.size() == 1) {
        snprintf(puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, "%s", vFileName.c_str());
    } else {
        snprintf(puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, "%zu files Selected", prSelectedFileNames.size());
    }
}
void IGFD::FileManager::prAddFileNameInSelection(
    const std::string& vFileName, bool vSetLastSelectionFileName) {
    prSelectedFileNames.emplace(vFileName);

    if (prSelectedFileNames.size() == 1) {
        snprintf(puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, "%s", vFileName.c_str());
    } else {
        snprintf(puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, "%zu files Selected", prSelectedFileNames.size());
    }

    if (vSetLastSelectionFileName)
        prLastSelectedFileName = vFileName;
}
void IGFD::FileManager::set_current_dir(const std::string& vPath) {
    std::string path = vPath;

#ifdef USE_STD_FILESYSTEM
    namespace fs = std::filesystem;
    bool dir_opened = fs::is_directory(vPath);
    if (!dir_opened) {
        path = ".";
        dir_opened = fs::is_directory(vPath);
    }
    if (dir_opened)
#else
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) {
        path = ".";
        dir = opendir(path.c_str());
    }

    if (dir != nullptr)
#endif  // USE_STD_FILESYSTEM
    {
        char real_path[PATH_MAX];
        char* numchar = realpath(path.c_str(), real_path);
        if (numchar != nullptr)
        {
            prCurrentPath = std::move(real_path);
            if (prCurrentPath[prCurrentPath.size() - 1] == '/') {
                prCurrentPath = prCurrentPath.substr(0, prCurrentPath.size() - 1);
            }
            IGFD::Utils::SetBuffer(puInputPathBuffer, MAX_PATH_BUFFER_SIZE, prCurrentPath);
            prCurrentPathDecomposition = IGFD::Utils::SplitStringToVector(prCurrentPath, '/', false);
            prCurrentPathDecomposition.insert(prCurrentPathDecomposition.begin(), std::string(1u, '/'));
            if (!prCurrentPathDecomposition.empty()) {
                puFsRoot = prCurrentPathDecomposition[0];
            }
        }
#ifndef USE_STD_FILESYSTEM
        closedir(dir);
#endif
    }
}
void IGFD::FileManager::SetCurrentPath(const std::string& vCurrentPath) {
    if (vCurrentPath.empty())
        prCurrentPath = ".";
    else
        prCurrentPath = vCurrentPath;
}
void IGFD::FileManager::SetDefaultFileName(const std::string& vFileName) {
    puDLGDefaultFileName = vFileName;
    IGFD::Utils::SetBuffer(puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, vFileName);
}
void IGFD::FileManager::SelectFileName(
    const FileDialogInternal& vFileDialogInternal, const std::shared_ptr<FileInfos>& vInfos) {
    if (!vInfos.use_count())
        return;

    if (ImGui::IsKeyDown(ImGuiMod_Ctrl)) {
        if (puDLGcountSelectionMax == 0)  // infinite selection
        {
            if (prSelectedFileNames.find(vInfos->fileNameExt) == prSelectedFileNames.end())  // not found +> add
            {
                prAddFileNameInSelection(vInfos->fileNameExt, true);
            } else {  // found +> remove
                prRemoveFileNameInSelection(vInfos->fileNameExt);
            }
        } else  // selection limited by size
        {
            if (prSelectedFileNames.size() < puDLGcountSelectionMax) {
                if (prSelectedFileNames.find(vInfos->fileNameExt) == prSelectedFileNames.end())  // not found +> add
                {
                    prAddFileNameInSelection(vInfos->fileNameExt, true);
                } else {  // found +> remove
                    prRemoveFileNameInSelection(vInfos->fileNameExt);
                }
            }
        }
    } else if (ImGui::IsKeyDown(ImGuiMod_Shift)) {
        if (puDLGcountSelectionMax != 1) {
            prSelectedFileNames.clear();
            // we will iterate filelist and get the last selection after the start selection
            bool startMultiSelection = false;
            std::string fileNameToSelect = vInfos->fileNameExt;
            std::string savedLastSelectedFileName;  // for invert selection mode
            for (const auto& file : prFileList) {
                if (!file.use_count())
                    continue;

                bool canTake = true;
                if (!file->SearchForTag(vFileDialogInternal.puSearchManager.puSearchTag))
                    canTake = false;
                if (canTake)  // if not filtered, we will take files who are filtered by the dialog
                {
                    if (file->fileNameExt == prLastSelectedFileName) {
                        startMultiSelection = true;
                        prAddFileNameInSelection(prLastSelectedFileName, false);
                    } else if (startMultiSelection) {
                        if (puDLGcountSelectionMax == 0)  // infinite selection
                        {
                            prAddFileNameInSelection(file->fileNameExt, false);
                        } else {  // selection limited by size
                            if (prSelectedFileNames.size() < puDLGcountSelectionMax) {
                                prAddFileNameInSelection(file->fileNameExt, false);
                            } else {
                                startMultiSelection = false;
                                if (!savedLastSelectedFileName.empty())
                                    prLastSelectedFileName = savedLastSelectedFileName;
                                break;
                            }
                        }
                    }

                    if (file->fileNameExt == fileNameToSelect) {
                        if (!startMultiSelection)  // we are before the last Selected FileName, so we must inverse
                        {
                            savedLastSelectedFileName = prLastSelectedFileName;
                            prLastSelectedFileName = fileNameToSelect;
                            fileNameToSelect = savedLastSelectedFileName;
                            startMultiSelection = true;
                            prAddFileNameInSelection(prLastSelectedFileName, false);
                        } else {
                            startMultiSelection = false;
                            if (!savedLastSelectedFileName.empty())
                                prLastSelectedFileName = savedLastSelectedFileName;
                            break;
                        }
                    }
                }
            }
        }
    } else {
        prSelectedFileNames.clear();
        IGFD::Utils::ResetBuffer(puFileNameBuffer);
        prAddFileNameInSelection(vInfos->fileNameExt, true);
    }
}
void IGFD::FileManager::DrawDirectoryCreation(const FileDialogInternal& vFileDialogInternal) {
    if (vFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableCreateDirectoryButton)
        return;

    if (ImGui::Button(createDirButtonString)) {
        if (!prCreateDirectoryMode) {
            prCreateDirectoryMode = true;
            IGFD::Utils::ResetBuffer(puDirectoryNameBuffer);
        }
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(buttonCreateDirString);

    if (prCreateDirectoryMode) {
        ImGui::SameLine();

        ImGui::PushItemWidth(100.0f);
        ImGui::InputText("##DirectoryFileName", puDirectoryNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER);
        ImGui::PopItemWidth();

        ImGui::SameLine();

        if (ImGui::Button(okButtonString)) {
            std::string newDir = std::string(puDirectoryNameBuffer);
            if (create_dir(newDir)) {
                SetCurrentPath(prCurrentPath + std::string(1u, '/') + newDir);
                OpenCurrentPath(vFileDialogInternal);
            }

            prCreateDirectoryMode = false;
        }

        ImGui::SameLine();

        if (ImGui::Button(cancelButtonString)) {
            prCreateDirectoryMode = false;
        }
    }

    ImGui::SameLine();
}
void IGFD::FileManager::DrawPathComposer(const FileDialogInternal& vFileDialogInternal) {
    if (ImGui::Button(resetButtonString)) {
        SetCurrentPath(".");
        OpenCurrentPath(vFileDialogInternal);
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(buttonResetPathString);

    ImGui::SameLine();

    if (ImGui::Button(editPathButtonString)) {
        puInputPathActivated = !puInputPathActivated;
        if (puInputPathActivated) {
            auto endIt = prCurrentPathDecomposition.end();
            prCurrentPath = ComposeNewPath(--endIt);
            IGFD::Utils::SetBuffer(puInputPathBuffer, MAX_PATH_BUFFER_SIZE, prCurrentPath);
        }
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(buttonEditPathString);

    ImGui::SameLine();

    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

    // show current path
    if (!prCurrentPathDecomposition.empty()) {
        ImGui::SameLine();

        if (puInputPathActivated) {
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::InputText("##pathedition", puInputPathBuffer, MAX_PATH_BUFFER_SIZE);
            ImGui::PopItemWidth();
        } else {
            int _id = 0;
            for (auto itPathDecomp = prCurrentPathDecomposition.begin();
                 itPathDecomp != prCurrentPathDecomposition.end(); ++itPathDecomp) {
                if (itPathDecomp != prCurrentPathDecomposition.begin()) {
                    ImGui::SameLine(0, 2);
                    if (!(vFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableQuickPathSelection)) {

                        const char* sep = "/";
                        if (itPathDecomp != prCurrentPathDecomposition.begin() + 1)
                        {
                            ImGui::PushID(_id++);
                            bool click = ImGui::Button(sep);
                            ImGui::PopID();


                            ImGui::SameLine(0, 2);


                            if (click) {
                                OpenPathPopup(vFileDialogInternal, itPathDecomp - 1);
                            } else if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                                SetCurrentPath(itPathDecomp - 1);
                                break;
                            }
                        }
                    }
                }

                ImGui::PushID(_id++);
                bool click = ImGui::Button((*itPathDecomp).c_str());
                ImGui::PopID();
                if (click) {
                    prCurrentPath = ComposeNewPath(itPathDecomp);
                    puPathClicked = true;
                    break;
                } else if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {  // activate input for path
                    SetCurrentPath(itPathDecomp);
                    break;
                }
            }
        }
    }
}
void IGFD::FileManager::SetCurrentPath(std::vector<std::string>::iterator vPathIter) {
    prCurrentPath = ComposeNewPath(vPathIter);
    IGFD::Utils::SetBuffer(puInputPathBuffer, MAX_PATH_BUFFER_SIZE, prCurrentPath);
    puInputPathActivated = true;
}

bool IGFD::FileManager::create_dir(const std::string& vPath) {
  bool res = false;
  //---------------------------

  if (!vPath.empty()) {
    std::string path = prCurrentPath + std::string(1u, '/') + vPath;
    res = IGFD::Utils::CreateDirectoryIfNotExist(path);
  }

  //---------------------------
  return res;
}
bool IGFD::FileManager::IsFileExist(const std::string& vFile) {
    std::ifstream docFile(vFile, std::ios::in);
    if (docFile.is_open()) {
        docFile.close();
        return true;
    }
    return false;
}
bool IGFD::FileManager::SetPathOnParentDirectoryIfAny() {
    if (prCurrentPathDecomposition.size() > 1) {
        prCurrentPath = ComposeNewPath(prCurrentPathDecomposition.end() - 2);
        return true;
    }
    return false;
}
bool IGFD::FileManager::SelectDirectory(const std::shared_ptr<FileInfos>& vInfos) {
    if (!vInfos.use_count())
        return false;

    bool pathClick = false;

    if (vInfos->fileNameExt == "..") {
        pathClick = SetPathOnParentDirectoryIfAny();
    } else {
        std::string newPath;

        if (puShowDrives) {
            newPath = vInfos->fileNameExt + std::string(1u, '/');
        } else {
#ifdef __linux__
            if (puFsRoot == prCurrentPath)
                newPath = prCurrentPath + vInfos->fileNameExt;
            else
#endif  // __linux__
                newPath = prCurrentPath + std::string(1u, '/') + vInfos->fileNameExt;
        }

        if (IGFD::Utils::IsDirectoryCanBeOpened(newPath)) {
            if (puShowDrives) {
                prCurrentPath = vInfos->fileNameExt;
                puFsRoot = prCurrentPath;
            } else {
                prCurrentPath = newPath;  //-V820
            }
            pathClick = true;
        }
    }

    return pathClick;
}
bool IGFD::FileManager::IsFilteredListEmpty() { return prFilteredFileList.empty(); }
bool IGFD::FileManager::IsPathFilteredListEmpty() { return prFilteredPathList.empty(); }
bool IGFD::FileManager::IsFileNameSelected(const std::string& vFileName) {
    return prSelectedFileNames.find(vFileName) != prSelectedFileNames.end();
}
bool IGFD::FileManager::IsFileListEmpty() { return prFileList.empty(); }
bool IGFD::FileManager::IsPathListEmpty() { return prPathList.empty(); }
bool IGFD::FileManager::GetDrives() {
    auto drives = IGFD::Utils::GetDrivesList();
    if (!drives.empty()) {
        prCurrentPath.clear();
        prCurrentPathDecomposition.clear();
        ClearFileLists();
        for (auto& drive : drives) {
            auto info = std::make_shared<FileInfos>();
            info->fileNameExt = drive;
            info->fileNameExt_optimized = Utils::LowerCaseString(drive);
            info->fileType.SetContent(FileType::ContentType::Directory);

            if (!info->fileNameExt.empty()) {
                prFileList.push_back(info);
            }
        }
        puShowDrives = true;
        return true;
    }
    return false;
}
bool IGFD::FileManager::IsComposerEmpty() { return prCurrentPathDecomposition.empty(); }

std::string IGFD::FileManager::GetBack() {
  return prCurrentPathDecomposition.back();
}
std::string IGFD::FileManager::prRoundNumber(double vvalue, int n) {
    std::stringstream tmp;
    tmp << std::setprecision(n) << std::fixed << vvalue;
    return tmp.str();
}
std::string IGFD::FileManager::prFormatFileSize(size_t vByteSize) {
    if (vByteSize != 0) {
        static double lo = 1024.0;
        static double ko = 1024.0 * 1024.0;
        static double mo = 1024.0 * 1024.0 * 1024.0;

        auto v = (double)vByteSize;

        if (v < lo)
            return prRoundNumber(v, 0) + " " + fileSizeBytes;  // octet
        else if (v < ko)
            return prRoundNumber(v / lo, 2) + " " + fileSizeKiloBytes;  // ko
        else if (v < mo)
            return prRoundNumber(v / ko, 2) + " " + fileSizeMegaBytes;  // Mo
        else
            return prRoundNumber(v / mo, 2) + " " + fileSizeGigaBytes;  // Go
    }

    return "";
}
std::string IGFD::FileManager::GetResultingPath() {
    std::string path = prCurrentPath;
    if (puDLGDirectoryMode) {  // if directory mode
        std::string selectedDirectory = puFileNameBuffer;
        if (!selectedDirectory.empty() && selectedDirectory != ".") {
            path += std::string(1u, '/') + selectedDirectory;
        }
    }
    return path;
}
std::string IGFD::FileManager::GetResultingFileName(
    FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag) {
    if (!puDLGDirectoryMode) {  // if not directory mode
        const auto& filename = std::string(puFileNameBuffer);
        return vFileDialogInternal.puFilterManager.ReplaceExtentionWithCurrentFilterIfNeeded(filename, vFlag);
    }
    return "";  // directory mode
}
std::string IGFD::FileManager::GetResultingFilePathName(
    FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag) {
    auto result = GetResultingPath();
    const auto& filename = GetResultingFileName(vFileDialogInternal, vFlag);
    if (!filename.empty()) {
#ifdef _IGFD_UNIX_
        if (puFsRoot != result)
#endif  // _IGFD_UNIX_
        {
            result += std::string(1u, '/');
        }
        result += filename;
    }

    return result;
}
std::string IGFD::FileManager::ComposeNewPath(std::vector<std::string>::iterator vIter) {
    std::string res;

    while (true) {
        if (!res.empty()) {
            if (*vIter == puFsRoot)
                res = *vIter + res;
            else
                res = *vIter + '/' + res;
        } else
            res = *vIter;

        if (vIter == prCurrentPathDecomposition.begin()) {
            if (res[0] != '/')
                res = '/' + res;
            break;
        }

        --vIter;
    }

    return res;
}
std::string IGFD::FileManager::GetCurrentPath() {
    if (prCurrentPath.empty())
        prCurrentPath = ".";
    return prCurrentPath;
}

std::map<std::string, std::string> IGFD::FileManager::GetResultingSelection(
    FileDialogInternal& vFileDialogInternal, IGFD_ResultMode vFlag) {
    std::map<std::string, std::string> res;
    for (const auto& selectedFileName : prSelectedFileNames) {
        auto result = GetResultingPath();
#ifdef _IGFD_UNIX_
        if (puFsRoot != result)
#endif  // _IGFD_UNIX_
        {
            result += std::string(1u, '/');
        }

        result +=
            vFileDialogInternal.puFilterManager.ReplaceExtentionWithCurrentFilterIfNeeded(selectedFileName, vFlag);
        res[selectedFileName] = result;
    }
    return res;
}

//File type
IGFD::FileType::FileType() = default;
IGFD::FileType::FileType(const ContentType& vContentType, const bool& vIsSymlink): m_Content(vContentType), m_Symlink(vIsSymlink) {}
void IGFD::FileType::SetContent(const ContentType& vContentType) { m_Content = vContentType; }
void IGFD::FileType::SetSymLink(const bool& vIsSymlink) { m_Symlink = vIsSymlink; }
bool IGFD::FileType::isValid() const { return m_Content != ContentType::Invalid; }
bool IGFD::FileType::isDir() const { return m_Content == ContentType::Directory; }
bool IGFD::FileType::isFile() const { return m_Content == ContentType::File; }
bool IGFD::FileType::isLinkToUnknown() const { return m_Content == ContentType::LinkToUnknown; }
bool IGFD::FileType::isSymLink() const { return m_Symlink; }
bool IGFD::FileType::operator==(const FileType& rhs) const { return m_Content == rhs.m_Content; }
bool IGFD::FileType::operator!=(const FileType& rhs) const { return m_Content != rhs.m_Content; }
bool IGFD::FileType::operator<(const FileType& rhs) const { return m_Content < rhs.m_Content; }
bool IGFD::FileType::operator>(const FileType& rhs) const { return m_Content > rhs.m_Content; }

//File dialog internal
void IGFD::FileDialogInternal::NewFrame() {
    puCanWeContinue = true;  // reset flag for possibily validate the dialog
    puIsOk = false;          // reset dialog result
    puFileManager.puDrivesClicked = false;
    puFileManager.puPathClicked = false;

    puNeedToExitDialog = false;

#ifdef USE_DIALOG_EXIT_WITH_KEY
    if (ImGui::IsKeyPressed(IGFD_EXIT_KEY)) {
        // we do that here with the data's defined at the last frame
        // because escape key can quit input activation and at the end of the frame all flag will be false
        // so we will detect nothing
        if (!(puFileManager.puInputPathActivated || puSearchManager.puSearchInputIsActive || puFileInputIsActive ||
                puFileListViewIsActive)) {
            puNeedToExitDialog = true;  // need to quit dialog
        }
    } else
#endif
    {
        puSearchManager.puSearchInputIsActive = false;
        puFileInputIsActive = false;
        puFileListViewIsActive = false;
    }
}
void IGFD::FileDialogInternal::EndFrame() {
    // directory change
    if (puFileManager.puPathClicked) {
        puFileManager.OpenCurrentPath(*this);
    }

    if (puFileManager.puDrivesClicked) {
        if (puFileManager.GetDrives()) {
            puFileManager.ApplyFilteringOnFileList(*this);
        }
    }

    if (puFileManager.puInputPathActivated) {
        auto gio = ImGui::GetIO();
        if (ImGui::IsKeyReleased(ImGuiKey_Enter)) {
            puFileManager.SetCurrentPath(std::string(puFileManager.puInputPathBuffer));
            puFileManager.OpenCurrentPath(*this);
            puFileManager.puInputPathActivated = false;
        }
        if (ImGui::IsKeyReleased(ImGuiKey_Escape)) {
            puFileManager.puInputPathActivated = false;
        }
    }
}
void IGFD::FileDialogInternal::ResetForNewDialog() {}





IGFD::ThumbnailFeature::ThumbnailFeature() {
#ifdef USE_THUMBNAILS
    prDisplayMode = DisplayModeEnum::FILE_LIST;
#endif
}
IGFD::ThumbnailFeature::~ThumbnailFeature() = default;
void IGFD::ThumbnailFeature::NewThumbnailFrame(FileDialogInternal& /*vFileDialogInternal*/) {
#ifdef USE_THUMBNAILS
    prStartThumbnailFileDatasExtraction();
#endif
}
void IGFD::ThumbnailFeature::EndThumbnailFrame(FileDialogInternal& vFileDialogInternal) {
#ifdef USE_THUMBNAILS
    prClearThumbnails(vFileDialogInternal);
#else
    (void)vFileDialogInternal;
#endif
}
void IGFD::ThumbnailFeature::QuitThumbnailFrame(FileDialogInternal& vFileDialogInternal) {
#ifdef USE_THUMBNAILS
    prStopThumbnailFileDatasExtraction();
    prClearThumbnails(vFileDialogInternal);
#else
    (void)vFileDialogInternal;
#endif
}
IGFD::BookMarkFeature::BookMarkFeature() {
#ifdef USE_BOOKMARK
    prBookmarkWidth = defaultBookmarkPaneWith;
#endif  // USE_BOOKMARK
}
IGFD::KeyExplorerFeature::KeyExplorerFeature() = default;




//Truc
ImDialog::FileDialog() : BookMarkFeature(), KeyExplorerFeature(), ThumbnailFeature() {}
ImDialog::~FileDialog() = default;

void ImDialog::OpenDialog(const std::string& vKey,
    const std::string& vTitle,
    const char* vFilters,
    const std::string& vPath,
    const std::string& vFileName,
    const int& vCountSelectionMax,
    UserDatas vUserDatas,
    ImGuiFileDialogFlags vFlags) {
    if (prFileDialogInternal.puShowDialog)  // if already opened, quit
        return;

    prFileDialogInternal.ResetForNewDialog();

    prFileDialogInternal.puDLGkey = vKey;
    prFileDialogInternal.puDLGtitle = vTitle;
    prFileDialogInternal.puDLGuserDatas = vUserDatas;
    prFileDialogInternal.puDLGflags = vFlags;
    prFileDialogInternal.puDLGoptionsPane = nullptr;
    prFileDialogInternal.puDLGoptionsPaneWidth = 0.0f;

    prFileDialogInternal.puFilterManager.puDLGdefaultExt.clear();
    prFileDialogInternal.puFilterManager.ParseFilters(vFilters);

    prFileDialogInternal.puFileManager.puDLGDirectoryMode = (vFilters == nullptr);
    if (vPath.empty())
        prFileDialogInternal.puFileManager.puDLGpath = prFileDialogInternal.puFileManager.GetCurrentPath();
    else
        prFileDialogInternal.puFileManager.puDLGpath = vPath;
    prFileDialogInternal.puFileManager.SetCurrentPath(vPath);
    prFileDialogInternal.puFileManager.puDLGcountSelectionMax = (size_t)vCountSelectionMax;
    prFileDialogInternal.puFileManager.SetDefaultFileName(vFileName);

    prFileDialogInternal.puFileManager.ClearAll();

    prFileDialogInternal.puShowDialog = true;  // open dialog
}
void ImDialog::OpenDialog(const std::string& vKey,
    const std::string& vTitle,
    const char* vFilters,
    const std::string& vFilePathName,
    const int& vCountSelectionMax,
    UserDatas vUserDatas,
    ImGuiFileDialogFlags vFlags) {
    if (prFileDialogInternal.puShowDialog)  // if already opened, quit
        return;

    prFileDialogInternal.ResetForNewDialog();

    prFileDialogInternal.puDLGkey = vKey;
    prFileDialogInternal.puDLGtitle = vTitle;
    prFileDialogInternal.puDLGoptionsPane = nullptr;
    prFileDialogInternal.puDLGoptionsPaneWidth = 0.0f;
    prFileDialogInternal.puDLGuserDatas = vUserDatas;
    prFileDialogInternal.puDLGflags = vFlags;

    auto ps = IGFD::Utils::ParsePathFileName(vFilePathName);
    if (ps.isOk) {
        prFileDialogInternal.puFileManager.puDLGpath = ps.path;
        prFileDialogInternal.puFileManager.SetDefaultFileName(ps.name);
        prFileDialogInternal.puFilterManager.puDLGdefaultExt = "." + ps.ext;
    } else {
        prFileDialogInternal.puFileManager.puDLGpath = prFileDialogInternal.puFileManager.GetCurrentPath();
        prFileDialogInternal.puFileManager.SetDefaultFileName("");
        prFileDialogInternal.puFilterManager.puDLGdefaultExt.clear();
    }

    prFileDialogInternal.puFilterManager.ParseFilters(vFilters);
    prFileDialogInternal.puFilterManager.SetSelectedFilterWithExt(prFileDialogInternal.puFilterManager.puDLGdefaultExt);

    prFileDialogInternal.puFileManager.SetCurrentPath(prFileDialogInternal.puFileManager.puDLGpath);

    prFileDialogInternal.puFileManager.puDLGDirectoryMode = (vFilters == nullptr);
    prFileDialogInternal.puFileManager.puDLGcountSelectionMax = vCountSelectionMax;  //-V101

    prFileDialogInternal.puFileManager.ClearAll();

    prFileDialogInternal.puShowDialog = true;
}
void ImDialog::OpenDialogWithPane(const std::string& vKey,
    const std::string& vTitle,
    const char* vFilters,
    const std::string& vPath,
    const std::string& vFileName,
    const PaneFun& vSidePane,
    const float& vSidePaneWidth,
    const int& vCountSelectionMax,
    UserDatas vUserDatas,
    ImGuiFileDialogFlags vFlags) {
    if (prFileDialogInternal.puShowDialog)  // if already opened, quit
        return;

    prFileDialogInternal.ResetForNewDialog();

    prFileDialogInternal.puDLGkey = vKey;
    prFileDialogInternal.puDLGtitle = vTitle;
    prFileDialogInternal.puDLGuserDatas = vUserDatas;
    prFileDialogInternal.puDLGflags = vFlags;

    prFileDialogInternal.puDLGoptionsPane = vSidePane;
    if (prFileDialogInternal.puDLGoptionsPane != nullptr) {
        prFileDialogInternal.puDLGoptionsPaneWidth = vSidePaneWidth;
    } else {
        prFileDialogInternal.puDLGoptionsPaneWidth = 0.0f;
    }

    prFileDialogInternal.puFilterManager.puDLGdefaultExt.clear();
    prFileDialogInternal.puFilterManager.ParseFilters(vFilters);

    prFileDialogInternal.puFileManager.puDLGcountSelectionMax = (size_t)vCountSelectionMax;
    prFileDialogInternal.puFileManager.puDLGDirectoryMode = (vFilters == nullptr);
    if (vPath.empty())
        prFileDialogInternal.puFileManager.puDLGpath = prFileDialogInternal.puFileManager.GetCurrentPath();
    else
        prFileDialogInternal.puFileManager.puDLGpath = vPath;

    prFileDialogInternal.puFileManager.SetCurrentPath(prFileDialogInternal.puFileManager.puDLGpath);

    prFileDialogInternal.puFileManager.SetDefaultFileName(vFileName);

    prFileDialogInternal.puFileManager.ClearAll();

    prFileDialogInternal.puShowDialog = true;  // open dialog
}
void ImDialog::OpenDialogWithPane(const std::string& vKey,
    const std::string& vTitle,
    const char* vFilters,
    const std::string& vFilePathName,
    const PaneFun& vSidePane,
    const float& vSidePaneWidth,
    const int& vCountSelectionMax,
    UserDatas vUserDatas,
    ImGuiFileDialogFlags vFlags) {
    if (prFileDialogInternal.puShowDialog)  // if already opened, quit
        return;

    prFileDialogInternal.ResetForNewDialog();

    prFileDialogInternal.puDLGkey = vKey;
    prFileDialogInternal.puDLGtitle = vTitle;

    prFileDialogInternal.puDLGoptionsPane = vSidePane;
    if (prFileDialogInternal.puDLGoptionsPane != nullptr) {
        prFileDialogInternal.puDLGoptionsPaneWidth = vSidePaneWidth;
    } else {
        prFileDialogInternal.puDLGoptionsPaneWidth = 0.0f;
    }
    prFileDialogInternal.puDLGuserDatas = vUserDatas;
    prFileDialogInternal.puDLGflags = vFlags;

    auto ps = IGFD::Utils::ParsePathFileName(vFilePathName);
    if (ps.isOk) {
        prFileDialogInternal.puFileManager.puDLGpath = ps.path;
        prFileDialogInternal.puFileManager.SetDefaultFileName(vFilePathName);
        prFileDialogInternal.puFilterManager.puDLGdefaultExt = "." + ps.ext;
    } else {
        prFileDialogInternal.puFileManager.puDLGpath = prFileDialogInternal.puFileManager.GetCurrentPath();
        prFileDialogInternal.puFileManager.SetDefaultFileName("");
        prFileDialogInternal.puFilterManager.puDLGdefaultExt.clear();
    }

    prFileDialogInternal.puFileManager.SetCurrentPath(prFileDialogInternal.puFileManager.puDLGpath);

    prFileDialogInternal.puFileManager.puDLGcountSelectionMax = vCountSelectionMax;  //-V101
    prFileDialogInternal.puFileManager.puDLGDirectoryMode = (vFilters == nullptr);
    prFileDialogInternal.puFilterManager.ParseFilters(vFilters);
    prFileDialogInternal.puFilterManager.SetSelectedFilterWithExt(prFileDialogInternal.puFilterManager.puDLGdefaultExt);

    prFileDialogInternal.puFileManager.ClearAll();

    prFileDialogInternal.puShowDialog = true;
}
void ImDialog::NewFrame() {
    prFileDialogInternal.NewFrame();
    NewThumbnailFrame(prFileDialogInternal);
}
void ImDialog::EndFrame() {
    EndThumbnailFrame(prFileDialogInternal);
    prFileDialogInternal.EndFrame();
}
void ImDialog::QuitFrame() { QuitThumbnailFrame(prFileDialogInternal); }
void ImDialog::prDrawHeader() {


    prFileDialogInternal.puFileManager.DrawDirectoryCreation(prFileDialogInternal);

    if (

        !(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableCreateDirectoryButton)) {
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine();
    }
    prFileDialogInternal.puFileManager.DrawPathComposer(prFileDialogInternal);


    prFileDialogInternal.puSearchManager.DrawSearchBar(prFileDialogInternal);
}
void ImDialog::prDrawContent() {
    ImVec2 size = ImGui::GetContentRegionAvail() - ImVec2(0.0f, prFileDialogInternal.puFooterHeight);

#ifdef USE_BOOKMARK
    if (!(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableBookmarkMode)) {
        if (prBookmarkPaneShown) {
            // size.x -= prBookmarkWidth;
            float otherWidth = size.x - prBookmarkWidth;
            ImGui::PushID("##splitterbookmark");
            IGFD::Utils::ImSplitter(true, 4.0f, &prBookmarkWidth, &otherWidth, 10.0f,
                10.0f + prFileDialogInternal.puDLGoptionsPaneWidth, size.y);
            ImGui::PopID();
            size.x -= otherWidth;
            prDrawBookmarkPane(prFileDialogInternal, size);
            ImGui::SameLine();
        }
    }
#endif  // USE_BOOKMARK

    size.x = ImGui::GetContentRegionAvail().x - prFileDialogInternal.puDLGoptionsPaneWidth;

    if (prFileDialogInternal.puDLGoptionsPane) {
        ImGui::PushID("##splittersidepane");
        IGFD::Utils::ImSplitter(true, 4.0f, &size.x, &prFileDialogInternal.puDLGoptionsPaneWidth, 10.0f, 10.0f, size.y);
        ImGui::PopID();
    }

#ifdef USE_THUMBNAILS
    if (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableThumbnailMode) {
        prDrawFileListView(size);
    } else {
        switch (prDisplayMode) {
            case DisplayModeEnum::FILE_LIST: prDrawFileListView(size); break;
            case DisplayModeEnum::THUMBNAILS_LIST: prDrawThumbnailsListView(size); break;
            case DisplayModeEnum::THUMBNAILS_GRID: prDrawThumbnailsGridView(size);
        }
    }
#else   // USE_THUMBNAILS
    prDrawFileListView(size);
#endif  // USE_THUMBNAILS

    if (prFileDialogInternal.puDLGoptionsPane) {
        prDrawSidePane(size.y);
    }

    if (!(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableQuickPathSelection)) {
        DisplayPathPopup(size);
    }
}
void ImDialog::DisplayPathPopup(ImVec2 vSize) {
    ImVec2 size = ImVec2(vSize.x * 0.5f, vSize.y * 0.5f);
    if (ImGui::BeginPopup("IGFD_Path_Popup")) {
        auto& fdi = prFileDialogInternal.puFileManager;

        ImGui::PushID(this);

        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg |
                                       ImGuiTableFlags_Hideable | ImGuiTableFlags_ScrollY |
                                       ImGuiTableFlags_NoHostExtendY;
        auto listViewID = ImGui::GetID("##FileDialog_pathTable");
        if (ImGui::BeginTableEx("##FileDialog_pathTable", listViewID, 1, flags, size, 0.0f))  //-V112
        {
            ImGui::TableSetupScrollFreeze(0, 1);  // Make header always visible
            ImGui::TableSetupColumn(tableHeaderFileNameString,
                ImGuiTableColumnFlags_WidthStretch |
                    (defaultSortOrderFilename ? ImGuiTableColumnFlags_PreferSortAscending
                                              : ImGuiTableColumnFlags_PreferSortDescending),
                -1, 0);

            ImGui::TableHeadersRow();

            if (!fdi.IsPathFilteredListEmpty()) {
                std::string _str;
                ImFont* _font = nullptr;
                bool _showColor = false;

                prPathListClipper.Begin((int)fdi.GetPathFilteredListSize(), ImGui::GetTextLineHeightWithSpacing());
                while (prPathListClipper.Step()) {
                    for (int i = prPathListClipper.DisplayStart; i < prPathListClipper.DisplayEnd; i++) {
                        if (i < 0)
                            continue;

                        auto infos = fdi.GetFilteredPathAt((size_t)i);
                        if (!infos.use_count())
                            continue;

                        prBeginFileColorIconStyle(infos, _showColor, _str, &_font);

                        bool selected = fdi.IsFileNameSelected(infos->fileNameExt);  // found

                        ImGui::TableNextRow();

                        if (ImGui::TableNextColumn())  // file name
                        {
                            if (ImGui::Selectable(infos->fileNameExt.c_str(), &selected,
                                    ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_SpanAvailWidth)) {
                                fdi.SetCurrentPath(fdi.ComposeNewPath(fdi.GetCurrentPopupComposedPath()));
                                fdi.puPathClicked = fdi.SelectDirectory(infos);
                                ImGui::CloseCurrentPopup();
                            }
                        }

                        prEndFileColorIconStyle(_showColor, _font);
                    }
                }
                prPathListClipper.End();
            }

            ImGui::EndTable();
        }

        ImGui::PopID();

        ImGui::EndPopup();
    }
}
void ImDialog::prSelectableItem(
    int vidx, std::shared_ptr<FileInfos> vInfos, bool vSelected, const char* vFmt, ...) {
    if (!vInfos.use_count())
        return;

    auto& fdi = prFileDialogInternal.puFileManager;

    static ImGuiSelectableFlags selectableFlags = ImGuiSelectableFlags_AllowDoubleClick |
                                                  ImGuiSelectableFlags_SpanAllColumns |
                                                  ImGuiSelectableFlags_SpanAvailWidth;

    va_list args;
    va_start(args, vFmt);
    vsnprintf(fdi.puVariadicBuffer, MAX_FILE_DIALOG_NAME_BUFFER, vFmt, args);
    va_end(args);

    float h = 0.0f;
#ifdef USE_THUMBNAILS
    if (prDisplayMode == DisplayModeEnum::THUMBNAILS_LIST &&
        !(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_DisableThumbnailMode)) {
        h = DisplayMode_ThumbailsList_ImageHeight;
    }
#endif  // USE_THUMBNAILS
#ifdef USE_EXPLORATION_BY_KEYS
    bool flashed = prBeginFlashItem((size_t)vidx);
    bool res = prFlashableSelectable(fdi.puVariadicBuffer, vSelected, selectableFlags, flashed, ImVec2(-1.0f, h));
    if (flashed)
        prEndFlashItem();
#else   // USE_EXPLORATION_BY_KEYS
    (void)vidx;  // remove a warnings ofr unused var

    bool res = ImGui::Selectable(fdi.puVariadicBuffer, vSelected, selectableFlags, ImVec2(-1.0f, h));
#endif  // USE_EXPLORATION_BY_KEYS
    if (res) {
        if (vInfos->fileType.isDir()) {
            // nav system, selectable cause open directory or select directory
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard) {
                // little fix for get back the mouse behavior in nav system
                if (ImGui::IsMouseDoubleClicked(0))  // 0 -> left mouse button double click
                {
                    fdi.puPathClicked = fdi.SelectDirectory(vInfos);
                } else if (fdi.puDLGDirectoryMode)  // directory chooser
                {
                    fdi.SelectFileName(prFileDialogInternal, vInfos);
                } else {
                    fdi.puPathClicked = fdi.SelectDirectory(vInfos);
                }
            } else  // no nav system => classic behavior
            {
                if (ImGui::IsMouseDoubleClicked(0))  // 0 -> left mouse button double click
                {
                    fdi.puPathClicked = fdi.SelectDirectory(vInfos);
                } else if (fdi.puDLGDirectoryMode)  // directory chooser
                {
                    fdi.SelectFileName(prFileDialogInternal, vInfos);
                }
            }
        } else {
            fdi.SelectFileName(prFileDialogInternal, vInfos);

            if (ImGui::IsMouseDoubleClicked(0)) {
                prFileDialogInternal.puIsOk = true;
            }
        }
    }
}
void ImDialog::prBeginFileColorIconStyle(
    std::shared_ptr<FileInfos> vFileInfos, bool& vOutShowColor, std::string& vOutStr, ImFont** vOutFont) {
    vOutStr.clear();
    vOutShowColor = false;

    if (vFileInfos->fileStyle.use_count())  //-V807 //-V522
    {
        vOutShowColor = true;

        *vOutFont = vFileInfos->fileStyle->font;
    }

    if (vOutShowColor && !vFileInfos->fileStyle->icon.empty())
        vOutStr = vFileInfos->fileStyle->icon;
    else if (vFileInfos->fileType.isDir())
        vOutStr = dirEntryString;
    else if (vFileInfos->fileType.isLinkToUnknown())
        vOutStr = linkEntryString;
    else if (vFileInfos->fileType.isFile())
        vOutStr = fileEntryString;

    vOutStr += " " + vFileInfos->fileNameExt;

    if (vOutShowColor)
        ImGui::PushStyleColor(ImGuiCol_Text, vFileInfos->fileStyle->color);
    if (*vOutFont)
        ImGui::PushFont(*vOutFont);
}
void ImDialog::prEndFileColorIconStyle(const bool& vShowColor, ImFont* vFont) {
    if (vFont)
        ImGui::PopFont();
    if (vShowColor)
        ImGui::PopStyleColor();
}
void ImDialog::prDrawFileListView(ImVec2 vSize) {
    auto& fdi = prFileDialogInternal.puFileManager;

    ImGui::PushID(this);

    static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Hideable |
                                   ImGuiTableFlags_ScrollY | ImGuiTableFlags_NoHostExtendY
#ifndef USE_CUSTOM_SORTING_ICON
                                   | ImGuiTableFlags_Sortable
#endif  // USE_CUSTOM_SORTING_ICON
        ;
    auto listViewID = ImGui::GetID("##FileDialog_fileTable");
    if (ImGui::BeginTableEx("##FileDialog_fileTable", listViewID, 4, flags, vSize, 0.0f))  //-V112
    {
        ImGui::TableSetupScrollFreeze(0, 1);  // Make header always visible
        ImGui::TableSetupColumn(fdi.puHeaderFileName.c_str(),
            ImGuiTableColumnFlags_WidthStretch |
                (defaultSortOrderFilename ? ImGuiTableColumnFlags_PreferSortAscending
                                          : ImGuiTableColumnFlags_PreferSortDescending),
            -1, 0);
        ImGui::TableSetupColumn(fdi.puHeaderFileType.c_str(),
            ImGuiTableColumnFlags_WidthFixed |
                (defaultSortOrderType ? ImGuiTableColumnFlags_PreferSortAscending
                                      : ImGuiTableColumnFlags_PreferSortDescending) |
                ((prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_HideColumnType)
                        ? ImGuiTableColumnFlags_DefaultHide
                        : 0),
            -1, 1);
        ImGui::TableSetupColumn(fdi.puHeaderFileSize.c_str(),
            ImGuiTableColumnFlags_WidthFixed |
                (defaultSortOrderSize ? ImGuiTableColumnFlags_PreferSortAscending
                                      : ImGuiTableColumnFlags_PreferSortDescending) |
                ((prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_HideColumnSize)
                        ? ImGuiTableColumnFlags_DefaultHide
                        : 0),
            -1, 2);
        ImGui::TableSetupColumn(fdi.puHeaderFileDate.c_str(),
            ImGuiTableColumnFlags_WidthFixed |
                (defaultSortOrderDate ? ImGuiTableColumnFlags_PreferSortAscending
                                      : ImGuiTableColumnFlags_PreferSortDescending) |
                ((prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_HideColumnDate)
                        ? ImGuiTableColumnFlags_DefaultHide
                        : 0),
            -1, 3);

#ifndef USE_CUSTOM_SORTING_ICON
        // Sort our data if sort specs have been changed!
        if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs()) {
            if (sorts_specs->SpecsDirty && !fdi.IsFileListEmpty()) {
                bool direction = sorts_specs->Specs->SortDirection == ImGuiSortDirection_Ascending;

                if (sorts_specs->Specs->ColumnUserID == 0) {
                    fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_FILENAME;
                    fdi.puSortingDirection[0] = direction;
                    fdi.SortFields(prFileDialogInternal);
                } else if (sorts_specs->Specs->ColumnUserID == 1) {
                    fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_TYPE;
                    fdi.puSortingDirection[1] = direction;
                    fdi.SortFields(prFileDialogInternal);
                } else if (sorts_specs->Specs->ColumnUserID == 2) {
                    fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_SIZE;
                    fdi.puSortingDirection[2] = direction;
                    fdi.SortFields(prFileDialogInternal);
                } else  // if (sorts_specs->Specs->ColumnUserID == 3) => alwayd true for the moment, to uncomment if we
                        // add a fourth column
                {
                    fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_DATE;
                    fdi.puSortingDirection[3] = direction;
                    fdi.SortFields(prFileDialogInternal);
                }

                sorts_specs->SpecsDirty = false;
            }
        }

        ImGui::TableHeadersRow();
#else   // USE_CUSTOM_SORTING_ICON
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        for (int column = 0; column < 4; column++)  //-V112
        {
            ImGui::TableSetColumnIndex(column);
            const char* column_name = ImGui::TableGetColumnName(column);  // Retrieve name passed to TableSetupColumn()
            ImGui::PushID(column);
            ImGui::TableHeader(column_name);
            ImGui::PopID();
            if (ImGui::IsItemClicked()) {
                if (column == 0) {
                    if (fdi.puSortingField == IGFD::FileManager::SortingFieldEnum::FIELD_FILENAME)
                        fdi.puSortingDirection[0] = !fdi.puSortingDirection[0];
                    else
                        fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_FILENAME;

                    fdi.SortFields(prFileDialogInternal);
                } else if (column == 1) {
                    if (fdi.puSortingField == IGFD::FileManager::SortingFieldEnum::FIELD_TYPE)
                        fdi.puSortingDirection[1] = !fdi.puSortingDirection[1];
                    else
                        fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_TYPE;

                    fdi.SortFields(prFileDialogInternal);
                } else if (column == 2) {
                    if (fdi.puSortingField == IGFD::FileManager::SortingFieldEnum::FIELD_SIZE)
                        fdi.puSortingDirection[2] = !fdi.puSortingDirection[2];
                    else
                        fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_SIZE;

                    fdi.SortFields(prFileDialogInternal);
                } else  // if (column == 3) => alwayd true for the moment, to uncomment if we add a fourth column
                {
                    if (fdi.puSortingField == IGFD::FileManager::SortingFieldEnum::FIELD_DATE)
                        fdi.puSortingDirection[3] = !fdi.puSortingDirection[3];
                    else
                        fdi.puSortingField = IGFD::FileManager::SortingFieldEnum::FIELD_DATE;

                    fdi.SortFields(prFileDialogInternal);
                }
            }
        }
#endif  // USE_CUSTOM_SORTING_ICON
        if (!fdi.IsFilteredListEmpty()) {
            std::string _str;
            ImFont* _font = nullptr;
            bool _showColor = false;

            prFileListClipper.Begin((int)fdi.GetFilteredListSize(), ImGui::GetTextLineHeightWithSpacing());
            while (prFileListClipper.Step()) {
                for (int i = prFileListClipper.DisplayStart; i < prFileListClipper.DisplayEnd; i++) {
                    if (i < 0)
                        continue;

                    auto infos = fdi.GetFilteredFileAt((size_t)i);
                    if (!infos.use_count())
                        continue;

                    prBeginFileColorIconStyle(infos, _showColor, _str, &_font);

                    bool selected = fdi.IsFileNameSelected(infos->fileNameExt);  // found

                    ImGui::TableNextRow();

                    if (ImGui::TableNextColumn())  // file name
                    {
                        prSelectableItem(i, infos, selected, _str.c_str());
                    }
                    if (ImGui::TableNextColumn())  // file type
                    {
                        ImGui::Text("%s", infos->fileExtLevels[0].c_str());
                    }
                    if (ImGui::TableNextColumn())  // file size
                    {
                        if (!infos->fileType.isDir()) {
                            ImGui::Text("%s ", infos->formatedFileSize.c_str());
                        } else {
                            ImGui::TextUnformatted("");
                        }
                    }
                    if (ImGui::TableNextColumn())  // file date + time
                    {
                        ImGui::Text("%s", infos->fileModifDate.c_str());
                    }

                    prEndFileColorIconStyle(_showColor, _font);
                }
            }
            prFileListClipper.End();
        }

#ifdef USE_EXPLORATION_BY_KEYS
        if (!fdi.puInputPathActivated) {
            prLocateByInputKey(prFileDialogInternal);
            prExploreWithkeys(prFileDialogInternal, listViewID);
        }
#endif  // USE_EXPLORATION_BY_KEYS

        ImGuiContext& g = *GImGui;
        if (g.LastActiveId - 1 == listViewID || g.LastActiveId == listViewID) {
            prFileDialogInternal.puFileListViewIsActive = true;
        }

        ImGui::EndTable();
    }

    ImGui::PopID();
}
void ImDialog::prDrawSidePane(float vHeight) {
    ImGui::SameLine();

    ImGui::BeginChild("##FileTypes", ImVec2(0, vHeight));

    prFileDialogInternal.puDLGoptionsPane(
        prFileDialogInternal.puFilterManager.GetSelectedFilter().getFirstFilter().c_str(),
        prFileDialogInternal.puDLGuserDatas, &prFileDialogInternal.puCanWeContinue);
    ImGui::EndChild();
}
void ImDialog::Close() {
    prFileDialogInternal.puDLGkey.clear();
    prFileDialogInternal.puShowDialog = false;
}
void ImDialog::SetFileStyle(
    const IGFD_FileStyleFlags& vFlags, const char* vCriteria, const FileStyle& vInfos) {
    prFileDialogInternal.puFilterManager.SetFileStyle(vFlags, vCriteria, vInfos);
}
void ImDialog::SetFileStyle(const IGFD_FileStyleFlags& vFlags,
    const char* vCriteria,
    const ImVec4& vColor,
    const std::string& vIcon,
    ImFont* vFont) {
    prFileDialogInternal.puFilterManager.SetFileStyle(vFlags, vCriteria, vColor, vIcon, vFont);
}
void ImDialog::SetFileStyle(FileStyle::FileStyleFunctor vFunctor) {
    prFileDialogInternal.puFilterManager.SetFileStyle(vFunctor);
}
void ImDialog::ClearFilesStyle() { prFileDialogInternal.puFilterManager.ClearFilesStyle(); }
void ImDialog::SetLocales(
    const int& /*vLocaleCategory*/, const std::string& vLocaleBegin, const std::string& vLocaleEnd) {
    prFileDialogInternal.puUseCustomLocale = true;
    prFileDialogInternal.puLocaleBegin = vLocaleBegin;
    prFileDialogInternal.puLocaleEnd = vLocaleEnd;
}

bool ImDialog::Display(
    const std::string& vKey, ImGuiWindowFlags vFlags, ImVec2 vMinSize, ImVec2 vMaxSize) {
    bool res = false;

    if (prFileDialogInternal.puShowDialog && prFileDialogInternal.puDLGkey == vKey) {
        if (prFileDialogInternal.puUseCustomLocale)
            setlocale(prFileDialogInternal.puLocaleCategory, prFileDialogInternal.puLocaleBegin.c_str());

        auto& fdFile = prFileDialogInternal.puFileManager;
        auto& fdFilter = prFileDialogInternal.puFilterManager;

        static ImGuiWindowFlags flags;  // todo: not a good solution for multi instance, to fix

        // to be sure than only one dialog is displayed per frame
        ImGuiContext& g = *GImGui;
        if (g.FrameCount == prFileDialogInternal.puLastImGuiFrameCount)  // one instance was displayed this frame before
                                                                         // for this key +> quit
            return res;
        prFileDialogInternal.puLastImGuiFrameCount = g.FrameCount;  // mark this instance as used this frame

        std::string name = prFileDialogInternal.puDLGtitle + "##" + prFileDialogInternal.puDLGkey;
        if (prFileDialogInternal.puName != name) {
            fdFile.ClearComposer();
            fdFile.ClearFileLists();
            flags = vFlags;
        }

        NewFrame();

#ifdef IMGUI_HAS_VIEWPORT
        if (!ImGui::GetIO().ConfigViewportsNoDecoration) {
            // https://github.com/ocornut/imgui/issues/4534
            ImGuiWindowClass window_class;
            window_class.ViewportFlagsOverrideClear = ImGuiViewportFlags_NoDecoration;
            ImGui::SetNextWindowClass(&window_class);
        }
#endif  // IMGUI_HAS_VIEWPORT

        bool beg = false;
        if (prFileDialogInternal.puDLGflags &
            ImGuiFileDialogFlags_NoDialog)  // disable our own dialog system (standard or modal)
        {
            beg = true;
        } else {
            ImGui::SetNextWindowSizeConstraints(vMinSize, vMaxSize);

            if (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_Modal &&
                !prFileDialogInternal.puOkResultToConfirm)  // disable modal because the confirm dialog for overwrite is
                                                            // a new modal
            {
                ImGui::OpenPopup(name.c_str());
                beg = ImGui::BeginPopupModal(name.c_str(), (bool*)nullptr, flags | ImGuiWindowFlags_NoScrollbar);
            } else {
                beg = ImGui::Begin(name.c_str(), &prFileDialogInternal.puShowDialog, flags | ImGuiWindowFlags_NoScrollbar);
            }
        }
        if (beg) {
#ifdef IMGUI_HAS_VIEWPORT
            // if decoration is enabled we disable the resizing feature of imgui for avoid crash with SDL2 and GLFW3
            if (ImGui::GetIO().ConfigViewportsNoDecoration) {
                flags = vFlags;
            } else {
                auto win = ImGui::GetCurrentWindowRead();
                if (win->Viewport->Idx != 0)
                    flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
                else
                    flags = vFlags;
            }
#endif  // IMGUI_HAS_VIEWPORT

            ImGuiID _frameId = ImGui::GetID(name.c_str());
            ImVec2 frameSize = ImVec2(0, 0);
            if (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_NoDialog)
                frameSize = vMaxSize;
            if (ImGui::BeginChild(_frameId, frameSize, false, flags | ImGuiWindowFlags_NoScrollbar)) {
                prFileDialogInternal.puName = name;  //-V820

                if (fdFile.puDLGpath.empty())
                    fdFile.puDLGpath = ".";  // defaut path is '.'

                fdFilter.SetDefaultFilterIfNotDefined();

                // init list of files
                if (fdFile.IsFileListEmpty() && !fdFile.puShowDrives) {
                    IGFD::Utils::ReplaceString(fdFile.puDLGDefaultFileName, fdFile.puDLGpath, "");  // local path
                    if (!fdFile.puDLGDefaultFileName.empty()) {
                        fdFile.SetDefaultFileName(fdFile.puDLGDefaultFileName);
                        fdFilter.SetSelectedFilterWithExt(fdFilter.puDLGdefaultExt);
                    } else if (fdFile.puDLGDirectoryMode)  // directory mode
                        fdFile.SetDefaultFileName(".");
                    fdFile.ScanDir(prFileDialogInternal, fdFile.puDLGpath);
                }

                // draw dialog parts
                prDrawHeader();        // bookmark, directory, path
                prDrawContent();       // bookmark, files view, side pane
                res = prDrawFooter();  // file field, filter combobox, ok/cancel buttons

                EndFrame();
            }
            ImGui::EndChild();

            // for display in dialog center, the confirm to overwrite dlg
            prFileDialogInternal.puDialogCenterPos = ImGui::GetCurrentWindowRead()->ContentRegionRect.GetCenter();

            // when the confirm to overwrite dialog will appear we need to
            // disable the modal mode of the main file dialog
            // see prOkResultToConfirm under
            if (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_Modal &&
                !prFileDialogInternal.puOkResultToConfirm) {
                ImGui::EndPopup();
            }
        }

        if (prFileDialogInternal.puDLGflags &
            ImGuiFileDialogFlags_NoDialog) {  // disable our own dialog system (standard or modal)
        } else {
            // same things here regarding prOkResultToConfirm
            if (!(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_Modal) ||
                prFileDialogInternal.puOkResultToConfirm) {
                ImGui::End();
            }
        }
        // confirm the result and show the confirm to overwrite dialog if needed
        res = prConfirm_Or_OpenOverWriteFileDialog_IfNeeded(res, vFlags);

        if (prFileDialogInternal.puUseCustomLocale)
            setlocale(prFileDialogInternal.puLocaleCategory, prFileDialogInternal.puLocaleEnd.c_str());
    }

    return res;
}
bool ImDialog::WasOpenedThisFrame(const std::string& vKey) const {
    bool res = prFileDialogInternal.puShowDialog && prFileDialogInternal.puDLGkey == vKey;
    if (res) {
        res &= prFileDialogInternal.puLastImGuiFrameCount ==
               GImGui->FrameCount;  // return true if a dialog was displayed in this frame
    }
    return res;
}
bool ImDialog::WasOpenedThisFrame() const {
    bool res = prFileDialogInternal.puShowDialog;
    if (res) {
        res &= prFileDialogInternal.puLastImGuiFrameCount ==
               GImGui->FrameCount;  // return true if a dialog was displayed in this frame
    }
    return res;
}
bool ImDialog::IsOpened(const std::string& vKey) const {
    return (prFileDialogInternal.puShowDialog && prFileDialogInternal.puDLGkey == vKey);
}
bool ImDialog::IsOpened() const { return prFileDialogInternal.puShowDialog; }
bool ImDialog::IsOk() const { return prFileDialogInternal.puIsOk; }
bool ImDialog::GetFileStyle(const IGFD_FileStyleFlags& vFlags,
    const std::string& vCriteria,
    ImVec4* vOutColor,
    std::string* vOutIcon,
    ImFont** vOutFont) {
    return prFileDialogInternal.puFilterManager.GetFileStyle(vFlags, vCriteria, vOutColor, vOutIcon, vOutFont);
}
bool ImDialog::prConfirm_Or_OpenOverWriteFileDialog_IfNeeded(
    bool vLastAction, ImGuiWindowFlags vFlags) {
    // if confirmation => return true for confirm the overwrite et quit the dialog
    // if cancel => return false && set IsOk to false for keep inside the dialog

    // if IsOk == false => return false for quit the dialog
    if (!prFileDialogInternal.puIsOk && vLastAction) {
        QuitFrame();
        return true;
    }

    // if IsOk == true && no check of overwrite => return true for confirm the dialog
    if (prFileDialogInternal.puIsOk && vLastAction &&
        !(prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_ConfirmOverwrite)) {
        QuitFrame();
        return true;
    }

    // if IsOk == true && check of overwrite => return false and show confirm to overwrite dialog
    if ((prFileDialogInternal.puOkResultToConfirm || (prFileDialogInternal.puIsOk && vLastAction)) &&
        (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_ConfirmOverwrite)) {
        if (prFileDialogInternal.puIsOk)  // catched only one time
        {
            if (!prFileDialogInternal.puFileManager.IsFileExist(GetFilePathName()))  // not existing => quit dialog
            {
                QuitFrame();
                return true;
            } else  // existing => confirm dialog to open
            {
                prFileDialogInternal.puIsOk = false;
                prFileDialogInternal.puOkResultToConfirm = true;
            }
        }

        std::string name = OverWriteDialogTitleString "##" + prFileDialogInternal.puDLGtitle +
                           prFileDialogInternal.puDLGkey + "OverWriteDialog";

        bool res = false;

        ImGui::OpenPopup(name.c_str());
        if (ImGui::BeginPopupModal(name.c_str(), (bool*)0,
                vFlags | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::SetWindowPos(prFileDialogInternal.puDialogCenterPos -
                                ImGui::GetWindowSize() * 0.5f);  // next frame needed for GetWindowSize to work

            ImGui::Text("%s", OverWriteDialogMessageString);

            if (ImGui::Button(OverWriteDialogConfirmButtonString)) {
                prFileDialogInternal.puOkResultToConfirm = false;
                prFileDialogInternal.puIsOk = true;
                res = true;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button(OverWriteDialogCancelButtonString)) {
                prFileDialogInternal.puOkResultToConfirm = false;
                prFileDialogInternal.puIsOk = false;
                res = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        if (res) {
            QuitFrame();
        }
        return res;
    }

    return false;
}
bool ImDialog::prDrawOkButton() {
    auto& fdFile = prFileDialogInternal.puFileManager;
    if (prFileDialogInternal.puCanWeContinue && strlen(fdFile.puFileNameBuffer)) {
        if (ImGui::Button(okButtonString "##validationdialog", ImVec2(okButtonWidth, 0.0f)) ||
            prFileDialogInternal.puIsOk) {
            prFileDialogInternal.puIsOk = true;
            return true;
        }

#if !invertOkAndCancelButtons
        ImGui::SameLine();
#endif
    }

    return false;
}
bool ImDialog::prDrawCancelButton() {
    if (ImGui::Button(cancelButtonString "##validationdialog", ImVec2(cancelButtonWidth, 0.0f)) ||
        prFileDialogInternal.puNeedToExitDialog)  // dialog exit asked
    {
        prFileDialogInternal.puIsOk = false;
        return true;
    }

#if invertOkAndCancelButtons
    ImGui::SameLine();
#endif

    return false;
}
bool ImDialog::prDrawValidationButtons() {
    bool res = false;

    ImGui::SetCursorPosX(
        ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - prOkCancelButtonWidth) * okCancelButtonAlignement);

    ImGui::BeginGroup();

    if (invertOkAndCancelButtons) {
        res |= prDrawCancelButton();
        res |= prDrawOkButton();
    } else {
        res |= prDrawOkButton();
        res |= prDrawCancelButton();
    }

    ImGui::EndGroup();

    prOkCancelButtonWidth = ImGui::GetItemRectSize().x;

    return res;
}
bool ImDialog::prDrawFooter() {
    auto& fdFile = prFileDialogInternal.puFileManager;

    float posY = ImGui::GetCursorPos().y;  // height of last bar calc
    ImGui::AlignTextToFramePadding();
    if (!fdFile.puDLGDirectoryMode)
        ImGui::Text(fileNameString);
    else  // directory chooser
        ImGui::Text(dirNameString);
    ImGui::SameLine();

    // Input file fields
    float width = ImGui::GetContentRegionAvail().x;
    if (!fdFile.puDLGDirectoryMode) {
        ImGuiContext& g = *GImGui;
        width -= prFileDialogInternal.puFilterManager.GetFilterComboBoxWidth() + g.Style.ItemSpacing.x;
    }

    ImGui::PushItemWidth(width);
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (prFileDialogInternal.puDLGflags & ImGuiFileDialogFlags_ReadOnlyFileNameField) {
        flags |= ImGuiInputTextFlags_ReadOnly;
    }
    if (ImGui::InputText("##FileName", fdFile.puFileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, flags)) {
        prFileDialogInternal.puIsOk = true;
    }
    if (ImGui::GetItemID() == ImGui::GetActiveID())
        prFileDialogInternal.puFileInputIsActive = true;
    ImGui::PopItemWidth();

    // combobox of filters
    prFileDialogInternal.puFilterManager.DrawFilterComboBox(prFileDialogInternal);

    bool res = prDrawValidationButtons();
    prFileDialogInternal.puFooterHeight = ImGui::GetCursorPosY() - posY;
    return res;
}

std::string ImDialog::GetOpenedKey() const {
    if (prFileDialogInternal.puShowDialog) {
        return prFileDialogInternal.puDLGkey;
    }
    return "";
}
std::string ImDialog::GetFilePathName(IGFD_ResultMode vFlag) {
    return prFileDialogInternal.puFileManager.GetResultingFilePathName(prFileDialogInternal, vFlag);
}
std::string ImDialog::GetCurrentPath() {
    return prFileDialogInternal.puFileManager.GetResultingPath();
}
std::string ImDialog::GetCurrentFileName(IGFD_ResultMode vFlag) {
    return prFileDialogInternal.puFileManager.GetResultingFileName(prFileDialogInternal, vFlag);
}
std::string ImDialog::GetCurrentFilter() {
    return prFileDialogInternal.puFilterManager.GetSelectedFilter().title;
}
std::map<std::string, std::string> ImDialog::GetSelection(IGFD_ResultMode vFlag) {
    return prFileDialogInternal.puFileManager.GetResultingSelection(prFileDialogInternal, vFlag);
}
IGFD::UserDatas ImDialog::GetUserDatas() const { return prFileDialogInternal.puDLGuserDatas; }
