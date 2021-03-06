#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QLineEdit;
class QProgressBar;

// Rq : attention : fermer un spoiler alors qu'on a le curseur dans une zdt fait quitter le curseur => finishediting

class InputText : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    enum Helper{None, Directory, SaveFile, OpenFile};

    explicit InputText(const QString & label = QString(),
                       const QString &defaultValue = QString(),
                       Helper= None);
    virtual ~InputText(){}

    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);
private slots :
    void openPopUp(void);
    void valueChanged(void);
private :
    QLineEdit * m_inputText;
    QFrame * m_frame;
    Helper m_helper;
};

#endif // INPUTTEXT_H
