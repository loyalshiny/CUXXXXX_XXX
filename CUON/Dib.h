// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__6D2B383B_C6DF_11D0_A526_0000E8206533__INCLUDED_)
#define AFX_DIB_H__6D2B383B_C6DF_11D0_A526_0000E8206533__INCLUDED_

#if _MSC_VER >= 1000
//#pragma once
#endif // _MSC_VER >= 1000

/* Handle to a DIB */
DECLARE_HANDLE(HDIB);

/* DIB constants */
#define PALVERSION   0x300

/* DIB Macros*/

#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#define BUFFERWIDTH(width)  (((width) + 3 ) / 4  * 4)
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/* Function prototypes */

#define hjh_dDST	206
#define hjh_dSRC	205
#define hjh_dBACK	201
#define hjh_dGND	200
#define hjh_dOBJ	199

class CDib  
{
public:
	LPSTR lpDib;
	int m_nErrorNo;
	BOOL SaveBitmap(CString filename);
	void CommonDib();
	CDib();
	CDib(CString filename, int tmp = 0);
	CDib(int width, int height, WORD depth = 8);
	BOOL	Create(CString filename, int tmp = 0);
	BOOL	Create(int width, int height, WORD depth = 8);
	int ReNewDib(int width, int height, WORD depth);
	CDib&	operator=( CDib &Src );  // Right side is the argument.
	virtual   ~CDib();
	void	Free();

	void      SpotLight(int x, int y, CDib *img, CDib *mask);
	BOOL      PaintViewImg(CDC *pDC, CPoint);
	BOOL      PaintImage(int x, int y, CDC *pDC);
	BOOL      PaintDIB (CDC *pDC, CPoint, int kind = 0);
	BOOL      PaintDIB (CDC *pDC, LPRECT, LPRECT, CPalette*, int kind = 0);
	BOOL      CreateDIBPalette();
	DWORD     GetWidth() {return m_cxDIB;}
	DWORD     GetHeight() {return m_cyDIB;}
	WORD      GetBitCount() {return m_wBitCount;}
	DWORD     GetSizeImage() {return ((LPBITMAPINFOHEADER)m_pDibHdr)->biSizeImage;}
	CPalette  *GetPalette() {return m_pPal;}
	WORD      PaletteSize (LPSTR lpbi);
	WORD      DIBNumColors (LPSTR lpbi);
	
	BOOL      SaveDIB (CFile& file);
	BOOL      ReadDIBFile(CFile& file);
	int       MakeViewImg();
    int       CleanBack();
    BYTE*     UseBuffer();
    void      EndUseBuffer();
	int       PutSprite(int px,int py, CDib *img, int type = 0);    
	// 배경에 원하는 그림을 넣는 함수 type = 0이면 투명하게 되고 0가 아니면 그냥 덮는다.
	int       PutSprite(CPoint pt, CDib *img, int type = 0);
	int	      PutSprite(CDib *img, CRect rcDest, CRect rcSrc, int type = 0);
	CBitmap   *GetBitmapHandle(HDC dc);	
	
	// 그림 색칠하기
public:
	BYTE* GetBits(){return m_pBits;}
	BYTE* SetBits(BYTE* pBits);
	BYTE ReadPixel( int x, int y);
//	BYTE** m_lpImage;
	int CDib::LineAdjFill(int SeedX, int SeedY, int D, int PrevXL, int PrevXR, int color);
    LPSTR FindDIBBits();
//	HDIB GetHandle();

protected:
	BOOL FillImage(int x, int y);
	BOOL CDib::Line(int x1, int y1, int x2, int y2, int color);
	void CDib::ScanLeft(int &x, int &y);
	void CDib::ScanRight( int &x, int &y);
	void InitDIBData();

protected:
	///HDIB      m_hDIB;
	DWORD     m_cxDIB, m_cyDIB;
	WORD     m_wBitCount;
	CPalette  *m_pPal;
	DWORD     DIBWidth (LPSTR lpbi);
	DWORD     DIBHeight (LPSTR lpbi);
	WORD     DIBBitCount (LPSTR lpbi);
	///HANDLE    m_hView;
	BYTE    *m_pViewBits;
	char	*m_pDibHdr;
	BYTE	*m_pBits;
};
#endif // !defined(AFX_DIB_H__6D2B383B_C6DF_11D0_A526_0000E8206533__INCLUDED_)
