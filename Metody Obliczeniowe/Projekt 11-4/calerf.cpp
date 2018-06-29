
#include "math.h"

#include "calerf.h"




    

const long double aintl_(const long double x)
{ // This function has been added by L. K. Bieniasz
if(x >= 0.0L)return floorl(x);
else return ceill(x);
}





////////////////////////
// long double versions
////////////////////////


long double CALERFL(const long double arg, const int jint)
{
//-----------------------------------------------------------------
//
//  This packet evaluates ERF(x), ERFC(x), and exp(x*x)*ERFC(x)
//  for a real argument x.  It contains four long double functions:
//  ERFL(), ERFCL(), and erexl(), and CALERFL().
//
//  The calling statements for the primary entries are:
//
//         y = ERFL(x),
//
//         y = ERFCL(x),
//  and
//         y = erexl(x).
//
//  The function CALERFL() is intended for internal packet use only,
//  all computations within the packet being concentrated in this
//  routine. The functions invoke CALERFL() with the
//  statement
//
//         CALERFL(arg,jint)
//
//  where the parameter usage is as follows
//
//      Function                     Parameters for CALERFL()
//       call       l       arg            jint
//
//     ERFL(arg)     ANY REAL ARGUMENT      0
//     ERFCL(arg)    fabs(arg)  < XBIG      1
//     EREXL(arg)    XNEG < arg < XMAX      2
//
//  The main computation evaluates near-minimax approximations
//  from "Rational Chebyshev approximations for the error function"
//  by W. J. Cody, Math. Comp., 1969, PP. 631-638.  This
//  transportable program uses rational functions that theoretically
//  approximate  ERFL(x) and  ERFCL(x) to at least 18 significant
//  decimal digits. The accuracy achieved depends on the arithmetic
//  system, the compiler, the intrinsic functions, and proper
//  selection of the machine-dependent constants.
//
//******************************************************************
//
//  Explanation of machine-dependent constants
//
//   XMIN   = the smallest positive floating-point number.
//   XINF   = the largest positive finite floating-point number.
//   XNEG   = the largest negative argument acceptable to EREXL();
//            the negative of the solution to the equation
//            2*exp(x*x) = XINF.
//   XSMALL = argument below which ERFL(x) may be represented by
//            2*x/sqrt(pi) and above which  x*x  will not underflow.
//            A conservative value is the largest machine number x
//            such that   1.0 + x = 1.0   to machine precision.
//   XBIG   = largest argument acceptable to ERFCL();  solution to
//            the equation:  W(x) * (1-0.5/x**2) = XMIN,  where
//            W(x) = exp(-x*x)/[x*sqrt(pi)].
//   XHUGE  = argument above which  1.0 - 1/(2*x*x) = 1.0  to
//            machine precision.  A conservative value is
//            1/[2*sqrt(XSMALL)]
//   XMAX   = largest acceptable argument to EREXL(); the minimum
//            of XINF and 1/[sqrt(pi)*XMIN].
//
//  Approximate values for some important machines are:
//
//                          XMIN       XINF        XNEG     XSMALL
//
//  IEEE (IBM/XT,
//    SUN, etc.)  (D.P.)  2.23D-308   1.79D+308   -26.628  1.11D-16
//  IBM 195       (D.P.)  5.40D-79    7.23E+75    -13.190  1.39D-17
//  UNIVAC 1108   (D.P.)  2.78D-309   8.98D+307   -26.615  1.73D-18
//  VAX D-Format  (D.P.)  2.94D-39    1.70D+38     -9.345  1.39D-17
//  VAX G-Format  (D.P.)  5.56D-309   8.98D+307   -26.615  1.11D-16
//
//
//                          XBIG       XHUGE       XMAX
//
//  IEEE (IBM/XT,
//    SUN, etc.)  (D.P.)  26.543      6.71D+7     2.53D+307
//  IBM 195       (D.P.)  13.306      1.90D+8     7.23E+75
//  UNIVAC 1108   (D.P.)  26.582      5.37D+8     8.98D+307
//  VAX D-Format  (D.P.)   9.269      1.90D+8     1.70D+38
//  VAX G-Format  (D.P.)  26.569      6.71D+7     8.98D+307
//
//******************************************************************
//
//  Error returns
//
//  The program returns  erfc = 0      for  arg >= XBIG;
//
//                       erex = XINF   for  arg <  XNEG;
//      and
//                       erex = 0      for  arg >= XMAX.
//
//
//  Intrinsic functions required are:
//
//     fabsl(), expl()
//
//-----------------------------------------------------------------
//  Based on the netlib FORTRAN package by W. J. Cody,
//  Mathematics and Computer Science Division
//  Argonne National Laboratory
//  Argonne, IL 60439
//
//  Latest modification of the above package: March 19, 1990
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//  Mathematical constants
//-----------------------------------------------------------------
const long double ZERO    =  0.0e0L;
const long double HALF    =  0.5e0L;
const long double ONE     =  1.0e0L;
const long double TWO     =  2.0e0L;
const long double FOUR    =  4.0e0L;
const long double SIXTEEN = 16.0e0L;

static const long double SQRPI  = 5.6418958354775628695e-1L;
static const long double THRESH = 0.46875e0L;

//-----------------------------------------------------------------
//  Machine-dependent constants (for IBM PC)
//-----------------------------------------------------------------
static const long double XINF   =    1.79e308L;
static const long double XNEG   = -26.628e0L;
static const long double XSMALL =  1.11e-16L; 
static const long double XBIG   =  26.543e0L;
static const long double XHUGE  =  1.0e10L;    // 6.71e7L;    // Modified by L. K. Bieniasz
static const long double XMAX   =  0.5e2466L;  // 2.53e307L;  // Modified by L.K. Bieniasz

//-----------------------------------------------------------------
//  Coefficients for approximation to  erf  in first interval
//-----------------------------------------------------------------
static const long double A[5] = {
                                3.16112374387056560e00L,
                                1.13864154151050156e02L,
                                3.77485237685302021e02L,
                                3.20937758913846947e03L,
                                1.85777706184603153e-1L
                                };

static const long double B[4] = {
                                2.36012909523441209e01L,
                                2.44024637934444173e02L,
                                1.28261652607737228e03L,
                                2.84423683343917062e03L
                                };
//-----------------------------------------------------------------
//  Coefficients for approximation to  erfc  in second interval
//-----------------------------------------------------------------
static const long double C[9] = {
                                5.64188496988670089e-1L,
                                8.88314979438837594e0L,
                                6.61191906371416295e01L,
                                2.98635138197400131e02L,
                                8.81952221241769090e02L,
                                1.71204761263407058e03L,
                                2.05107837782607147e03L,
                                1.23033935479799725e03L,
                                2.15311535474403846e-8L
                                };

static const long double D[8] = {
                                1.57449261107098347e01L,
                                1.17693950891312499e02L,
                                5.37181101862009858e02L,
                                1.62138957456669019e03L,
                                3.29079923573345963e03L,
                                4.36261909014324716e03L,
                                3.43936767414372164e03L,
                                1.23033935480374942e03L
                                };
//-----------------------------------------------------------------
//  Coefficients for approximation to  erfc  in third interval
//-----------------------------------------------------------------
static const long double P[6] = {
                                3.05326634961232344e-1L,
                                3.60344899949804439e-1L,
                                1.25781726111229246e-1L,
                                1.60837851487422766e-2L,
                                6.58749161529837803e-4L,
                                1.63153871373020978e-2L
                                };

static const long double Q[5] = {
                                2.56852019228982242e00L,
                                1.87295284992346047e00L,
                                5.27905102951428412e-1L,
                                6.05183413124413191e-2L,
                                2.33520497626869185e-3L
                                };
//-----------------------------------------------------------------

register int i;
		//int iysq;
long double del,x,xden,xnum,y,ysq;
long double result;

x = arg;
y = fabsl(x);
if(y <= THRESH)
  {
  //------------------------------------
  //  Evaluate  erf  for  |x| <= 0.46875
  //------------------------------------
  ysq = ZERO;
  if(y > XSMALL)ysq = y * y;
  xnum = A[4]*ysq;
  xden = ysq;
  for(i=0; i<3; i++)
     {
     xnum = (xnum + A[i])*ysq;
     xden = (xden + B[i])*ysq;
     }
  result = x * (xnum + A[3])/(xden + B[3]);
  if(jint != 0)result = ONE - result;
  if(jint == 2)result = expl(ysq)*result;

  return result;
  }
//-------------------------------------------
//  Evaluate  erfc  for 0.46875 <= |x| <= 4.0
//-------------------------------------------
else
if(y <= FOUR)
  {
  xnum = C[8]*y;
  xden = y;
  for(i=0; i<7; i++)
     {
     xnum = (xnum + C[i])*y;
     xden = (xden + D[i])*y;
     }
  result = (xnum + C[7])/(xden + D[7]);
  if(jint != 2)
    {
    	/*
    iysq = (int)(y*SIXTEEN);
    ysq = ((long double)iysq)/SIXTEEN;
       */
       
    ysq = aintl_(y*SIXTEEN)/SIXTEEN; 
    
    del = (y-ysq)*(y+ysq);
    result = expl(-ysq*ysq) * expl(-del)*result;
    }
  }
//-------------------------------
//  Evaluate  erfc  for |x| > 4.0
//-------------------------------
else{
    result = ZERO;
    if(y >= XBIG)
      {
      if((jint != 2) || (y >= XMAX))goto LAB300;
      if(y >= XHUGE)
        {
        result = SQRPI/y;
        goto LAB300;
        }
      }
    ysq = ONE/(y * y);
    xnum = P[5]*ysq;
    xden = ysq;
    for(i=0; i<4; i++)
       {
       xnum = (xnum + P[i])*ysq;
       xden = (xden + Q[i])*ysq;
       }
    result = ysq *(xnum + P[4])/(xden + Q[4]);
    result = (SQRPI - result)/y;
    if(jint != 2)
      {
      	/*
      iysq = (int)(y*SIXTEEN);
      ysq = ((long double)iysq)/SIXTEEN;
         */
         
      ysq = aintl_(y*SIXTEEN)/SIXTEEN; 
      
      
      del = (y-ysq)*(y+ysq);
      result = expl(-ysq*ysq) * expl(-del)*result;
      }
    }

//-----------------------------------------
//  Fix up for negative argument, erf, etc.
//-----------------------------------------
LAB300:
if(jint == 0)
  {
  result = (HALF - result)+HALF;
  if(x < ZERO)result = -result;
  }
else
if(jint == 1)
  {
  if(x < ZERO)result = TWO - result;
  }
else{ // jint == 2

    if(x < ZERO)
      {
      if(x < XNEG)result = XINF;
      else{
      	
      	            /*
          iysq = (int)(x*SIXTEEN);
          ysq = ((long double)iysq)/SIXTEEN;
                    */
          
          ysq = aintl_(x*SIXTEEN)/SIXTEEN;
          
          
          del = (x-ysq)*(x+ysq);
          y = expl(ysq*ysq) * expl(del);
          result = (y+y)-result;
          }
      }
    }

return result;
}





long double ERFL(const long double x)
{
//-------------------------------------------------------------------
//  This function computes approximate values for ERF(x).
//  (see comments heading CALERF()).
//
//  Based on the netlib package by W. J. Cody, January 8, 1985
//-------------------------------------------------------------------
return CALERFL(x,0);
}






long double ERFCL(const long double x)
{
//-------------------------------------------------------------------
//  This function computes approximate values for ERFC(x).
//  (see comments heading CALERF()).
//
//  Based on the netlib package by W. J. Cody, January 8, 1985
//-------------------------------------------------------------------
return CALERFL(x,1);
}





long double EREXL(const long double x)
{
//-----------------------------------------------------------------
//  This function computes approximate values for
//  exp(x*x) * ERFC(x).
//  (see comments heading CALERF()).
//
//  Based on the netlib package by W. J. Cody, March 30, 1987
//-----------------------------------------------------------------
return CALERFL(x,2);
}








