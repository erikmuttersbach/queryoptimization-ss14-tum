#include "Database.hpp"
#include "operator/Tablescan.hpp"
#include "operator/CrossProduct.hpp"
#include "operator/Selection.hpp"
#include "operator/Projection.hpp"
#include "operator/Printer.hpp"
#include "operator/Chi.hpp"
#include <iostream>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
int main()
{
   Database db;
   db.open("data/uni");
   Table& vorlesungen=db.getTable("vorlesungen");
   Table& professoren=db.getTable("professoren");
   Table& hoeren=db.getTable("hoeren");

   unique_ptr<Tablescan> scanVorlesungen(new Tablescan(vorlesungen));
   unique_ptr<Tablescan> scanProfessoren(new Tablescan(professoren));
   unique_ptr<Tablescan> scanHoeren(new Tablescan(hoeren));
   
   const Register* pname=scanProfessoren->getOutput("name");
   const Register* ppersnr=scanProfessoren->getOutput("persnr");
   const Register* vvorlnr=scanVorlesungen->getOutput("vorlnr");
   const Register* vgelesenvon=scanVorlesungen->getOutput("gelesenvon");
   const Register* hvorlnr=scanHoeren->getOutput("vorlnr");   

   // join hoeren with vorlesungen on vorlnr
   unique_ptr<CrossProduct> cpHoerenVorl(new CrossProduct(move(scanHoeren),move(scanVorlesungen)));
   unique_ptr<Selection> selectHVorlnrVVorlnr(new Selection(move(cpHoerenVorl),hvorlnr,vvorlnr));
   
   // select schopenhauer from student table
   Register schopenhauer; schopenhauer.setString("Schopenhauer");
   unique_ptr<Chi> chiSchopenhauer(new Chi(move(scanStudenten),Chi::Equal,name,&schopenhauer));
   const Register* chiSchopenhauerResult=chiSchopenhauer->getResult();
   unique_ptr<Selection> selectSchopenhauer(new Selection(move(chiSchopenhauer),chiSchopenhauerResult));

   // join schopenhauer with hoeren1 on matrnr
   unique_ptr<CrossProduct> cpSchopenhauerHoeren1(new CrossProduct(move(selectSchopenhauer),move(scanHoeren1)));
   unique_ptr<Selection> selectSMatrNrH1MatrNr(new Selection(move(cpSchopenhauerHoeren1),smatrnr,h1matrnr));

   // join last join with hoeren2 on vorlnr
   unique_ptr<CrossProduct> cpLastjoinHoeren2(new CrossProduct(move(selectSMatrNrH1MatrNr),move(scanHoeren2)));
   unique_ptr<Selection> selectLastjoinVorlNrH2VorlNr(new Selection(move(cpLastjoinHoeren2),h1vorlnr,h2vorlnr));

   // select all students but schopenhauer from last join
   unique_ptr<Chi> chiNotSchopenhauer(new Chi(move(selectLastjoinVorlNrH2VorlNr),Chi::NotEqual,h1matrnr, h2matrnr));
   const Register* chiNotSchopenhauerResult=chiNotSchopenhauer->getResult();
   unique_ptr<Selection> selectNotSchopenhauer(new Selection(move(chiNotSchopenhauer),chiNotSchopenhauerResult));
   unique_ptr<Projection> project(new Projection(move(selectNotSchopenhauer),{h2matrnr}));

   // print the result (a list of MatrNr of all students that attended lectures together with Schopenhauer)
   Printer out(move(project));

   out.open();
   while (out.next());
   out.close();
}
//---------------------------------------------------------------------------
