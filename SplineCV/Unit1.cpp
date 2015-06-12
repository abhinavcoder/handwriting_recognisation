//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "overhauser.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

CRSpline* spline = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
	if (!spline)
		return;
	TCanvas* canvas = this->Canvas;

	// Draw the control points
	canvas->Brush->Color = (TColor)0x201020;
	for (int i = 0; i < spline->GetNumPoints(); i++) {
		vec3& rv = spline->GetNthPoint(i);
		canvas->Ellipse((int)rv.x-4, (int)rv.y-4, (int)rv.x+4, (int)rv.y+4);
	}

	// Draw the spline
	vec3& rv = spline->GetNthPoint(0);
	canvas->MoveTo(rv.x, rv.y);
	for (int i = 0; i < 2000; i++) {
		float t = (float)i / (float)2000;
		vec3 rv = spline->GetInterpolatedSplinePoint(t);
		canvas->LineTo((int)rv.x, (int)rv.y);
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
#define frand(n) ((n)*((float)rand() / (float)RAND_MAX))
	int w = this->Width;
	int h = this->Height;
	if (spline)
	    delete spline;
	spline = new CRSpline();
    this->Color = (TColor)(rand() + rand());
	for (int i = 0; i < 20; i++) {
		vec3 v(10 + i * (w/20), 20.0 + frand(h/2), 0);
		spline->AddSplinePoint(v);
	}
	Repaint();
}
//---------------------------------------------------------------------------

