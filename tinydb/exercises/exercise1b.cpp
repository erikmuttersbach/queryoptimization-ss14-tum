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
   
   //const Register* pname=scanProfessoren->getOutput("name");
   //const Register* ppersnr=scanProfessoren->getOutput("persnr");
   const Register* vvorlnr=scanVorlesungen->getOutput("vorlnr");
   //const Register* vgelesenvon=scanVorlesungen->getOutput("gelesenvon");
   const Register* hvorlnr=scanHoeren->getOutput("vorlnr");   

   // join hoeren with vorlesungen on vorlnr
   unique_ptr<CrossProduct> cpHoerenVorl(new CrossProduct(move(scanHoeren),move(scanVorlesungen)));
   unique_ptr<Selection> selectHVorlnrVVorlnr(new Selection(move(cpHoerenVorl),hvorlnr,vvorlnr));
   
  // count the occurrences of every lecture(???)
  
  
   // debug print
   unique_ptr<Projection> project(new Projection(move(selectHVorlnrVVorlnr),{hvorlnr}));

   // print the result 
   Printer out(move(project));

   out.open();
   while (out.next());
   out.close();
}
//---------------------------------------------------------------------------
