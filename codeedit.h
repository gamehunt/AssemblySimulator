#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QPlainTextEdit>

class CodeEdit : public QPlainTextEdit
{
public:
    explicit CodeEdit(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

public slots:
    void setExecutedLine(int line);
    void highlightCurrentLine();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
};

#endif // CODEEDIT_H
