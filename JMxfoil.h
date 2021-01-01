#ifndef _XFOIL_H_
#define _XFOIL_H_

#include <iostream>
#include <fstream>
#include <string>

#include "JMmath.h"
#include "JMconvert.h"
#include "itoa.h"

void DelFile(string File);

class XFOIL
{
	public:

	char airfoil_in1[255];
	char airfoil_in2[255];
	char dir_out[255];
	char airfoil_out[255];
	
	double T;
	double T_x;
	double F;
	double F_x;
	
	double Xhinge;
	double Yhinge;
	double FlapAngle;
	
	double Gap;
	double GapBlend;
	
	double FoilMix;

	int	   PparN;
	double PparP;
	double PparT;
	double PparR;
	
	double Filt;
	int    Ncrit;
	double Vacc;
	
	double Re;
	double Ma;
	int	   XfoilIter;

	std::string global_pipe_command;
	std::string XfoilLogFile;
	std::string Airfoil;
	
	//Data
	
	double Alfa, CL, CD, CDp, CM, Top_Xtr, Bot_Xtr;
	
	XFOIL();
	void	PrintParams(std::ostream &out);
	int 	MakeAirfoil(std::string airfoil_in, std::string airfoil_out, std::string pipe_command="");
	int 	Mixing(std::string airfoil_in1, std::string airfoil_in2, std::string airfoil_out, std::string pipe_command="");
	int 	ModifyAirfoil(std::string airfoil_in, std::string airfoil_out, std::string pipe_command="");
	int		Flap(std::string airfoil_in, std::string airfoil_out, std::string pipe_command="");
	int		Analyz(bool FlowFlag, double Flow, std::string airfoil_in, std::string aero_dat, std::string pipe_command="");
	int		Convergence(std::string log_file, int &err_nr, std::string &errors);
	int  	GetData(std::string aero_dat);
	void	DelFile(std::string file);
	
	private:
	
	void	pPpar(FILE *pXfoil);
	void 	pGap(FILE *pXfoil);
};

#endif
