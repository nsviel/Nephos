#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <regex>
#include <imgui/core/imgui.h>

class TextEditor
{
public:
	enum class PaletteIndex{
		Default,
		Keyword,
		Number,
		String,
		CharLiteral,
		Punctuation,
		Preprocessor,
		Identifier,
		KnownIdentifier,
		PreprocIdentifier,
		Comment,
		MultiLineComment,
		Background,
		Cursor,
		Selection,
		ErrorMarker,
		Breakpoint,
		LineNumber,
		CurrentLineFill,
		CurrentLineFillInactive,
		CurrentLineEdge,
		Max
	};
	enum class SelectionMode{
		Normal,
		Word,
		Line
	};

	struct Breakpoint{
		Breakpoint(){
			this->mLine = -1;
			this->mEnabled = false;
		}

		std::string mCondition;
		bool mEnabled;
		int mLine;
	};
	struct Coordinates{
		// Represents a character coordinate from the user's point of view,
		// i. e. consider an uniform grid (assuming fixed-width font) on the
		// screen as it is rendered, and each cell has its own coordinate, starting from 0.
		// Tabs are counted as [1..tab_size] count empty spaces, depending on
		// how many space is necessary to reach the next tab stop.
		// For example, coordinate (1, 5) represents the character 'B' in a line "\tABC", when tab_size = 4,
		// because it is rendered as "    ABC" on the screen.
		int mLine, mColumn;
		Coordinates() : mLine(0), mColumn(0) {}
		Coordinates(int aLine, int aColumn) : mLine(aLine), mColumn(aColumn){
			assert(aLine >= 0);
			assert(aColumn >= 0);
		}
		static Coordinates Invalid() { static Coordinates invalid(-1, -1); return invalid; }

		bool operator ==(const Coordinates& o) const{
			return	mLine == o.mLine &&	mColumn == o.mColumn;
		}
		bool operator !=(const Coordinates& o) const{
			return mLine != o.mLine ||	mColumn != o.mColumn;
		}
		bool operator <(const Coordinates& o) const{
			if (mLine != o.mLine){
				return mLine < o.mLine;
			}
			return mColumn < o.mColumn;
		}
		bool operator >(const Coordinates& o) const{
			if (mLine != o.mLine){
				return mLine > o.mLine;
			}
			return mColumn > o.mColumn;
		}
		bool operator <=(const Coordinates& o) const{
			if (mLine != o.mLine){
				return mLine < o.mLine;
			}
			return mColumn <= o.mColumn;
		}
		bool operator >=(const Coordinates& o) const{
			if (mLine != o.mLine){
				return mLine > o.mLine;
			}
			return mColumn >= o.mColumn;
		}
	};
	struct Identifier{
		Coordinates mLocation;
		std::string mDeclaration;
	};

	typedef std::string String;
	typedef std::unordered_map<std::string, Identifier> Identifiers;
	typedef std::unordered_set<std::string> Keywords;
	typedef std::map<int, std::string> ErrorMarkers;
	typedef std::unordered_set<int> Breakpoints;
	typedef std::array<ImU32, (unsigned)PaletteIndex::Max> Palette;
	typedef uint8_t Char;

	struct Glyph{
		Glyph(Char aChar, PaletteIndex aColorIndex){
			this->mChar = aChar;
			this->color_index = aColorIndex;
			this->preprocessor = false;
			this->comment = false;
			this->multiline_comment = false;
		}

		PaletteIndex color_index = PaletteIndex::Default;
		Char mChar;
		bool comment : 1;
		bool multiline_comment : 1;
		bool preprocessor : 1;
	};

	typedef std::vector<Glyph> Line;
	typedef std::vector<Line> Lines;

	struct LanguageDefinition{
		typedef std::pair<std::string, PaletteIndex> TokenRegexString;
		typedef std::vector<TokenRegexString> TokenRegexStrings;
		typedef bool(*TokenizeCallback)(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex);

		LanguageDefinition(){
			this->preproc_char = '#';
			this->auto_indentation = true;
			this->tokenize = nullptr;
			this->case_sensitive = true;
		}

		std::string name;
		std::string comment_start;
		std::string comment_end;
		std::string single_line_comment;
		char preproc_char;
		bool auto_indentation;
		bool case_sensitive;
		Keywords keywords;
		Identifiers identifiers;
		Identifiers preproc_dentifiers;
		TokenizeCallback tokenize;
		TokenRegexStrings token_regex_strings;

		static const LanguageDefinition& Cpp();
		static const LanguageDefinition& HLSL();
		static const LanguageDefinition& GLSL();
		static const LanguageDefinition& C();
		static const LanguageDefinition& SQL();
		static const LanguageDefinition& AngelScript();
		static const LanguageDefinition& Lua();
	};

	TextEditor();
	~TextEditor();

	void Render(const char* aTitle, const ImVec2& aSize = ImVec2(), bool aBorder = false);
	void Copy();
	void Cut();
	void Paste();
	void Delete();
	void InsertText(const std::string& value);
	void InsertText(const char* value);

	bool CanUndo() const;
	bool CanRedo() const;
	void Undo(int aSteps = 1);
	void Redo(int aSteps = 1);

	void set_language_definition(std::string language);
	void SetReadOnly(bool value);
	void SetLanguageDefinition(const LanguageDefinition& aLanguageDef);
	void SetPalette(const Palette& value);
	void SetErrorMarkers(const ErrorMarkers& aMarkers) { error_markers = aMarkers; }
	void SetBreakpoints(const Breakpoints& aMarkers) { breakpoint = aMarkers; }
	void SetText(const std::string& aText);
	void SetTextLines(const std::vector<std::string>& aLines);
	void SetColorizerEnable(bool value);
	void SetCursorPosition(const Coordinates& aPosition);
	void SetTabSize(int value);
	void SetSelectionStart(const Coordinates& aPosition);
	void SetSelectionEnd(const Coordinates& aPosition);
	void SetSelection(const Coordinates& aStart, const Coordinates& aEnd, SelectionMode aMode = SelectionMode::Normal);
	void SelectWordUnderCursor();
	void SelectAll();

	const LanguageDefinition& GetLanguageDefinition() const { return language_definition; }
	const Palette& GetPalette() const { return palette_base; }
	std::vector<std::string> GetTextLines() const;
	std::string GetText() const;
	std::string GetSelectedText() const;
	std::string GetCurrentLineText()const;
	int GetTotalLines() const { return (int)lines.size(); }
	Coordinates GetCursorPosition() const { return GetActualCursorCoordinates(); }

	bool IsOverwrite() const { return overwrite; }
	bool IsReadOnly() const { return read_only; }
	bool IsTextChanged() const { return text_changed; }
	bool IsCursorPositionChanged() const { return cursor_position_changed; }
	bool IsColorizerEnabled() const { return colorizer_enabled; }
	bool HasSelection() const;

	inline void set_is_text_changed     (bool value){ text_changed    = value;}
	inline void SetHandleMouseInputs    (bool value){ handle_mouse_inputs    = value;}
	inline void SetHandleKeyboardInputs (bool value){ handle_keyboard_inputs = value;}
	inline void SetImGuiChildIgnored    (bool value){ ignore_imgui_child     = value;}
	inline void SetShowWhitespaces(bool value) { show_whitespaces = value; }
	inline bool IsHandleMouseInputsEnabled() const { return handle_keyboard_inputs; }
	inline bool IsHandleKeyboardInputsEnabled() const { return handle_keyboard_inputs; }
	inline bool IsImGuiChildIgnored() const { return ignore_imgui_child; }
	inline bool IsShowingWhitespaces() const { return show_whitespaces; }
	inline int GetTabSize() const { return tab_size; }

	void MoveUp(int aAmount = 1, bool aSelect = false);
	void MoveDown(int aAmount = 1, bool aSelect = false);
	void MoveLeft(int aAmount = 1, bool aSelect = false, bool aWordMode = false);
	void MoveRight(int aAmount = 1, bool aSelect = false, bool aWordMode = false);
	void MoveTop(bool aSelect = false);
	void MoveBottom(bool aSelect = false);
	void MoveHome(bool aSelect = false);
	void MoveEnd(bool aSelect = false);

	static const Palette& get_custom_palette();
	static const Palette& GetDarkPalette();
	static const Palette& GetLightPalette();
	static const Palette& GetRetroBluePalette();

private:
	struct EditorState{
		Coordinates mSelectionStart;
		Coordinates mSelectionEnd;
		Coordinates mCursorPosition;
	};
	class UndoRecord{
	public:
		UndoRecord() {}
		~UndoRecord() {}

		UndoRecord(
			const std::string& aAdded,
			const TextEditor::Coordinates aAddedStart,
			const TextEditor::Coordinates aAddedEnd,

			const std::string& aRemoved,
			const TextEditor::Coordinates aRemovedStart,
			const TextEditor::Coordinates aRemovedEnd,

			TextEditor::EditorState& aBefore,
			TextEditor::EditorState& aAfter);

		void Undo(TextEditor* aEditor);
		void Redo(TextEditor* aEditor);

		std::string mAdded;
		Coordinates mAddedStart;
		Coordinates mAddedEnd;

		std::string mRemoved;
		Coordinates mRemovedStart;
		Coordinates mRemovedEnd;

		EditorState mBefore;
		EditorState mAfter;
	};

	typedef std::vector<std::pair<std::regex, PaletteIndex>> RegexList;
	typedef std::vector<UndoRecord> UndoBuffer;

	void ProcessInputs();
	void Colorize(int aFromLine = 0, int aCount = -1);
	void ColorizeRange(int aFromLine = 0, int aToLine = 0);
	void ColorizeInternal();
	void EnsureCursorVisible();
	void Advance(Coordinates& aCoordinates) const;
	void DeleteRange(const Coordinates& aStart, const Coordinates& aEnd);
	void AddUndo(UndoRecord& value);
	void RemoveLine(int aStart, int aEnd);
	void RemoveLine(int aIndex);
	void EnterCharacter(ImWchar aChar, bool aShift);
	void Backspace();
	void DeleteSelection();
	void HandleKeyboardInputs();
	void HandleMouseInputs();
	void Render();
	int InsertTextAt(Coordinates& aWhere, const char* value);

	int GetPageSize() const;
	int GetCharacterIndex(const Coordinates& aCoordinates) const;
	int GetCharacterColumn(int aLine, int aIndex) const;
	int GetLineCharacterCount(int aLine) const;
	int GetLineMaxColumn(int aLine) const;

	std::string GetText(const Coordinates& aStart, const Coordinates& aEnd) const;
	std::string GetWordUnderCursor() const;
	std::string GetWordAt(const Coordinates& aCoords) const;

	Coordinates GetActualCursorCoordinates() const;
	Coordinates SanitizeCoordinates(const Coordinates& value) const;
	Coordinates ScreenPosToCoordinates(const ImVec2& aPosition) const;
	Coordinates FindWordStart(const Coordinates& aFrom) const;
	Coordinates FindWordEnd(const Coordinates& aFrom) const;
	Coordinates FindNextWord(const Coordinates& aFrom) const;

	bool IsOnWordBoundary(const Coordinates& aAt) const;
	Line& InsertLine(int aIndex);
	ImU32 GetGlyphColor(const Glyph& aGlyph) const;
	float TextDistanceToLineStart(const Coordinates& aFrom) const;

	Lines lines;
	EditorState state;
	UndoBuffer undo_buffer;
	SelectionMode selection_mode;
	Palette palette_base;
	Palette palette;
	LanguageDefinition language_definition;
	RegexList regex_list;
	Breakpoints breakpoint;
	ErrorMarkers error_markers;
	Coordinates interactive_start;
	Coordinates interactive_end;

	std::string line_buffer;
	uint64_t start_time;
	ImVec2 char_advance;
	float last_click;
	float line_spacing;
	float text_start; // position (in pixels) where a code line starts relative to the left of the TextEditor.
	int undo_index;
	int tab_size;
	int left_margin;
	int color_range_min;
	int color_range_max;
	bool overwrite;
	bool read_only;
	bool within_render;
	bool scroll_to_cursor;
	bool scroll_to_top;
	bool text_changed;
	bool colorizer_enabled;
	bool cursor_position_changed;
	bool handle_keyboard_inputs;
	bool handle_mouse_inputs;
	bool ignore_imgui_child;
	bool show_whitespaces;
	bool check_comments;
};

#endif
