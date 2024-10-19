#ifndef CODEEDITLINENUMBERAREA_H
#define CODEEDITLINENUMBERAREA_H

#include <QTextEdit>
#include <QWidget>
#include <codeedit.h>

class CodeEditLineNumberArea: public QWidget
{
    Q_OBJECT

public:
    CodeEditLineNumberArea(CodeEdit *editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    CodeEdit *codeEditor;
};

#endif // CODEEDITLINENUMBERAREA_H
