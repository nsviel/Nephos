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
		int mLine;
		bool mEnabled;
		std::string mCondition;

		Breakpoint() : mLine(-1), mEnabled(false){}
	};
	struct Coordinates{
		// Represents a character coordinate from the user's point of view,
		// i. e. consider an uniform grid (assuming fixed-width font) on the
		// screen as it is rendered, and each cell has its own coordinate, starting from 0.
		// Tabs are counted as [1..mTabSize] count empty spaces, depending on
		// how many space is necessary to reach the next tab stop.
		// For example, coordinate (1, 5) represents the character 'B' in a line "\tABC", when mTabSize = 4,
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
		Char mChar;
		PaletteIndex mColorIndex = PaletteIndex::Default;
		bool mComment : 1;
		bool mMultiLineComment : 1;
		bool mPreprocessor : 1;

		Glyph(Char aChar, PaletteIndex aColorIndex) : mChar(aChar), mColorIndex(aColorIndex),
			mComment(false), mMultiLineComment(false), mPreprocessor(false) {}
	};

	typedef std::vector<Glyph> Line;
	typedef std::vector<Line> Lines;

	struct LanguageDefinition{
		typedef std::pair<std::string, PaletteIndex> TokenRegexString;
		typedef std::vector<TokenRegexString> TokenRegexStrings;
		typedef bool(*TokenizeCallback)(const char * in_begin, const char * in_end, const char *& out_begin, const char *& out_end, PaletteIndex & paletteIndex);

		std::string mName;
		Keywords mKeywords;
		Identifiers mIdentifiers;
		Identifiers mPreprocIdentifiers;
		std::string mCommentStart, mCommentEnd, mSingleLineComment;
		char mPreprocChar;
		bool mAutoIndentation;

		TokenizeCallback mTokenize;

		TokenRegexStrings mTokenRegexStrings;

		bool mCaseSensitive;

		LanguageDefinition()
			: mPreprocChar('#'), mAutoIndentation(true), mTokenize(nullptr), mCaseSensitive(true)
		{
		}

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
	void InsertText(const std::string& aValue);
	void InsertText(const char* aValue);

	bool CanUndo() const;
	bool CanRedo() const;
	void Undo(int aSteps = 1);
	void Redo(int aSteps = 1);

	void SetReadOnly(bool aValue);
	void SetLanguageDefinition(const LanguageDefinition& aLanguageDef);
	void SetPalette(const Palette& aValue);
	void SetErrorMarkers(const ErrorMarkers& aMarkers) { mErrorMarkers = aMarkers; }
	void SetBreakpoints(const Breakpoints& aMarkers) { mBreakpoints = aMarkers; }
	void SetText(const std::string& aText);
	void SetTextLines(const std::vector<std::string>& aLines);
	void SetColorizerEnable(bool aValue);
	void SetCursorPosition(const Coordinates& aPosition);
	void SetTabSize(int aValue);
	void SetSelectionStart(const Coordinates& aPosition);
	void SetSelectionEnd(const Coordinates& aPosition);
	void SetSelection(const Coordinates& aStart, const Coordinates& aEnd, SelectionMode aMode = SelectionMode::Normal);
	void SelectWordUnderCursor();
	void SelectAll();

	const LanguageDefinition& GetLanguageDefinition() const { return mLanguageDefinition; }
	const Palette& GetPalette() const { return mPaletteBase; }
	std::vector<std::string> GetTextLines() const;
	std::string GetText() const;
	std::string GetSelectedText() const;
	std::string GetCurrentLineText()const;
	int GetTotalLines() const { return (int)mLines.size(); }
	Coordinates GetCursorPosition() const { return GetActualCursorCoordinates(); }

	bool IsOverwrite() const { return mOverwrite; }
	bool IsReadOnly() const { return mReadOnly; }
	bool IsTextChanged() const { return mTextChanged; }
	bool IsCursorPositionChanged() const { return mCursorPositionChanged; }
	bool IsColorizerEnabled() const { return mColorizerEnabled; }
	bool HasSelection() const;

	inline void SetHandleMouseInputs    (bool aValue){ mHandleMouseInputs    = aValue;}
	inline void SetHandleKeyboardInputs (bool aValue){ mHandleKeyboardInputs = aValue;}
	inline void SetImGuiChildIgnored    (bool aValue){ mIgnoreImGuiChild     = aValue;}
	inline void SetShowWhitespaces(bool aValue) { mShowWhitespaces = aValue; }
	inline bool IsHandleMouseInputsEnabled() const { return mHandleKeyboardInputs; }
	inline bool IsHandleKeyboardInputsEnabled() const { return mHandleKeyboardInputs; }
	inline bool IsImGuiChildIgnored() const { return mIgnoreImGuiChild; }
	inline bool IsShowingWhitespaces() const { return mShowWhitespaces; }
	inline int GetTabSize() const { return mTabSize; }

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
	void AddUndo(UndoRecord& aValue);
	void RemoveLine(int aStart, int aEnd);
	void RemoveLine(int aIndex);
	void EnterCharacter(ImWchar aChar, bool aShift);
	void Backspace();
	void DeleteSelection();
	void HandleKeyboardInputs();
	void HandleMouseInputs();
	void Render();
	int InsertTextAt(Coordinates& aWhere, const char* aValue);

	int GetPageSize() const;
	int GetCharacterIndex(const Coordinates& aCoordinates) const;
	int GetCharacterColumn(int aLine, int aIndex) const;
	int GetLineCharacterCount(int aLine) const;
	int GetLineMaxColumn(int aLine) const;

	std::string GetText(const Coordinates& aStart, const Coordinates& aEnd) const;
	std::string GetWordUnderCursor() const;
	std::string GetWordAt(const Coordinates& aCoords) const;

	Coordinates GetActualCursorCoordinates() const;
	Coordinates SanitizeCoordinates(const Coordinates& aValue) const;
	Coordinates ScreenPosToCoordinates(const ImVec2& aPosition) const;
	Coordinates FindWordStart(const Coordinates& aFrom) const;
	Coordinates FindWordEnd(const Coordinates& aFrom) const;
	Coordinates FindNextWord(const Coordinates& aFrom) const;

	bool IsOnWordBoundary(const Coordinates& aAt) const;
	Line& InsertLine(int aIndex);
	ImU32 GetGlyphColor(const Glyph& aGlyph) const;
	float TextDistanceToLineStart(const Coordinates& aFrom) const;

	Lines mLines;
	EditorState mState;
	UndoBuffer mUndoBuffer;
	SelectionMode mSelectionMode;
	Palette mPaletteBase;
	Palette mPalette;
	LanguageDefinition mLanguageDefinition;
	RegexList mRegexList;
	Breakpoints mBreakpoints;
	ErrorMarkers mErrorMarkers;
	Coordinates mInteractiveStart, mInteractiveEnd;

	std::string mLineBuffer;
	uint64_t mStartTime;
	ImVec2 mCharAdvance;
	float mLastClick;
	float mLineSpacing;
	float mTextStart; // position (in pixels) where a code line starts relative to the left of the TextEditor.
	int mUndoIndex;
	int mTabSize;
	int mLeftMargin;
	int mColorRangeMin, mColorRangeMax;
	bool mOverwrite;
	bool mReadOnly;
	bool mWithinRender;
	bool mScrollToCursor;
	bool mScrollToTop;
	bool mTextChanged;
	bool mColorizerEnabled;
	bool mCursorPositionChanged;
	bool mHandleKeyboardInputs;
	bool mHandleMouseInputs;
	bool mIgnoreImGuiChild;
	bool mShowWhitespaces;
	bool mCheckComments;
};

#endif
