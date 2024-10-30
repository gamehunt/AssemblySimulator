#include "amd64syntaxhighlighter.h"

AMD64SyntaxHighlighter::AMD64SyntaxHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter{parent}
{
    HighlightingRule rule;

    operationFormat.setForeground(Qt::darkBlue);
    operationFormat.setFontWeight(QFont::Bold);

    const QString opPatterns[] = {
        QStringLiteral("\\bnop\\b" ),
        QStringLiteral("\\bmov\\b" ),
        QStringLiteral("\\bpush\\b"),
        QStringLiteral("\\bpop\\b" ),
        QStringLiteral("\\binc\\b" ),
        QStringLiteral("\\bdec\\b" ),
        QStringLiteral("\\badd\\b" ),
        QStringLiteral("\\bsub\\b" ),
        QStringLiteral("\\bdiv\\b" ),
        QStringLiteral("\\bmul\\b" ),
        QStringLiteral("\\bcmp\\b" ),
        QStringLiteral("\\bjmp\\b" ),
        QStringLiteral("\\bje\\b"  ),
        QStringLiteral("\\bjne\\b" ),
        QStringLiteral("\\bjz\\b"  ),
        QStringLiteral("\\bjnz\\b" ),
        QStringLiteral("\\bjg\\b"  ),
        QStringLiteral("\\bjl\\b"  ),
        QStringLiteral("\\bjge\\b" ),
        QStringLiteral("\\bjle\\b" ),
        QStringLiteral("\\bjc\\b"  ),
        QStringLiteral("\\bcall\\b"),
        QStringLiteral("\\bret\\b" ),
        QStringLiteral("\\bxchg\\b" ),
    };

    for (const QString &pattern : opPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = operationFormat;
        highlightingRules.append(rule);
    }

    registerFormat.setForeground(QColor(0xFF4C00));
    operationFormat.setFontWeight(QFont::Bold);

    const QString registerPatterns[] = {
        QStringLiteral("\\brax\\b"),
        QStringLiteral("\\brbx\\b"),
        QStringLiteral("\\brcx\\b"),
        QStringLiteral("\\brdx\\b"),
        QStringLiteral("\\brdi\\b"),
        QStringLiteral("\\brsi\\b"),
        QStringLiteral("\\brbp\\b"),
        QStringLiteral("\\brsp\\b"),
        QStringLiteral("\\br8\\b"),
        QStringLiteral("\\br9\\b"),
        QStringLiteral("\\br10\\b"),
        QStringLiteral("\\br11\\b"),
        QStringLiteral("\\br12\\b"),
        QStringLiteral("\\br13\\b"),
        QStringLiteral("\\br14\\b"),
        QStringLiteral("\\br15\\b"),
    };

    for (const QString &pattern : registerPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = registerFormat;
        highlightingRules.append(rule);
    }

}

void AMD64SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
