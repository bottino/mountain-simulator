/*
 * EPFL
 * CAESV3
 * Guide wxWidgets et OpenGL
 * Mini-Projet
 */
#include "Conversions.h"

wxString double2wxString(double i) {
	wxString string = wxString()<<i;
	return string;
	
}

wxString int2wxString(int i)
{
	wxString string = wxString()<<i;
	return string;
}
wxString string2wxString(std::string s)
{
	wxString retour(s.c_str(), wxConvUTF8);
	return retour;
}
std::string wxString2string(wxString s)
{
	std::string str = std::string(s.mb_str());
	return str;
}
