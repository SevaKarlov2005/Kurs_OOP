#ifndef NUMPASSPORTDIALOG_H
#define NUMPASSPORTDIALOG_H

#include <QDialog>

namespace Ui {
class NumPassportDialog;
}

class NumPassportDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NumPassportDialog *ui;
public:
    explicit NumPassportDialog(QWidget *parent = nullptr);
    ~NumPassportDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // NUMPASSPORTDIALOG_H
