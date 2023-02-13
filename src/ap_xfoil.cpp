#include "ap_xfoil.h"

#include "ap_convert.h"

#include <fstream>
#include <iostream>

#include <cstring> // refactor and remove !!!!

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
	
	//global_pipe_command = "./Xfoil > Xfoil.log";
    global_pipe_command = "Xfoil > Xfoil.log";
}

void XFOIL::PrintParams(std::ostream &out)
{
	using namespace std;

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

int XFOIL::MakeAirfoil(std::string airfoil_in, std::string airfoil_out, std::string pipe_command)
{ 
	std::string command = global_pipe_command;

	if(pipe_command.length())
		command = pipe_command;
	
    FILE *pXfoil;
          
    if (( pXfoil = popen(command.c_str(), "w")) == NULL)
    {
        std::clog << "XFoil pipe error!!!" << std::endl;
        return 1;
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
	
	return 0;
}

int XFOIL::Mixing(std::string airfoil_in1, std::string airfoil_in2, std::string airfoil_out, std::string pipe_command)
{
	std::string command = global_pipe_command;

	if(pipe_command.length())
		command = pipe_command;

	FILE *pXfoil;
          
    if (( pXfoil = popen(command.c_str(), "w")) == NULL)
    {
        std::clog << "XFoil pipe error!!!" << std::endl;
        return 1;
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
	
	return 0;
}

int XFOIL::ModifyAirfoil(std::string airfoil_in, std::string airfoil_out, std::string pipe_command)
{
	std::string command = global_pipe_command;

	if(pipe_command.length())
		command = pipe_command;

	FILE *pXfoil;
          
    if (( pXfoil = popen(command.c_str(), "w")) == NULL)
    {
        std::clog << "XFoil pipe error!!!" << std::endl;
        return 1;
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
	
	return 0;
}

int XFOIL::Flap(std::string airfoil_in, std::string airfoil_out, std::string pipe_command)
{
	std::string command = global_pipe_command;

	if(pipe_command.length())
		command = pipe_command;

	FILE *pXfoil;
          
    if (( pXfoil = popen(command.c_str(), "w")) == NULL)
    {
        std::clog << "XFoil pipe error!!!" << std::endl;
        return 1;
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
	
	return 0;
}

int XFOIL::Analyz(bool FlowFlag, double Flow, std::string airfoil_in, std::string aero_dat, std::string pipe_command)
{       
	std::string command = global_pipe_command;

	if(pipe_command.length())
		command = pipe_command;

    FILE *pXfoil;
    
	if (( pXfoil = popen(command.c_str(), "w")) == NULL)
    {
        std::clog << "XFoil pipe error!!!" << std::endl;
        return 1;
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
	
	return 0;
}

int XFOIL::Convergence(std::string log_file, int &err_nr, std::string &errors)
{
	int  i   = 0;
	std::string logline;
	size_t found;
	
	err_nr   = 0;
	
	std::ifstream in(log_file.c_str());
	
	if(!in)
	{
		std::clog << "Couldn't read log file for convergence check!" << std::endl;
		return 1;
	}

	while(!in.eof())
	{
		i++;
		
		getline(in, logline);
	
		found = logline.find("VISCAL:  Convergence failed");
		found = logline.find("Local speed too large");
  
		if (found != std::string::npos)
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

	return 0;
}

int XFOIL::GetData(std::string aero_dat)
{
	using namespace std;
	
    // *** DATA FROM Xfoil ***
     
    std::string linia;
    
    ifstream in(aero_dat.c_str());
	
    if(!in)
    {
        clog << "Data_out error!!!" << endl;
        return 1;
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
				return 2;
			}
			
			in >> fixed >> Alfa >> CL >> CD >> CDp >> CM >> Top_Xtr >> Bot_Xtr;
			in.close(); 
			return 0;
		}
	}

    //in.close(); 
	
	return 1;
}

void DelFile(std::string File)
{
	std::string Str;

	#ifdef _WIN32
		Str = "@if exist \"" + File + "\" del /q \"" + File + "\"";
	#else
		Str = "test -f \"" + File + "\" && rm -f \"" + File + "\"";
	#endif
	
	std::clog << "del_file: "<< system(Str.c_str()) << std::endl;
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
