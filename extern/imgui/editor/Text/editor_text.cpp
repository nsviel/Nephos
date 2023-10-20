#include "editor_text.h"
#include "editor_text_theme.h"
//#include "language_cpp.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/core/imgui.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <regex>
#include <cmath>


template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equals(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p){
	//---------------------------

	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!p(*first1, *first2))
			return false;
	}

	//---------------------------
	return first1 == last1 && first2 == last2;
}

TextEditor::TextEditor(){
	//---------------------------

	SetPalette(get_custom_palette());
	SetLanguageDefinition(LanguageDefinition::Cpp());
	lines.push_back(Line());

	this->show_whitespaces = true;
	this->check_comments = true;
	this->last_click = -1.0f;
	this->handle_keyboard_inputs = true;
	this->handle_mouse_inputs = true;
	this->ignore_imgui_child = false;
	this->scroll_to_cursor = false;
	this->scroll_to_top = false;
	this->text_changed = false;
	this->colorizer_enabled = true;
	this->text_start = 20.0f;
	this->left_margin = 10;
	this->cursor_position_changed = false;
	this->color_range_min = 0;
	this->color_range_max = 0;
	this->undo_index = 0;
	this->tab_size = 4;
	this->overwrite = false;
	this->read_only = false;
	this->within_render = false;
	this->selection_mode = SelectionMode::Normal;
	this->line_spacing = 1.2f;
	this->start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	//---------------------------
}
TextEditor::~TextEditor(){}
TextEditor::UndoRecord::UndoRecord(
	const std::string& aAdded,
	const TextEditor::Coordinates aAddedStart,
	const TextEditor::Coordinates aAddedEnd,
	const std::string& aRemoved,
	const TextEditor::Coordinates aRemovedStart,
	const TextEditor::Coordinates aRemovedEnd,
	TextEditor::EditorState& aBefore,
	TextEditor::EditorState& aAfter)
	: mAdded(aAdded)
	, mAddedStart(aAddedStart)
	, mAddedEnd(aAddedEnd)
	, mRemoved(aRemoved)
	, mRemovedStart(aRemovedStart)
	, mRemovedEnd(aRemovedEnd)
{
	assert(mAddedStart <= mAddedEnd);
	assert(mRemovedStart <= mRemovedEnd);

	this->mBefore = aBefore;
	this->mAfter = aAfter;
}

static int UTF8CharLength(TextEditor::Char c){
	// https://en.wikipedia.org/wiki/UTF-8
	// We assume that the char is a standalone character (<128) or a leading byte of an UTF-8 code sequence (non-10xxxxxx code)
	//---------------------------

	if ((c & 0xFE) == 0xFC)
		return 6;
	if ((c & 0xFC) == 0xF8)
		return 5;
	if ((c & 0xF8) == 0xF0)
		return 4;
	else if ((c & 0xF0) == 0xE0)
		return 3;
	else if ((c & 0xE0) == 0xC0)
		return 2;

	//---------------------------
	return 1;
}
static inline int ImTextCharToUtf8(char* buf, int buf_size, unsigned int c){
	// "Borrowed" from ImGui source
	//---------------------------

	if (c < 0x80){
		buf[0] = (char)c;
		return 1;
	}
	if (c < 0x800){
		if (buf_size < 2) return 0;
		buf[0] = (char)(0xc0 + (c >> 6));
		buf[1] = (char)(0x80 + (c & 0x3f));
		return 2;
	}
	if (c >= 0xdc00 && c < 0xe000){
		return 0;
	}
	if (c >= 0xd800 && c < 0xdc00){
		if (buf_size < 4) return 0;
		buf[0] = (char)(0xf0 + (c >> 18));
		buf[1] = (char)(0x80 + ((c >> 12) & 0x3f));
		buf[2] = (char)(0x80 + ((c >> 6) & 0x3f));
		buf[3] = (char)(0x80 + ((c) & 0x3f));
		return 4;
	}
	//else if (c < 0x10000)
	{
		if (buf_size < 3) return 0;
		buf[0] = (char)(0xe0 + (c >> 12));
		buf[1] = (char)(0x80 + ((c >> 6) & 0x3f));
		buf[2] = (char)(0x80 + ((c) & 0x3f));
		return 3;
	}

	//---------------------------
}
static bool IsUTFSequence(char c){
	return (c & 0xC0) == 0x80;
}
static bool TokenizeCStyleString(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end){
	const char * p = in_begin;
	//---------------------------

	if (*p == '"'){
		p++;

		while (p < in_end){
			// handle end of string
			if (*p == '"'){
				out_begin = in_begin;
				out_end = p + 1;
				return true;
			}

			// handle escape character for "
			if (*p == '\\' && p + 1 < in_end && p[1] == '"'){
				p++;
			}

			p++;
		}
	}

	//---------------------------
	return false;
}
static bool TokenizeCStyleCharacterLiteral(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end){
	const char * p = in_begin;
	//---------------------------

	if (*p == '\''){
		p++;

		// handle escape characters
		if (p < in_end && *p == '\\')
			p++;

		if (p < in_end)
			p++;

		// handle end of character literal
		if (p < in_end && *p == '\'')
		{
			out_begin = in_begin;
			out_end = p + 1;
			return true;
		}
	}

	//---------------------------
	return false;
}
static bool TokenizeCStyleIdentifier(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end){
	const char * p = in_begin;
	//---------------------------

	if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_'){
		p++;

		while ((p < in_end) && ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_'))
			p++;

		out_begin = in_begin;
		out_end = p;
		return true;
	}

	//---------------------------
	return false;
}
static bool TokenizeCStyleNumber(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end){
	const char * p = in_begin;
	//---------------------------

	const bool startsWithNumber = *p >= '0' && *p <= '9';

	if (*p != '+' && *p != '-' && !startsWithNumber){
		return false;
	}

	p++;

	bool hasNumber = startsWithNumber;
	while (p < in_end && (*p >= '0' && *p <= '9')){
		hasNumber = true;

		p++;
	}

	if (hasNumber == false){
		return false;
	}

	bool isFloat = false;
	bool isHex = false;
	bool isBinary = false;

	if (p < in_end){
		if (*p == '.')
		{
			isFloat = true;

			p++;

			while (p < in_end && (*p >= '0' && *p <= '9'))
				p++;
		}
		else if (*p == 'x' || *p == 'X')
		{
			// hex formatted integer of the type 0xef80

			isHex = true;

			p++;

			while (p < in_end && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')))
				p++;
		}
		else if (*p == 'b' || *p == 'B')
		{
			// binary formatted integer of the type 0b01011101

			isBinary = true;

			p++;

			while (p < in_end && (*p >= '0' && *p <= '1'))
				p++;
		}
	}
	if (isHex == false && isBinary == false){
		// floating point exponent
		if (p < in_end && (*p == 'e' || *p == 'E'))
		{
			isFloat = true;

			p++;

			if (p < in_end && (*p == '+' || *p == '-'))
				p++;

			bool hasDigits = false;

			while (p < in_end && (*p >= '0' && *p <= '9'))
			{
				hasDigits = true;

				p++;
			}

			if (hasDigits == false)
				return false;
		}

		// single precision floating point type
		if (p < in_end && *p == 'f')
			p++;
	}
	if (isFloat == false){
		// integer size type
		while (p < in_end && (*p == 'u' || *p == 'U' || *p == 'l' || *p == 'L'))
			p++;
	}

	out_begin = in_begin;
	out_end = p;

	//---------------------------
	return true;
}
static bool TokenizeCStylePunctuation(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end){
	(void)in_end;
	//---------------------------

	switch (*in_begin){
	case '[':
	case ']':
	case '{':
	case '}':
	case '!':
	case '%':
	case '^':
	case '&':
	case '*':
	case '(':
	case ')':
	case '-':
	case '+':
	case '=':
	case '~':
	case '|':
	case '<':
	case '>':
	case '?':
	case ':':
	case '/':
	case ';':
	case ',':
	case '.':
		out_begin = in_begin;
		out_end = in_begin + 1;
		return true;
	}

	//---------------------------
	return false;
}

TextEditor::Coordinates TextEditor::GetActualCursorCoordinates() const{
	//---------------------------

	//---------------------------
	return SanitizeCoordinates(state.mCursorPosition);
}
TextEditor::Coordinates TextEditor::SanitizeCoordinates(const Coordinates & aValue) const{
	//---------------------------

	auto line = aValue.mLine;
	auto column = aValue.mColumn;
	if (line >= (int)lines.size()){
		if (lines.empty()){
			line = 0;
			column = 0;
		}
		else{
			line = (int)lines.size() - 1;
			column = GetLineMaxColumn(line);
		}
		return Coordinates(line, column);
	}
	else{
		column = lines.empty() ? 0 : std::min(column, GetLineMaxColumn(line));
		return Coordinates(line, column);
	}

	//---------------------------
}
TextEditor::Coordinates TextEditor::ScreenPosToCoordinates(const ImVec2& aPosition) const{
	//---------------------------

	ImVec2 origin = ImGui::GetCursorScreenPos();
	ImVec2 local(aPosition.x - origin.x, aPosition.y - origin.y);
	int lineNo = std::max(0, (int)floor(local.y / char_advance.y));
	int columnCoord = 0;

	if (lineNo >= 0 && lineNo < (int)lines.size()){
		auto& line = lines.at(lineNo);

		int columnIndex = 0;
		float columnX = 0.0f;

		while ((size_t)columnIndex < line.size()){
			float columnWidth = 0.0f;

			if (line[columnIndex].mChar == '\t'){
				float spaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, " ").x;
				float oldX = columnX;
				float newColumnX = (1.0f + std::floor((1.0f + columnX) / (float(tab_size) * spaceSize))) * (float(tab_size) * spaceSize);
				columnWidth = newColumnX - oldX;
				if (text_start + columnX + columnWidth * 0.5f > local.x){
					break;
				}
				columnX = newColumnX;
				columnCoord = (columnCoord / tab_size) * tab_size + tab_size;
				columnIndex++;
			}
			else{
				char buf[7];
				auto d = UTF8CharLength(line[columnIndex].mChar);
				int i = 0;
				while (i < 6 && d-- > 0){
					buf[i++] = line[columnIndex++].mChar;
				}
				buf[i] = '\0';
				columnWidth = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, buf).x;
				if (text_start + columnX + columnWidth * 0.5f > local.x){
					break;
				}
				columnX += columnWidth;
				columnCoord++;
			}
		}
	}

	//---------------------------
	return SanitizeCoordinates(Coordinates(lineNo, columnCoord));
}
TextEditor::Coordinates TextEditor::FindWordStart(const Coordinates & aFrom) const{
	//---------------------------

	Coordinates at = aFrom;
	if (at.mLine >= (int)lines.size()){
		return at;
	}

	auto& line = lines[at.mLine];
	auto cindex = GetCharacterIndex(at);

	if (cindex >= (int)line.size()){
		return at;
	}

	while (cindex > 0 && isspace(line[cindex].mChar)){
		--cindex;
	}

	auto cstart = (PaletteIndex)line[cindex].color_index;
	while (cindex > 0){
		auto c = line[cindex].mChar;
		if ((c & 0xC0) != 0x80){	// not UTF code sequence 10xxxxxx{
			if (c <= 32 && isspace(c)){
				cindex++;
				break;
			}
			if (cstart != (PaletteIndex)line[size_t(cindex - 1)].color_index){
				break;
			}
		}
		--cindex;
	}

	//---------------------------
	return Coordinates(at.mLine, GetCharacterColumn(at.mLine, cindex));
}
TextEditor::Coordinates TextEditor::FindWordEnd(const Coordinates & aFrom) const{
	//---------------------------

	Coordinates at = aFrom;
	if (at.mLine >= (int)lines.size()){
		return at;
	}

	auto& line = lines[at.mLine];
	auto cindex = GetCharacterIndex(at);

	if (cindex >= (int)line.size()){
		return at;
	}

	bool prevspace = (bool)isspace(line[cindex].mChar);
	auto cstart = (PaletteIndex)line[cindex].color_index;
	while (cindex < (int)line.size()){
		auto c = line[cindex].mChar;
		auto d = UTF8CharLength(c);
		if (cstart != (PaletteIndex)line[cindex].color_index){
			break;
		}

		if (prevspace != !!isspace(c)){
			if (isspace(c)){
				while (cindex < (int)line.size() && isspace(line[cindex].mChar)){
					++cindex;
				}
			}
			break;
		}
		cindex += d;
	}

	//---------------------------
	return Coordinates(aFrom.mLine, GetCharacterColumn(aFrom.mLine, cindex));
}
TextEditor::Coordinates TextEditor::FindNextWord(const Coordinates & aFrom) const{
	//---------------------------

	Coordinates at = aFrom;
	if (at.mLine >= (int)lines.size()){
		return at;
	}

	// skip to the next non-word character
	auto cindex = GetCharacterIndex(aFrom);
	bool isword = false;
	bool skip = false;
	if (cindex < (int)lines[at.mLine].size()){
		auto& line = lines[at.mLine];
		isword = isalnum(line[cindex].mChar);
		skip = isword;
	}

	while (!isword || skip){
		if (at.mLine >= lines.size()){
			auto l = std::max(0, (int) lines.size() - 1);
			return Coordinates(l, GetLineMaxColumn(l));
		}

		auto& line = lines[at.mLine];
		if (cindex < (int)line.size()){
			isword = isalnum(line[cindex].mChar);

			if (isword && !skip){
				return Coordinates(at.mLine, GetCharacterColumn(at.mLine, cindex));
			}

			if (!isword){
				skip = false;
			}

			cindex++;
		}
		else{
			cindex = 0;
			++at.mLine;
			skip = false;
			isword = false;
		}
	}

	//---------------------------
	return at;
}

int TextEditor::GetCharacterIndex(const Coordinates& aCoordinates) const{
	if (aCoordinates.mLine >= lines.size())
		return -1;
	auto& line = lines[aCoordinates.mLine];
	int c = 0;
	int i = 0;
	for (; i < line.size() && c < aCoordinates.mColumn;)
	{
		if (line[i].mChar == '\t')
			c = (c / tab_size) * tab_size + tab_size;
		else
			++c;
		i += UTF8CharLength(line[i].mChar);
	}
	return i;
}
int TextEditor::GetCharacterColumn(int aLine, int aIndex) const{
	if (aLine >= lines.size())
		return 0;
	auto& line = lines[aLine];
	int col = 0;
	int i = 0;
	while (i < aIndex && i < (int)line.size())
	{
		auto c = line[i].mChar;
		i += UTF8CharLength(c);
		if (c == '\t')
			col = (col / tab_size) * tab_size + tab_size;
		else
			col++;
	}
	return col;
}
int TextEditor::GetLineCharacterCount(int aLine) const{
	if (aLine >= lines.size())
		return 0;
	auto& line = lines[aLine];
	int c = 0;
	for (unsigned i = 0; i < line.size(); c++)
		i += UTF8CharLength(line[i].mChar);
	return c;
}
int TextEditor::GetLineMaxColumn(int aLine) const{
	if (aLine >= lines.size())
		return 0;
	auto& line = lines[aLine];
	int col = 0;
	for (unsigned i = 0; i < line.size(); )
	{
		auto c = line[i].mChar;
		if (c == '\t')
			col = (col / tab_size) * tab_size + tab_size;
		else
			col++;
		i += UTF8CharLength(c);
	}
	return col;
}
int TextEditor::InsertTextAt(Coordinates& /* inout */ aWhere, const char * aValue){
	//---------------------------

	assert(!read_only);

	int cindex = GetCharacterIndex(aWhere);
	int totalLines = 0;
	while (*aValue != '\0'){
		assert(!lines.empty());

		if (*aValue == '\r'){
			// skip
			++aValue;
		}
		else if (*aValue == '\n'){
			if (cindex < (int)lines[aWhere.mLine].size()){
				auto& newLine = InsertLine(aWhere.mLine + 1);
				auto& line = lines[aWhere.mLine];
				newLine.insert(newLine.begin(), line.begin() + cindex, line.end());
				line.erase(line.begin() + cindex, line.end());
			}
			else{
				InsertLine(aWhere.mLine + 1);
			}
			++aWhere.mLine;
			aWhere.mColumn = 0;
			cindex = 0;
			++totalLines;
			++aValue;
		}
		else{
			auto& line = lines[aWhere.mLine];
			auto d = UTF8CharLength(*aValue);
			while (d-- > 0 && *aValue != '\0')
				line.insert(line.begin() + cindex++, Glyph(*aValue++, PaletteIndex::Default));
			++aWhere.mColumn;
		}

		text_changed = true;
	}

	//---------------------------
	return totalLines;
}
int TextEditor::GetPageSize() const{
	auto height = ImGui::GetWindowHeight() - 20.0f;
	return (int)floor(height / char_advance.y);
}

std::string TextEditor::GetText(const Coordinates & aStart, const Coordinates & aEnd) const{
	//---------------------------

	std::string result;

	auto lstart = aStart.mLine;
	auto lend = aEnd.mLine;
	auto istart = GetCharacterIndex(aStart);
	auto iend = GetCharacterIndex(aEnd);
	size_t s = 0;

	for (size_t i = lstart; i < lend; i++){
		s += lines[i].size();
	}

	result.reserve(s + s / 8);

	while (istart < iend || lstart < lend){
		if (lstart >= (int)lines.size()){
			break;
		}

		auto& line = lines[lstart];
		if (istart < (int)line.size()){
			result += line[istart].mChar;
			istart++;
		}
		else{
			istart = 0;
			++lstart;
			result += '\n';
		}
	}

	//---------------------------
	return result;
}
std::string TextEditor::GetWordUnderCursor() const{
	auto c = GetCursorPosition();
	return GetWordAt(c);
}
std::string TextEditor::GetWordAt(const Coordinates & aCoords) const{
	auto start = FindWordStart(aCoords);
	auto end = FindWordEnd(aCoords);

	std::string r;

	auto istart = GetCharacterIndex(start);
	auto iend = GetCharacterIndex(end);

	for (auto it = istart; it < iend; ++it)
		r.push_back(lines[aCoords.mLine][it].mChar);

	return r;
}
std::string TextEditor::GetText() const{
	return GetText(Coordinates(), Coordinates((int)lines.size(), 0));
}
std::string TextEditor::GetSelectedText() const{
	return GetText(state.mSelectionStart, state.mSelectionEnd);
}
std::string TextEditor::GetCurrentLineText()const{
	auto lineLength = GetLineMaxColumn(state.mCursorPosition.mLine);
	return GetText(
		Coordinates(state.mCursorPosition.mLine, 0),
		Coordinates(state.mCursorPosition.mLine, lineLength));
}
bool TextEditor::IsOnWordBoundary(const Coordinates & aAt) const{
	if (aAt.mLine >= (int)lines.size() || aAt.mColumn == 0)
		return true;

	auto& line = lines[aAt.mLine];
	auto cindex = GetCharacterIndex(aAt);
	if (cindex >= (int)line.size())
		return true;

	if (colorizer_enabled)
		return line[cindex].color_index != line[size_t(cindex - 1)].color_index;

	return isspace(line[cindex].mChar) != isspace(line[cindex - 1].mChar);
}
bool TextEditor::HasSelection() const{
	return state.mSelectionEnd > state.mSelectionStart;
}
bool TextEditor::CanUndo() const{
	return !read_only && undo_index > 0;
}
bool TextEditor::CanRedo() const{
	return !read_only && undo_index < (int)undo_buffer.size();
}
float TextEditor::TextDistanceToLineStart(const Coordinates& aFrom) const{
	auto& line = lines[aFrom.mLine];
	float distance = 0.0f;
	float spaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, " ", nullptr, nullptr).x;
	int colIndex = GetCharacterIndex(aFrom);
	for (size_t it = 0u; it < line.size() && it < colIndex; )
	{
		if (line[it].mChar == '\t')
		{
			distance = (1.0f + std::floor((1.0f + distance) / (float(tab_size) * spaceSize))) * (float(tab_size) * spaceSize);
			++it;
		}
		else
		{
			auto d = UTF8CharLength(line[it].mChar);
			char tempCString[7];
			int i = 0;
			for (; i < 6 && d-- > 0 && it < (int)line.size(); i++, it++)
				tempCString[i] = line[it].mChar;

			tempCString[i] = '\0';
			distance += ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, tempCString, nullptr, nullptr).x;
		}
	}

	return distance;
}
ImU32 TextEditor::GetGlyphColor(const Glyph & aGlyph) const{
	if (!colorizer_enabled)
		return palette[(int)PaletteIndex::Default];
	if (aGlyph.comment)
		return palette[(int)PaletteIndex::Comment];
	if (aGlyph.multiline_comment)
		return palette[(int)PaletteIndex::MultiLineComment];
	auto const color = palette[(int)aGlyph.color_index];
	if (aGlyph.preprocessor)
	{
		const auto ppcolor = palette[(int)PaletteIndex::Preprocessor];
		const int c0 = ((ppcolor & 0xff) + (color & 0xff)) / 2;
		const int c1 = (((ppcolor >> 8) & 0xff) + ((color >> 8) & 0xff)) / 2;
		const int c2 = (((ppcolor >> 16) & 0xff) + ((color >> 16) & 0xff)) / 2;
		const int c3 = (((ppcolor >> 24) & 0xff) + ((color >> 24) & 0xff)) / 2;
		return ImU32(c0 | (c1 << 8) | (c2 << 16) | (c3 << 24));
	}
	return color;
}
std::vector<std::string> TextEditor::GetTextLines() const{
	std::vector<std::string> result;

	result.reserve(lines.size());

	for (auto & line : lines)
	{
		std::string text;

		text.resize(line.size());

		for (size_t i = 0; i < line.size(); ++i)
			text[i] = line[i].mChar;

		result.emplace_back(std::move(text));
	}

	return result;
}
TextEditor::Line& TextEditor::InsertLine(int aIndex){
	assert(!read_only);

	auto& result = *lines.insert(lines.begin() + aIndex, Line());

	ErrorMarkers etmp;
	for (auto& i : error_markers)
		etmp.insert(ErrorMarkers::value_type(i.first >= aIndex ? i.first + 1 : i.first, i.second));
	error_markers = std::move(etmp);

	Breakpoints btmp;
	for (auto i : breakpoint)
		btmp.insert(i >= aIndex ? i + 1 : i);
	breakpoint = std::move(btmp);

	return result;
}

void TextEditor::SetLanguageDefinition(const LanguageDefinition & aLanguageDef){
	//---------------------------

	language_definition = aLanguageDef;
	regex_list.clear();

	for (auto& r : language_definition.token_regex_strings)
		regex_list.push_back(std::make_pair(std::regex(r.first, std::regex_constants::optimize), r.second));

	Colorize();

	//---------------------------
}
void TextEditor::SetPalette(const Palette & aValue){
	//---------------------------

	palette_base = aValue;

	//---------------------------
}
void TextEditor::Advance(Coordinates & aCoordinates) const{
	//---------------------------

	if (aCoordinates.mLine < (int)lines.size()){
		auto& line = lines[aCoordinates.mLine];
		auto cindex = GetCharacterIndex(aCoordinates);

		if (cindex + 1 < (int)line.size()){
			auto delta = UTF8CharLength(line[cindex].mChar);
			cindex = std::min(cindex + delta, (int)line.size() - 1);
		}
		else{
			++aCoordinates.mLine;
			cindex = 0;
		}
		aCoordinates.mColumn = GetCharacterColumn(aCoordinates.mLine, cindex);
	}

	//---------------------------
}
void TextEditor::DeleteRange(const Coordinates & aStart, const Coordinates & aEnd){
	//---------------------------

	assert(aEnd >= aStart);
	assert(!read_only);

	if (aEnd == aStart){
		return;
	}

	auto start = GetCharacterIndex(aStart);
	auto end = GetCharacterIndex(aEnd);

	if (aStart.mLine == aEnd.mLine){
		auto& line = lines[aStart.mLine];
		auto n = GetLineMaxColumn(aStart.mLine);
		if (aEnd.mColumn >= n){
			line.erase(line.begin() + start, line.end());
		}
		else{
			line.erase(line.begin() + start, line.begin() + end);
		}
	}
	else{
		auto& firstLine = lines[aStart.mLine];
		auto& lastLine = lines[aEnd.mLine];

		firstLine.erase(firstLine.begin() + start, firstLine.end());
		lastLine.erase(lastLine.begin(), lastLine.begin() + end);

		if (aStart.mLine < aEnd.mLine){
			firstLine.insert(firstLine.end(), lastLine.begin(), lastLine.end());
		}

		if (aStart.mLine < aEnd.mLine){
			RemoveLine(aStart.mLine + 1, aEnd.mLine + 1);
		}
	}

	text_changed = true;

	//---------------------------
}
void TextEditor::AddUndo(UndoRecord& aValue){
	//---------------------------

	assert(!read_only);
	//printf("AddUndo: (@%d.%d) +\'%s' [%d.%d .. %d.%d], -\'%s', [%d.%d .. %d.%d] (@%d.%d)\n",
	//	aValue.mBefore.mCursorPosition.mLine, aValue.mBefore.mCursorPosition.mColumn,
	//	aValue.mAdded.c_str(), aValue.mAddedStart.mLine, aValue.mAddedStart.mColumn, aValue.mAddedEnd.mLine, aValue.mAddedEnd.mColumn,
	//	aValue.mRemoved.c_str(), aValue.mRemovedStart.mLine, aValue.mRemovedStart.mColumn, aValue.mRemovedEnd.mLine, aValue.mRemovedEnd.mColumn,
	//	aValue.mAfter.mCursorPosition.mLine, aValue.mAfter.mCursorPosition.mColumn
	//	);

	undo_buffer.resize((size_t)(undo_index + 1));
	undo_buffer.back() = aValue;
	++undo_index;

	//---------------------------
}
void TextEditor::RemoveLine(int aStart, int aEnd){
	assert(!read_only);
	assert(aEnd >= aStart);
	assert(lines.size() > (size_t)(aEnd - aStart));

	ErrorMarkers etmp;
	for (auto& i : error_markers)
	{
		ErrorMarkers::value_type e(i.first >= aStart ? i.first - 1 : i.first, i.second);
		if (e.first >= aStart && e.first <= aEnd)
			continue;
		etmp.insert(e);
	}
	error_markers = std::move(etmp);

	Breakpoints btmp;
	for (auto i : breakpoint)
	{
		if (i >= aStart && i <= aEnd)
			continue;
		btmp.insert(i >= aStart ? i - 1 : i);
	}
	breakpoint = std::move(btmp);

	lines.erase(lines.begin() + aStart, lines.begin() + aEnd);
	assert(!lines.empty());

	text_changed = true;
}
void TextEditor::RemoveLine(int aIndex){
	assert(!read_only);
	assert(lines.size() > 1);

	ErrorMarkers etmp;
	for (auto& i : error_markers)
	{
		ErrorMarkers::value_type e(i.first > aIndex ? i.first - 1 : i.first, i.second);
		if (e.first - 1 == aIndex)
			continue;
		etmp.insert(e);
	}
	error_markers = std::move(etmp);

	Breakpoints btmp;
	for (auto i : breakpoint)
	{
		if (i == aIndex)
			continue;
		btmp.insert(i >= aIndex ? i - 1 : i);
	}
	breakpoint = std::move(btmp);

	lines.erase(lines.begin() + aIndex);
	assert(!lines.empty());

	text_changed = true;
}
void TextEditor::HandleKeyboardInputs(){
	//---------------------------

	ImGuiIO& io = ImGui::GetIO();
	auto shift = io.KeyShift;
	auto ctrl = io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
	auto alt = io.ConfigMacOSXBehaviors ? io.KeyCtrl : io.KeyAlt;

	if (ImGui::IsWindowFocused()){
		if (ImGui::IsWindowHovered()){
			ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
		}
		//ImGui::CaptureKeyboardFromApp(true);

		io.WantCaptureKeyboard = true;
		io.WantTextInput = true;

		if (!IsReadOnly() && ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z)))
			Undo();
		else if (!IsReadOnly() && !ctrl && !shift && alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Backspace)))
			Undo();
		else if (!IsReadOnly() && ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Y)))
			Redo();
		else if (!ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_UpArrow)))
			MoveUp(1, shift);
		else if (!ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_DownArrow)))
			MoveDown(1, shift);
		else if (!alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)))
			MoveLeft(1, shift, ctrl);
		else if (!alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_RightArrow)))
			MoveRight(1, shift, ctrl);
		else if (!alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_PageUp)))
			MoveUp(GetPageSize() - 4, shift);
		else if (!alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_PageDown)))
			MoveDown(GetPageSize() - 4, shift);
		else if (!alt && ctrl && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Home)))
			MoveTop(shift);
		else if (ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_End)))
			MoveBottom(shift);
		else if (!ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Home)))
			MoveHome(shift);
		else if (!ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_End)))
			MoveEnd(shift);
		else if (!IsReadOnly() && !ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
			Delete();
		else if (!IsReadOnly() && !ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Backspace)))
			Backspace();
		else if (!ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert)))
			overwrite ^= true;
		else if (ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert)))
			Copy();
		else if (ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_C)))
			Copy();
		else if (!IsReadOnly() && !ctrl && shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert)))
			Paste();
		else if (!IsReadOnly() && ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_V)))
			Paste();
		else if (ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_X)))
			Cut();
		else if (!ctrl && shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
			Cut();
		else if (ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_A)))
			SelectAll();
		else if (!IsReadOnly() && !ctrl && !shift && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
			EnterCharacter('\n', false);
		else if (!IsReadOnly() && !ctrl && !alt && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Tab)))
			EnterCharacter('\t', shift);

		if (!IsReadOnly() && !io.InputQueueCharacters.empty()){
			for (int i = 0; i < io.InputQueueCharacters.Size; i++)
			{
				auto c = io.InputQueueCharacters[i];
				if (c != 0 && (c == '\n' || c >= 32))
					EnterCharacter(c, shift);
			}
			io.InputQueueCharacters.resize(0);
		}
	}

	//---------------------------
}
void TextEditor::HandleMouseInputs(){
	ImGuiIO& io = ImGui::GetIO();
	auto shift = io.KeyShift;
	auto ctrl = io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
	auto alt = io.ConfigMacOSXBehaviors ? io.KeyCtrl : io.KeyAlt;

	if (ImGui::IsWindowHovered())
	{
		if (!shift && !alt)
		{
			auto click = ImGui::IsMouseClicked(0);
			auto doubleClick = ImGui::IsMouseDoubleClicked(0);
			auto t = ImGui::GetTime();
			auto tripleClick = click && !doubleClick && (last_click != -1.0f && (t - last_click) < io.MouseDoubleClickTime);

			/*
			Left mouse button triple click
			*/

			if (tripleClick)
			{
				if (!ctrl)
				{
					state.mCursorPosition = interactive_start = interactive_end = ScreenPosToCoordinates(ImGui::GetMousePos());
					selection_mode = SelectionMode::Line;
					SetSelection(interactive_start, interactive_end, selection_mode);
				}

				last_click = -1.0f;
			}

			/*
			Left mouse button double click
			*/

			else if (doubleClick)
			{
				if (!ctrl)
				{
					state.mCursorPosition = interactive_start = interactive_end = ScreenPosToCoordinates(ImGui::GetMousePos());
					if (selection_mode == SelectionMode::Line)
						selection_mode = SelectionMode::Normal;
					else
						selection_mode = SelectionMode::Word;
					SetSelection(interactive_start, interactive_end, selection_mode);
				}

				last_click = (float)ImGui::GetTime();
			}

			/*
			Left mouse button click
			*/
			else if (click)
			{
				state.mCursorPosition = interactive_start = interactive_end = ScreenPosToCoordinates(ImGui::GetMousePos());
				if (ctrl)
					selection_mode = SelectionMode::Word;
				else
					selection_mode = SelectionMode::Normal;
				SetSelection(interactive_start, interactive_end, selection_mode);

				last_click = (float)ImGui::GetTime();
			}
			// Mouse left button dragging (=> update selection)
			else if (ImGui::IsMouseDragging(0) && ImGui::IsMouseDown(0))
			{
				io.WantCaptureMouse = true;
				state.mCursorPosition = interactive_end = ScreenPosToCoordinates(ImGui::GetMousePos());
				SetSelection(interactive_start, interactive_end, selection_mode);
			}
		}
	}
}
void TextEditor::Render(){
	//---------------------------

	/* Compute char_advance regarding to scaled font size (Ctrl + mouse wheel)*/
	const float fontSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, "#", nullptr, nullptr).x;
	char_advance = ImVec2(fontSize, ImGui::GetTextLineHeightWithSpacing() * line_spacing);

	/* Update palette with the current alpha from style */
	for (int i = 0; i < (int)PaletteIndex::Max; ++i){
		auto color = ImGui::ColorConvertU32ToFloat4(palette_base[i]);
		color.w *= ImGui::GetStyle().Alpha;
		palette[i] = ImGui::ColorConvertFloat4ToU32(color);
	}

	assert(line_buffer.empty());

	auto contentSize = ImGui::GetWindowContentRegionMax();
	auto drawList = ImGui::GetWindowDrawList();
	float longest(text_start);

	if (scroll_to_top){
		scroll_to_top = false;
		ImGui::SetScrollY(0.f);
	}

	ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
	auto scrollX = ImGui::GetScrollX();
	auto scrollY = ImGui::GetScrollY();

	auto lineNo = (int)floor(scrollY / char_advance.y);
	auto globalLineMax = (int)lines.size();
	auto lineMax = std::max(0, std::min((int)lines.size() - 1, lineNo + (int)floor((scrollY + contentSize.y) / char_advance.y)));

	// Deduce text_start by evaluating lines size (global lineMax) plus two spaces as text width
	char buf[16];
	snprintf(buf, 16, " %d ", globalLineMax);
	text_start = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, buf, nullptr, nullptr).x + left_margin;

	if (!lines.empty()){
		float spaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, " ", nullptr, nullptr).x;

		while (lineNo <= lineMax){
			ImVec2 lineStartScreenPos = ImVec2(cursorScreenPos.x, cursorScreenPos.y + lineNo * char_advance.y);
			ImVec2 textScreenPos = ImVec2(lineStartScreenPos.x + text_start, lineStartScreenPos.y);

			auto& line = lines[lineNo];
			longest = std::max(text_start + TextDistanceToLineStart(Coordinates(lineNo, GetLineMaxColumn(lineNo))), longest);
			auto columnNo = 0;
			Coordinates lineStartCoord(lineNo, 0);
			Coordinates lineEndCoord(lineNo, GetLineMaxColumn(lineNo));

			// Draw selection for the current line
			float sstart = -1.0f;
			float ssend = -1.0f;

			assert(state.mSelectionStart <= state.mSelectionEnd);
			if (state.mSelectionStart <= lineEndCoord){
				sstart = state.mSelectionStart > lineStartCoord ? TextDistanceToLineStart(state.mSelectionStart) : 0.0f;
			}
			if (state.mSelectionEnd > lineStartCoord){
				ssend = TextDistanceToLineStart(state.mSelectionEnd < lineEndCoord ? state.mSelectionEnd : lineEndCoord);
			}
			if (state.mSelectionEnd.mLine > lineNo){
				ssend += char_advance.x;
			}
			if (sstart != -1 && ssend != -1 && sstart < ssend){
				ImVec2 vstart(lineStartScreenPos.x + text_start + sstart, lineStartScreenPos.y);
				ImVec2 vend(lineStartScreenPos.x + text_start + ssend, lineStartScreenPos.y + char_advance.y);
				drawList->AddRectFilled(vstart, vend, palette[(int)PaletteIndex::Selection]);
			}

			// Draw breakpoints
			auto start = ImVec2(lineStartScreenPos.x + scrollX, lineStartScreenPos.y);

			if (breakpoint.count(lineNo + 1) != 0){
				auto end = ImVec2(lineStartScreenPos.x + contentSize.x + 2.0f * scrollX, lineStartScreenPos.y + char_advance.y);
				drawList->AddRectFilled(start, end, palette[(int)PaletteIndex::Breakpoint]);
			}

			// Draw error markers
			auto errorIt = error_markers.find(lineNo + 1);
			if (errorIt != error_markers.end()){
				auto end = ImVec2(lineStartScreenPos.x + contentSize.x + 2.0f * scrollX, lineStartScreenPos.y + char_advance.y);
				drawList->AddRectFilled(start, end, palette[(int)PaletteIndex::ErrorMarker]);

				if (ImGui::IsMouseHoveringRect(lineStartScreenPos, end))
				{
					ImGui::BeginTooltip();
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
					ImGui::Text("Error at line %d:", errorIt->first);
					ImGui::PopStyleColor();
					ImGui::Separator();
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.2f, 1.0f));
					ImGui::Text("%s", errorIt->second.c_str());
					ImGui::PopStyleColor();
					ImGui::EndTooltip();
				}
			}

			// Draw line number (right aligned)
			snprintf(buf, 16, "%d  ", lineNo + 1);

			auto lineNoWidth = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, buf, nullptr, nullptr).x;
			drawList->AddText(ImVec2(lineStartScreenPos.x + text_start - lineNoWidth, lineStartScreenPos.y), palette[(int)PaletteIndex::LineNumber], buf);

			if (state.mCursorPosition.mLine == lineNo){
				auto focused = ImGui::IsWindowFocused();

				// Highlight the current line (where the cursor is)
				if (!HasSelection()){
					auto end = ImVec2(start.x + contentSize.x + scrollX, start.y + char_advance.y);
					drawList->AddRectFilled(start, end, palette[(int)(focused ? PaletteIndex::CurrentLineFill : PaletteIndex::CurrentLineFillInactive)]);
					drawList->AddRect(start, end, palette[(int)PaletteIndex::CurrentLineEdge], 1.0f);
				}

				// Render the cursor
				if (focused){
					auto timeEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					auto elapsed = timeEnd - start_time;
					if (elapsed > 400){
						float width = 1.0f;
						auto cindex = GetCharacterIndex(state.mCursorPosition);
						float cx = TextDistanceToLineStart(state.mCursorPosition);

						if (overwrite && cindex < (int)line.size()){
							auto c = line[cindex].mChar;
							if (c == '\t'){
								auto x = (1.0f + std::floor((1.0f + cx) / (float(tab_size) * spaceSize))) * (float(tab_size) * spaceSize);
								width = x - cx;
							}
							else{
								char buf2[2];
								buf2[0] = line[cindex].mChar;
								buf2[1] = '\0';
								width = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, buf2).x;
							}
						}
						ImVec2 cstart(textScreenPos.x + cx, lineStartScreenPos.y);
						ImVec2 cend(textScreenPos.x + cx + width, lineStartScreenPos.y + char_advance.y);
						drawList->AddRectFilled(cstart, cend, palette[(int)PaletteIndex::Cursor]);
						if (elapsed > 800){
							start_time = timeEnd;
						}
					}
				}
			}

			// Render colorized text
			auto prevColor = line.empty() ? palette[(int)PaletteIndex::Default] : GetGlyphColor(line[0]);
			ImVec2 bufferOffset;

			for (int i = 0; i < line.size();){
				auto& glyph = line[i];
				auto color = GetGlyphColor(glyph);

				if ((color != prevColor || glyph.mChar == '\t' || glyph.mChar == ' ') && !line_buffer.empty()){
					const ImVec2 newOffset(textScreenPos.x + bufferOffset.x, textScreenPos.y + bufferOffset.y);
					drawList->AddText(newOffset, prevColor, line_buffer.c_str());
					auto textSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, line_buffer.c_str(), nullptr, nullptr);
					bufferOffset.x += textSize.x;
					line_buffer.clear();
				}
				prevColor = color;

				if (glyph.mChar == '\t'){
					auto oldX = bufferOffset.x;
					bufferOffset.x = (1.0f + std::floor((1.0f + bufferOffset.x) / (float(tab_size) * spaceSize))) * (float(tab_size) * spaceSize);
					++i;

					if (show_whitespaces){
						const auto s = ImGui::GetFontSize();
						const auto x1 = textScreenPos.x + oldX + 1.0f;
						const auto x2 = textScreenPos.x + bufferOffset.x - 1.0f;
						const auto y = textScreenPos.y + bufferOffset.y + s * 0.5f;
						const ImVec2 p1(x1, y);
						const ImVec2 p2(x2, y);
						const ImVec2 p3(x2 - s * 0.2f, y - s * 0.2f);
						const ImVec2 p4(x2 - s * 0.2f, y + s * 0.2f);
						drawList->AddLine(p1, p2, 0x90909090);
						drawList->AddLine(p2, p3, 0x90909090);
						drawList->AddLine(p2, p4, 0x90909090);
					}
				}
				else if (glyph.mChar == ' '){
					if (show_whitespaces){
						const auto s = ImGui::GetFontSize();
						const auto x = textScreenPos.x + bufferOffset.x + spaceSize * 0.5f;
						const auto y = textScreenPos.y + bufferOffset.y + s * 0.5f;
						drawList->AddCircleFilled(ImVec2(x, y), 1.5f, 0x80808080, 4);
					}
					bufferOffset.x += spaceSize;
					i++;
				}
				else{
					auto l = UTF8CharLength(glyph.mChar);
					while (l-- > 0)
						line_buffer.push_back(line[i++].mChar);
				}
				++columnNo;
			}

			if (!line_buffer.empty()){
				const ImVec2 newOffset(textScreenPos.x + bufferOffset.x, textScreenPos.y + bufferOffset.y);
				drawList->AddText(newOffset, prevColor, line_buffer.c_str());
				line_buffer.clear();
			}

			++lineNo;
		}

		// Draw a tooltip on known identifiers/preprocessor symbols
		if (ImGui::IsMousePosValid()){
			auto id = GetWordAt(ScreenPosToCoordinates(ImGui::GetMousePos()));
			if (!id.empty())
			{
				auto it = language_definition.identifiers.find(id);
				if (it != language_definition.identifiers.end())
				{
					ImGui::BeginTooltip();
					ImGui::TextUnformatted(it->second.mDeclaration.c_str());
					ImGui::EndTooltip();
				}
				else
				{
					auto pi = language_definition.preproc_dentifiers.find(id);
					if (pi != language_definition.preproc_dentifiers.end())
					{
						ImGui::BeginTooltip();
						ImGui::TextUnformatted(pi->second.mDeclaration.c_str());
						ImGui::EndTooltip();
					}
				}
			}
		}
	}

	ImGui::Dummy(ImVec2((longest + 2), lines.size() * char_advance.y));

	if (scroll_to_cursor){
		EnsureCursorVisible();
		ImGui::SetWindowFocus();
		scroll_to_cursor = false;
	}

	//---------------------------
}
void TextEditor::Render(const char* aTitle, const ImVec2& aSize, bool aBorder){
	within_render = true;
	text_changed = false;
	cursor_position_changed = false;

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::ColorConvertU32ToFloat4(palette[(int)PaletteIndex::Background]));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	if (!ignore_imgui_child){
		ImGui::BeginChild(aTitle, aSize, aBorder, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NoMove);
	}
	if (handle_keyboard_inputs){
		HandleKeyboardInputs();
		ImGui::PushAllowKeyboardFocus(true);
	}
	if (handle_mouse_inputs){
		HandleMouseInputs();
	}

	ColorizeInternal();
	Render();

	if (handle_keyboard_inputs)
		ImGui::PopAllowKeyboardFocus();

	if (!ignore_imgui_child)
		ImGui::EndChild();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	within_render = false;
}
void TextEditor::SetText(const std::string & aText){
	lines.clear();
	lines.emplace_back(Line());
	for (auto chr : aText)
	{
		if (chr == '\r')
		{
			// ignore the carriage return character
		}
		else if (chr == '\n')
			lines.emplace_back(Line());
		else
		{
			lines.back().emplace_back(Glyph(chr, PaletteIndex::Default));
		}
	}

	text_changed = true;
	scroll_to_top = true;

	undo_buffer.clear();
	undo_index = 0;

	Colorize();
}
void TextEditor::SetTextLines(const std::vector<std::string> & aLines){
	lines.clear();

	if (aLines.empty())
	{
		lines.emplace_back(Line());
	}
	else
	{
		lines.resize(aLines.size());

		for (size_t i = 0; i < aLines.size(); ++i)
		{
			const std::string & aLine = aLines[i];

			lines[i].reserve(aLine.size());
			for (size_t j = 0; j < aLine.size(); ++j)
				lines[i].emplace_back(Glyph(aLine[j], PaletteIndex::Default));
		}
	}

	text_changed = true;
	scroll_to_top = true;

	undo_buffer.clear();
	undo_index = 0;

	Colorize();
}
void TextEditor::EnterCharacter(ImWchar aChar, bool aShift){
	//---------------------------

	assert(!read_only);

	UndoRecord u;

	u.mBefore = state;

	if (HasSelection()){
		if (aChar == '\t' && state.mSelectionStart.mLine != state.mSelectionEnd.mLine){

			auto start = state.mSelectionStart;
			auto end = state.mSelectionEnd;
			auto originalEnd = end;

			if (start > end)
				std::swap(start, end);
			start.mColumn = 0;
			//			end.mColumn = end.mLine < lines.size() ? lines[end.mLine].size() : 0;
			if (end.mColumn == 0 && end.mLine > 0)
				--end.mLine;
			if (end.mLine >= (int)lines.size())
				end.mLine = lines.empty() ? 0 : (int)lines.size() - 1;
			end.mColumn = GetLineMaxColumn(end.mLine);

			//if (end.mColumn >= GetLineMaxColumn(end.mLine))
			//	end.mColumn = GetLineMaxColumn(end.mLine) - 1;

			u.mRemovedStart = start;
			u.mRemovedEnd = end;
			u.mRemoved = GetText(start, end);

			bool modified = false;

			for (int i = start.mLine; i <= end.mLine; i++)
			{
				auto& line = lines[i];
				if (aShift)
				{
					if (!line.empty())
					{
						if (line.front().mChar == '\t')
						{
							line.erase(line.begin());
							modified = true;
						}
						else
						{
							for (int j = 0; j < tab_size && !line.empty() && line.front().mChar == ' '; j++)
							{
								line.erase(line.begin());
								modified = true;
							}
						}
					}
				}
				else
				{
					line.insert(line.begin(), Glyph('\t', TextEditor::PaletteIndex::Background));
					modified = true;
				}
			}

			if (modified)
			{
				start = Coordinates(start.mLine, GetCharacterColumn(start.mLine, 0));
				Coordinates rangeEnd;
				if (originalEnd.mColumn != 0)
				{
					end = Coordinates(end.mLine, GetLineMaxColumn(end.mLine));
					rangeEnd = end;
					u.mAdded = GetText(start, end);
				}
				else
				{
					end = Coordinates(originalEnd.mLine, 0);
					rangeEnd = Coordinates(end.mLine - 1, GetLineMaxColumn(end.mLine - 1));
					u.mAdded = GetText(start, rangeEnd);
				}

				u.mAddedStart = start;
				u.mAddedEnd = rangeEnd;
				u.mAfter = state;

				state.mSelectionStart = start;
				state.mSelectionEnd = end;
				AddUndo(u);

				text_changed = true;

				EnsureCursorVisible();
			}

			return;
		} // c == '\t'
		else{
			u.mRemoved = GetSelectedText();
			u.mRemovedStart = state.mSelectionStart;
			u.mRemovedEnd = state.mSelectionEnd;
			DeleteSelection();
		}
	} // HasSelection

	auto coord = GetActualCursorCoordinates();
	u.mAddedStart = coord;

	assert(!lines.empty());

	if (aChar == '\n'){
		InsertLine(coord.mLine + 1);
		auto& line = lines[coord.mLine];
		auto& newLine = lines[coord.mLine + 1];

		if (language_definition.auto_indentation)
			for (size_t it = 0; it < line.size() && isascii(line[it].mChar) && isblank(line[it].mChar); ++it)
				newLine.push_back(line[it]);

		const size_t whitespaceSize = newLine.size();
		auto cindex = GetCharacterIndex(coord);
		newLine.insert(newLine.end(), line.begin() + cindex, line.end());
		line.erase(line.begin() + cindex, line.begin() + line.size());
		SetCursorPosition(Coordinates(coord.mLine + 1, GetCharacterColumn(coord.mLine + 1, (int)whitespaceSize)));
		u.mAdded = (char)aChar;
	}
	else{
		char buf[7];
		int e = ImTextCharToUtf8(buf, 7, aChar);
		if (e > 0){
			buf[e] = '\0';
			auto& line = lines[coord.mLine];
			auto cindex = GetCharacterIndex(coord);

			if (overwrite && cindex < (int)line.size()){
				auto d = UTF8CharLength(line[cindex].mChar);

				u.mRemovedStart = state.mCursorPosition;
				u.mRemovedEnd = Coordinates(coord.mLine, GetCharacterColumn(coord.mLine, cindex + d));

				while (d-- > 0 && cindex < (int)line.size()){
					u.mRemoved += line[cindex].mChar;
					line.erase(line.begin() + cindex);
				}
			}

			for (auto p = buf; *p != '\0'; p++, ++cindex){
				line.insert(line.begin() + cindex, Glyph(*p, PaletteIndex::Default));
			}
			u.mAdded = buf;

			SetCursorPosition(Coordinates(coord.mLine, GetCharacterColumn(coord.mLine, cindex)));
		}
		else{
			return;
		}
	}

	text_changed = true;

	u.mAddedEnd = GetActualCursorCoordinates();
	u.mAfter = state;

	AddUndo(u);

	Colorize(coord.mLine - 1, 3);
	EnsureCursorVisible();

	//---------------------------
}
void TextEditor::SetReadOnly(bool aValue){
	read_only = aValue;
}
void TextEditor::SetColorizerEnable(bool aValue){
	colorizer_enabled = aValue;
}
void TextEditor::SetCursorPosition(const Coordinates & aPosition){
	if (state.mCursorPosition != aPosition)
	{
		state.mCursorPosition = aPosition;
		cursor_position_changed = true;
		EnsureCursorVisible();
	}
}
void TextEditor::SetSelectionStart(const Coordinates & aPosition){
	state.mSelectionStart = SanitizeCoordinates(aPosition);
	if (state.mSelectionStart > state.mSelectionEnd)
		std::swap(state.mSelectionStart, state.mSelectionEnd);
}
void TextEditor::SetSelectionEnd(const Coordinates & aPosition){
	state.mSelectionEnd = SanitizeCoordinates(aPosition);
	if (state.mSelectionStart > state.mSelectionEnd)
		std::swap(state.mSelectionStart, state.mSelectionEnd);
}
void TextEditor::SetSelection(const Coordinates & aStart, const Coordinates & aEnd, SelectionMode aMode){
	auto oldSelStart = state.mSelectionStart;
	auto oldSelEnd = state.mSelectionEnd;

	state.mSelectionStart = SanitizeCoordinates(aStart);
	state.mSelectionEnd = SanitizeCoordinates(aEnd);
	if (state.mSelectionStart > state.mSelectionEnd)
		std::swap(state.mSelectionStart, state.mSelectionEnd);

	switch (aMode)
	{
	case TextEditor::SelectionMode::Normal:
		break;
	case TextEditor::SelectionMode::Word:
	{
		state.mSelectionStart = FindWordStart(state.mSelectionStart);
		if (!IsOnWordBoundary(state.mSelectionEnd))
			state.mSelectionEnd = FindWordEnd(FindWordStart(state.mSelectionEnd));
		break;
	}
	case TextEditor::SelectionMode::Line:
	{
		const auto lineNo = state.mSelectionEnd.mLine;
		const auto lineSize = (size_t)lineNo < lines.size() ? lines[lineNo].size() : 0;
		state.mSelectionStart = Coordinates(state.mSelectionStart.mLine, 0);
		state.mSelectionEnd = Coordinates(lineNo, GetLineMaxColumn(lineNo));
		break;
	}
	default:
		break;
	}

	if (state.mSelectionStart != oldSelStart ||
		state.mSelectionEnd != oldSelEnd)
		cursor_position_changed = true;
}
void TextEditor::SetTabSize(int aValue){
	tab_size = std::max(0, std::min(32, aValue));
}
void TextEditor::InsertText(const std::string & aValue){
	InsertText(aValue.c_str());
}
void TextEditor::InsertText(const char * aValue){
	if (aValue == nullptr)
		return;

	auto pos = GetActualCursorCoordinates();
	auto start = std::min(pos, state.mSelectionStart);
	int totalLines = pos.mLine - start.mLine;

	totalLines += InsertTextAt(pos, aValue);

	SetSelection(pos, pos);
	SetCursorPosition(pos);
	Colorize(start.mLine - 1, totalLines + 2);
}
void TextEditor::DeleteSelection(){
	assert(state.mSelectionEnd >= state.mSelectionStart);

	if (state.mSelectionEnd == state.mSelectionStart)
		return;

	DeleteRange(state.mSelectionStart, state.mSelectionEnd);

	SetSelection(state.mSelectionStart, state.mSelectionStart);
	SetCursorPosition(state.mSelectionStart);
	Colorize(state.mSelectionStart.mLine, 1);
}
void TextEditor::MoveUp(int aAmount, bool aSelect){
	auto oldPos = state.mCursorPosition;
	state.mCursorPosition.mLine = std::max(0, state.mCursorPosition.mLine - aAmount);
	if (oldPos != state.mCursorPosition)
	{
		if (aSelect)
		{
			if (oldPos == interactive_start)
				interactive_start = state.mCursorPosition;
			else if (oldPos == interactive_end)
				interactive_end = state.mCursorPosition;
			else
			{
				interactive_start = state.mCursorPosition;
				interactive_end = oldPos;
			}
		}
		else
			interactive_start = interactive_end = state.mCursorPosition;
		SetSelection(interactive_start, interactive_end);

		EnsureCursorVisible();
	}
}
void TextEditor::MoveDown(int aAmount, bool aSelect){
	assert(state.mCursorPosition.mColumn >= 0);
	auto oldPos = state.mCursorPosition;
	state.mCursorPosition.mLine = std::max(0, std::min((int)lines.size() - 1, state.mCursorPosition.mLine + aAmount));

	if (state.mCursorPosition != oldPos)
	{
		if (aSelect)
		{
			if (oldPos == interactive_end)
				interactive_end = state.mCursorPosition;
			else if (oldPos == interactive_start)
				interactive_start = state.mCursorPosition;
			else
			{
				interactive_start = oldPos;
				interactive_end = state.mCursorPosition;
			}
		}
		else
			interactive_start = interactive_end = state.mCursorPosition;
		SetSelection(interactive_start, interactive_end);

		EnsureCursorVisible();
	}
}
void TextEditor::MoveLeft(int aAmount, bool aSelect, bool aWordMode){
	if (lines.empty())
		return;

	auto oldPos = state.mCursorPosition;
	state.mCursorPosition = GetActualCursorCoordinates();
	auto line = state.mCursorPosition.mLine;
	auto cindex = GetCharacterIndex(state.mCursorPosition);

	while (aAmount-- > 0)
	{
		if (cindex == 0)
		{
			if (line > 0)
			{
				--line;
				if ((int)lines.size() > line)
					cindex = (int)lines[line].size();
				else
					cindex = 0;
			}
		}
		else
		{
			--cindex;
			if (cindex > 0)
			{
				if ((int)lines.size() > line)
				{
					while (cindex > 0 && IsUTFSequence(lines[line][cindex].mChar))
						--cindex;
				}
			}
		}

		state.mCursorPosition = Coordinates(line, GetCharacterColumn(line, cindex));
		if (aWordMode)
		{
			state.mCursorPosition = FindWordStart(state.mCursorPosition);
			cindex = GetCharacterIndex(state.mCursorPosition);
		}
	}

	state.mCursorPosition = Coordinates(line, GetCharacterColumn(line, cindex));

	assert(state.mCursorPosition.mColumn >= 0);
	if (aSelect)
	{
		if (oldPos == interactive_start)
			interactive_start = state.mCursorPosition;
		else if (oldPos == interactive_end)
			interactive_end = state.mCursorPosition;
		else
		{
			interactive_start = state.mCursorPosition;
			interactive_end = oldPos;
		}
	}
	else
		interactive_start = interactive_end = state.mCursorPosition;
	SetSelection(interactive_start, interactive_end, aSelect && aWordMode ? SelectionMode::Word : SelectionMode::Normal);

	EnsureCursorVisible();
}
void TextEditor::MoveRight(int aAmount, bool aSelect, bool aWordMode){
	auto oldPos = state.mCursorPosition;

	if (lines.empty() || oldPos.mLine >= lines.size())
		return;

	auto cindex = GetCharacterIndex(state.mCursorPosition);
	while (aAmount-- > 0)
	{
		auto lindex = state.mCursorPosition.mLine;
		auto& line = lines[lindex];

		if (cindex >= line.size())
		{
			if (state.mCursorPosition.mLine < lines.size() - 1)
			{
				state.mCursorPosition.mLine = std::max(0, std::min((int)lines.size() - 1, state.mCursorPosition.mLine + 1));
				state.mCursorPosition.mColumn = 0;
			}
			else
				return;
		}
		else
		{
			cindex += UTF8CharLength(line[cindex].mChar);
			state.mCursorPosition = Coordinates(lindex, GetCharacterColumn(lindex, cindex));
			if (aWordMode)
				state.mCursorPosition = FindNextWord(state.mCursorPosition);
		}
	}

	if (aSelect)
	{
		if (oldPos == interactive_end)
			interactive_end = SanitizeCoordinates(state.mCursorPosition);
		else if (oldPos == interactive_start)
			interactive_start = state.mCursorPosition;
		else
		{
			interactive_start = oldPos;
			interactive_end = state.mCursorPosition;
		}
	}
	else
		interactive_start = interactive_end = state.mCursorPosition;
	SetSelection(interactive_start, interactive_end, aSelect && aWordMode ? SelectionMode::Word : SelectionMode::Normal);

	EnsureCursorVisible();
}
void TextEditor::MoveTop(bool aSelect){
	auto oldPos = state.mCursorPosition;
	SetCursorPosition(Coordinates(0, 0));

	if (state.mCursorPosition != oldPos)
	{
		if (aSelect)
		{
			interactive_end = oldPos;
			interactive_start = state.mCursorPosition;
		}
		else
			interactive_start = interactive_end = state.mCursorPosition;
		SetSelection(interactive_start, interactive_end);
	}
}
void TextEditor::TextEditor::MoveBottom(bool aSelect){
	auto oldPos = GetCursorPosition();
	auto newPos = Coordinates((int)lines.size() - 1, 0);
	SetCursorPosition(newPos);
	if (aSelect)
	{
		interactive_start = oldPos;
		interactive_end = newPos;
	}
	else
		interactive_start = interactive_end = newPos;
	SetSelection(interactive_start, interactive_end);
}
void TextEditor::MoveHome(bool aSelect){
	auto oldPos = state.mCursorPosition;
	SetCursorPosition(Coordinates(state.mCursorPosition.mLine, 0));

	if (state.mCursorPosition != oldPos)
	{
		if (aSelect)
		{
			if (oldPos == interactive_start)
				interactive_start = state.mCursorPosition;
			else if (oldPos == interactive_end)
				interactive_end = state.mCursorPosition;
			else
			{
				interactive_start = state.mCursorPosition;
				interactive_end = oldPos;
			}
		}
		else
			interactive_start = interactive_end = state.mCursorPosition;
		SetSelection(interactive_start, interactive_end);
	}
}
void TextEditor::MoveEnd(bool aSelect){
	auto oldPos = state.mCursorPosition;
	SetCursorPosition(Coordinates(state.mCursorPosition.mLine, GetLineMaxColumn(oldPos.mLine)));

	if (state.mCursorPosition != oldPos)
	{
		if (aSelect)
		{
			if (oldPos == interactive_end)
				interactive_end = state.mCursorPosition;
			else if (oldPos == interactive_start)
				interactive_start = state.mCursorPosition;
			else
			{
				interactive_start = oldPos;
				interactive_end = state.mCursorPosition;
			}
		}
		else
			interactive_start = interactive_end = state.mCursorPosition;
		SetSelection(interactive_start, interactive_end);
	}
}
void TextEditor::Delete(){
	assert(!read_only);

	if (lines.empty())
		return;

	UndoRecord u;
	u.mBefore = state;

	if (HasSelection())
	{
		u.mRemoved = GetSelectedText();
		u.mRemovedStart = state.mSelectionStart;
		u.mRemovedEnd = state.mSelectionEnd;

		DeleteSelection();
	}
	else
	{
		auto pos = GetActualCursorCoordinates();
		SetCursorPosition(pos);
		auto& line = lines[pos.mLine];

		if (pos.mColumn == GetLineMaxColumn(pos.mLine))
		{
			if (pos.mLine == (int)lines.size() - 1)
				return;

			u.mRemoved = '\n';
			u.mRemovedStart = u.mRemovedEnd = GetActualCursorCoordinates();
			Advance(u.mRemovedEnd);

			auto& nextLine = lines[pos.mLine + 1];
			line.insert(line.end(), nextLine.begin(), nextLine.end());
			RemoveLine(pos.mLine + 1);
		}
		else
		{
			auto cindex = GetCharacterIndex(pos);
			u.mRemovedStart = u.mRemovedEnd = GetActualCursorCoordinates();
			u.mRemovedEnd.mColumn++;
			u.mRemoved = GetText(u.mRemovedStart, u.mRemovedEnd);

			auto d = UTF8CharLength(line[cindex].mChar);
			while (d-- > 0 && cindex < (int)line.size())
				line.erase(line.begin() + cindex);
		}

		text_changed = true;

		Colorize(pos.mLine, 1);
	}

	u.mAfter = state;
	AddUndo(u);
}
void TextEditor::Backspace(){
	assert(!read_only);

	if (lines.empty())
		return;

	UndoRecord u;
	u.mBefore = state;

	if (HasSelection())
	{
		u.mRemoved = GetSelectedText();
		u.mRemovedStart = state.mSelectionStart;
		u.mRemovedEnd = state.mSelectionEnd;

		DeleteSelection();
	}
	else
	{
		auto pos = GetActualCursorCoordinates();
		SetCursorPosition(pos);

		if (state.mCursorPosition.mColumn == 0)
		{
			if (state.mCursorPosition.mLine == 0)
				return;

			u.mRemoved = '\n';
			u.mRemovedStart = u.mRemovedEnd = Coordinates(pos.mLine - 1, GetLineMaxColumn(pos.mLine - 1));
			Advance(u.mRemovedEnd);

			auto& line = lines[state.mCursorPosition.mLine];
			auto& prevLine = lines[state.mCursorPosition.mLine - 1];
			auto prevSize = GetLineMaxColumn(state.mCursorPosition.mLine - 1);
			prevLine.insert(prevLine.end(), line.begin(), line.end());

			ErrorMarkers etmp;
			for (auto& i : error_markers)
				etmp.insert(ErrorMarkers::value_type(i.first - 1 == state.mCursorPosition.mLine ? i.first - 1 : i.first, i.second));
			error_markers = std::move(etmp);

			RemoveLine(state.mCursorPosition.mLine);
			--state.mCursorPosition.mLine;
			state.mCursorPosition.mColumn = prevSize;
		}
		else
		{
			auto& line = lines[state.mCursorPosition.mLine];
			auto cindex = GetCharacterIndex(pos) - 1;
			auto cend = cindex + 1;
			while (cindex > 0 && IsUTFSequence(line[cindex].mChar))
				--cindex;

			//if (cindex > 0 && UTF8CharLength(line[cindex].mChar) > 1)
			//	--cindex;

			u.mRemovedStart = u.mRemovedEnd = GetActualCursorCoordinates();
			--u.mRemovedStart.mColumn;
			--state.mCursorPosition.mColumn;

			while (cindex < line.size() && cend-- > cindex)
			{
				u.mRemoved += line[cindex].mChar;
				line.erase(line.begin() + cindex);
			}
		}

		text_changed = true;

		EnsureCursorVisible();
		Colorize(state.mCursorPosition.mLine, 1);
	}

	u.mAfter = state;
	AddUndo(u);
}
void TextEditor::SelectWordUnderCursor(){
	auto c = GetCursorPosition();
	SetSelection(FindWordStart(c), FindWordEnd(c));
}
void TextEditor::SelectAll(){
	SetSelection(Coordinates(0, 0), Coordinates((int)lines.size(), 0));
}
void TextEditor::Copy(){
	if (HasSelection())
	{
		ImGui::SetClipboardText(GetSelectedText().c_str());
	}
	else
	{
		if (!lines.empty())
		{
			std::string str;
			auto& line = lines[GetActualCursorCoordinates().mLine];
			for (auto& g : line)
				str.push_back(g.mChar);
			ImGui::SetClipboardText(str.c_str());
		}
	}
}
void TextEditor::Cut(){
	if (IsReadOnly())
	{
		Copy();
	}
	else
	{
		if (HasSelection())
		{
			UndoRecord u;
			u.mBefore = state;
			u.mRemoved = GetSelectedText();
			u.mRemovedStart = state.mSelectionStart;
			u.mRemovedEnd = state.mSelectionEnd;

			Copy();
			DeleteSelection();

			u.mAfter = state;
			AddUndo(u);
		}
	}
}
void TextEditor::Paste(){
	if (IsReadOnly())
		return;

	auto clipText = ImGui::GetClipboardText();
	if (clipText != nullptr && strlen(clipText) > 0)
	{
		UndoRecord u;
		u.mBefore = state;

		if (HasSelection())
		{
			u.mRemoved = GetSelectedText();
			u.mRemovedStart = state.mSelectionStart;
			u.mRemovedEnd = state.mSelectionEnd;
			DeleteSelection();
		}

		u.mAdded = clipText;
		u.mAddedStart = GetActualCursorCoordinates();

		InsertText(clipText);

		u.mAddedEnd = GetActualCursorCoordinates();
		u.mAfter = state;
		AddUndo(u);
	}
}
void TextEditor::Undo(int aSteps){
	while (CanUndo() && aSteps-- > 0)
		undo_buffer[--undo_index].Undo(this);
}
void TextEditor::Redo(int aSteps){
	while (CanRedo() && aSteps-- > 0)
		undo_buffer[undo_index++].Redo(this);
}
void TextEditor::ProcessInputs(){
}
void TextEditor::Colorize(int aFromLine, int aLines){
	int toLine = aLines == -1 ? (int)lines.size() : std::min((int)lines.size(), aFromLine + aLines);
	color_range_min = std::min(color_range_min, aFromLine);
	color_range_max = std::max(color_range_max, toLine);
	color_range_min = std::max(0, color_range_min);
	color_range_max = std::max(color_range_min, color_range_max);
	check_comments = true;
}
void TextEditor::ColorizeRange(int aFromLine, int aToLine){
	if (lines.empty() || aFromLine >= aToLine){
		return;
	}

	std::string buffer;
	std::cmatch results;
	std::string id;

	int endLine = std::max(0, std::min((int)lines.size(), aToLine));
	for (int i = aFromLine; i < endLine; ++i){
		auto& line = lines[i];

		if (line.empty()){
			continue;
		}

		buffer.resize(line.size());
		for (size_t j = 0; j < line.size(); ++j){
			auto& col = line[j];
			buffer[j] = col.mChar;
			col.color_index = PaletteIndex::Default;
		}

		const char * bufferBegin = &buffer.front();
		const char * bufferEnd = bufferBegin + buffer.size();

		auto last = bufferEnd;

		for (auto first = bufferBegin; first != last; ){
			const char * token_begin = nullptr;
			const char * token_end = nullptr;
			PaletteIndex token_color = PaletteIndex::Default;
			bool hasTokenizeResult = false;

			if (language_definition.tokenize != nullptr){
				if (language_definition.tokenize(first, last, token_begin, token_end, token_color)){
					hasTokenizeResult = true;
				}
			}
			if (hasTokenizeResult == false){
				// todo : remove
				//printf("using regex for %.*s\n", first + 10 < last ? 10 : int(last - first), first);

				for (auto& p : regex_list)
				{
					if (std::regex_search(first, last, results, p.first, std::regex_constants::match_continuous))
					{
						hasTokenizeResult = true;

						auto& v = *results.begin();
						token_begin = v.first;
						token_end = v.second;
						token_color = p.second;
						break;
					}
				}
			}
			if (hasTokenizeResult == false){
				first++;
			}
			else{
				const size_t token_length = token_end - token_begin;

				if (token_color == PaletteIndex::Identifier){
					id.assign(token_begin, token_end);

					// todo : allmost all language definitions use lower case to specify keywords, so shouldn't this use ::tolower ?
					if (!language_definition.case_sensitive){
						std::transform(id.begin(), id.end(), id.begin(), ::toupper);
					}

					if (!line[first - bufferBegin].preprocessor){
						if (language_definition.keywords.count(id) != 0){
							token_color = PaletteIndex::Keyword;
						}
						else if (language_definition.identifiers.count(id) != 0){
							token_color = PaletteIndex::KnownIdentifier;
						}
						else if (language_definition.preproc_dentifiers.count(id) != 0){
							token_color = PaletteIndex::PreprocIdentifier;
						}
					}
					else{
						if (language_definition.preproc_dentifiers.count(id) != 0){
							token_color = PaletteIndex::PreprocIdentifier;
						}
					}
				}

				for (size_t j = 0; j < token_length; ++j){
					line[(token_begin - bufferBegin) + j].color_index = token_color;
				}

				first = token_end;
			}
		}
	}
}
void TextEditor::ColorizeInternal(){
	if (lines.empty() || !colorizer_enabled){
		return;
	}

	if (check_comments){
		auto endLine = lines.size();
		auto endIndex = 0;
		auto commentStartLine = endLine;
		auto commentStartIndex = endIndex;
		auto withinString = false;
		auto withinSingleLineComment = false;
		auto withinPreproc = false;
		auto firstChar = true;			// there is no other non-whitespace characters in the line before
		auto concatenate = false;		// '\' on the very end of the line
		auto currentLine = 0;
		auto currentIndex = 0;
		while (currentLine < endLine || currentIndex < endIndex){
			auto& line = lines[currentLine];

			if (currentIndex == 0 && !concatenate){
				withinSingleLineComment = false;
				withinPreproc = false;
				firstChar = true;
			}

			concatenate = false;

			if (!line.empty()){
				auto& g = line[currentIndex];
				auto c = g.mChar;

				if (c != language_definition.preproc_char && !isspace(c)){
					firstChar = false;
				}

				if (currentIndex == (int)line.size() - 1 && line[line.size() - 1].mChar == '\\'){
					concatenate = true;
				}

				bool inComment = (commentStartLine < currentLine || (commentStartLine == currentLine && commentStartIndex <= currentIndex));

				if (withinString){
					line[currentIndex].multiline_comment = inComment;

					if (c == '\"')
					{
						if (currentIndex + 1 < (int)line.size() && line[currentIndex + 1].mChar == '\"')
						{
							currentIndex += 1;
							if (currentIndex < (int)line.size())
								line[currentIndex].multiline_comment = inComment;
						}
						else
							withinString = false;
					}
					else if (c == '\\')
					{
						currentIndex += 1;
						if (currentIndex < (int)line.size())
							line[currentIndex].multiline_comment = inComment;
					}
				}
				else{
					if (firstChar && c == language_definition.preproc_char){
						withinPreproc = true;
					}

					if (c == '\"'){
						withinString = true;
						line[currentIndex].multiline_comment = inComment;
					}
					else{
						auto pred = [](const char& a, const Glyph& b) { return a == b.mChar; };
						auto from = line.begin() + currentIndex;
						auto& startStr = language_definition.comment_start;
						auto& singleStartStr = language_definition.single_line_comment;

						if (singleStartStr.size() > 0 &&
							currentIndex + singleStartStr.size() <= line.size() &&
							equals(singleStartStr.begin(), singleStartStr.end(), from, from + singleStartStr.size(), pred))
						{
							withinSingleLineComment = true;
						}
						else if (!withinSingleLineComment && currentIndex + startStr.size() <= line.size() &&
							equals(startStr.begin(), startStr.end(), from, from + startStr.size(), pred))
						{
							commentStartLine = currentLine;
							commentStartIndex = currentIndex;
						}

						inComment = inComment = (commentStartLine < currentLine || (commentStartLine == currentLine && commentStartIndex <= currentIndex));

						line[currentIndex].multiline_comment = inComment;
						line[currentIndex].comment = withinSingleLineComment;

						auto& endStr = language_definition.comment_end;
						if (currentIndex + 1 >= (int)endStr.size() &&
							equals(endStr.begin(), endStr.end(), from + 1 - endStr.size(), from + 1, pred))
						{
							commentStartIndex = endIndex;
							commentStartLine = endLine;
						}
					}
				}
				line[currentIndex].preprocessor = withinPreproc;
				currentIndex += UTF8CharLength(c);
				if (currentIndex >= (int)line.size()){
					currentIndex = 0;
					++currentLine;
				}
			}
			else{
				currentIndex = 0;
				++currentLine;
			}
		}
		check_comments = false;
	}

	if (color_range_min < color_range_max){
		const int increment = (language_definition.tokenize == nullptr) ? 10 : 10000;
		const int to = std::min(color_range_min + increment, color_range_max);
		ColorizeRange(color_range_min, to);
		color_range_min = to;

		if (color_range_max == color_range_min){
			color_range_min = std::numeric_limits<int>::max();
			color_range_max = 0;
		}
		return;
	}
}
void TextEditor::EnsureCursorVisible(){
	if (!within_render){
		scroll_to_cursor = true;
		return;
	}

	float scrollX = ImGui::GetScrollX();
	float scrollY = ImGui::GetScrollY();

	auto height = ImGui::GetWindowHeight();
	auto width = ImGui::GetWindowWidth();

	auto top = 1 + (int)ceil(scrollY / char_advance.y);
	auto bottom = (int)ceil((scrollY + height) / char_advance.y);

	auto left = (int)ceil(scrollX / char_advance.x);
	auto right = (int)ceil((scrollX + width) / char_advance.x);

	auto pos = GetActualCursorCoordinates();
	auto len = TextDistanceToLineStart(pos);

	if (pos.mLine < top)
		ImGui::SetScrollY(std::max(0.0f, (pos.mLine - 1) * char_advance.y));
	if (pos.mLine > bottom - 4)
		ImGui::SetScrollY(std::max(0.0f, (pos.mLine + 4) * char_advance.y - height));
	if (len + text_start < left + 4)
		ImGui::SetScrollX(std::max(0.0f, len + text_start - 4));
	if (len + text_start > right - 4)
		ImGui::SetScrollX(std::max(0.0f, len + text_start + 4 - width));
}
void TextEditor::UndoRecord::Undo(TextEditor * aEditor){
	if (!mAdded.empty())
	{
		aEditor->DeleteRange(mAddedStart, mAddedEnd);
		aEditor->Colorize(mAddedStart.mLine - 1, mAddedEnd.mLine - mAddedStart.mLine + 2);
	}

	if (!mRemoved.empty())
	{
		auto start = mRemovedStart;
		aEditor->InsertTextAt(start, mRemoved.c_str());
		aEditor->Colorize(mRemovedStart.mLine - 1, mRemovedEnd.mLine - mRemovedStart.mLine + 2);
	}

	aEditor->state = mBefore;
	aEditor->EnsureCursorVisible();

}
void TextEditor::UndoRecord::Redo(TextEditor * aEditor){
	if (!mRemoved.empty())
	{
		aEditor->DeleteRange(mRemovedStart, mRemovedEnd);
		aEditor->Colorize(mRemovedStart.mLine - 1, mRemovedEnd.mLine - mRemovedStart.mLine + 1);
	}

	if (!mAdded.empty())
	{
		auto start = mAddedStart;
		aEditor->InsertTextAt(start, mAdded.c_str());
		aEditor->Colorize(mAddedStart.mLine - 1, mAddedEnd.mLine - mAddedStart.mLine + 1);
	}

	aEditor->state = mAfter;
	aEditor->EnsureCursorVisible();
}

const TextEditor::Palette & TextEditor::GetDarkPalette(){
	const static Palette p = { {
			0xff7f7f7f,	// Default
			0xffd69c56,	// Keyword
			0xff00ff00,	// Number
			0xff7070e0,	// String
			0xff70a0e0, // Char literal
			0xffffffff, // Punctuation
			0xff408080,	// Preprocessor
			0xffaaaaaa, // Identifier
			0xff9bc64d, // Known identifier
			0xffc040a0, // Preproc identifier
			0xff206020, // Comment (single line)
			0xff406020, // Comment (multi line)
			0xff101010, // Background
			0xffe0e0e0, // Cursor
			0x80a06020, // Selection
			0x800020ff, // ErrorMarker
			0x40f08000, // Breakpoint
			0xff707000, // Line number
			0x40000000, // Current line fill
			0x40808080, // Current line fill (inactive)
			0x40a0a0a0, // Current line edge
		} };
	return p;
}
const TextEditor::Palette & TextEditor::GetLightPalette(){
	const static Palette p = { {
			0xff7f7f7f,	// None
			0xffff0c06,	// Keyword
			0xff008000,	// Number
			0xff2020a0,	// String
			0xff304070, // Char literal
			0xff000000, // Punctuation
			0xff406060,	// Preprocessor
			0xff404040, // Identifier
			0xff606010, // Known identifier
			0xffc040a0, // Preproc identifier
			0xff205020, // Comment (single line)
			0xff405020, // Comment (multi line)
			0xffffffff, // Background
			0xff000000, // Cursor
			0x80600000, // Selection
			0xa00010ff, // ErrorMarker
			0x80f08000, // Breakpoint
			0xff505000, // Line number
			0x40000000, // Current line fill
			0x40808080, // Current line fill (inactive)
			0x40000000, // Current line edge
		} };
	return p;
}
const TextEditor::Palette & TextEditor::GetRetroBluePalette(){
	const static Palette p = { {
			0xff00ffff,	// None
			0xffffff00,	// Keyword
			0xff00ff00,	// Number
			0xff808000,	// String
			0xff808000, // Char literal
			0xffffffff, // Punctuation
			0xff008000,	// Preprocessor
			0xff00ffff, // Identifier
			0xffffffff, // Known identifier
			0xffff00ff, // Preproc identifier
			0xff808080, // Comment (single line)
			0xff404040, // Comment (multi line)
			0xff800000, // Background
			0xff0080ff, // Cursor
			0x80ffff00, // Selection
			0xa00000ff, // ErrorMarker
			0x80ff8000, // Breakpoint
			0xff808000, // Line number
			0x40000000, // Current line fill
			0x40808080, // Current line fill (inactive)
			0x40000000, // Current line edge
		} };
	return p;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::Cpp(){
	static bool inited = false;
	static LanguageDefinition langDef;
	//---------------------------

	if (!inited){
		static const char* const cppKeywords[] = {
			"alignas", "vec2", "vec3", "vec4", "mat4", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
			"compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float",
			"for", "friend", "goto", "if", "import", "inline", "int", "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
			"register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
			"throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
		};
		for (auto& k : cppKeywords){
			langDef.keywords.insert(k);
		}

		static const char* const identifiers[] = {
			"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
			"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "printf", "sprintf", "snprintf", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper",
			"std", "string", "vector", "map", "unordered_map", "set", "unordered_set", "min", "max"
		};
		for (auto& k : identifiers){
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.tokenize = [](const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex) -> bool{
			paletteIndex = PaletteIndex::Max;

			while (in_begin < in_end && isascii(*in_begin) && isblank(*in_begin)){
				in_begin++;
			}

			if (in_begin == in_end){
				out_begin = in_end;
				out_end = in_end;
				paletteIndex = PaletteIndex::Default;
			}
			else if (TokenizeCStyleString(in_begin, in_end, out_begin, out_end)){
				paletteIndex = PaletteIndex::String;
			}
			else if (TokenizeCStyleCharacterLiteral(in_begin, in_end, out_begin, out_end)){
				paletteIndex = PaletteIndex::CharLiteral;
			}
			else if (TokenizeCStyleIdentifier(in_begin, in_end, out_begin, out_end)){
				paletteIndex = PaletteIndex::Identifier;
			}
			else if (TokenizeCStyleNumber(in_begin, in_end, out_begin, out_end)){
				paletteIndex = PaletteIndex::Number;
			}
			else if (TokenizeCStylePunctuation(in_begin, in_end, out_begin, out_end)){
				paletteIndex = PaletteIndex::Punctuation;
			}

			return paletteIndex != PaletteIndex::Max;
		};

		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";
		langDef.case_sensitive = true;
		langDef.auto_indentation = true;
		langDef.name = "C++";
		inited = true;
	}

	//---------------------------
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::HLSL(){
	static bool inited = false;
	static LanguageDefinition langDef;
	//---------------------------

	if (!inited){
		static const char* const keywords[] = {
			"AppendStructuredBuffer", "asm", "asm_fragment", "BlendState", "bool", "break", "Buffer", "ByteAddressBuffer", "case", "cbuffer", "centroid", "class", "column_major", "compile", "compile_fragment",
			"CompileShader", "const", "continue", "ComputeShader", "ConsumeStructuredBuffer", "default", "DepthStencilState", "DepthStencilView", "discard", "do", "double", "DomainShader", "dword", "else",
			"export", "extern", "false", "float", "for", "fxgroup", "GeometryShader", "groupshared", "half", "Hullshader", "if", "in", "inline", "inout", "InputPatch", "int", "interface", "line", "lineadj",
			"linear", "LineStream", "matrix", "min16float", "min10float", "min16int", "min12int", "min16uint", "namespace", "nointerpolation", "noperspective", "NULL", "out", "OutputPatch", "packoffset",
			"pass", "pixelfragment", "PixelShader", "point", "PointStream", "precise", "RasterizerState", "RenderTargetView", "return", "register", "row_major", "RWBuffer", "RWByteAddressBuffer", "RWStructuredBuffer",
			"RWTexture1D", "RWTexture1DArray", "RWTexture2D", "RWTexture2DArray", "RWTexture3D", "sample", "sampler", "SamplerState", "SamplerComparisonState", "shared", "snorm", "stateblock", "stateblock_state",
			"static", "string", "struct", "switch", "StructuredBuffer", "tbuffer", "technique", "technique10", "technique11", "texture", "Texture1D", "Texture1DArray", "Texture2D", "Texture2DArray", "Texture2DMS",
			"Texture2DMSArray", "Texture3D", "TextureCube", "TextureCubeArray", "true", "typedef", "triangle", "triangleadj", "TriangleStream", "uint", "uniform", "unorm", "unsigned", "vector", "vertexfragment",
			"VertexShader", "void", "volatile", "while",
			"bool1","bool2","bool3","bool4","double1","double2","double3","double4", "float1", "float2", "float3", "float4", "int1", "int2", "int3", "int4", "in", "out", "inout",
			"uint1", "uint2", "uint3", "uint4", "dword1", "dword2", "dword3", "dword4", "half1", "half2", "half3", "half4",
			"float1x1","float2x1","float3x1","float4x1","float1x2","float2x2","float3x2","float4x2",
			"float1x3","float2x3","float3x3","float4x3","float1x4","float2x4","float3x4","float4x4",
			"half1x1","half2x1","half3x1","half4x1","half1x2","half2x2","half3x2","half4x2",
			"half1x3","half2x3","half3x3","half4x3","half1x4","half2x4","half3x4","half4x4",
		};
		for (auto& k : keywords){
			langDef.keywords.insert(k);
		}

		static const char* const identifiers[] = {
			"abort", "abs", "acos", "all", "AllMemoryBarrier", "AllMemoryBarrierWithGroupSync", "any", "asdouble", "asfloat", "asin", "asint", "asint", "asuint",
			"asuint", "atan", "atan2", "ceil", "CheckAccessFullyMapped", "clamp", "clip", "cos", "cosh", "countbits", "cross", "D3DCOLORtoUBYTE4", "ddx",
			"ddx_coarse", "ddx_fine", "ddy", "ddy_coarse", "ddy_fine", "degrees", "determinant", "DeviceMemoryBarrier", "DeviceMemoryBarrierWithGroupSync",
			"distance", "dot", "dst", "errorf", "EvaluateAttributeAtCentroid", "EvaluateAttributeAtSample", "EvaluateAttributeSnapped", "exp", "exp2",
			"f16tof32", "f32tof16", "faceforward", "firstbithigh", "firstbitlow", "floor", "fma", "fmod", "frac", "frexp", "fwidth", "GetRenderTargetSampleCount",
			"GetRenderTargetSamplePosition", "GroupMemoryBarrier", "GroupMemoryBarrierWithGroupSync", "InterlockedAdd", "InterlockedAnd", "InterlockedCompareExchange",
			"InterlockedCompareStore", "InterlockedExchange", "InterlockedMax", "InterlockedMin", "InterlockedOr", "InterlockedXor", "isfinite", "isinf", "isnan",
			"ldexp", "length", "lerp", "lit", "log", "log10", "log2", "mad", "max", "min", "modf", "msad4", "mul", "noise", "normalize", "pow", "printf",
			"Process2DQuadTessFactorsAvg", "Process2DQuadTessFactorsMax", "Process2DQuadTessFactorsMin", "ProcessIsolineTessFactors", "ProcessQuadTessFactorsAvg",
			"ProcessQuadTessFactorsMax", "ProcessQuadTessFactorsMin", "ProcessTriTessFactorsAvg", "ProcessTriTessFactorsMax", "ProcessTriTessFactorsMin",
			"radians", "rcp", "reflect", "refract", "reversebits", "round", "rsqrt", "saturate", "sign", "sin", "sincos", "sinh", "smoothstep", "sqrt", "step",
			"tan", "tanh", "tex1D", "tex1D", "tex1Dbias", "tex1Dgrad", "tex1Dlod", "tex1Dproj", "tex2D", "tex2D", "tex2Dbias", "tex2Dgrad", "tex2Dlod", "tex2Dproj",
			"tex3D", "tex3D", "tex3Dbias", "tex3Dgrad", "tex3Dlod", "tex3Dproj", "texCUBE", "texCUBE", "texCUBEbias", "texCUBEgrad", "texCUBElod", "texCUBEproj", "transpose", "trunc"
		};
		for (auto& k : identifiers){
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[ \\t]*#[ \\t]*[a-zA-Z_]+", PaletteIndex::Preprocessor));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("\\'\\\\?[^\\']\\'", PaletteIndex::CharLiteral));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[0-7]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", PaletteIndex::Identifier));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", PaletteIndex::Punctuation));

		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";

		langDef.case_sensitive = true;
		langDef.auto_indentation = true;

		langDef.name = "HLSL";

		inited = true;
	}

	//---------------------------
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::GLSL(){
	static bool inited = false;
	static LanguageDefinition langDef;
	//---------------------------

	if (!inited){
		static const char* const keywords[] = {
			"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
			"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
			"_Noreturn", "_Static_assert", "_Thread_local"
		};
		for (auto& k : keywords)
			langDef.keywords.insert(k);

		static const char* const identifiers[] = {
			"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
			"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
		};
		for (auto& k : identifiers)
		{
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[ \\t]*#[ \\t]*[a-zA-Z_]+", PaletteIndex::Preprocessor));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("\\'\\\\?[^\\']\\'", PaletteIndex::CharLiteral));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[0-7]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", PaletteIndex::Identifier));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", PaletteIndex::Punctuation));

		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";

		langDef.case_sensitive = true;
		langDef.auto_indentation = true;

		langDef.name = "GLSL";

		inited = true;
	}

	//---------------------------
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::C(){
	static bool inited = false;
	static LanguageDefinition langDef;
	if (!inited){
		static const char* const keywords[] = {
			"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
			"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
			"_Noreturn", "_Static_assert", "_Thread_local"
		};
		for (auto& k : keywords)
			langDef.keywords.insert(k);

		static const char* const identifiers[] = {
			"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
			"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
		};
		for (auto& k : identifiers)
		{
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.tokenize = [](const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex) -> bool
		{
			paletteIndex = PaletteIndex::Max;

			while (in_begin < in_end && isascii(*in_begin) && isblank(*in_begin))
				in_begin++;

			if (in_begin == in_end)
			{
				out_begin = in_end;
				out_end = in_end;
				paletteIndex = PaletteIndex::Default;
			}
			else if (TokenizeCStyleString(in_begin, in_end, out_begin, out_end))
				paletteIndex = PaletteIndex::String;
			else if (TokenizeCStyleCharacterLiteral(in_begin, in_end, out_begin, out_end))
				paletteIndex = PaletteIndex::CharLiteral;
			else if (TokenizeCStyleIdentifier(in_begin, in_end, out_begin, out_end))
				paletteIndex = PaletteIndex::Identifier;
			else if (TokenizeCStyleNumber(in_begin, in_end, out_begin, out_end))
				paletteIndex = PaletteIndex::Number;
			else if (TokenizeCStylePunctuation(in_begin, in_end, out_begin, out_end))
				paletteIndex = PaletteIndex::Punctuation;

			return paletteIndex != PaletteIndex::Max;
		};

		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";

		langDef.case_sensitive = true;
		langDef.auto_indentation = true;

		langDef.name = "C";

		inited = true;
	}
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::SQL(){
	static bool inited = false;
	static LanguageDefinition langDef;
	if (!inited){
		static const char* const keywords[] = {
			"ADD", "EXCEPT", "PERCENT", "ALL", "EXEC", "PLAN", "ALTER", "EXECUTE", "PRECISION", "AND", "EXISTS", "PRIMARY", "ANY", "EXIT", "PRINT", "AS", "FETCH", "PROC", "ASC", "FILE", "PROCEDURE",
			"AUTHORIZATION", "FILLFACTOR", "PUBLIC", "BACKUP", "FOR", "RAISERROR", "BEGIN", "FOREIGN", "READ", "BETWEEN", "FREETEXT", "READTEXT", "BREAK", "FREETEXTTABLE", "RECONFIGURE",
			"BROWSE", "FROM", "REFERENCES", "BULK", "FULL", "REPLICATION", "BY", "FUNCTION", "RESTORE", "CASCADE", "GOTO", "RESTRICT", "CASE", "GRANT", "RETURN", "CHECK", "GROUP", "REVOKE",
			"CHECKPOINT", "HAVING", "RIGHT", "CLOSE", "HOLDLOCK", "ROLLBACK", "CLUSTERED", "IDENTITY", "ROWCOUNT", "COALESCE", "IDENTITY_INSERT", "ROWGUIDCOL", "COLLATE", "IDENTITYCOL", "RULE",
			"COLUMN", "IF", "SAVE", "COMMIT", "IN", "SCHEMA", "COMPUTE", "INDEX", "SELECT", "CONSTRAINT", "INNER", "SESSION_USER", "CONTAINS", "INSERT", "SET", "CONTAINSTABLE", "INTERSECT", "SETUSER",
			"CONTINUE", "INTO", "SHUTDOWN", "CONVERT", "IS", "SOME", "CREATE", "JOIN", "STATISTICS", "CROSS", "KEY", "SYSTEM_USER", "CURRENT", "KILL", "TABLE", "CURRENT_DATE", "LEFT", "TEXTSIZE",
			"CURRENT_TIME", "LIKE", "THEN", "CURRENT_TIMESTAMP", "LINENO", "TO", "CURRENT_USER", "LOAD", "TOP", "CURSOR", "NATIONAL", "TRAN", "DATABASE", "NOCHECK", "TRANSACTION",
			"DBCC", "NONCLUSTERED", "TRIGGER", "DEALLOCATE", "NOT", "TRUNCATE", "DECLARE", "NULL", "TSEQUAL", "DEFAULT", "NULLIF", "UNION", "DELETE", "OF", "UNIQUE", "DENY", "OFF", "UPDATE",
			"DESC", "OFFSETS", "UPDATETEXT", "DISK", "ON", "USE", "DISTINCT", "OPEN", "USER", "DISTRIBUTED", "OPENDATASOURCE", "VALUES", "DOUBLE", "OPENQUERY", "VARYING","DROP", "OPENROWSET", "VIEW",
			"DUMMY", "OPENXML", "WAITFOR", "DUMP", "OPTION", "WHEN", "ELSE", "OR", "WHERE", "END", "ORDER", "WHILE", "ERRLVL", "OUTER", "WITH", "ESCAPE", "OVER", "WRITETEXT"
		};

		for (auto& k : keywords)
			langDef.keywords.insert(k);

		static const char* const identifiers[] = {
			"ABS",  "ACOS",  "ADD_MONTHS",  "ASCII",  "ASCIISTR",  "ASIN",  "ATAN",  "ATAN2",  "AVG",  "BFILENAME",  "BIN_TO_NUM",  "BITAND",  "CARDINALITY",  "CASE",  "CAST",  "CEIL",
			"CHARTOROWID",  "CHR",  "COALESCE",  "COMPOSE",  "CONCAT",  "CONVERT",  "CORR",  "COS",  "COSH",  "COUNT",  "COVAR_POP",  "COVAR_SAMP",  "CUME_DIST",  "CURRENT_DATE",
			"CURRENT_TIMESTAMP",  "DBTIMEZONE",  "DECODE",  "DECOMPOSE",  "DENSE_RANK",  "DUMP",  "EMPTY_BLOB",  "EMPTY_CLOB",  "EXP",  "EXTRACT",  "FIRST_VALUE",  "FLOOR",  "FROM_TZ",  "GREATEST",
			"GROUP_ID",  "HEXTORAW",  "INITCAP",  "INSTR",  "INSTR2",  "INSTR4",  "INSTRB",  "INSTRC",  "LAG",  "LAST_DAY",  "LAST_VALUE",  "LEAD",  "LEAST",  "LENGTH",  "LENGTH2",  "LENGTH4",
			"LENGTHB",  "LENGTHC",  "LISTAGG",  "LN",  "LNNVL",  "LOCALTIMESTAMP",  "LOG",  "LOWER",  "LPAD",  "LTRIM",  "MAX",  "MEDIAN",  "MIN",  "MOD",  "MONTHS_BETWEEN",  "NANVL",  "NCHR",
			"NEW_TIME",  "NEXT_DAY",  "NTH_VALUE",  "NULLIF",  "NUMTODSINTERVAL",  "NUMTOYMINTERVAL",  "NVL",  "NVL2",  "POWER",  "RANK",  "RAWTOHEX",  "REGEXP_COUNT",  "REGEXP_INSTR",
			"REGEXP_REPLACE",  "REGEXP_SUBSTR",  "REMAINDER",  "REPLACE",  "ROUND",  "ROWNUM",  "RPAD",  "RTRIM",  "SESSIONTIMEZONE",  "SIGN",  "SIN",  "SINH",
			"SOUNDEX",  "SQRT",  "STDDEV",  "SUBSTR",  "SUM",  "SYS_CONTEXT",  "SYSDATE",  "SYSTIMESTAMP",  "TAN",  "TANH",  "TO_CHAR",  "TO_CLOB",  "TO_DATE",  "TO_DSINTERVAL",  "TO_LOB",
			"TO_MULTI_BYTE",  "TO_NCLOB",  "TO_NUMBER",  "TO_SINGLE_BYTE",  "TO_TIMESTAMP",  "TO_TIMESTAMP_TZ",  "TO_YMINTERVAL",  "TRANSLATE",  "TRIM",  "TRUNC", "TZ_OFFSET",  "UID",  "UPPER",
			"USER",  "USERENV",  "VAR_POP",  "VAR_SAMP",  "VARIANCE",  "VSIZE "
		};
		for (auto& k : identifiers)
		{
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("\\\'[^\\\']*\\\'", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[0-7]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", PaletteIndex::Identifier));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", PaletteIndex::Punctuation));

		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";

		langDef.case_sensitive = false;
		langDef.auto_indentation = false;

		langDef.name = "SQL";

		inited = true;
	}
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::AngelScript(){
	static bool inited = false;
	static LanguageDefinition langDef;
	if (!inited){
		static const char* const keywords[] = {
			"and", "abstract", "auto", "bool", "break", "case", "cast", "class", "const", "continue", "default", "do", "double", "else", "enum", "false", "final", "float", "for",
			"from", "funcdef", "function", "get", "if", "import", "in", "inout", "int", "interface", "int8", "int16", "int32", "int64", "is", "mixin", "namespace", "not",
			"null", "or", "out", "override", "private", "protected", "return", "set", "shared", "super", "switch", "this ", "true", "typedef", "uint", "uint8", "uint16", "uint32",
			"uint64", "void", "while", "xor"
		};

		for (auto& k : keywords)
			langDef.keywords.insert(k);

		static const char* const identifiers[] = {
			"cos", "sin", "tab", "acos", "asin", "atan", "atan2", "cosh", "sinh", "tanh", "log", "log10", "pow", "sqrt", "abs", "ceil", "floor", "fraction", "closeTo", "fpFromIEEE", "fpToIEEE",
			"complex", "opEquals", "opAddAssign", "opSubAssign", "opMulAssign", "opDivAssign", "opAdd", "opSub", "opMul", "opDiv"
		};
		for (auto& k : identifiers)
		{
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("\\'\\\\?[^\\']\\'", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[0-7]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", PaletteIndex::Identifier));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", PaletteIndex::Punctuation));
		langDef.comment_start = "/*";
		langDef.comment_end = "*/";
		langDef.single_line_comment = "//";
		langDef.case_sensitive = true;
		langDef.auto_indentation = true;
		langDef.name = "AngelScript";

		inited = true;
	}
	return langDef;
}
const TextEditor::LanguageDefinition& TextEditor::LanguageDefinition::Lua(){
	static bool inited = false;
	static LanguageDefinition langDef;
	if (!inited){
		static const char* const keywords[] = {
			"and", "break", "do", "", "else", "elseif", "end", "false", "for", "function", "if", "in", "", "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while"
		};

		for (auto& k : keywords)
			langDef.keywords.insert(k);

		static const char* const identifiers[] = {
			"assert", "collectgarbage", "dofile", "error", "getmetatable", "ipairs", "loadfile", "load", "loadstring",  "next",  "pairs",  "pcall",  "print",  "rawequal",  "rawlen",  "rawget",  "rawset",
			"select",  "setmetatable",  "tonumber",  "tostring",  "type",  "xpcall",  "_G",  "_VERSION","arshift", "band", "bnot", "bor", "bxor", "btest", "extract", "lrotate", "lshift", "replace",
			"rrotate", "rshift", "create", "resume", "running", "status", "wrap", "yield", "isyieldable", "debug","getuservalue", "gethook", "getinfo", "getlocal", "getregistry", "getmetatable",
			"getupvalue", "upvaluejoin", "upvalueid", "setuservalue", "sethook", "setlocal", "setmetatable", "setupvalue", "traceback", "close", "flush", "input", "lines", "open", "output", "popen",
			"read", "tmpfile", "type", "write", "close", "flush", "lines", "read", "seek", "setvbuf", "write", "__gc", "__tostring", "abs", "acos", "asin", "atan", "ceil", "cos", "deg", "exp", "tointeger",
			"floor", "fmod", "ult", "log", "max", "min", "modf", "rad", "random", "randomseed", "sin", "sqrt", "string", "tan", "type", "atan2", "cosh", "sinh", "tanh",
			"pow", "frexp", "ldexp", "log10", "pi", "huge", "maxinteger", "mininteger", "loadlib", "searchpath", "seeall", "preload", "cpath", "path", "searchers", "loaded", "module", "require", "clock",
			"date", "difftime", "execute", "exit", "getenv", "remove", "rename", "setlocale", "time", "tmpname", "byte", "char", "dump", "find", "format", "gmatch", "gsub", "len", "lower", "match", "rep",
			"reverse", "sub", "upper", "pack", "packsize", "unpack", "concat", "maxn", "insert", "pack", "unpack", "remove", "move", "sort", "offset", "codepoint", "char", "len", "codes", "charpattern",
			"coroutine", "table", "io", "os", "string", "utf8", "bit32", "math", "debug", "package"
		};
		for (auto& k : identifiers)
		{
			Identifier id;
			id.mDeclaration = "Built-in function";
			langDef.identifiers.insert(std::make_pair(std::string(k), id));
		}

		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("\\\'[^\\\']*\\\'", PaletteIndex::String));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[+-]?[0-9]+[Uu]?[lL]?[lL]?", PaletteIndex::Number));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", PaletteIndex::Identifier));
		langDef.token_regex_strings.push_back(std::make_pair<std::string, PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", PaletteIndex::Punctuation));

		langDef.comment_start = "--[[";
		langDef.comment_end = "]]";
		langDef.single_line_comment = "--";

		langDef.case_sensitive = true;
		langDef.auto_indentation = false;

		langDef.name = "Lua";

		inited = true;
	}
	return langDef;
}
