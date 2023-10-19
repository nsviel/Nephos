#ifndef TEXT_EDITOR_THEME_H
#define TEXT_EDITOR_THEME_H


const TextEditor::Palette & TextEditor::get_custom_palette(){
	const static Palette p = { {
		0xff7f7f7f,	// Default
		0xfffcbc65,	// Keyword - drityblue 65bcfc
		0xff84CCAF,	// Number - vert pale
		0xff6ad169,	// String - vert
		0xffCE9178, // Char literal
		0xffffffff, // Punctuation - white
		0xffffffff,	// Preprocessor - ex include - white
		0xffffffff, // Identifier
		0xffffffff, // Known identifier
		0xffffffff, // Preproc identifier
		0xff579336, // Comment (single line) - green
		0xffa3a3a3, // Comment (multi line)
		0xff151515, // Background	- black
		0xffffffff, // Cursor - white
		0xff435652, // Selection - gunmetal
		0x80F44747, // ErrorMarker
		0x40f08000, // Breakpoint
		0xff5A5A5A, // Line number - grey
		0x40404040, // Current line fill - grey
		0x40808080, // Current line fill (inactive)
		0x40a0a0a0, // Current line edge
		} };
	return p;
}

#endif
