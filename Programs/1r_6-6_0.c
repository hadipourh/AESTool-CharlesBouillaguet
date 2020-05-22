#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "1r_6-6_0.h"

const unsigned char sbox[256] = {
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F   
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0  
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1   
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2   
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3   
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4   
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5   
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6   
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7   
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8   
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9   
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A   
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B   
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C   
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D   
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E   
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
	};

const unsigned char rsbox[256] = { 
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,  
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,  
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,  
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,  
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,  
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,  
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,  
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,  
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,  
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,  
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,  
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,  
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,  
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,  
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,  
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d 
	};

/*const unsigned char Rcon[255] = { 
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,    
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,    
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,    
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,    
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,    
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,    
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,    
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,    
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,    
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,    
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,    
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,    
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,    
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,    
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,    
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb
	};*/

#define S(x) sbox[x]
#define R(x) rsbox[x]

unsigned char TableMul2_8[256][256];

void MakeTableMul2_8(void)
{
	int a,b;
	unsigned char aa,bb,r,t;
	for (a = 0; a <256 ; a++)
	{
		for (b = a; b < 256 ; b++)
		{
			aa=a;
			bb=b;
			r=0;
			while (aa != 0)
			{
				if ((aa & 1) != 0) r=r^bb;
				t=bb & 0x80;
				bb=bb<<1;
				if (t != 0) bb=bb^0x1b;
				aa=aa>>1;
			}
			TableMul2_8[a][b]=TableMul2_8[b][a]=r;
		}
	}
}

#define Multiply(a,b) TableMul2_8[a][b]

/*unsigned char Inverse(unsigned char a)
{
	static unsigned char TableInverse[256]={0x00,0x01,0x8d,0xf6,0xcb,0x52,0x7b,0xd1,0xe8,0x4f,0x29,0xc0,0xb0,0xe1,0xe5,0xc7,0x74,0xb4,0xaa,0x4b,0x99,0x2b,0x60,0x5f,0x58,0x3f,0xfd,0xcc,0xff,0x40,0xee,0xb2,0x3a,0x6e,0x5a,0xf1,0x55,0x4d,0xa8,0xc9,0xc1,0x0a,0x98,0x15,0x30,0x44,0xa2,0xc2,0x2c,0x45,0x92,0x6c,0xf3,0x39,0x66,0x42,0xf2,0x35,0x20,0x6f,0x77,0xbb,0x59,0x19,0x1d,0xfe,0x37,0x67,0x2d,0x31,0xf5,0x69,0xa7,0x64,0xab,0x13,0x54,0x25,0xe9,0x09,0xed,0x5c,0x05,0xca,0x4c,0x24,0x87,0xbf,0x18,0x3e,0x22,0xf0,0x51,0xec,0x61,0x17,0x16,0x5e,0xaf,0xd3,0x49,0xa6,0x36,0x43,0xf4,0x47,0x91,0xdf,0x33,0x93,0x21,0x3b,0x79,0xb7,0x97,0x85,0x10,0xb5,0xba,0x3c,0xb6,0x70,0xd0,0x06,0xa1,0xfa,0x81,0x82,0x83,0x7e,0x7f,0x80,0x96,0x73,0xbe,0x56,0x9b,0x9e,0x95,0xd9,0xf7,0x02,0xb9,0xa4,0xde,0x6a,0x32,0x6d,0xd8,0x8a,0x84,0x72,0x2a,0x14,0x9f,0x88,0xf9,0xdc,0x89,0x9a,0xfb,0x7c,0x2e,0xc3,0x8f,0xb8,0x65,0x48,0x26,0xc8,0x12,0x4a,0xce,0xe7,0xd2,0x62,0x0c,0xe0,0x1f,0xef,0x11,0x75,0x78,0x71,0xa5,0x8e,0x76,0x3d,0xbd,0xbc,0x86,0x57,0x0b,0x28,0x2f,0xa3,0xda,0xd4,0xe4,0x0f,0xa9,0x27,0x53,0x04,0x1b,0xfc,0xac,0xe6,0x7a,0x07,0xae,0x63,0xc5,0xdb,0xe2,0xea,0x94,0x8b,0xc4,0xd5,0x9d,0xf8,0x90,0x6b,0xb1,0x0d,0xd6,0xeb,0xc6,0x0e,0xcf,0xad,0x08,0x4e,0xd7,0xe3,0x5d,0x50,0x1e,0xb3,0x5b,0x23,0x38,0x34,0x68,0x46,0x03,0x8c,0xdd,0x9c,0x7d,0xa0,0xcd,0x1a,0x41,0x1c};
	return TableInverse[a];
}
*//* Index variables 
 * x[0] = 1
 * x[1] = X_1[3,3]
 * x[2] = X_1[3,2]
 * x[3] = X_1[3,1]
 * x[4] = X_1[3,0]
 * x[5] = X_1[2,3]
 * x[6] = X_1[2,2]
 * x[7] = X_1[2,1]
 * x[8] = X_1[2,0]
 * x[9] = X_1[1,3]
 * x[10] = X_1[1,2]
 * x[11] = X_1[1,1]
 * x[12] = X_1[1,0]
 * x[13] = X_1[0,3]
 * x[14] = X_1[0,2]
 * x[15] = X_1[0,1]
 * x[16] = X_1[0,0]
 * x[17] = X_0[1,1]
 * x[18] = X_0[0,0]
 * x[19] = X_0[1,2]
 * x[20] = X_0[0,1]
 * x[21] = guess2
 * x[22] = guess1
 * x[23] = K_1[0,0]
 * x[24] = K_0[1,3]
 * x[25] = K_0[0,0]
 * x[26] = K_1[0,1]
 * x[27] = K_0[0,1]
 * x[28] = K_1[0,2]
 * x[29] = K_0[0,2]
 * x[30] = K_1[0,3]
 * x[31] = K_0[0,3]
 * x[32] = K_1[1,0]
 * x[33] = K_0[2,3]
 * x[34] = K_0[1,0]
 * x[35] = K_1[1,1]
 * x[36] = K_0[1,1]
 * x[37] = K_1[1,2]
 * x[38] = K_0[1,2]
 * x[39] = K_1[1,3]
 * x[40] = K_1[2,0]
 * x[41] = K_0[3,3]
 * x[42] = K_0[2,0]
 * x[43] = K_1[2,1]
 * x[44] = K_0[2,1]
 * x[45] = K_1[2,2]
 * x[46] = K_0[2,2]
 * x[47] = K_1[2,3]
 * x[48] = K_1[3,0]
 * x[49] = K_0[3,0]
 * x[50] = K_1[3,1]
 * x[51] = K_0[3,1]
 * x[52] = K_1[3,2]
 * x[53] = K_0[3,2]
 * x[54] = K_1[3,3]
 * x[55] = X_0[3,3]
 * x[56] = P[3,3]
 * x[57] = X_0[3,2]
 * x[58] = P[3,2]
 * x[59] = X_0[3,1]
 * x[60] = P[3,1]
 * x[61] = X_0[3,0]
 * x[62] = P[3,0]
 * x[63] = X_0[2,3]
 * x[64] = P[2,3]
 * x[65] = X_0[2,2]
 * x[66] = P[2,2]
 * x[67] = X_0[2,1]
 * x[68] = P[2,1]
 * x[69] = X_0[2,0]
 * x[70] = P[2,0]
 * x[71] = X_0[1,3]
 * x[72] = P[1,3]
 * x[73] = P[1,2]
 * x[74] = P[1,1]
 * x[75] = X_0[1,0]
 * x[76] = P[1,0]
 * x[77] = X_0[0,3]
 * x[78] = P[0,3]
 * x[79] = X_0[0,2]
 * x[80] = P[0,2]
 * x[81] = P[0,1]
 * x[82] = P[0,0]
 * x[83] = W_0[3,3]
 * x[84] = W_0[3,2]
 * x[85] = W_0[3,1]
 * x[86] = W_0[3,0]
 * x[87] = W_0[2,3]
 * x[88] = W_0[2,2]
 * x[89] = W_0[2,1]
 * x[90] = W_0[2,0]
 * x[91] = W_0[1,3]
 * x[92] = W_0[1,2]
 * x[93] = W_0[1,1]
 * x[94] = W_0[1,0]
 * x[95] = W_0[0,3]
 * x[96] = W_0[0,2]
 * x[97] = W_0[0,1]
 * x[98] = W_0[0,0]
 **/
void Attack(const unsigned char Known[33])
{
	const unsigned char x0=Known[0]; /* 1 */
	const unsigned char x1=Known[1]; /* X_1[3,3] */
	const unsigned char x2=Known[2]; /* X_1[3,2] */
	const unsigned char x3=Known[3]; /* X_1[3,1] */
	const unsigned char x4=Known[4]; /* X_1[3,0] */
	const unsigned char x5=Known[5]; /* X_1[2,3] */
	const unsigned char x6=Known[6]; /* X_1[2,2] */
	const unsigned char x7=Known[7]; /* X_1[2,1] */
	const unsigned char x8=Known[8]; /* X_1[2,0] */
	const unsigned char x9=Known[9]; /* X_1[1,3] */
	const unsigned char x10=Known[10]; /* X_1[1,2] */
	const unsigned char x11=Known[11]; /* X_1[1,1] */
	const unsigned char x12=Known[12]; /* X_1[1,0] */
	const unsigned char x13=Known[13]; /* X_1[0,3] */
	const unsigned char x14=Known[14]; /* X_1[0,2] */
	const unsigned char x15=Known[15]; /* X_1[0,1] */
	const unsigned char x16=Known[16]; /* X_1[0,0] */
	const unsigned char x56=Known[17]; /* P[3,3] */
	const unsigned char x58=Known[18]; /* P[3,2] */
	const unsigned char x60=Known[19]; /* P[3,1] */
	const unsigned char x62=Known[20]; /* P[3,0] */
	const unsigned char x64=Known[21]; /* P[2,3] */
	const unsigned char x66=Known[22]; /* P[2,2] */
	const unsigned char x68=Known[23]; /* P[2,1] */
	const unsigned char x70=Known[24]; /* P[2,0] */
	const unsigned char x72=Known[25]; /* P[1,3] */
	const unsigned char x73=Known[26]; /* P[1,2] */
	const unsigned char x74=Known[27]; /* P[1,1] */
	const unsigned char x76=Known[28]; /* P[1,0] */
	const unsigned char x78=Known[29]; /* P[0,3] */
	const unsigned char x80=Known[30]; /* P[0,2] */
	const unsigned char x81=Known[31]; /* P[0,1] */
	const unsigned char x82=Known[32]; /* P[0,0] */
	int i_0;
	for (i_0 = 0; i_0 < 0x100; i_0++)
	{
		const unsigned char x41=i_0;
		const unsigned char x55=x56 ^ x41;
		int i_1;
		for (i_1 = 0; i_1 < 0x100; i_1++)
		{
			const unsigned char x17=i_1;
			int i_2;
			for (i_2 = 0; i_2 < 0x100; i_2++)
			{
				const unsigned char x19=i_2;
				int i_3;
				for (i_3 = 0; i_3 < 0x100; i_3++)
				{
					const unsigned char x20=i_3;
					int i_4;
					for (i_4 = 0; i_4 < 0x100; i_4++)
					{
						const unsigned char x59=i_4;
						int i_5;
						for (i_5 = 0; i_5 < 0x100; i_5++)
						{
							const unsigned char x65=i_5;
							const unsigned char x69=Multiply(0x76,x81) ^ Multiply(0x5b,x74) ^ x70 ^ Multiply(0x9b,x60) ^ Multiply(0x9b,x59) ^ Multiply(0x76,x20) ^ Multiply(0x5b,x17) ^ Multiply(0x76,x16) ^ Multiply(0x76,x15) ^ Multiply(0x5b,x12) ^ Multiply(0x5b,x11) ^ x8 ^ Multiply(0x9b,x4) ^ Multiply(0x9b,x3) ^ Multiply(0x02,S(x65)) ^ Multiply(0x03,S(x55)) ^ S(x41) ^ S(x20) ^ Multiply(0xb7,S(x19)) ^ Multiply(0xb6,S(x17));
							const unsigned char x63=R(Multiply(0xc0,x81) ^ Multiply(0x76,x74) ^ Multiply(0x5b,x60) ^ Multiply(0x5b,x59) ^ Multiply(0xc0,x20) ^ Multiply(0x76,x17) ^ Multiply(0xc0,x16) ^ Multiply(0xc0,x15) ^ Multiply(0x76,x12) ^ Multiply(0x76,x11) ^ Multiply(0x5b,x4) ^ Multiply(0x5b,x3) ^ S(x65) ^ Multiply(0xec,S(x19)) ^ Multiply(0xec,S(x17)));
							const unsigned char x67=Multiply(0x9a,x81) ^ Multiply(0xec,x74) ^ x68 ^ Multiply(0xb7,x60) ^ Multiply(0xb7,x59) ^ Multiply(0x9a,x20) ^ Multiply(0xec,x17) ^ Multiply(0x9a,x16) ^ Multiply(0x9a,x15) ^ Multiply(0xec,x12) ^ Multiply(0xec,x11) ^ x8 ^ x7 ^ Multiply(0xb7,x4) ^ Multiply(0xb7,x3) ^ Multiply(0xc0,S(x19)) ^ Multiply(0xc0,S(x17));
							const unsigned char x71=R(Multiply(0x36,x81) ^ Multiply(0x80,x74) ^ Multiply(0xf6,x73) ^ Multiply(0xf6,x66) ^ Multiply(0xf6,x65) ^ Multiply(0xad,x60) ^ Multiply(0xad,x59) ^ Multiply(0x36,x20) ^ Multiply(0xf6,x19) ^ Multiply(0x80,x17) ^ Multiply(0x36,x16) ^ Multiply(0x36,x15) ^ Multiply(0x80,x12) ^ Multiply(0x76,x11) ^ Multiply(0xf6,x10) ^ Multiply(0xf6,x7) ^ Multiply(0xf6,x6) ^ Multiply(0xad,x4) ^ Multiply(0xad,x3) ^ Multiply(0xf6,S(x69)) ^ Multiply(0xf6,S(x63)) ^ Multiply(0xf7,S(x59)) ^ Multiply(0xf7,S(x55)) ^ Multiply(0xed,S(x19)) ^ Multiply(0xec,S(x17)));
							const unsigned char x57=Multiply(0xaf,x81) ^ Multiply(0x6d,x74) ^ Multiply(0xf7,x73) ^ Multiply(0xf4,x66) ^ Multiply(0xf4,x65) ^ Multiply(0x18,x60) ^ Multiply(0x18,x59) ^ x58 ^ Multiply(0xaf,x20) ^ Multiply(0xf7,x19) ^ Multiply(0x6d,x17) ^ Multiply(0xaf,x16) ^ Multiply(0xaf,x15) ^ Multiply(0x6d,x12) ^ Multiply(0x9a,x11) ^ Multiply(0xf7,x10) ^ Multiply(0xf4,x7) ^ Multiply(0xf4,x6) ^ Multiply(0x18,x4) ^ Multiply(0x19,x3) ^ x2 ^ Multiply(0xf0,S(x69)) ^ Multiply(0xf0,S(x63)) ^ Multiply(0xf2,S(x59)) ^ Multiply(0xf2,S(x55)) ^ Multiply(0x28,S(x19)) ^ Multiply(0x28,S(x17));
							if ((Multiply(0x8c,x57) ^ Multiply(0x8b,S(x57)))==(Multiply(0x75,x81) ^ Multiply(0xd6,x74) ^ x73 ^ x72 ^ x71 ^ Multiply(0x8e,x66) ^ Multiply(0x8e,x65) ^ Multiply(0x8e,x64) ^ Multiply(0x8e,x63) ^ Multiply(0x14,x60) ^ Multiply(0x14,x59) ^ Multiply(0x8c,x58) ^ Multiply(0x8c,x41) ^ Multiply(0x75,x20) ^ x19 ^ Multiply(0xd6,x17) ^ Multiply(0x75,x16) ^ Multiply(0x75,x15) ^ Multiply(0xd6,x12) ^ Multiply(0xd7,x11) ^ x9 ^ Multiply(0x8e,x7) ^ Multiply(0x8e,x5) ^ Multiply(0x14,x4) ^ Multiply(0x98,x3) ^ Multiply(0x8c,x1) ^ Multiply(0x88,S(x67)) ^ Multiply(0x88,S(x63)) ^ Multiply(0x8b,S(x55)) ^ Multiply(0x3c,S(x19)) ^ Multiply(0x3c,S(x17))))
							{
								const unsigned char x33=x64 ^ x63;
								const unsigned char x75=Multiply(0x2d,x81) ^ x76 ^ Multiply(0xc1,x74) ^ Multiply(0x76,x60) ^ Multiply(0x76,x59) ^ Multiply(0x2d,x20) ^ Multiply(0xc1,x17) ^ Multiply(0x2d,x16) ^ Multiply(0x2d,x15) ^ Multiply(0xc0,x12) ^ Multiply(0xc1,x11) ^ Multiply(0x76,x4) ^ Multiply(0x76,x3) ^ Multiply(0x03,S(x63)) ^ S(x55) ^ S(x33) ^ S(x20) ^ Multiply(0x98,S(x19)) ^ Multiply(0x9a,S(x17));
								if ((S(x75))==(Multiply(0xec,x81) ^ Multiply(0x3b,x74) ^ Multiply(0x8c,x66) ^ Multiply(0x8c,x65) ^ Multiply(0xa1,x60) ^ Multiply(0xa1,x59) ^ Multiply(0x8d,x58) ^ Multiply(0x8d,x57) ^ Multiply(0x8d,x41) ^ Multiply(0x8c,x33) ^ Multiply(0xec,x20) ^ Multiply(0x3b,x17) ^ Multiply(0xec,x16) ^ Multiply(0xec,x15) ^ Multiply(0x3b,x12) ^ Multiply(0x3b,x11) ^ Multiply(0x8c,x7) ^ Multiply(0x8c,x5) ^ Multiply(0xa1,x4) ^ Multiply(0x2c,x3) ^ Multiply(0x8d,x1) ^ Multiply(0x8e,S(x67)) ^ Multiply(0x8e,S(x63)) ^ Multiply(0x8e,S(x57)) ^ Multiply(0x8e,S(x55)) ^ Multiply(0xf9,S(x19)) ^ Multiply(0xf8,S(x17))))
								{
									const unsigned char x61=R(Multiply(0x2d,x81) ^ Multiply(0xc0,x74) ^ Multiply(0x76,x60) ^ Multiply(0x76,x59) ^ Multiply(0x2d,x20) ^ Multiply(0xc0,x17) ^ Multiply(0x2d,x16) ^ Multiply(0x2d,x15) ^ Multiply(0xc0,x12) ^ Multiply(0xc0,x11) ^ Multiply(0x76,x4) ^ Multiply(0x76,x3) ^ S(x55) ^ Multiply(0x9a,S(x19)) ^ Multiply(0x9a,S(x17)));
									const unsigned char x31=R(Multiply(0x5a,x81) ^ Multiply(0x9b,x74) ^ x62 ^ x61 ^ Multiply(0xed,x60) ^ Multiply(0xed,x59) ^ Multiply(0x5a,x20) ^ Multiply(0x9b,x17) ^ Multiply(0x5a,x16) ^ Multiply(0x5a,x15) ^ Multiply(0x9b,x12) ^ Multiply(0x9b,x11) ^ Multiply(0xec,x4) ^ Multiply(0xed,x3) ^ S(x63) ^ Multiply(0x02,S(x55)) ^ Multiply(0x03,S(x20)) ^ Multiply(0x2e,S(x19)) ^ Multiply(0x2f,S(x17)));
									if ((Multiply(0xd9,x31) ^ S(x31))==(Multiply(0xd9,x81) ^ Multiply(0xfd,x74) ^ Multiply(0x9b,x73) ^ Multiply(0x76,x66) ^ Multiply(0x76,x65) ^ x62 ^ x61 ^ Multiply(0xc4,x60) ^ Multiply(0xc4,x59) ^ Multiply(0x5b,x58) ^ Multiply(0x5b,x57) ^ Multiply(0xe1,x41) ^ Multiply(0x91,x33) ^ Multiply(0xd9,x20) ^ Multiply(0x9b,x19) ^ Multiply(0xfd,x17) ^ Multiply(0xd9,x16) ^ Multiply(0xd9,x15) ^ Multiply(0xd9,x14) ^ Multiply(0xd9,x13) ^ Multiply(0xfd,x12) ^ Multiply(0x66,x11) ^ Multiply(0x9b,x10) ^ Multiply(0x76,x7) ^ Multiply(0xe7,x6) ^ Multiply(0x91,x5) ^ Multiply(0xc5,x4) ^ Multiply(0x9f,x3) ^ Multiply(0xba,x2) ^ Multiply(0xe1,x1) ^ S(x67) ^ Multiply(0x1f,S(x59)) ^ Multiply(0xa8,S(x57)) ^ Multiply(0xb5,S(x55)) ^ Multiply(0x03,S(x20)) ^ Multiply(0x55,S(x19)) ^ Multiply(0x54,S(x17))))
									{
										const unsigned char x77=x78 ^ x31;
										if ((S(x77))==(Multiply(0xd4,x81) ^ Multiply(0x35,x74) ^ Multiply(0x5b,x73) ^ Multiply(0xc0,x66) ^ Multiply(0xc0,x65) ^ Multiply(0x8b,x60) ^ Multiply(0x8b,x59) ^ Multiply(0x76,x58) ^ Multiply(0x76,x57) ^ Multiply(0x91,x41) ^ Multiply(0xd9,x33) ^ Multiply(0x38,x31) ^ Multiply(0xd4,x20) ^ Multiply(0x5b,x19) ^ Multiply(0x35,x17) ^ Multiply(0xd4,x16) ^ Multiply(0xd4,x15) ^ Multiply(0x38,x14) ^ Multiply(0x38,x13) ^ Multiply(0x35,x12) ^ Multiply(0x6e,x11) ^ Multiply(0x5b,x10) ^ Multiply(0xc0,x7) ^ Multiply(0x19,x6) ^ Multiply(0xd9,x5) ^ Multiply(0x8b,x4) ^ Multiply(0xfd,x3) ^ Multiply(0xe7,x2) ^ Multiply(0x91,x1) ^ Multiply(0x9d,S(x59)) ^ Multiply(0x71,S(x57)) ^ Multiply(0xec,S(x55)) ^ S(x20) ^ Multiply(0x86,S(x19)) ^ Multiply(0x86,S(x17))))
										{
											const unsigned char x79=Multiply(0xc4,x81) ^ x80 ^ Multiply(0x31,x74) ^ Multiply(0xb7,x73) ^ Multiply(0x9a,x66) ^ Multiply(0x9a,x65) ^ Multiply(0x97,x60) ^ Multiply(0x97,x59) ^ Multiply(0xec,x58) ^ Multiply(0xec,x57) ^ Multiply(0xc4,x20) ^ Multiply(0xb7,x19) ^ Multiply(0x31,x17) ^ Multiply(0xc4,x16) ^ Multiply(0xc5,x15) ^ x14 ^ Multiply(0x31,x12) ^ Multiply(0x86,x11) ^ Multiply(0xb7,x10) ^ Multiply(0x9a,x7) ^ Multiply(0x9a,x6) ^ Multiply(0x97,x4) ^ Multiply(0x7b,x3) ^ Multiply(0xec,x2) ^ Multiply(0xc0,S(x59)) ^ Multiply(0xc0,S(x55)) ^ Multiply(0xa2,S(x19)) ^ Multiply(0xa2,S(x17));
											if ((S(x79))==(Multiply(0xd4,x81) ^ Multiply(0x35,x74) ^ Multiply(0x5b,x73) ^ Multiply(0xc0,x66) ^ Multiply(0xc0,x65) ^ Multiply(0x8b,x60) ^ Multiply(0x8b,x59) ^ Multiply(0x76,x58) ^ Multiply(0x76,x57) ^ Multiply(0xd4,x20) ^ Multiply(0x5b,x19) ^ Multiply(0x35,x17) ^ Multiply(0xd4,x16) ^ Multiply(0xd4,x15) ^ Multiply(0x35,x12) ^ Multiply(0x6e,x11) ^ Multiply(0x5b,x10) ^ Multiply(0xc0,x7) ^ Multiply(0xc0,x6) ^ Multiply(0x8b,x4) ^ Multiply(0xfd,x3) ^ Multiply(0x76,x2) ^ Multiply(0xec,S(x59)) ^ Multiply(0xec,S(x55)) ^ S(x20) ^ Multiply(0x86,S(x19)) ^ Multiply(0x86,S(x17))))
											{
												const unsigned char x24=Multiply(0x39,x41) ^ Multiply(0xa8,x33) ^ Multiply(0x71,x31) ^ Multiply(0x71,x14) ^ Multiply(0x71,x13) ^ x10 ^ x9 ^ Multiply(0xa8,x6) ^ Multiply(0xa8,x5) ^ Multiply(0x39,x2) ^ Multiply(0x39,x1) ^ Multiply(0xe1,S(x59)) ^ Multiply(0xe1,S(x57));
												const unsigned char x18=R(Multiply(0x76,x81) ^ Multiply(0x5b,x74) ^ Multiply(0x9b,x60) ^ Multiply(0x9b,x59) ^ Multiply(0x76,x20) ^ Multiply(0x5b,x17) ^ Multiply(0x76,x16) ^ Multiply(0x76,x15) ^ Multiply(0x5b,x12) ^ Multiply(0x5b,x11) ^ Multiply(0x9b,x4) ^ Multiply(0x9b,x3) ^ S(x20) ^ Multiply(0xb7,S(x19)) ^ Multiply(0xb7,S(x17)));
												if ((x18 ^ S(x18))==(x82 ^ x62 ^ x61 ^ x16 ^ x4 ^ x0 ^ Multiply(0x03,S(x55)) ^ S(x31) ^ S(x24) ^ Multiply(0x02,S(x17))))
												{
													const unsigned char x21=x20 ^ x17 ^ Multiply(0x03,S(x20)) ^ S(x19) ^ Multiply(0xf4,S(x18)) ^ Multiply(0xf4,S(x17));
													const unsigned char x22=x18 ^ Multiply(0xf4,S(x18)) ^ Multiply(0xf4,S(x17));
													const unsigned char x23=x82 ^ x18 ^ x0 ^ S(x24);
													const unsigned char x25=x23 ^ x0 ^ S(x24);
													const unsigned char x26=x81 ^ x23 ^ x20;
													const unsigned char x27=x26 ^ x23;
													const unsigned char x28=x80 ^ x79 ^ x26;
													const unsigned char x29=x28 ^ x26;
													const unsigned char x30=x31 ^ x28;
													const unsigned char x32=x76 ^ x75 ^ S(x33);
													const unsigned char x34=x32 ^ S(x33);
													const unsigned char x35=x74 ^ x32 ^ x17;
													const unsigned char x36=x35 ^ x32;
													const unsigned char x37=x73 ^ x35 ^ x19;
													const unsigned char x38=x37 ^ x35;
													const unsigned char x39=x37 ^ x24;
													const unsigned char x40=x70 ^ x69 ^ S(x41);
													const unsigned char x42=x40 ^ S(x41);
													const unsigned char x43=x68 ^ x67 ^ x40;
													const unsigned char x44=x43 ^ x40;
													const unsigned char x45=x66 ^ x65 ^ x43;
													const unsigned char x46=x45 ^ x43;
													const unsigned char x47=x45 ^ x33;
													const unsigned char x48=x62 ^ x61 ^ S(x31);
													const unsigned char x49=x48 ^ S(x31);
													const unsigned char x50=x60 ^ x59 ^ x48;
													const unsigned char x51=x50 ^ x48;
													const unsigned char x52=x58 ^ x57 ^ x50;
													const unsigned char x53=x52 ^ x50;
													const unsigned char x54=x52 ^ x41;
													const unsigned char x83=Multiply(0x03,S(x77)) ^ S(x75) ^ S(x67) ^ Multiply(0x02,S(x57));
													const unsigned char x84=Multiply(0x03,S(x79)) ^ S(x71) ^ S(x69) ^ Multiply(0x02,S(x59));
													const unsigned char x85=S(x63) ^ Multiply(0x02,S(x61)) ^ Multiply(0x03,S(x20)) ^ S(x19);
													const unsigned char x86=S(x65) ^ Multiply(0x02,S(x55)) ^ Multiply(0x03,S(x18)) ^ S(x17);
													const unsigned char x87=S(x77) ^ S(x75) ^ Multiply(0x02,S(x67)) ^ Multiply(0x03,S(x57));
													const unsigned char x88=S(x79) ^ S(x71) ^ Multiply(0x02,S(x69)) ^ Multiply(0x03,S(x59));
													const unsigned char x89=Multiply(0x02,S(x63)) ^ Multiply(0x03,S(x61)) ^ S(x20) ^ S(x19);
													const unsigned char x90=Multiply(0x02,S(x65)) ^ Multiply(0x03,S(x55)) ^ S(x18) ^ S(x17);
													const unsigned char x91=S(x77) ^ Multiply(0x02,S(x75)) ^ Multiply(0x03,S(x67)) ^ S(x57);
													const unsigned char x92=S(x79) ^ Multiply(0x02,S(x71)) ^ Multiply(0x03,S(x69)) ^ S(x59);
													const unsigned char x93=Multiply(0x03,S(x63)) ^ S(x61) ^ S(x20) ^ Multiply(0x02,S(x19));
													const unsigned char x94=Multiply(0x03,S(x65)) ^ S(x55) ^ S(x18) ^ Multiply(0x02,S(x17));
													const unsigned char x95=Multiply(0x02,S(x77)) ^ Multiply(0x03,S(x75)) ^ S(x67) ^ S(x57);
													const unsigned char x96=Multiply(0x02,S(x79)) ^ Multiply(0x03,S(x71)) ^ S(x69) ^ S(x59);
													const unsigned char x97=S(x63) ^ S(x61) ^ Multiply(0x02,S(x20)) ^ Multiply(0x03,S(x19));
													const unsigned char x98=S(x65) ^ S(x55) ^ Multiply(0x02,S(x18)) ^ Multiply(0x03,S(x17));
													printf("# Solution found :\n");
													printf("X_1[3,3] = %02x\n",x1);
													printf("X_1[3,2] = %02x\n",x2);
													printf("X_1[3,1] = %02x\n",x3);
													printf("X_1[3,0] = %02x\n",x4);
													printf("X_1[2,3] = %02x\n",x5);
													printf("X_1[2,2] = %02x\n",x6);
													printf("X_1[2,1] = %02x\n",x7);
													printf("X_1[2,0] = %02x\n",x8);
													printf("X_1[1,3] = %02x\n",x9);
													printf("X_1[1,2] = %02x\n",x10);
													printf("X_1[1,1] = %02x\n",x11);
													printf("X_1[1,0] = %02x\n",x12);
													printf("X_1[0,3] = %02x\n",x13);
													printf("X_1[0,2] = %02x\n",x14);
													printf("X_1[0,1] = %02x\n",x15);
													printf("X_1[0,0] = %02x\n",x16);
													printf("X_0[1,1] = %02x\n",x17);
													printf("X_0[0,0] = %02x\n",x18);
													printf("X_0[1,2] = %02x\n",x19);
													printf("X_0[0,1] = %02x\n",x20);
													printf("guess2 = %02x\n",x21);
													printf("guess1 = %02x\n",x22);
													printf("K_1[0,0] = %02x\n",x23);
													printf("K_0[1,3] = %02x\n",x24);
													printf("K_0[0,0] = %02x\n",x25);
													printf("K_1[0,1] = %02x\n",x26);
													printf("K_0[0,1] = %02x\n",x27);
													printf("K_1[0,2] = %02x\n",x28);
													printf("K_0[0,2] = %02x\n",x29);
													printf("K_1[0,3] = %02x\n",x30);
													printf("K_0[0,3] = %02x\n",x31);
													printf("K_1[1,0] = %02x\n",x32);
													printf("K_0[2,3] = %02x\n",x33);
													printf("K_0[1,0] = %02x\n",x34);
													printf("K_1[1,1] = %02x\n",x35);
													printf("K_0[1,1] = %02x\n",x36);
													printf("K_1[1,2] = %02x\n",x37);
													printf("K_0[1,2] = %02x\n",x38);
													printf("K_1[1,3] = %02x\n",x39);
													printf("K_1[2,0] = %02x\n",x40);
													printf("K_0[3,3] = %02x\n",x41);
													printf("K_0[2,0] = %02x\n",x42);
													printf("K_1[2,1] = %02x\n",x43);
													printf("K_0[2,1] = %02x\n",x44);
													printf("K_1[2,2] = %02x\n",x45);
													printf("K_0[2,2] = %02x\n",x46);
													printf("K_1[2,3] = %02x\n",x47);
													printf("K_1[3,0] = %02x\n",x48);
													printf("K_0[3,0] = %02x\n",x49);
													printf("K_1[3,1] = %02x\n",x50);
													printf("K_0[3,1] = %02x\n",x51);
													printf("K_1[3,2] = %02x\n",x52);
													printf("K_0[3,2] = %02x\n",x53);
													printf("K_1[3,3] = %02x\n",x54);
													printf("X_0[3,3] = %02x\n",x55);
													printf("P[3,3] = %02x\n",x56);
													printf("X_0[3,2] = %02x\n",x57);
													printf("P[3,2] = %02x\n",x58);
													printf("X_0[3,1] = %02x\n",x59);
													printf("P[3,1] = %02x\n",x60);
													printf("X_0[3,0] = %02x\n",x61);
													printf("P[3,0] = %02x\n",x62);
													printf("X_0[2,3] = %02x\n",x63);
													printf("P[2,3] = %02x\n",x64);
													printf("X_0[2,2] = %02x\n",x65);
													printf("P[2,2] = %02x\n",x66);
													printf("X_0[2,1] = %02x\n",x67);
													printf("P[2,1] = %02x\n",x68);
													printf("X_0[2,0] = %02x\n",x69);
													printf("P[2,0] = %02x\n",x70);
													printf("X_0[1,3] = %02x\n",x71);
													printf("P[1,3] = %02x\n",x72);
													printf("P[1,2] = %02x\n",x73);
													printf("P[1,1] = %02x\n",x74);
													printf("X_0[1,0] = %02x\n",x75);
													printf("P[1,0] = %02x\n",x76);
													printf("X_0[0,3] = %02x\n",x77);
													printf("P[0,3] = %02x\n",x78);
													printf("X_0[0,2] = %02x\n",x79);
													printf("P[0,2] = %02x\n",x80);
													printf("P[0,1] = %02x\n",x81);
													printf("P[0,0] = %02x\n",x82);
													printf("W_0[3,3] = %02x\n",x83);
													printf("W_0[3,2] = %02x\n",x84);
													printf("W_0[3,1] = %02x\n",x85);
													printf("W_0[3,0] = %02x\n",x86);
													printf("W_0[2,3] = %02x\n",x87);
													printf("W_0[2,2] = %02x\n",x88);
													printf("W_0[2,1] = %02x\n",x89);
													printf("W_0[2,0] = %02x\n",x90);
													printf("W_0[1,3] = %02x\n",x91);
													printf("W_0[1,2] = %02x\n",x92);
													printf("W_0[1,1] = %02x\n",x93);
													printf("W_0[1,0] = %02x\n",x94);
													printf("W_0[0,3] = %02x\n",x95);
													printf("W_0[0,2] = %02x\n",x96);
													printf("W_0[0,1] = %02x\n",x97);
													printf("W_0[0,0] = %02x\n",x98);
													return ;/*getchar();*/
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int Generator(unsigned char Known[33]/*, unsigned char y[99]*/)
{
	const unsigned char x0=1;
	const unsigned char x16=0;
	const unsigned char x15=0;
	const unsigned char x14=0;
	const unsigned char x13=0;
	const unsigned char x12=0;
	const unsigned char x11=0;
	const unsigned char x10=0;
	const unsigned char x9=0;
	const unsigned char x8=0;
	const unsigned char x7=0;
	const unsigned char x6=0;
	const unsigned char x5=0;
	const unsigned char x4=0;
	const unsigned char x3=0;
	const unsigned char x2=0;
	const unsigned char x1=0;
	const unsigned char x17=1+(rand()%255);
	const unsigned char x18=1+(rand()%255);
	const unsigned char x19=1+(rand()%255);
	const unsigned char x20=1+(rand()%255);
	const unsigned char x24=1+(rand()%255);
	const unsigned char x31=1+(rand()%255);
	const unsigned char x33=1+(rand()%255);
	const unsigned char x41=1+(rand()%255);
	const unsigned char x55=1+(rand()%255);
	const unsigned char x57=1+(rand()%255);
	const unsigned char x59=R(Multiply(0x0e,x41) ^ Multiply(0x09,x33) ^ Multiply(0x0b,x31) ^ Multiply(0x0d,x24) ^ Multiply(0x0b,x14) ^ Multiply(0x0b,x13) ^ Multiply(0x0d,x10) ^ Multiply(0x0d,x9) ^ Multiply(0x09,x6) ^ Multiply(0x09,x5) ^ Multiply(0x0e,x2) ^ Multiply(0x0e,x1) ^ S(x57));
	const unsigned char x61=1+(rand()%255);
	const unsigned char x63=1+(rand()%255);
	const unsigned char x65=1+(rand()%255);
	const unsigned char x67=1+(rand()%255);
	const unsigned char x69=R(Multiply(0x0b,x41) ^ Multiply(0x0e,x33) ^ Multiply(0x0d,x31) ^ Multiply(0x09,x24) ^ Multiply(0x0d,x14) ^ Multiply(0x0d,x13) ^ Multiply(0x09,x10) ^ Multiply(0x09,x9) ^ Multiply(0x0e,x6) ^ Multiply(0x0e,x5) ^ Multiply(0x0b,x2) ^ Multiply(0x0b,x1) ^ S(x67));
	const unsigned char x71=1+(rand()%255);
	const unsigned char x75=R(Multiply(0x0d,x41) ^ Multiply(0x0b,x33) ^ Multiply(0x09,x31) ^ Multiply(0x0e,x24) ^ Multiply(0x09,x14) ^ Multiply(0x09,x13) ^ Multiply(0x0e,x10) ^ Multiply(0x0e,x9) ^ Multiply(0x0b,x6) ^ Multiply(0x0b,x5) ^ Multiply(0x0d,x2) ^ Multiply(0x0d,x1) ^ S(x71));
	const unsigned char x77=1+(rand()%255);
	const unsigned char x79=R(Multiply(0x09,x41) ^ Multiply(0x0d,x33) ^ Multiply(0x0e,x31) ^ Multiply(0x0b,x24) ^ Multiply(0x0e,x14) ^ Multiply(0x0e,x13) ^ Multiply(0x0b,x10) ^ Multiply(0x0b,x9) ^ Multiply(0x0d,x6) ^ Multiply(0x0d,x5) ^ Multiply(0x09,x2) ^ Multiply(0x09,x1) ^ S(x77));
	const unsigned char x98=S(x65) ^ S(x55) ^ Multiply(0x02,S(x18)) ^ Multiply(0x03,S(x17));
	const unsigned char x21=x20 ^ x17 ^ Multiply(0x03,S(x20)) ^ S(x19) ^ Multiply(0xf4,S(x18)) ^ Multiply(0xf4,S(x17));
	const unsigned char x22=x18 ^ Multiply(0xf4,S(x18)) ^ Multiply(0xf4,S(x17));
	const unsigned char x23=S(x65) ^ S(x55) ^ Multiply(0x02,S(x18)) ^ Multiply(0x03,S(x17));
	const unsigned char x25=x23 ^ x0 ^ S(x24);
	const unsigned char x26=S(x63) ^ S(x61) ^ Multiply(0x02,S(x20)) ^ Multiply(0x03,S(x19));
	const unsigned char x27=x26 ^ x23;
	const unsigned char x28=Multiply(0x17,x41) ^ Multiply(0x1d,x33) ^ Multiply(0x1a,x31) ^ Multiply(0x12,x24) ^ Multiply(0x02,S(x77)) ^ Multiply(0x03,S(x71)) ^ S(x67) ^ S(x57);
	const unsigned char x29=x28 ^ x26;
	const unsigned char x30=x31 ^ x28;
	const unsigned char x32=Multiply(0x03,x23) ^ Multiply(0x02,S(x55)) ^ Multiply(0x07,S(x18)) ^ Multiply(0x07,S(x17));
	const unsigned char x34=x32 ^ S(x33);
	const unsigned char x35=Multiply(0x03,x26) ^ Multiply(0x02,S(x61)) ^ Multiply(0x07,S(x20)) ^ Multiply(0x07,S(x19));
	const unsigned char x36=x35 ^ x32;
	const unsigned char x37=Multiply(0x9c,x41) ^ Multiply(0x95,x33) ^ Multiply(0x1f,x30) ^ Multiply(0x92,x28) ^ Multiply(0x14,x24) ^ Multiply(0x8e,S(x71)) ^ Multiply(0x8e,S(x67)) ^ Multiply(0x8c,S(x57));
	const unsigned char x38=x37 ^ x35;
	const unsigned char x39=x37 ^ x24;
	const unsigned char x40=Multiply(0x8d,x32) ^ Multiply(0x8e,x23) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x42=Multiply(0x8d,x32) ^ Multiply(0x8e,x23) ^ S(x41) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x43=Multiply(0x8d,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19));
	const unsigned char x44=Multiply(0x8d,x35) ^ Multiply(0x8d,x32) ^ Multiply(0x8e,x26) ^ Multiply(0x8e,x23) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19)) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x45=Multiply(0xd1,x37) ^ x33 ^ Multiply(0x68,x30) ^ Multiply(0xd1,x24) ^ Multiply(0x02,S(x67)) ^ Multiply(0xba,S(x57));
	const unsigned char x46=x45 ^ Multiply(0x8d,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19));
	const unsigned char x47=x45 ^ x33;
	const unsigned char x48=Multiply(0x8c,x32) ^ Multiply(0x8e,x23) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x49=Multiply(0x8c,x32) ^ Multiply(0x8e,x23) ^ S(x31) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x50=Multiply(0x8c,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19));
	const unsigned char x51=Multiply(0x8c,x35) ^ Multiply(0x8c,x32) ^ Multiply(0x8e,x26) ^ Multiply(0x8e,x23) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19)) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x52=Multiply(0x8c,x45) ^ x41 ^ Multiply(0x35,x37) ^ Multiply(0x8c,x33) ^ Multiply(0x5d,x30) ^ Multiply(0x35,x24) ^ Multiply(0xe5,S(x57));
	const unsigned char x53=x52 ^ Multiply(0x8c,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19));
	const unsigned char x54=x52 ^ x41;
	const unsigned char x56=x55 ^ x41;
	const unsigned char x58=x57 ^ x52 ^ Multiply(0x8c,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19));
	const unsigned char x60=x59 ^ Multiply(0x8c,x35) ^ Multiply(0x8c,x32) ^ Multiply(0x8e,x26) ^ Multiply(0x8e,x23) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19)) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x62=x61 ^ Multiply(0x8c,x32) ^ Multiply(0x8e,x23) ^ S(x31) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x64=x63 ^ x33;
	const unsigned char x66=x65 ^ x45 ^ Multiply(0x8d,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19));
	const unsigned char x68=x67 ^ Multiply(0x8d,x35) ^ Multiply(0x8d,x32) ^ Multiply(0x8e,x26) ^ Multiply(0x8e,x23) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19)) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x70=x69 ^ Multiply(0x8d,x32) ^ Multiply(0x8e,x23) ^ S(x41) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x72=x71 ^ x24;
	const unsigned char x73=x37 ^ x35 ^ x19;
	const unsigned char x74=x35 ^ x32 ^ x17;
	const unsigned char x76=x75 ^ x32 ^ S(x33);
	const unsigned char x78=x77 ^ x30 ^ x28;
	const unsigned char x80=x79 ^ x28 ^ x26;
	const unsigned char x81=x26 ^ x23 ^ x20;
	const unsigned char x82=x23 ^ x18 ^ x0 ^ S(x24);
	const unsigned char x83=x52 ^ x41;
	const unsigned char x84=x52;
	const unsigned char x85=Multiply(0x8c,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x88,S(x20)) ^ Multiply(0x8b,S(x19));
	const unsigned char x86=Multiply(0x8c,x32) ^ Multiply(0x8e,x23) ^ Multiply(0x88,S(x18)) ^ Multiply(0x8b,S(x17));
	const unsigned char x87=x45 ^ x33;
	const unsigned char x88=x45;
	const unsigned char x89=Multiply(0x8d,x35) ^ Multiply(0x8e,x26) ^ Multiply(0x8b,S(x20)) ^ Multiply(0x89,S(x19));
	const unsigned char x90=Multiply(0x8d,x32) ^ Multiply(0x8e,x23) ^ Multiply(0x8b,S(x18)) ^ Multiply(0x89,S(x17));
	const unsigned char x91=x37 ^ x24;
	const unsigned char x92=x37;
	const unsigned char x93=x35;
	const unsigned char x94=x32;
	const unsigned char x95=x30;
	const unsigned char x96=x28;
	const unsigned char x97=x26;
	Known[0]=x0; /* 1 */
	Known[1]=x1; /* X_1[3,3] */
	Known[2]=x2; /* X_1[3,2] */
	Known[3]=x3; /* X_1[3,1] */
	Known[4]=x4; /* X_1[3,0] */
	Known[5]=x5; /* X_1[2,3] */
	Known[6]=x6; /* X_1[2,2] */
	Known[7]=x7; /* X_1[2,1] */
	Known[8]=x8; /* X_1[2,0] */
	Known[9]=x9; /* X_1[1,3] */
	Known[10]=x10; /* X_1[1,2] */
	Known[11]=x11; /* X_1[1,1] */
	Known[12]=x12; /* X_1[1,0] */
	Known[13]=x13; /* X_1[0,3] */
	Known[14]=x14; /* X_1[0,2] */
	Known[15]=x15; /* X_1[0,1] */
	Known[16]=x16; /* X_1[0,0] */
	Known[17]=x56; /* P[3,3] */
	Known[18]=x58; /* P[3,2] */
	Known[19]=x60; /* P[3,1] */
	Known[20]=x62; /* P[3,0] */
	Known[21]=x64; /* P[2,3] */
	Known[22]=x66; /* P[2,2] */
	Known[23]=x68; /* P[2,1] */
	Known[24]=x70; /* P[2,0] */
	Known[25]=x72; /* P[1,3] */
	Known[26]=x73; /* P[1,2] */
	Known[27]=x74; /* P[1,1] */
	Known[28]=x76; /* P[1,0] */
	Known[29]=x78; /* P[0,3] */
	Known[30]=x80; /* P[0,2] */
	Known[31]=x81; /* P[0,1] */
	Known[32]=x82; /* P[0,0] */
	return 1;
	return 0;
}

int main(int argc, char** argv)
{
	unsigned char Known[33];
   srand(getpid()); /* Init PRNG */
	MakeTableMul2_8();
	/* assign values */
	Generator(Known);
	/* Attack */
	Attack(Known);
	return 0;
}
