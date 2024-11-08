#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QHelpEngine>
#include <QObject>
#include <QTextBrowser>

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = 0);
    virtual QVariant loadResource(int type, const QUrl &url);

private:
    QHelpEngine *helpEngine;
};

#endif // HELPBROWSER_H
