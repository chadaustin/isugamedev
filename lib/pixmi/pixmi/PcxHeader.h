#ifndef PCX_FILE_HEADER
#define PCX_FILE_HEADER

namespace pixmi
{
   //  The PCX header format.
   struct PcxHeader                        // Offset   Description               
   {                                                                  
      unsigned char   Id;                     //  00h     Manufacturer ID            
      unsigned char   Version;               //  01h     Version                  
      unsigned char   Format;                  //  02h     Encoding Scheme            
      unsigned char   BitsPixelPlane;            //  03h     Bits/Pixel/Plane         
      unsigned short  Xmin;                  //  04h     X Start (upper left)      
      unsigned short  Ymin;                  //  06h     Y Start (top)            
      unsigned short  Xmax;                  //  08h     X End (lower right)         
      unsigned short  Ymax;                  //  0Ah     Y End (bottom)            
      unsigned short  Hdpi;                  //  0Ch     Horizontal Resolution      
      unsigned short  Vdpi;                  //  0Eh     Vertical Resolution         
      unsigned char   EgaPalette[48];            //  10h     16-Color EGA Palette      
      unsigned char   Reserved;               //  40h     Reserved               
      unsigned char   NumberOfPlanes;            //  41h     Number of Color Planes      
      unsigned short  charsLinePlane;            //  42h     unsigned chars/Line/Plane   
      unsigned short  PaletteInfo;            //  44h     Palette Interpretation      
      unsigned short  HScreenSize;            //  46h     Horizontal Screen Size      
      unsigned short  VScreenSize;            //  48h     Vertical Screen Size      
      unsigned char   Filler[54];               //  4Ah     Reserved               
   };

   //  PCX VGA palette.
   struct PcxVgaPalette
   {
      unsigned char   VgaPalette[768];         // 256 VGA Color Palette  
   };

} // namespace
#endif
