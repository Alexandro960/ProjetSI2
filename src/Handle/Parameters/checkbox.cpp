#include <QLabel>
#include <QLayout>
#include <QCheckBox>
#include <QButtonGroup>

#include "checkbox.h"
#include "handleparameters.h"


CheckBox::CheckBox( const QString &label, const QStringList &boxes, const QStringList & defaultChecked )
    : SourceParameters(label),
      m_frame( new QFrame() )
{
    QLayout * layout = new QVBoxLayout();
    m_frame->setLayout( layout );
    m_checkboxs.reserve( boxes.size() );
    for(auto label : boxes)
    {
        QCheckBox * box = new QCheckBox(label);
        m_checkboxs.push_back( box );
        layout->addWidget( box );
        m_values.insert(label, false);
        connect(box, SIGNAL( clicked(bool) ), this, SLOT( changeValue(bool) ) );
        if( defaultChecked.contains(label) )
            box->setChecked(true);
    }
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void CheckBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_values );
}


void CheckBox::changeValue(const QString & text, bool  value)
{
    m_values[text] = value;
    for(QCheckBox * check : m_checkboxs)
        if(check->text() == text)
            check->setChecked(value);
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( m_values );
}


void CheckBox::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_frame->hide();
}


void CheckBox::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void CheckBox::changeValue(bool  value)
{
    QCheckBox * check = (QCheckBox *)QObject::sender();
    m_values[check->text()] = value;

    for(HandleParameters * hp : m_suscribers )
        hp->setValue( m_values );
}
