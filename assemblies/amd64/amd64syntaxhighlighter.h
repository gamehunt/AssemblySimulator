#ifndef AMD64SYNTAXHIGHLIGHTER_H
#define AMD64SYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class AMD64SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    AMD64SyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QList<HighlightingRule> highlightingRules;

    QTextCharFormat operationFormat;
    QTextCharFormat registerFormat;
};

#endif // AMD64SYNTAXHIGHLIGHTER_H
