#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "sourceparameters.h"
#include <QObject>
#include <QProgressBar>

class ProgressBar : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    ProgressBar(const QString & label = QString());

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~ProgressBar();

    virtual void setValue(int percent);

    virtual void setMaximum(int max);

private :
    QProgressBar * m_progressbar;
private slots :
    void changeValue(int);

signals:

public slots:
    void valueChanged(int);

};

#endif // PROGRESSBAR_H