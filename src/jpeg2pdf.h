
#ifndef _JPEG2PDF_H_
#define _JPEG2PDF_H_

/* Defined for Compiling on Windows. Might need to be changed for other compiler */
typedef unsigned char UINT8;
typedef unsigned long UINT32;
typedef int STATUS;

#define logMsg printf
#define ERROR 1
#define OK 0
/* */

#ifndef JPEG2PDF_DEBUG
#define JPEG2PDF_DEBUG  0
#endif /* JPEG2PDF_DEBUG */

#define MAX_PDF_PAGES           15256

#define PDF_DOT_PER_INCH        72
#define PDF_DEF_DENSITY         300

#define MAX_PDF_PREFORMAT_SIZE  256             /* Format Before each image, Usually less than 142 Bytes */
#define MAX_PDF_PSTFORMAT_SIZE  512             /* Format After  each image, Usually less than 400 Bytes */

struct jpeg2pdf_Node_struct
{
    struct jpeg2pdf_Node_struct *pNext;
    UINT8  *pJpeg;
    UINT32 JpegSize;
    UINT32 JpegW, JpegH;
    UINT32 PageObj;
    UINT8 preFormat[MAX_PDF_PREFORMAT_SIZE];
    UINT8 pstFormat[MAX_PDF_PSTFORMAT_SIZE];
};

struct jpeg2pdf_Margin
{
    float left;
    float top;
    float right;
    float bottom;
    float width;
    float height;
};

typedef struct jpeg2pdf_Node_struct JPEG2PDF_NODE, *PJPEG2PDF_NODE;
typedef struct jpeg2pdf_Margin JPEG2PDF_MARGIN, *PJPEG2PDF_MARGIN;

#define XREF_ENTRY_LEN          20              /* Each XREF entry is 20 Bytes */
#define OBJNUM_EXTRA            3               /* First Free Object; Kids Object; Catalog Object */
#define OBJNUM_PER_IMAGE        5

#define MAX_KIDS_STRLEN         10              /* Kids Str Looks Like: "X 0 R ", X = OBJNUM_EXTRA + OBJNUM_PER_IMAGE * (pageNum - 1) */

#define MAX_PDF_XREF            (MAX_PDF_PAGES * OBJNUM_PER_IMAGE + OBJNUM_EXTRA)
#define MAX_PDF_HEADER          64              /* PDF Header, Usually less than 40 Bytes */
#define MAX_PDF_TAILER          ( ( MAX_PDF_PAGES * (MAX_KIDS_STRLEN + (OBJNUM_PER_IMAGE * XREF_ENTRY_LEN)) ) + (OBJNUM_EXTRA * XREF_ENTRY_LEN) + 256 )

typedef struct
{
    /* Link List Stuff */
    PJPEG2PDF_NODE pFirstNode;
    PJPEG2PDF_NODE pLastNode;
    UINT32 nodeCount;
    /* PDF Stuff */
    UINT8 pdfHeader[MAX_PDF_HEADER];
    UINT8 pdfTailer[MAX_PDF_TAILER]; /* 28K Bytes */
    UINT8 pdfXREF[MAX_PDF_XREF][XREF_ENTRY_LEN + 1]; /* 27K Bytes */
    UINT32 pdfObj, currentOffSet, imgObj;
    float pageW, pageH;
    JPEG2PDF_MARGIN margin;
    float maxImgW, maxImgH;
} JPEG2PDF, *PJPEG2PDF;

typedef enum {PageOrientationAuto, Portrait, Landscape} PageOrientation; // specified by user
typedef enum {ScaleFit, ScaleFitWidth, ScaleFitHeight, ScaleReduce, ScaleReduceWidth, ScaleReduceHeight, ScaleNone} ScaleMethod; // specified by user
typedef enum {FitWidth, FitHeight, FitNone} Fit; // how we should actually fit the image
typedef enum {false=0, true} bool;

PJPEG2PDF       Jpeg2PDF_BeginDocument(float pdfW, float pdfH, JPEG2PDF_MARGIN margin); /* pdfW, pdfH: Page Size in Inch ( 1 inch=25.4 mm ) */
STATUS          Jpeg2PDF_AddJpeg(PJPEG2PDF pPDF, UINT32 imgW, UINT32 imgH, UINT32 fileSize, UINT8 *pJpeg, UINT8 isColor, PageOrientation pageOrientation, float dpiX, float dpiY, ScaleMethod scale, bool cropHeight, bool cropWidth);
UINT32          Jpeg2PDF_EndDocument(PJPEG2PDF pPDF, char *timestamp, char* title, char* author, char* keywords, char* subject, char *creator);
STATUS          Jpeg2PDF_GetFinalDocumentAndCleanup(PJPEG2PDF pPDF, UINT8 *outPDF, UINT32 *outPDFSize);

#endif /* _JPEG2PDF_H_ */
