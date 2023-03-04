#include "MemberFeesController.h"

#include <iostream>
#include "MemberModel.h"
#include <QMessageBox>
#include "MemberFeesView.h"
#include "ListModel.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include "Defs.h"

MemberFeesController::MemberFeesController(Model *pModel, View *pView):
    TableController(pModel, pView)
{

}

void MemberFeesController::init()
{
    try
    {
        ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
        listModel->getAll();
    }
    catch(std::runtime_error &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void MemberFeesController::updateView()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    try
    {
        listModel->getAll();
        view->render();
    }
    catch(std::runtime_error &error)
    {
        QMessageBox box(QMessageBox::Warning, "Databasfel", QString::fromStdString(error.what()));
        box.exec();
    }
}

void MemberFeesController::changeSelection()
{
    selectedRows.clear();
    MemberFeesView *mView = static_cast<MemberFeesView*>(view);

    QList<QTableWidgetItem*> list = mView->getTable()->selectedItems();
    for(QTableWidgetItem *item : list)
    {
        selectedRows.insert((item->row()));
    }

    if(this->selectedRows.size() == 0)
    {        
        mView->activateButtons(false);
    }
    else
    {
        mView->activateButtons(true);
    }
}

void MemberFeesController::toggle()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);

    unsigned int row = *selectedRows.begin();
    MemberModel mModel = listModel->atIndex(row);

    if(mModel.isMemberFeePayed())
    {
        mModel.setMemberFeeStatus(false);
    }
    else
    {
        mModel.setMemberFeeStatus(true);
    }

    mModel.save(false);
    updateView();
}

void MemberFeesController::exportToPdf()
{   
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    std::set<MemberModel>::const_iterator citerator;
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);    
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName("medlemsavgifter.pdf");

    QTextDocument doc;
    QString html = "<html><head><link rel='stylesheet' type='text/css' href='styles.css' /></head><body><h1><center>Medlemsavgifter</center></h1>";
    html += "<table><thead><tr><th>Namn</th><th>Födelsedag</th><th>Medlemsavgift</th></thead><tbody>";
    for(citerator = listModel->cbegin(); citerator != listModel->cend(); ++citerator)
    {
        html += "<tr><td>" + citerator->getFullName()+ "</td><td>" + citerator->getBirthdate() + "</td>";

        if(citerator->isMemberFeePayed())
        {
            html += "<td style='background:green'></td></tr>";
        }
        else
        {
            html += "<td style='background:red'></td></tr>";
        }
    }

    html += "</tbody></table>";
    html += "<br /><hr>";
    html += "<footer><p><i>©" + DEVELOPER_NAME + "</i></p></footer>";
    html += "</body></html>";

    doc.setHtml(html);
    doc.print(&printer);
}
