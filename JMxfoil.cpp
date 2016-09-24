#include "JMxfoil.h"

using namespace std;

XFOIL::XFOIL()
{
	T	= 0;
	T_x	= 0;
	F	= 0;
	F_x = 0;
	
	Xhinge = 0.8;
	Yhinge = 0.5;
	FlapAngle = 0;
	
	Gap      = 0;
	GapBlend = 0.9;
	
	FoilMix  = 0.5;
		
	PparN = 160;
	PparP = 0.8; //1.0
	PparT = 0.8; //0.15
	PparR = 0.1; //0.2
	
	Filt  = 1;
	
	Ncrit = 9;
	Vacc  = 0.001;
	
	Re = 200000;
	Ma = 0;
	XfoilIter = 40;
}

void XFOIL::PrintParams(ostream &out)
{
	out << "Gap = " << Gap << endl;
	out << "GapBlend = " << GapBlend << endl;
	
	out << "FoilMix = " << FoilMix << endl;
		
	out << "PparN = " << PparN << endl;
	out << "PparP = " << PparP << endl;
	out << "PparT = " << PparT << endl;
	out << "PparR = " << PparR << endl;
	
	out << "Filt  = " << Filt << endl;
	
	out << "Ncrit = " << Ncrit << endl;
	out << "Vacc  = " << Vacc << endl;
	
	out << "Re    = " << Re << endl;
	out << "Ma    = " << Ma << endl;
	out << "XfoilIter = " << XfoilIter << endl;
}

int XFOIL::MakeAirfoil(string airfoil_in, string airfoil_out)
{   
    FILE *pXfoil;
          
    if (( pXfoil = popen("Xfoil > XfoilMake.log", "w")) == NULL)
    {
        cout << "XFoil pipe error!!!" << endl;
        return 0;
    }
    
    fputs("PLOP\n", pXfoil);
    fputs("G\n\n", pXfoil);
    
	fputs(airfoil_in.c_str(), pXfoil);
	fputs("\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
		pPpar(pXfoil);
		pGap(pXfoil);
    fputs("PANE\n", pXfoil);
    fputs("SAVE ", pXfoil);
    fputs(airfoil_out.c_str(), pXfoil);
    fputs("\n", pXfoil);
	fputs("Y\n", pXfoil);	//POTWIRDZENIE NADPISYWANIA!!!
    fputs("QUIT\n", pXfoil);
    
	fputs("echo", pXfoil);
	fputs(airfoil_out.c_str(), pXfoil);
	fputs("\n", pXfoil);
	
    fflush(pXfoil);
  
    pclose(pXfoil);
	
	return 1;
}

int XFOIL::Mixing(string airfoil_in1, string airfoil_in2, string airfoil_out)
{
	FILE *pXfoil;
          
    if (( pXfoil = popen("Xfoil > XfoilMixing.log", "w")) == NULL)
    {
        cout << "XFoil pipe error!!!" << endl;
        return 0;
    }
	
	fputs("PLOP\n", pXfoil);
    fputs("G\n\n", pXfoil);
    
    fputs("INTE\n", pXfoil);
    fputs("F\n", pXfoil);
    fputs(airfoil_in1.c_str(), pXfoil);
    fputs("\n", pXfoil);
    fputs("F\n", pXfoil);
    fputs(airfoil_in2.c_str(), pXfoil);
    fputs("\n", pXfoil);
    fputs(d2Cstr(FoilMix), pXfoil);
    fputs("\n", pXfoil);
    fputs(airfoil_out.c_str(), pXfoil);
    fputs("\n", pXfoil);
		pPpar(pXfoil);
		pGap(pXfoil);
	fputs("PANE\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
	fputs("SAVE ", pXfoil);
    fputs(airfoil_out.c_str(), pXfoil);
    fputs("\n", pXfoil);
	fputs("Y\n", pXfoil);	//POTWIRDZENIE NADPISYWANIA!!!
    fputs("QUIT\n", pXfoil);
	
	fflush(pXfoil);
  
    pclose(pXfoil);
	
	return 1;
}

int XFOIL::ModifyAirfoil(string airfoil_in, string airfoil_out)
{
	FILE *pXfoil;
          
    if (( pXfoil = popen("Xfoil > XfoilModify.log", "w")) == NULL)
    {
        cout << "XFoil pipe error!!!" << endl;
        return 0;
    }
	
	fputs("PLOP\n", pXfoil);
    fputs("G\n\n", pXfoil);
    
	fputs(airfoil_in.c_str(), pXfoil);
	fputs("\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
		pPpar(pXfoil);
		pGap(pXfoil);
	fputs("GDES\n", pXfoil);
		fputs("TSET\n", pXfoil); 
		if(T == 0)
			fputs("\n", pXfoil);
		else
			fputs(d2Cstr(T), pXfoil);
		fputs("\n", pXfoil); 
		if(F == 0)
			fputs("\n", pXfoil);
		else
			fputs(d2Cstr(F), pXfoil);
        fputs("\n", pXfoil);
		fputs("HIGH\n", pXfoil);
	if(T_x == 0)
		fputs("\n", pXfoil);
	else
		fputs(d2Cstr(T_x), pXfoil);
        fputs("\n", pXfoil);
	if(F_x == 0)
		fputs("\n", pXfoil);
	else
		fputs(d2Cstr(F_x), pXfoil);
        fputs("\n", pXfoil);
		
    fputs("CADD\n\n\n\n", pXfoil);
    fputs("EXEC\n\n", pXfoil);
	fputs("PANE\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
	fputs("SAVE ", pXfoil);
    fputs(airfoil_out.c_str(), pXfoil);
    fputs("\n", pXfoil);
	fputs("Y\n", pXfoil);	//POTWIRDZENIE NADPISYWANIA!!!
    fputs("QUIT\n", pXfoil);
	
	fflush(pXfoil);
  
    pclose(pXfoil);
	
	return 1;
}

int XFOIL::Flap(string airfoil_in, string airfoil_out)
{
	FILE *pXfoil;
          
    if (( pXfoil = popen("Xfoil > Xfoil.log", "w")) == NULL)
    {
        cout << "XFoil pipe error!!!" << endl;
        return 0;
    }
	
	fputs("PLOP\n", pXfoil);
    fputs("G\n\n", pXfoil);
    
	fputs(airfoil_in.c_str(), pXfoil);
	fputs("\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
		pPpar(pXfoil);
		pGap(pXfoil);
	fputs("GDES\n", pXfoil);
		fputs("FLAP\n", pXfoil); 
        fputs(d2Cstr(Xhinge), pXfoil);
		fputs("\n", pXfoil); 
        fputs("999\n", pXfoil);
        fputs(d2Cstr(Yhinge), pXfoil);
        fputs("\n", pXfoil);
		fputs(d2Cstr(FlapAngle), pXfoil);
        fputs("\n", pXfoil);
    fputs("CADD\n\n\n\n", pXfoil);
    fputs("EXEC\n\n", pXfoil);
	fputs("PANE\n", pXfoil);
	fputs("NAME\n\n", pXfoil);
	fputs("SAVE ", pXfoil);
    fputs(airfoil_out.c_str(), pXfoil);
    fputs("\n", pXfoil);
	fputs("Y\n", pXfoil);	//POTWIRDZENIE NADPISYWANIA!!!
    fputs("QUIT\n", pXfoil);
	
	fflush(pXfoil);
  
    pclose(pXfoil);
	
	return 1;
}

int XFOIL::Analyz(bool FlowFlag, double Flow, string airfoil_in, string aero_dat)
{       
    FILE *pXfoil;
          
    if (( pXfoil = popen("Xfoil > XfoilAnalyz.log", "w")) == NULL)
    {
        cout << "XFoil pipe error!!!" << endl;
        return 0;
    }
	
	fputs("PLOP\n", pXfoil);
	fputs("G\n\n", pXfoil);
	
	fputs(airfoil_in.c_str(), pXfoil);
	fputs("\n", pXfoil);
		pPpar(pXfoil);
		pGap(pXfoil);
    fputs("PANE\n", pXfoil);
    
    fputs("MDES\n", pXfoil);  
    fputs(d2Cstr(Filt), pXfoil);
	fputs("\n", pXfoil);
    fputs("EXEC\n\n", pXfoil);
    
	fputs("PANE\n", pXfoil);
    fputs("OPER\n", pXfoil);
    
    fputs("VPAR\n", pXfoil);
	fputs("N\n", pXfoil);
    fputs(int2Cstr(Ncrit), pXfoil);
	fputs("\n", pXfoil);
	fputs("VACC\n", pXfoil);  
    fputs(d2Cstr(Vacc), pXfoil);
    fputs("\n\n", pXfoil);
	
	char FlowCh[8];
	
	if(FlowFlag)
		strcpy(FlowCh, "a ");
	else
		strcpy(FlowCh, "c ");
		
	fputs(FlowCh, pXfoil); 
    fputs(d2Cstr(Flow), pXfoil);
	fputs("\n", pXfoil);
	fputs("VISC ", pXfoil);  
    fputs(d2Cstr(Re), pXfoil);
	fputs("\n", pXfoil);
	fputs("MACH ", pXfoil);   
    fputs(d2Cstr(Ma), pXfoil);
	fputs("\n", pXfoil);
    fputs("ITER\n", pXfoil);   
    fputs(int2Cstr(XfoilIter), pXfoil);
	fputs("\n", pXfoil);
	fputs(FlowCh, pXfoil);  
    fputs(d2Cstr(Flow), pXfoil);
	fputs("\n", pXfoil);
    fputs("INIT\n", pXfoil);
    fputs(FlowCh, pXfoil);  
    fputs(d2Cstr(Flow), pXfoil);
	fputs("\n", pXfoil);
    fputs("PACC\n", pXfoil);
	fputs(aero_dat.c_str(), pXfoil);
    fputs("\n\n", pXfoil);
    fputs(FlowCh, pXfoil);   
    fputs(d2Cstr(Flow), pXfoil);
	fputs("\n", pXfoil);
    fputs("PACC\n", pXfoil);
	fputs("y\n\n", pXfoil);
	fputs("\n", pXfoil);
	
    fputs("QUIT\n", pXfoil);
   
    fflush(pXfoil);
  
    pclose(pXfoil);
	
	return 1;
}

void XFOIL::Convergence(string log_file, int &err_nr, string &errors)
{
	int  i   = 0;
	string logline;
	size_t found;
	
	err_nr   = 0;
	
	ifstream in(log_file.c_str());
	
	while(!in.eof())
	{
		i++;
		
		getline(in, logline);
	
		found = logline.find("VISCAL:  Convergence failed");
		found = logline.find("Local speed too large");
  
		if (found != string::npos)
		{
			if(err_nr == 0)
				errors = logline + " (" + int2Str(i) + ")\n"; 
			else
				errors += logline + " (" + int2Str(i) + ")\n";
			
			err_nr += 1;
		}
	}
	
	errors += "nr of log lines: " + int2Str(i) + "\n";
	
	in.close();
}

int  XFOIL::GetData(string aero_dat)
{
    // *** DATA FROM Xfoil ***
     
    string linia;
     
    ifstream in(aero_dat.c_str());
	
    if(!in)
    {
        cout << "Data_out error!!!" << endl;
        return 0;
    }
       
    while(true)
    {
        //getline(in, linia, '\n');
		in >> linia;
        
        if ("-" == linia.substr(1,1))  
		{
			getline(in, linia, '\n');
            break;     
		}
    }
   
	int PeekResult;
	
	for(int i=0; i<100; i++)
	{
		PeekResult = in.peek();
		
		if(PeekResult==10 || PeekResult==32)
		{
			in.get();
			continue;
		}
		
		else
		{
			if(PeekResult==-1)
			{
				in.close(); 
				return 0;
			}
			
			in >> fixed >> Alfa >> CL >> CD >> CDp >> CM >> Top_Xtr >> Bot_Xtr;
			in.close(); 
			return 1;
		}
	}

    //in.close(); 
	
	return 1;
}

void DelFile(string File)
{
	string Str = "@if exist \"" + File + "\" del /q \"" + File + "\"";
    system(Str.c_str());
}

void XFOIL::pPpar(FILE *pXfoil)
{
	fputs("PPAR\n", pXfoil);
	fputs("N\n", pXfoil);
	fputs(int2Cstr(PparN), pXfoil);
	fputs("\n", pXfoil);
	fputs("P\n", pXfoil);
	fputs(d2Cstr(PparP), pXfoil);
	fputs("\n", pXfoil);
	fputs("T\n", pXfoil);
	fputs(d2Cstr(PparT), pXfoil);
	fputs("\n", pXfoil);
	fputs("R\n", pXfoil);
	fputs(d2Cstr(PparR), pXfoil);
	fputs("\n", pXfoil);
	//fputs("XT 0.2 0.6\n", pXfoil);
	//fputs("XB 0.2 0.6\n", pXfoil);
    fputs("\n\n", pXfoil);
}

void XFOIL::pGap(FILE *pXfoil)
{
	fputs("GDES\n", pXfoil);
	fputs("TGAP\n", pXfoil);
	fputs(d2Cstr(Gap), pXfoil);
	fputs("\n", pXfoil);
	fputs(d2Cstr(GapBlend), pXfoil);
	fputs("\n", pXfoil);
	fputs("X\n\n\n", pXfoil);
}