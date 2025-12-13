#ifndef NOMINATIONDIALOG_H
#define NOMINATIONDIALOG_H

#include <QDialog>

namespace Ui {
class NominationDialog;
}

class NominationDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NominationDialog *ui;
public:
    explicit NominationDialog(QWidget *parent = nullptr);
    ~NominationDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // NOMINATIONDIALOG_H
