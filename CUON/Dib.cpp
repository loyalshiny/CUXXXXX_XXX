// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "Dib.h"
#include <memory.h>
#include <string.h>
//#include "ManualEqip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CDib::CommonDib()
{
	m_pDibHdr = NULL;
	m_pBits = NULL;
	m_pPal = NULL;
	m_pViewBits = NULL;
	m_nErrorNo = 0;
	m_cxDIB = 0;
	m_cyDIB = 0;
	m_wBitCount = 0;
}

CDib::CDib()
{
	CommonDib();
}

CDib::CDib(CString filename, int tmp)
{
	CommonDib();
	if (!Create(filename, tmp))
		m_nErrorNo = 1;
}

CDib::CDib(int width, int height, WORD depth)
{
	CommonDib();
	Create(width, height, depth);
}

BOOL CDib::Create(CString filename, int tmp)
{
	CFile file;
	if ( file.Open(filename, CFile::modeRead) == NULL)
	{
		CString str;
		str = filename + "을 열 수 없습니다.";
		AfxMessageBox(str);
		return FALSE;
	}
	else {
		if(!ReadDIBFile(file))
		{
			file.Close();
			CString str;
			str = filename + "을 읽는데 실패했습니다.\n"
				+ "파일형식이 맏는지 확인해주십시요.";
			AfxMessageBox(str);
			return FALSE;
		}
		file.Close();

		m_cxDIB  = DIBWidth(m_pDibHdr);
		m_cyDIB  = DIBHeight(m_pDibHdr);
		m_wBitCount = DIBBitCount(m_pDibHdr);

		InitDIBData();
	}
	return TRUE;
}

int CDib::ReNewDib(int width, int height, WORD depth)
{
	Free();
    DWORD       dwSizeImage;
    dwSizeImage = height*(DWORD)((width*depth/8+3)&~3);

	if(depth == 24)
	{
		m_pDibHdr = new char[sizeof(BITMAPINFOHEADER)];
	}else{
		m_pDibHdr = new char[sizeof(BITMAPINFOHEADER) +(256*4)];
	}
	m_pBits = new BYTE[dwSizeImage];

    if ( !m_pDibHdr || !m_pBits)
	{
		m_cxDIB = 0;
		m_cyDIB = 0;
		m_wBitCount = 0;
        return FALSE;
	}
	m_cxDIB = width;
	m_cyDIB = height;
	m_wBitCount = depth;
	
	return dwSizeImage;
}

BOOL CDib::Create(int width, int height, WORD depth)
{	
	LPBITMAPINFOHEADER lpbi ;
	BYTE		*lpPal;
    DWORD       dwSizeImage;
    int         i;

	if(!(dwSizeImage=ReNewDib(width, height, depth)))
		return FALSE;
	lpbi = (LPBITMAPINFOHEADER)m_pDibHdr;
	lpbi->biSize            = sizeof(BITMAPINFOHEADER) ;
    lpbi->biWidth           = width;
    lpbi->biHeight          = height;
    lpbi->biPlanes          = 1;
    lpbi->biBitCount        = depth;
    lpbi->biCompression     = BI_RGB ;
    lpbi->biSizeImage       = dwSizeImage;
    lpbi->biXPelsPerMeter   = 0 ;
    lpbi->biYPelsPerMeter   = 0 ;
    lpbi->biClrUsed         = 0 ;
    lpbi->biClrImportant    = 0 ;

	lpPal = (BYTE *) lpbi;
	if (depth == 8)
	{
		lpbi->biClrUsed = 256;

		DWORD offDest = sizeof(BITMAPINFOHEADER);
		for(i = 0; i < 256; i++)
		{
			lpPal[offDest++] = (BYTE)i;
			lpPal[offDest++] = (BYTE)i;
			lpPal[offDest++] = (BYTE)i;
			lpPal[offDest++] = 0x00;
		}                  
	}
	InitDIBData();
	
	return TRUE;
}

CDib::~CDib()
{
	Free();
}

void CDib::Free()
{
	if (m_pDibHdr)
	{
		delete[] m_pDibHdr;
		m_pDibHdr = NULL;
	}
	if (m_pBits)
	{
		delete[] m_pBits;
		m_pBits = NULL;
	}

	if (m_pViewBits != NULL)
	{
		delete[] m_pViewBits;
		m_pViewBits = NULL;
	}	
	if (m_pPal != NULL)
	{
		delete m_pPal;
		m_pPal = NULL;
	}
	m_cxDIB = 0;
	m_cyDIB = 0;
	m_wBitCount = 0;
}

CDib& CDib::operator=( CDib &Src )  // Right side is the argument.
{
	ReNewDib(Src.GetWidth(), Src.GetHeight(), Src.GetBitCount());
// 	memcpy(m_pDibHdr,Src.m_pDibHdr,_msize(m_pDibHdr));
 //	memcpy(m_pBits,Src.m_pBits,_msize(m_pBits));
	InitDIBData();
	return (*this);
}

/*************************************************************************
 *
 * SaveDIB()
 *
 * Saves the specified DIB into the specified CFile.  The CFile
 * is opened and closed by the caller.
 *
 * Parameters:
 *
 * HDIB hDib - Handle to the dib to save
 *
 * CFile& file - open CFile used to save DIB
 *
 * Return value: TRUE if successful, else FALSE or CFileException
 *
 *************************************************************************/

BOOL CDib::SaveBitmap(CString filename)
{
	CFile file;
	BOOL ret;
	if ( file.Open(filename, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary) == NULL)
	{
		CString str;
		str = filename + "을 열 수 없습니다.";
		AfxMessageBox(str);
		return FALSE;
	}else {
		ret = SaveDIB(file);
		file.Close();
	}
	return ret;
}

BOOL CDib::SaveDIB(CFile& file)
{
	BITMAPFILEHEADER bmfHdr; // Header for Bitmap file
	LPBITMAPINFOHEADER lpBI;   // Pointer to DIB info structure
	DWORD dwDibHdrSize;

	if (!m_pDibHdr || !m_pBits)
		return FALSE;

	/*
	 * Get a pointer to the DIB memory, the first of which contains
	 * a BITMAPINFO structure
	 */
	lpBI = (LPBITMAPINFOHEADER) m_pDibHdr;

	if (!IS_WIN30_DIB(lpBI))
	{
		return FALSE;       // It's an other-style DIB (save not supported)
	}

	/*
	 * Fill in the fields of the file header
	 */

	/* Fill in file type (first 2 bytes must be "BM" for a bitmap) */
	bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call GlobalSize()
	// on our global handle, but since the size of our global memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.

	dwDibHdrSize = *(LPDWORD)lpBI + PaletteSize((LPSTR)lpBI);  // Partial Calculation

	// Now calculate the size of the image
	DWORD dwBmBitsSize;  // Size of Bitmap Bits only

	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwBmBitsSize = lpBI->biSizeImage;
	}
	else
	{
		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * lpBI->biHeight;

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBmBitsSize;
	}

	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)

	bmfHdr.bfSize = sizeof(BITMAPFILEHEADER) +dwDibHdrSize +dwBmBitsSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	/*
	 * Now, calculate the offset the actual bitmap bits will be in
	 * the file -- It's the Bitmap file header plus the DIB header,
	 * plus the size of the color table.
	 */
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize
											  + PaletteSize((LPSTR)lpBI);
	TRY
	{
		// Write the file header
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		
		// Write the DIB header
		file.Write(lpBI, dwDibHdrSize);
		
		//and the bits
		file.Write(m_pBits, dwBmBitsSize);
	}
	CATCH (CFileException, e)
	{
		THROW_LAST();
	}
	END_CATCH

	return TRUE;
}

void CDib::InitDIBData()
{
	if (m_pPal != NULL)
	{
		delete m_pPal;
		m_pPal = NULL;
	}
	if (!m_pDibHdr || !m_pBits)
	{
		return;
	}
	// Create copy of palette
	m_pPal = new CPalette;
	if (m_pPal == NULL)
	{
		// we must be really low on memory
		delete[] m_pDibHdr;
		m_pDibHdr = NULL;
		
		delete[] m_pBits;
		m_pBits = NULL;
		
		return;
	}
	if (CreateDIBPalette() == NULL)
	{
		// DIB may not have a palette
		delete m_pPal;
		m_pPal = NULL;
		return;
	}
}


/*************************************************************************

  Function:  ReadDIBFile (CFile&)

   Purpose:  Reads in the specified DIB file into a global chunk of
			 memory.

   Returns:  A handle to a dib (hDIB) if successful.
			 NULL if an error occurs.

  Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
			 from the end of the BITMAPFILEHEADER structure on is
			 returned in the global memory handle.

*************************************************************************/


BOOL CDib::ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER DibHdr;
	DWORD dwBitsSize;
	LPSTR pDIB;

	/*
	 * Go read the DIB file header and check if it's valid.
	 */
	if ((file.Read((LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER)) !=
		sizeof(BITMAPFILEHEADER)) || (bmfHeader.bfType != DIB_HEADER_MARKER))
	{
		return FALSE;
	}
	if ((file.Read((LPSTR)&DibHdr, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER)))
	{
		return FALSE;
	}
	/*
	 * Allocate memory for DIB
	 */
	if(!(dwBitsSize = ReNewDib(DibHdr.biWidth, DibHdr.biHeight, DibHdr.biBitCount)))
		return FALSE;
	memcpy(m_pDibHdr, &DibHdr,sizeof(BITMAPINFOHEADER));
	pDIB = m_pDibHdr + sizeof(BITMAPINFOHEADER);
	DWORD palsize = PaletteSize((LPSTR)m_pDibHdr);
	
	if (file.Read(pDIB, palsize) != palsize)
	{
		return FALSE;
	}
	/*
	 * Go read the bits.
	 */
	if (file.Read(m_pBits, dwBitsSize) != dwBitsSize)
	{
		return FALSE;
	}
	return TRUE;
}

/*************************************************************************
 *
 * PaintDIB()
 *
 * Parameters:
 *
 * HDC hDC          - DC to do output to
 *
 * LPRECT lpDCRect  - rectangle on DC to do output to
 *
 * HDIB hDIB        - handle to global memory with a DIB spec
 *                    in it followed by the DIB bits
 *
 * LPRECT lpDIBRect - rectangle of DIB to output into lpDCRect
 *
 * CPalette* pPal   - pointer to CPalette containing DIB's palette
 *
 * Return Value:
 *
 * BOOL             - TRUE if DIB was drawn, FALSE otherwise
 *
 * Description:
 *   Painting routine for a DIB.  Calls StretchDIBits() or
 *   SetDIBitsToDevice() to paint the DIB.  The DIB is
 *   output to the specified DC, at the coordinates given
 *   in lpDCRect.  The area of the DIB to be output is
 *   given by lpDIBRect.
 *
 ************************************************************************/


// 현재 화면의 temp영상을 화면에 출력하는 함수

BOOL CDib::PaintViewImg(CDC *pDC, CPoint Point)
{
	return PaintDIB(pDC, Point, 1);
}

// PaintDIB함수와 같음

BOOL CDib::PaintImage(int x, int y, CDC *pDC)
{
	return (PaintDIB(pDC, CPoint(x,y)));
}

BOOL CDib::PaintDIB(CDC *pDC, CPoint Point, int kind)
{
	CRect DCRect(Point, CSize((int)m_cxDIB, (int)m_cyDIB) );
	CRect DIBRect(CPoint(0,0),CSize((int)m_cxDIB, (int)m_cyDIB) );
	
	return PaintDIB(pDC, DCRect, DIBRect, m_pPal, kind);
}

BOOL CDib::PaintDIB(CDC *pDC,
					LPRECT  lpDCRect,
					LPRECT  lpDIBRect,
					CPalette* pPal, int kind)
{
	LPSTR    lpDIBHdr;            // Pointer to BITMAPINFOHEADER
	BYTE*    lpDIBBits;           // Pointer to DIB bits
	BOOL     bSuccess=FALSE;      // Success/fail flag
	///HPALETTE hPal=NULL;           // Our DIB's palette
	CPalette *poldPal=NULL;        // Previous palette

	/* Check for valid DIB handle */
	if (!m_pDibHdr || !m_pBits)
		return FALSE;

	/* Lock down the DIB, and get a pointer to the beginning of the bit
	 *  buffer
	 */
	lpDIBHdr = m_pDibHdr;
	
	// kind가 1이면 m_lpView를 화면에 출력한다.
	if (kind == 1)
		lpDIBBits = m_pViewBits;
	else
		lpDIBBits = m_pBits;

	// Get the DIB's palette, then select it into DC
	if (pPal != NULL)
	{
		// Select as background since we have
		// already realized in forground if needed
		poldPal = pDC->SelectPalette(pPal, TRUE);
		pDC->RealizePalette();
	} else {
		// Select as background since we have
		// already realized in forground if needed
		poldPal = pDC->SelectPalette(m_pPal, TRUE);
		pDC->RealizePalette();
	}

	/* Make sure to use the stretching mode best for color pictures */
	pDC->SetStretchBltMode(COLORONCOLOR);

	/* Determine whether to call StretchDIBits() or SetDIBitsToDevice() */
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) &&
	   (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
	   bSuccess = ::SetDIBitsToDevice(pDC->GetSafeHdc(),	   // hDC
								   lpDCRect->left,             // DestX
								   lpDCRect->top,              // DestY
								   RECTWIDTH(lpDCRect),        // nDestWidth
								   RECTHEIGHT(lpDCRect),       // nDestHeight
								   lpDIBRect->left,            // SrcX
								   (int)m_cyDIB -
									  lpDIBRect->top -
									  RECTHEIGHT(lpDIBRect),   // SrcY
								   0,                          // nStartScan
								   (WORD)m_cyDIB,  // nNumScans
								   lpDIBBits,                  // lpBits
								   (LPBITMAPINFO)lpDIBHdr,     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
   else
	   bSuccess = ::StretchDIBits(pDC->GetSafeHdc(),         // hDC
							   lpDCRect->left,                 // DestX
							   lpDCRect->top,                  // DestY
							   RECTWIDTH(lpDCRect),            // nDestWidth
							   RECTHEIGHT(lpDCRect),           // nDestHeight
							   lpDIBRect->left,                // SrcX
							   (int)m_cyDIB -
								  lpDIBRect->top -
								  RECTHEIGHT(lpDIBRect),	  // SrcY
//							   lpDIBRect->top,                 // SrcY
							   RECTWIDTH(lpDIBRect),           // wSrcWidth
							   RECTHEIGHT(lpDIBRect),          // wSrcHeight
							   lpDIBBits,                      // lpBits
							   (LPBITMAPINFO)lpDIBHdr,         // lpBitsInfo
							   DIB_RGB_COLORS,                 // wUsage
							   SRCCOPY);                       // dwROP

	/* Reselect old palette */
	if (poldPal != NULL)
	{
		pDC->SelectPalette(poldPal, TRUE);
		pDC->RealizePalette();
	}
	
   return bSuccess;
}

/*************************************************************************
 *
 * CreateDIBPalette()
 *
 * Parameter:
 *
 * HDIB hDIB        - specifies the DIB
 *
 * Return Value:
 *
 * HPALETTE         - specifies the palette
 *
 * Description:
 *
 * This function creates a palette from a DIB by allocating memory for the
 * logical palette, reading and storing the colors from the DIB's color table
 * into the logical palette, creating a palette from this logical palette,
 * and then returning the palette's handle. This allows the DIB to be
 * displayed using the best possible colors (important for DIBs with 256 or
 * more colors).
 *
 ************************************************************************/


BOOL CDib::CreateDIBPalette()
{
	LPLOGPALETTE lpPal;      // pointer to a logical palette
	WORD wNumColors;         // number of colors in color table
	LPSTR lpbi;              // pointer to packed-DIB
	LPBITMAPINFO lpbmi;      // pointer to BITMAPINFO structure (Win3.0)
	LPBITMAPCOREINFO lpbmc;  // pointer to BITMAPCOREINFO structure (old)
	BOOL bWinStyleDIB;       // flag which signifies whether this is a Win3.0 DIB
	BOOL bResult = FALSE;

	/* if handle to DIB is invalid, return FALSE */

	if (!m_pDibHdr || !m_pBits)
	  return FALSE;

   lpbi = m_pDibHdr;

   /* get pointer to BITMAPINFO (Win 3.0) */
   lpbmi = (LPBITMAPINFO)lpbi;

   /* get pointer to BITMAPCOREINFO (old 1.x) */
   lpbmc = (LPBITMAPCOREINFO)lpbi;

   /* get the number of colors in the DIB */
   wNumColors = DIBNumColors(lpbi);

   if (wNumColors != 0)
   {
		/* allocate memory block for logical palette */
		char *pch = new char[sizeof(LOGPALETTE)
									+ sizeof(PALETTEENTRY)
									* wNumColors];

		/* if not enough memory, clean up and return NULL */
		if (pch == 0)
		{
			return FALSE;
		}
		lpPal = (LPLOGPALETTE)pch;
		/* set version and number of palette entries */
		lpPal->palVersion = PALVERSION;
		lpPal->palNumEntries = (WORD)wNumColors;

		/* is this a Win 3.0 DIB? */
		bWinStyleDIB = IS_WIN30_DIB(lpbi);
		for (int i = 0; i < (int)wNumColors; i++)
		{
			if (bWinStyleDIB)
			{
				lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
				lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
				lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
				lpPal->palPalEntry[i].peFlags = 0;
			}
			else
			{
				lpPal->palPalEntry[i].peRed = lpbmc->bmciColors[i].rgbtRed;
				lpPal->palPalEntry[i].peGreen = lpbmc->bmciColors[i].rgbtGreen;
				lpPal->palPalEntry[i].peBlue = lpbmc->bmciColors[i].rgbtBlue;
				lpPal->palPalEntry[i].peFlags = 0;
			}
		}

		/* create the palette and get handle to it */
		bResult = m_pPal->CreatePalette(lpPal);
		delete[] pch;
	}

	return bResult;
}

/*************************************************************************
 *
 * DIBWidth()
 *
 * Parameter:
 *
 * LPSTR lpbi       - pointer to packed-DIB memory block
 *
 * Return Value:
 *
 * DWORD            - width of the DIB
 *
 * Description:
 *
 * This function gets the width of the DIB from the BITMAPINFOHEADER
 * width field if it is a Windows 3.0-style DIB or from the BITMAPCOREHEADER
 * width field if it is an other-style DIB.
 *
 ************************************************************************/


DWORD CDib::DIBWidth(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	/* point to the header (whether Win 3.0 and old) */

	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	/* return the DIB width if it is a Win 3.0 DIB */
	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biWidth;
	else  /* it is an other-style DIB, so return its width */
		return (DWORD)lpbmc->bcWidth;
}


/*************************************************************************
 *
 * DIBHeight()
 *
 * Parameter:
 *
 * LPSTR lpbi       - pointer to packed-DIB memory block
 *
 * Return Value:
 *
 * DWORD            - height of the DIB
 *
 * Description:
 *
 * This function gets the height of the DIB from the BITMAPINFOHEADER
 * height field if it is a Windows 3.0-style DIB or from the BITMAPCOREHEADER
 * height field if it is an other-style DIB.
 *
 ************************************************************************/


DWORD CDib::DIBHeight(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	/* point to the header (whether old or Win 3.0 */

	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	/* return the DIB height if it is a Win 3.0 DIB */
	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biHeight;
	else  /* it is an other-style DIB, so return its height */
		return (DWORD)lpbmc->bcHeight;
}

WORD CDib::DIBBitCount(LPSTR lpDIB)
{
	LPBITMAPINFOHEADER lpbmi;  // pointer to a Win 3.0-style DIB
	LPBITMAPCOREHEADER lpbmc;  // pointer to an other-style DIB

	/* point to the header (whether old or Win 3.0 */

	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	/* return the DIB height if it is a Win 3.0 DIB */
	if (IS_WIN30_DIB(lpDIB))
		return lpbmi->biBitCount;
	else  /* it is an other-style DIB, so return its height */
		return lpbmc->bcBitCount;
}


/*************************************************************************
 *
 * PaletteSize()
 *
 * Parameter:
 *
 * LPSTR lpbi       - pointer to packed-DIB memory block
 *
 * Return Value:
 *
 * WORD             - size of the color palette of the DIB
 *
 * Description:
 *
 * This function gets the size required to store the DIB's palette by
 * multiplying the number of colors by the size of an RGBQUAD (for a
 * Windows 3.0-style DIB) or by the size of an RGBTRIPLE (for an other-
 * style DIB).
 *
 ************************************************************************/


WORD CDib::PaletteSize(LPSTR lpbi)
{
   /* calculate the size required by the palette */
   if (IS_WIN30_DIB (lpbi))
	  return (WORD)(DIBNumColors(lpbi) * sizeof(RGBQUAD));
   else
	  return (WORD)(DIBNumColors(lpbi) * sizeof(RGBTRIPLE));
}


/*************************************************************************
 *
 * DIBNumColors()
 *
 * Parameter:
 *
 * LPSTR lpbi       - pointer to packed-DIB memory block
 *
 * Return Value:
 *
 * WORD             - number of colors in the color table
 *
 * Description:
 *
 * This function calculates the number of colors in the DIB's color table
 * by finding the bits per pixel for the DIB (whether Win3.0 or other-style
 * DIB). If bits per pixel is 1: colors=2, if 4: colors=16, if 8: colors=256,
 * if 24, no colors in color table.
 *
 ************************************************************************/


WORD CDib::DIBNumColors(LPSTR lpbi)
{
	WORD wBitCount;  // DIB bit count

	/*  If this is a Windows-style DIB, the number of colors in the
	 *  color table can be less than the number of bits per pixel
	 *  allows for (i.e. lpbi->biClrUsed can be set to some value).
	 *  If this is the case, return the appropriate value.
	 */

	if (IS_WIN30_DIB(lpbi))
	{
		DWORD dwClrUsed;

		dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;
		if (dwClrUsed != 0)
			return (WORD)dwClrUsed;
	}

	/*  Calculate the number of colors in the color table based on
	 *  the number of bits per pixel for the DIB.
	 */
	if (IS_WIN30_DIB(lpbi))
		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
	else
		wBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;

	/* return number of colors based on bits per pixel */
	switch (wBitCount)
	{
		case 1:
			return 2;

		case 4:
			return 16;

		case 8:
			return 256;

		default:
			return 0;
	}
}

// 화면출력을 위한 임시변수를 만드는 함수

int CDib::MakeViewImg()
{
	if((m_pViewBits= new BYTE[(long)BUFFERWIDTH(m_cxDIB)*m_cyDIB]))
		return TRUE;
	else
		return FALSE;
}

// 화면출력 버퍼를 배경화면으로 초기화 하는 함수

int CDib::CleanBack()
{
	long    size = (long)BUFFERWIDTH(m_cxDIB)*m_cyDIB;
	memcpy(m_pViewBits,m_pBits, size );
	
	return TRUE;
}

BYTE* CDib::UseBuffer()
{
	return m_pBits;
}

void CDib::EndUseBuffer()
{
}

// 배경에 원하는 그림을 넣는 함수 type = 0이면 투명하게 되고 0가 아니면 그냥 덮는다.
int CDib::PutSprite(CPoint pt, CDib *img,int type /* = 0*/)
{
	return PutSprite(pt.x, pt.y, img, type);
}

// 배경에 원하는 그림을 넣는 함수 type = 0이면 투명하게 되고 0가 아니면 그냥 덮는다.
int CDib::PutSprite(int px,int py, CDib *img, int type/* = 0*/)
{
	BYTE  *lpDIBBits;          
	lpDIBBits = (BYTE *)img->UseBuffer();

	int cxDest = BUFFERWIDTH(m_cxDIB);
	int cxSrc  = BUFFERWIDTH(img->GetWidth());
	int x, y;
	if (py + img->GetHeight() > GetHeight()) 
		py = GetHeight() - img->GetHeight();
	for( y = 0; y < (int)img->GetHeight() ; y++)
	{
        int cury = py + y;
        BYTE * dest = (BYTE *)m_pViewBits +  (long)(m_cyDIB - cury - 1) * cxDest + px;	
        BYTE * src  = lpDIBBits + (img->GetHeight() - y - 1) * cxSrc;
		for(x=0;x<(int)img->GetWidth();x++)
		{
			if(*src!=0xff || type )
				*dest = *src;
			dest++;
			src++;
		}
	}
        
	img->EndUseBuffer();
	return TRUE;
}

int CDib::PutSprite(CDib *img, CRect rcDest, CRect rcSrc, int type/* = 0*/)
{
	BYTE  *lpDIBBits;          
	lpDIBBits = (BYTE *)img->UseBuffer();

	int cxDest = BUFFERWIDTH(m_cxDIB);
	int cxSrc  = BUFFERWIDTH(img->GetWidth());
	int x, y;
	int px = rcDest.left;
	int py = rcDest.top;
//	if (py + img->GetHeight() > GetHeight()) 
//		py = GetHeight() - img->GetHeight();
	for(y=0;y<rcSrc.Height();y++)
	{
        int cury = py + y;
        BYTE * dest = (BYTE *)m_pViewBits +  (long)(m_cyDIB - cury - 1) * cxDest + px;	
        BYTE * src  = lpDIBBits + (img->GetHeight() - ( y + rcSrc.top ) - 1) * cxSrc;
		for(x=0;x<rcSrc.Width();x++)
		{
			if(*src!=0xff || type )
				*dest = *src;
			dest++;
			src++;
		}
	}
        
	img->EndUseBuffer();
	return TRUE;
}

CBitmap *CDib::GetBitmapHandle(HDC dc)
{
	LPSTR    lpbi;
	lpbi = (LPSTR) m_pDibHdr;
	HBITMAP hbm = CreateDIBitmap(dc, (BITMAPINFOHEADER FAR*) lpbi, CBM_INIT,
    	m_pViewBits, (BITMAPINFO FAR*)lpbi, DIB_RGB_COLORS);
    return ((CBitmap *)CBitmap::FromHandle(hbm));
}

// SpotLight
// 겹쳐진 두개의 영상을 마스크를 씌워가면서 보여줌으로 스포트 라이트와 같은
// 효과를 내도록 한다.
// 매개번수들
// x, y : 스포트라이트의 중심점을 나타낸다.
// img  : 스포트 라이트를 비추었을 때 나타나는 영상이다.
//        이 영상의 크기는 배경의 크기와 같아야 한다.
// mask : 스포트라이트의 모양을 가지고 있는 마스크이다. 
//        이 영상은 256색의 비트맵이며 실제로는 흰 색과 검정색 두 색만 사용한다.
//        mask의 가로크기는 4의 배수이여야 한다.

#define SPOTSIZE 256
void CDib::SpotLight(int x, int y, CDib *img, CDib *mask)
{
	BYTE  *lpDIBBits;
	BYTE  *lpMask;
	CRect rc;
	int half = SPOTSIZE/2;

	lpDIBBits = (BYTE *)img->UseBuffer();
	lpMask    = (BYTE *)mask->UseBuffer();
	int cxDest = BUFFERWIDTH(m_cxDIB);
	int cxSrc  = BUFFERWIDTH(img->GetWidth());
	
	int xgap  = max(0, half - x);
	int ygap  = max(0, half - y);
	rc.left   = max(0, x-half);
	rc.top    = max(0, y-half);
	rc.right  = min(640, x + half);
	rc.bottom = min(420, y + half);
	int i, j;
	for(i=rc.top;i<rc.bottom;i++)
	{
        int tpos = (i + ygap - rc.top)*SPOTSIZE + xgap;
        BYTE * dest = (BYTE *)m_pViewBits +  (m_cyDIB - i - 1) * cxDest + rc.left;	
        BYTE * src  = lpDIBBits + (img->GetHeight() - i - 1) * cxSrc + rc.left;
		for(j=0;j<rc.right-rc.left;j++)
		{
			if (!lpMask[tpos + j])
				*dest = *src;
			dest++;
			src++;
		}
	}
	img->EndUseBuffer();
	mask->EndUseBuffer();
}

// 영상 채워놓기에 필요한 부속 함수들
//#define ReadPixel( x, y) (m_lpView[(m_cyDIB - (y) - 1) * m_cxDIB + (x)]);
#define UP  -1
#define DOWN 1

BOOL CDib::Line(int x1, int y1, int x2, int y2, int color)
{

	if (!m_pDibHdr || !m_pBits)
		return FALSE;

	int cx = (m_cxDIB+3)/4*4;
	int cy = m_cyDIB;
	
	int sy = (cy - y1 - 1);
	int start = (sy * cx + x1);
	for (int i = 0 ; i < x2 - x1 + 1; i++)
	{
		m_pViewBits[start + i] = color;
	}
	return TRUE;
}

int CDib::LineAdjFill(int SeedX, int SeedY, int D, int PrevXL, int PrevXR, int color)
{
	
	int x,y;
	int xl, xr;
	int v;

	y  = SeedY;
	xl = SeedX;
	xr = SeedX;

	if (!m_pDibHdr || !m_pBits)
		return FALSE;

	ScanLeft( xl, y);
	ScanRight(xr, y);

	Line(xl, y, xr, y, color);

// find and fill adjacent line segmets in same direction
	
	for(x = xl; x <= xr ;x++)
	{
		v = (BYTE)ReadPixel(x, y+D);
//		if (( v != BorderValue) && (v != FillValue) )
		if ( v == 255)
			x = LineAdjFill(x, y+D, D, xl, xr, color);
	}

// find and fill adjacent line segments in opposite direction

	for (x = xl ; x < PrevXL; x++)
	{
		v = (BYTE)ReadPixel(x, y-D);
		if ( v == 255)
			x = LineAdjFill(x, y-D, -D, xl, xr, color);
	}
	
	for (x = PrevXR ; x < xr; x++)
	{
		v = (BYTE)ReadPixel(x, y-D);
		if ( v == 255)
			x = LineAdjFill(x, y-D, -D, xl, xr, color);
	}

	return (xr);
}

void CDib::ScanLeft(int &x, int &y)
{
	BYTE v;
	do
	{
		--x;						// move left one pixel
		v = (BYTE)ReadPixel( x, y);     // determine its value
	}
	while ( v == 255 );

	++x;                         // x-cordinate of leftmost pixel in row
}

void CDib::ScanRight( int &x, int &y)
{

	BYTE v;

	do
	{
		++x;						// move left one pixel
		v = (BYTE)ReadPixel( x, y);     // determine its value
	}
	while ( v == 255 );

	--x;                         // x-cordinate of leftmost pixel in row
}

BYTE CDib::ReadPixel(int x, int y)
{
	BYTE pv = m_pBits[(m_cyDIB - (y) - 1) * m_cxDIB + (x)];
	return pv;
}


BYTE* CDib::SetBits(BYTE *pBits)
{

	BYTE* ptempBits=m_pBits;
	m_pBits=pBits;

	return ptempBits;
}

LPSTR CDib::FindDIBBits()
{
	return (lpDib + *(LPDWORD)lpDib + PaletteSize(lpDib));
}
/*
HDIB CDib::GetHandle()
{
	return m_hDIB;
}
*/
