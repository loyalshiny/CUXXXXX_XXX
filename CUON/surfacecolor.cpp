// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "pch.h"
#include "framework.h"
#include "surfacecolor.h"


/////////////////////////////////////////////////////////////////////////////
// CSurfaceColor properties

unsigned long CSurfaceColor::GetColor()
{
	unsigned long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CSurfaceColor::SetColor(unsigned long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

long CSurfaceColor::GetGradientType()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CSurfaceColor::SetGradientType(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

short CSurfaceColor::GetGradientFactor()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

void CSurfaceColor::SetGradientFactor(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}

long CSurfaceColor::GetRender3DType()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

void CSurfaceColor::SetRender3DType(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}

unsigned long CSurfaceColor::GetColor2()
{
	unsigned long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CSurfaceColor::SetColor2(unsigned long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CSurfaceColor operations