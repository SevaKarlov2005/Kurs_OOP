#ifndef PURPOSEDIALOG_H
#define PURPOSEDIALOG_H

#include <QDialog>
#include "purpose.h"

namespace Ui {
class PurposeDialog;
}

class PurposeDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::PurposeDialog *ui;
public:
    explicit PurposeDialog(Purpose* purpose, QWidget *parent = nullptr);
    ~PurposeDialog();
    void Validation() const;
    Purpose GetData() const;
};

#endif // PURPOSEDIALOG_H
