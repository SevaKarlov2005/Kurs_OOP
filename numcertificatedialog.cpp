#include "numcertificatedialog.h"
#include "ui_numcertificatedialog.h"

#include "QRegularExpressionValidator"

NumCertificateDialog::NumCertificateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NumCertificateDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("(БП|ИН|ПЛ)-[0-9]{6}"));
    ui->num_certificate_edit->setValidator(val);

    connect(ui->num_certificate_edit, &QLineEdit::textChanged, this, &NumCertificateDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

NumCertificateDialog::~NumCertificateDialog()
{
    delete ui;
}

void NumCertificateDialog::Validation() const
{
    if (ui->num_certificate_edit->text().length() == 9)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString NumCertificateDialog::GetData() const
{
    return ui->num_certificate_edit->text();
}
