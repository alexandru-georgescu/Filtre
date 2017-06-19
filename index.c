#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include"bmp_header.h"

#define AGE 100

//BMP IMAGE STRUCT
typedef struct
{ 

   unsigned char b;
   unsigned char g;
   unsigned char r;

} pixel ;

typedef struct
{

  int b;
  int g;
  int r;

} pixel_int;

//CREATE IMAG TYPE UNSIGNED CHAR
pixel **create_IMG( int height ,int width )
{

  int i, j;
  pixel **IMG;

  IMG = malloc( height * sizeof( pixel * ));
  if( IMG == NULL )
  {
    return NULL;
  }
    
  for( i = 0; i < height; i++ )
  {
     IMG[i] = malloc( width * sizeof( pixel ));
     if( IMG[i] == NULL )
     {
       for( j = 0; j < i; j++ )
       {
          free( IMG[i] );
       }  
       free( IMG );
       return NULL;
     }
  }
  return IMG;

}

//CREATE IMAG TYPE INT
pixel_int **create_IMG_int( int height ,int width )
{

  int i, j;
  pixel_int **IMG;

  IMG = malloc( height * sizeof( pixel_int * ));
  if( IMG == NULL )
  {
    return NULL;
  }
    
  for( i = 0; i < height; i++ )
  {
     IMG[i] = malloc( width * sizeof( pixel_int ));
     if( IMG[i] == NULL )
     {
       for( j = 0; j < i; j++ )
       {
          free( IMG[i] );
       }  
       free( IMG );
       return NULL;
     }
  }
  return IMG;

}

//COPY IMG
void copy_IMG( pixel **IMG , pixel **COPY , int height , int width)
{

  int i , j;

  for(i = 0 ; i < height ; i++)
  {
     for(j = 0 ; j < width ; j++)
     {
        COPY[i][j].b = IMG[i][j].b;
        COPY[i][j].g = IMG[i][j].g;
        COPY[i][j].r = IMG[i][j].r;
     }
  }

}

//FREE IMAGE.
void free_IMG( pixel **img, int height )
{
 
  int i;
  for( i = 0 ; i < height ; i++ )
  {
     free( img[i] );
  }
  free(img);
 
}

//FREE IMAGE TYPE INT.
void free_IMG_int( pixel_int **img, int height )
{
 
  int i;
  for( i = 0 ; i < height ; i++ )
  {
     free( img[i] );
  }
  free(img);
 
}

//ADD IMAGE.
void add_IMG( bmp_fileheader file ,
              bmp_infoheader info , FILE* BMP , pixel **IMG )
{
 
  int i , j;

  //POZITION FOR FSEEK
  int DOG = ( info.biSizeImage - 3 * ( info.height * info.width )) /
              info.height;
  
  for( i = info.height - 1; i >= 0; i-- )
  {
     for( j = 0; j < info.width; j++ ) 
     {
        fread(&IMG[i][j], sizeof( pixel ), 1, BMP );
     }
     fseek( BMP , DOG , SEEK_CUR );
  }      

}

//CONVERT IMAGE IN BLACK AND WHITE
void black_w( pixel **IMG , int height , int width ) 
{

  int i , j ;
  pixel_int **black ;
  black = create_IMG_int( height , width );

  for( i = 0 ; i < height ; i++ )
  {
     for( j = 0 ; j < width ; j++)
     {
        black[i][j].b = ( IMG[i][j].b + IMG[i][j].g + IMG[i][j].r ) /3;
	black[i][j].g = ( IMG[i][j].b + IMG[i][j].g + IMG[i][j].r ) /3;
	black[i][j].r = ( IMG[i][j].b + IMG[i][j].g + IMG[i][j].r ) /3;
     }
  }
  
  for( i = 0 ; i < height ; i++ )
  {  
     for( j = 0 ; j < width ; j++)
     {
        IMG[i][j].b = black[i][j].b;
	IMG[i][j].g = black[i][j].g;
	IMG[i][j].r = black[i][j].r;
     }
  }
  free_IMG_int(black , height);

}

//CONVERT WITH FILTRE IMAGE
//ESTE O FUNCTIE FOARTE URATA, SUNT CONSTIEND CA O SA PRIMESC -1p.
void filtre( pixel **IMG , int height , int width , int filtre[3][3])
{
 
  int i , j , p  ;
  pixel_int **filtre_IMG ;
  pixel a[AGE] = {0} ; 
  filtre_IMG = create_IMG_int( height , width );


  for( i = 0 ; i < height ; i++ )
  {
     for( j = 0 ; j < width ; j++)
     {  

	for( p = 0 ; p < 9 ; p++)
	{
	   a[p].b = 0 ;
	   a[p].g = 0 ;
	   a[p].r = 0 ;
	}
  
        if( i < height && i >= 0 && j < width && j >= 0 )
	{ 
           a[0] = IMG[i][j] ;
	}

        if( i-1 < height && i-1 >= 0 && j < width && j >= 0 )
	{
	   a[1] = IMG[i-1][j];
	}

        if( i+1 < height && i+1 >= 0 && j < width && j >= 0 )
	{
	   a[2] = IMG[i+1][j];
 
	}

        if( i < height && i >= 0 && j-1 < width && j-1 >= 0 )
	{
	   a[3] = IMG[i][j-1];
 
	}

        if( i < height && i >= 0 && j+1 < width && j+1 >= 0 )
	{
	   a[4] = IMG[i][j+1];
 
	}

        if( i-1 < height && i-1 >= 0 && j-1 < width && j-1 >= 0 )
	{
	   a[5] = IMG[i-1][j-1];
 
	}

 	if( i+1 < height && i+1 >= 0 && j+1 < width && j+1 >= 0 )
	{
	   a[6] = IMG[i+1][j+1];
 
	}

	if( i+1 < height && i+1 >= 0 && j-1 < width && j-1 >= 0 )
	{
	   a[7] = IMG[i+1][j-1];
 
	}

	if( i-1 < height && i-1 >= 0 && j+1 < width && j+1 >= 0 )
	{
	   a[8] = IMG[i-1][j+1];
 
	}

	//B CONVERT
        filtre_IMG[i][j].b =( a[6].b * filtre[0][0]+
			      a[2].b * filtre[0][1]+
 			      a[7].b * filtre[0][2]+
			      a[4].b * filtre[1][0]+
			      a[0].b * filtre[1][1]+
			      a[3].b * filtre[1][2]+
			      a[8].b * filtre[2][0]+
			      a[1].b * filtre[2][1]+
			      a[5].b * filtre[2][2]
			    );

	//G CONVERT
        filtre_IMG[i][j].g =( a[6].g * filtre[0][0]+
			      a[2].g * filtre[0][1]+
 			      a[7].g * filtre[0][2]+
			      a[4].g * filtre[1][0]+
			      a[0].g * filtre[1][1]+
			      a[3].g * filtre[1][2]+
			      a[8].g * filtre[2][0]+
			      a[1].g * filtre[2][1]+
			      a[5].g * filtre[2][2]
			    );

	//R CONVERT
        filtre_IMG[i][j].r =( a[6].r * filtre[0][0]+
			      a[2].r * filtre[0][1]+
 			      a[7].r * filtre[0][2]+
			      a[4].r * filtre[1][0]+
			      a[0].r * filtre[1][1]+
			      a[3].r * filtre[1][2]+
			      a[8].r * filtre[2][0]+
			      a[1].r * filtre[2][1]+
			      a[5].r * filtre[2][2]
			    );

	if( filtre_IMG[i][j].b < 0 ) { filtre_IMG[i][j].b = 0;}   
        if( filtre_IMG[i][j].g < 0 ) { filtre_IMG[i][j].g = 0;}
        if( filtre_IMG[i][j].r < 0 ) { filtre_IMG[i][j].r = 0;}


        if( filtre_IMG[i][j].b > 255 ) { filtre_IMG[i][j].b = 255;}
        if( filtre_IMG[i][j].g > 255 ) { filtre_IMG[i][j].g = 255;}
        if( filtre_IMG[i][j].r > 255 ) { filtre_IMG[i][j].r = 255;}
   }

 }
 
 
 for( i = 0 ; i < height ; i++ )
 {
    for( j = 0 ; j < width ; j++)
    {
        IMG[i][j].b = filtre_IMG[i][j].b;
        IMG[i][j].g = filtre_IMG[i][j].g;
        IMG[i][j].r = filtre_IMG[i][j].r;
    }
 } 
 free_IMG_int(filtre_IMG , height);

}

//DECOMPRESS
void decompresse(pixel **IMG , FILE *BIN  )
{

  int j ;

//POZITION POINTS
  short i1 , j1 , i2 , j2;

//COLOR POINTS
  pixel color1;
  pixel color2;

//READ POZITION
  fread(&i1, sizeof(short int), 1, BIN);
  fread(&j1, sizeof(short int), 1, BIN);
  
//READ COLOR RGB MODE
  fread(&color1.r, sizeof(unsigned char), 1, BIN);
  fread(&color1.g, sizeof(unsigned char), 1, BIN);
  fread(&color1.b, sizeof(unsigned char), 1, BIN);

//HOW TO DECOMPRESS IMAGE WITH "NU AM LUAT PARTIALUL LA MATE"
NU_AM_LUAT_PARTIALUL_LA_MATE_1:

//READ A NEW POZITION
  fread(&i2, sizeof(short int), 1, BIN);
  fread(&j2, sizeof(short int), 1, BIN);

//READ COLOR FROM THIS POZITION
  fread(&color2.r, sizeof(unsigned char), 1, BIN);
  fread(&color2.g, sizeof(unsigned char), 1, BIN);
  fread(&color2.b, sizeof(unsigned char), 1, BIN);

//CONDTION FROM PAIND FROM J1 TO J2
  if( color1.r == color2.r &&
      color1.g == color2.g &&
      color1.b == color2.b && i1 == i2 )
  {

    for(j = j1; j <= j2; j++)
    {
       IMG[i1-1][j-1] = color1;			
    }

  }
  else
  {      
       IMG[i1 - 1][j1 - 1] = color1;
       IMG[i2 - 1][j2 - 1] = color2;
  }

//MOVE POZITION	
       i1 = i2;  j1 = j2;  color1 = color2;

//IF FILE IS NOT EMPTY GO TO "NU AM LUAT PARTIALUL"
//AND READ A NEW PIXEL
  if(feof(BIN) == 0) { goto NU_AM_LUAT_PARTIALUL_LA_MATE_1; }

}


//EXPORT IMAGE
void export_IMG( bmp_fileheader file , bmp_infoheader info ,
	         FILE* BMP , pixel **IMG )
{
 
   int i , j;
 
   //POZITION FOR FSEEK
   int DOG = ( info.biSizeImage - 3 * ( info.height * info.width )) /
               info.height;
 
   for( i = info.height - 1; i >= 0; i-- )
   {
      for( j = 0; j < info.width; j++ )
      {
         fwrite(&IMG[i][j], sizeof( pixel ), 1, BMP );
      }
      fseek( BMP , DOG , SEEK_CUR );
   }
 
}

int main()
{

//DECLARATION WITH HEADERS FILE
 bmp_fileheader file;
 bmp_infoheader info;

//MATRIX WITH PIXELS
 pixel **IMG; 
 pixel **black_i;
 pixel **IMG2;

 char fname[]= "input.txt" ;
 char bmp[AGE] ;
 char dcmp[AGE] ;
 int  comp ;
 int final_free;

/*
AM FOLOSIT UN VECTOR PENTRU INPUT DEOARECE DACA AS
111 MODIFICA NUMELE FISIERULUI DIN INPUT SA NU MODIFIC
112 15 PARAMETRII CI DOAR 1. 
*/

//FILTRES
 int F1[3][3] = { { -1,-1 , -1 } , { -1, 8 ,-1 } , {-1 ,-1 ,-1 } };
 int F2[3][3] = { { 0 , 1 ,  0 } , { 1 ,-4 , 1 } , { 0 , 1 , 0 } };
 int F3[3][3] = { { 1 , 0 , -1 } , { 0 , 0 , 0 } , {-1 , 0 , 1 } };

 pixel **fill_1;
 pixel **fill_2;
 pixel **fill_3;

//IMAGE NAME
 char BLACK_IMG[AGE];
 char FILTRE_1[AGE];
 char FILTRE_2[AGE];
 char FILTRE_3[AGE];
 char decompress[] = "decompressed.bmp";

// char compress[] = "compresesd.bin";

//OPEN INPUT
  FILE *INPUT = fopen( fname , "rt");  
  if(INPUT == NULL)
  {
    fprintf(stderr, "ERROR: Can't open file %s", fname);
    return 1;   
  }

//READ BMP FILE AND ..   
  fscanf( INPUT , "%s" , bmp );
  fscanf( INPUT , "%d" , &comp );
  fscanf( INPUT , "%s" , dcmp );

//CLOSE INPUT
  fclose( INPUT );

//OPEN FILE
  FILE *bmp_bin = fopen( bmp , "rb" );

//READ IMAGE
  fread(&file , sizeof( bmp_fileheader ) , 1 , bmp_bin );
  fread(&info , sizeof( bmp_infoheader ) , 1 , bmp_bin );
//sec fault 1

//GO TO IMAGE HEAD
  fseek(bmp_bin , file.imageDataOffset , SEEK_SET );

//CREATE IMAGE
  IMG = create_IMG( info.height , info.width ) ;
  if( IMG == NULL )
  {
    fprintf( stderr , "Image allocate error!" );
    return 1;
  }

//FOR THE LAST FREE
final_free = info.height ;

//CREATE IMAGE WITH HEADER INFORMATION
  add_IMG( file, info , bmp_bin , IMG );

//CLOSE IMAGE
  fclose( bmp_bin );

//CONVERT FOTO NAME
  strcpy(BLACK_IMG, bmp); 
  strcpy(FILTRE_1, bmp);
  strcpy(FILTRE_2, bmp);
  strcpy(FILTRE_3, bmp);
 
 //BLACK AND WITH IMAGE NAME
 BLACK_IMG[ strlen( BLACK_IMG ) -4 ] = '\0';
 strcat( BLACK_IMG , "_black_white.bmp" );

 //FILTRE 1 IMAGE NAME
 FILTRE_1[ strlen( FILTRE_1 ) -4 ] = '\0';
 strcat( FILTRE_1 , "_f1.bmp" );

 //FILTRE 2 IMAGE NAME
 FILTRE_2[ strlen( FILTRE_2 ) -4 ] = '\0';
 strcat( FILTRE_2 , "_f2.bmp" );

 //FILTRE 3 IMAGE NAME
 FILTRE_3[ strlen( FILTRE_3 ) -4 ] = '\0';
 strcat( FILTRE_3 , "_f3.bmp" );


//////////////////////////////////////////BLACK AND WITHE IMAGE.

//CONVERT TO BLACK AND WHITE.
  black_i = create_IMG( info.height , info.width );
  copy_IMG( IMG , black_i , info.height , info.width );
  black_w( black_i , info.height , info.width );
 
//READ IN FILE BLACK IMAGE IMAGE.
  FILE *NEW_IMG = fopen( BLACK_IMG , "wb" );
  if( NEW_IMG == NULL)
  {
    fprintf(stderr, "ERROR: Can't open file %s", BLACK_IMG);
    return 1;
  }

//READ IMAGE
  fwrite(&file , sizeof( bmp_fileheader ) , 1 , NEW_IMG );
  fwrite(&info , sizeof( bmp_infoheader ) , 1 , NEW_IMG ); 

//GO TO IMAGE HEAD.
  fseek(NEW_IMG , file.imageDataOffset , SEEK_SET );

//EXPORT.
  export_IMG( file , info , NEW_IMG , black_i );
  fclose(NEW_IMG);

///////////////////////////////////////////BLACK AND WITHE IMAGE.

////////////////////////////////////////////////////////FILTRE 1.
//CONVERT TO filtre 1.
///CREATE IMAGE FOR FILTRE AND CREATE ONE CLONE FOR IMG
  fill_1 = create_IMG( info.height , info.width );
  copy_IMG(black_i , fill_1 , info.height , info.width );

//APPLY FILTRE
  filtre( fill_1 , info.height , info.width , F1 );

//NEW IMAGE.
  FILE *FILL1_IMG = fopen( FILTRE_1 , "wb" );
  if( FILL1_IMG == NULL)
  {
    fprintf(stderr, "ERROR: Can't open file %s", FILTRE_1);
    return 1;
  }

//READ IMAGE
  fwrite(&file , sizeof( bmp_fileheader ) , 1 , FILL1_IMG );
  fwrite(&info , sizeof( bmp_infoheader ) , 1 , FILL1_IMG ); 

//GO TO IMAGE HEAD.
  fseek(FILL1_IMG , file.imageDataOffset , SEEK_SET );

//EXPORT.
  export_IMG( file , info , FILL1_IMG , fill_1 );
  fclose(FILL1_IMG);

  free_IMG(fill_1 , info.height ) ;

////////////////////////////////////////////////////////FILTRE 1.

////////////////////////////////////////////////////////FILTRE 2.
//CONVERT TO filtre 2.

///CREATE IMAGE FOR FILTRE AND CREATE ONE CLONE FOR IMG
  fill_2 = create_IMG( info.height , info.width );
  copy_IMG(black_i , fill_2 , info.height , info.width );

//APPLY FILTRE
  filtre( fill_2 , info.height , info.width , F2 );

//READ IN FILE BLACK IMAGE IMAGE.
  FILE *FILL2_IMG = fopen( FILTRE_2 , "wb" );
  if( FILL2_IMG == NULL)
  {
    fprintf(stderr, "ERROR: Can't open file %s", FILTRE_2);
    return 1;
  }

//READ IMAGE
  fwrite(&file , sizeof( bmp_fileheader ) , 1 , FILL2_IMG );
  fwrite(&info , sizeof( bmp_infoheader ) , 1 , FILL2_IMG ); 

//GO TO IMAGE HEAD.
  fseek(FILL2_IMG , file.imageDataOffset , SEEK_SET );

//EXPORT.
  export_IMG( file , info , FILL2_IMG , fill_2 );
  fclose(FILL2_IMG);

  free_IMG(fill_2 , info.height ) ;

////////////////////////////////////////////////////////FILTRE 2.


////////////////////////////////////////////////////////FILTRE 3.
//CONVERT TO filtre 3.

//CREATE IMAGE FOR FILTRE AND CREATE ONE CLONE FOR IMG
  fill_3 = create_IMG( info.height , info.width );
  copy_IMG(black_i , fill_3 , info.height , info.width );

//APPLY FILTRE
  filtre( fill_3 , info.height , info.width , F3 );

//NEW IMAGE.
  FILE *FILL3_IMG = fopen( FILTRE_3 , "wb" );
  if( FILL3_IMG == NULL)
  {
    fprintf(stderr, "ERROR: Can't open file %s", FILTRE_3);
    return 1;
  }

//READ IMAGE
  fwrite(&file , sizeof( bmp_fileheader ) , 1 , FILL3_IMG );
  fwrite(&info , sizeof( bmp_infoheader ) , 1 , FILL3_IMG ); 

//GO TO IMAGE HEAD.
  fseek(FILL3_IMG , file.imageDataOffset , SEEK_SET );

//EXPORT.
  export_IMG( file , info , FILL3_IMG , fill_3 );
  fclose(FILL3_IMG);

  free_IMG(fill_3 , info.height ) ;

//FREE
  free_IMG(black_i , info.height);

////////////////////////////////////////////////////////FILTRE 3.


//////////////////////////////////////////////////////DECOMPRESS.

  FILE *decompr = fopen(dcmp , "rb");
  if( decompr == NULL) 
  {
    fprintf(stderr, "ERROR: Can't open file %s", dcmp);
    return 1;
  }

//READ FILE HEADER AND INFO HEADER
  fread(&file , sizeof( bmp_fileheader ) , 1 , decompr );
  fread(&info , sizeof( bmp_infoheader ) , 1 , decompr );

//MOVE TO POZITION
  fseek( decompr ,  file.imageDataOffset , SEEK_SET );

//CREATE IMAGE
  IMG2 = create_IMG( info.height , info.width ) ; 

//DECOMORESS
  decompresse(IMG2 , decompr );

//CLOSE FILE
  fclose(decompr);

//OPEN OPEN FILE TO WRITE DECOMPRESSED IMAGE  
  FILE *decompr2 = fopen(decompress , "wb");

//WRITE HEADERS
  fwrite(&file , sizeof( bmp_fileheader ) , 1 , decompr2 );
  fwrite(&info , sizeof( bmp_infoheader ) , 1 , decompr2 );

//MOVE TO POZITION
  fseek( decompr2 ,  file.imageDataOffset , SEEK_SET );
  export_IMG ( file , info , decompr2 , IMG2 );

//CLOSE FILE
  fclose(decompr2);

//FREE IMAGE
  free_IMG(IMG2 , info.height );

//////////////////////////////////////////////////////DECOMPRESS.

//FREE IMAGE
  free_IMG( IMG , final_free );

return 0;

}

//0 MEMORY LASK :d

/*
HEAP SUMMARY:in use at exit: 0 bytes in 0 blocks
All heap blocks were freed -- no leaks are possible
*/
