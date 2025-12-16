#include "staffwindow.h"
#include "ui_staffwindow.h"

#include <QMessageBox>
#include "staffdialog.h"
#include "numcertificatedialog.h"

StaffWindow::StaffWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StaffWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new StaffTableModel(this->database, this);

    this->proxy_model = new StaffProxyModel(ui->num_certificate_edit, ui->surname_edit, ui->name_edit,
                                            ui->patronym_edit, ui->profession_box, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->staff_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("(БП|ПЛ|ИН)-[0-9]{6}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));

    ui->num_certificate_edit->setValidator(val1);
    ui->surname_edit->setValidator(val2);
    ui->name_edit->setValidator(val3);
    ui->patronym_edit->setValidator(val4);

    connect(ui->add_button, &QPushButton::clicked, this, &StaffWindow::AddStaff);
    connect(ui->change_button, &QPushButton::clicked, this, &StaffWindow::ChangeStaff);
    connect(ui->delete_button, &QPushButton::clicked, this, &StaffWindow::RemoveStaff);
}

StaffWindow::~StaffWindow()
{
    delete ui;
}

void StaffWindow::AddStaff()
{
    StaffDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Staff staff = add_dialog.GetData();
        bool (*func)(const Staff&, const Staff&) = [](const Staff& a, const Staff& b)
        {
            return a.GetNumCertificate() == b.GetNumCertificate();
        };

        if (this->database->FindStaff(staff, func) != -1)
        {
            box.setText("Сотрудник с таким номером удостоверения уже есть в системе!");
            box.exec();
        }
        else
        {
            this->database->AddStaff(staff, true);

            box.setText("Сотрудник добавлен в систему!");
            box.exec();
        }
    }
}

void StaffWindow::ChangeStaff()
{
    NumCertificateDialog old_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QString old_num_certificate = old_dialog.GetData();

        int i = this->database->FindStaff(Staff(old_num_certificate, "", "", "", Profession::PILOT),
                                          [](const Staff& a, const Staff& b)
                                          {
                                              return a.GetNumCertificate() == b.GetNumCertificate();
                                          });

        if (i == -1)
        {
            box.setText("Сотрудника с таким номером удостоверения нет в системе!");
            box.exec();
        }
        else
        {
            Staff staff = this->database->GetStaff(i);
            StaffDialog upd_dialog(&staff, this);

            if (upd_dialog.exec() == 1)
            {
                Staff new_staff = upd_dialog.GetData();

                int j = this->database->FindStaff(new_staff,
                                                  [](const Staff& a, const Staff& b)
                                                  {
                                                      return a.GetNumCertificate() == b.GetNumCertificate();
                                                  });

                if (j != -1)
                {
                    box.setText("Система не смогла обновить сотрудника!");
                    box.exec();
                }
                else
                {
                    int g;

                    this->database->ChangeState(false);

                    while ((g = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, "", old_num_certificate),
                                                            [](const Purpose& a, const Purpose& b)
                                                            {
                                                                return a.GetNumCertificate() == b.GetNumCertificate();
                                                            })) != -1)
                    {
                        Purpose purpose = this->database->GetPurpose(g);
                        purpose.SetNumCertificate(new_staff.GetNumCertificate());
                        this->database->UpdatePurpose(purpose, g, true);
                    }

                    this->database->ChangeState(true);
                    this->database->UpdateStaff(new_staff, i, true);

                    box.setText("Система обновила сотрудника!");
                    box.exec();
                }
            }
        }
    }
}

void StaffWindow::RemoveStaff()
{
    NumCertificateDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QString num_certificate = del_dialog.GetData();
        bool (*func)(const Staff&, const Staff&) = [](const Staff& a, const Staff& b)
        {
            return a.GetNumCertificate() == b.GetNumCertificate();
        };

        if (this->database->FindStaff(Staff(num_certificate, "", "", "", Profession::PILOT), func) == -1)
        {
            box.setText("Сотрудника с таким номером удостоверения нет в системе!");
            box.exec();
        }
        else
        {
            this->database->ChangeState(false);

            int i;

            while ((i = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, "", num_certificate),
                                                   [](const Purpose& a, const Purpose& b)
                                                   {
                                                       return a.GetNumCertificate() == b.GetNumCertificate();
                                                   })) != -1)
            {
                this->database->RemovePurpose(i, true);
            }

            this->database->ChangeState(true);

            this->database->RemoveStaff(this->database->FindStaff(Staff(num_certificate, "", "", "", Profession::PILOT), func), true);

            box.setText("Сотрудник и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}
