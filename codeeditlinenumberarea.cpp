#include "codeeditlinenumberarea.h"

#include <codeedit.h>

CodeEditLineNumberArea::CodeEditLineNumberArea(CodeEdit *editor) : QWidget(editor) {
    codeEditor = editor;
}

QSize CodeEditLineNumberArea::sizeHint() const {
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void CodeEditLineNumberArea::paintEvent(QPaintEvent *event) {
    codeEditor->lineNumberAreaPaintEvent(event);
}
