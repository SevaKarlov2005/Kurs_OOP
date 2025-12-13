#ifndef NUMCERTIFICATEDIALOG_H
#define NUMCERTIFICATEDIALOG_H

#include <QDialog>

namespace Ui {
class NumCertificateDialog;
}

class NumCertificateDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NumCertificateDialog *ui;
public:
    explicit NumCertificateDialog(QWidget *parent = nullptr);
    ~NumCertificateDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // NUMCERTIFICATEDIALOG_H
