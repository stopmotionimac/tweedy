#include "GPhotoWidgetTextField.hpp"

GPhotoWidgetTextField::GPhotoWidgetTextField(CameraWidget* widget)
{
    _widget = widget;
}

QLineEdit * GPhotoWidgetTextField::makeMenu() {
    _textField = new QLineEdit(/*this*/);
    /*make the appropriate action*/
    QLineEdit::connect(_textField, SIGNAL(textChanged(const QString&)), this, SLOT(on_setValue_textChanged(const QString&)));
    return _textField;
}

void GPhotoWidgetTextField::on_setValue_textChanged(const QString & valueChoice){
    Projet& projectInstance = Projet::getInstance();
    projectInstance.gPhotoInstance().setValue(_widget, valueChoice.toStdString().data());
}
