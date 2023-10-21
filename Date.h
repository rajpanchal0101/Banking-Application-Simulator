#ifndef H__DATE_H
#define H__DATE_H
#include <string>
#include <iosfwd>

// $Id: Date.h,v 1.3 2002/10/18 05:56:10 tknarr Exp $
// Copyright (C) 2000, 2002
// Todd T. Knarr <tknarr@silverglass.org>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

//
// Classname      : Date
//
// Author         : Todd Knarr
//
// Creation Date  : 29 Nov 1995
//
// Superclasses   : none
//
// Subclasses     : none
//
// Required files :
//
// Description    :
//
// Provides a Date class which represents dates as
// Julian day numbers ( days since 1 Jan 4713 BC ).
// This class can handle all dates from  1 Jan 4713BC to 31 Dec 4999AD.
//
// Note: Years AD are positive, years BC are negative. There is
// no year 0AD, it goes from 1BC to 1AD. A year of 0 will be treated
// as 1BC. No attempt is made to validate ranges. Physical errors
// will not result from insane day-month combinations like the 87th
// day of the 45th month, but the results will obviously not make
// much sense.
//
// Date conversion routines  by Eric bergman-Terrell, Computer Language,
//     Dec 1990.
// Alternate method by David Burki, CUJ Feb 1993.
//
// To Do:
// * Add << and >> operators for iostreams. They should probably output
//   and input the string form.
//

// Modified by Paul Wolfgang
// The ToString function has been deleted and replaced by
// a to_string function that returns a std::string in the form
// yyyy-mm-dd.
// Added << and >> operators for iostreams. They read and write in the
// form yyyy-mm-dd.

#include <stdlib.h>
#include <time.h>

class Date
{

private:

    long        lJulianDay;

    //
    // Function      : YmdToJd
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : int year, month, day
    //
    // Return values : long julian day
    //
    // Description   :
    //
    // Internal routine that does the physical conversion
    // from YMD form to Julian day number.
    //
    static long YmdToJd( const int iYear, const int iMonth, const int iDay );

    //
    // Function      : JdToYmd
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : long julian day, pointers to int year, month, day
    //
    // Return values : none
    //
    // Description   :
    //
    // Internal routine that reverses the conversion, turning a Julian
    // day number into YMD values.
    //
    static void JdToYmd( const long lJD, int *piYear, int *piMonth,
                         int *piDay );

public:

    //
    // Function      : IsLeapYear
    //
    // Author        : Todd Knarr
    //
    // Creation date : 5 Dec 1995
    //
    // Parameters    : int year
    //
    // Return values : 1 if the year given is a leap year
    //                 0 if it is not
    //
    static int IsLeapYear( const int iYear )
    {
        long jd1, jd2;
        jd1 = YmdToJd( iYear, 2, 28 );
        jd2 = YmdToJd( iYear, 3, 1 );
        return ( ( jd2 - jd1 ) > 1 );
    }

    //
    // Function      : default constructor
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : none
    //
    // Return values : none
    //
    // Description   :
    //
    // Constructs a new object initialized to 1 Jan 4713BC
    //
    Date()
    {
        lJulianDay = 0L;
    }

    //
    // Function      : copy constructor
    //
    // Author        : Todd Knarr
    //
    // Creation date : 13 Mar 1996
    //
    // Parameters    : 
    //
    // Return values : 
    //
    Date( const Date& Orig ) { lJulianDay = Orig.lJulianDay; }
    Date& operator=( const Date& Orig )
    {
        lJulianDay = Orig.lJulianDay;
        return *this;
    }

    //
    // Function      : time_t constructor
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : none
    //
    // Return values : none
    //
    // Description   :
    //
    // Constructs an object initialized to the date
    // represented by a system time value.
    //
    Date( const time_t tSysTime )
    {
        struct tm *ptm;
        int y, m, d;

        ptm = localtime( &tSysTime );
        y = ptm->tm_year + 1900;
        m = ptm->tm_mon + 1;
        d = ptm->tm_mday;
        lJulianDay = YmdToJd( y, m, d );
    }

    //
    // Function      : char* ( string ) constructor
    //
    // Author        : Todd Knarr
    //
    // Creation date : 30 Nov 1995
    //
    // Parameters    :
    //
    // Return values :
    //
    // Description   :
    //
    // Constructs an object from a string.
    // The string is formatted as the ASCII representation
    // of the long Julian day number.
    //
    Date( const char *String )
    {
        lJulianDay = atol( String );
    }

    //
    // Function      : year/month/day constructor
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : int year, month, day
    //
    // Return values : none
    //
    // Description   :
    //
    // Constructs an object initialized to
    // the date given by the arguments
    //
    Date( const int iDay, const int iMonth, const int iYear )
    {
        lJulianDay = YmdToJd( iYear, iMonth, iDay );
    }

    //
    // Function      : Year, Month, Day, DayOfYear, DayOfWeek, DayOfWorkWeek,
    //                 IsLeapYear, YMD
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : none
    //
    // Return values : int or none
    //
    // Description   :
    //
    // Functions to return various parts of the date. The Year(),
    // Month() and Day() functions return the corresponding parts
    // of the date. The DayOfYear() returns the day of the year,
    // with 1 Jan being day 1. The DayOfWeek() and DayOfWorkWeek()
    // functions return the day of the week, from 0 through 6, with
    // the DayOfWeek() matching localtime()'s convention ( 0 = Sunday,
    // 6 = Saturday ) and DayOfWorkWeek() starting the week on
    // Monday ( 0 = Monday, 6 = Sunday ). IsLeapYear() returns 1 if
    // the date is in a leap year, 0 otherwise. YMD() puts the
    // year, month and day values directly into three integer variables,
    // for times when you need all three at the same time.
    //
    int Year( void ) const
    {
        int y, m, d;

        JdToYmd( lJulianDay, &y, &m, &d );
        return y;
    }
    int Month( void ) const
    {
        int y, m, d;

        JdToYmd( lJulianDay, &y, &m, &d );
        return m;
    }
    int Day( void ) const
    {
        int y, m, d;

        JdToYmd( lJulianDay, &y, &m, &d );
        return d;
    }
    int DayOfYear( void ) const;
    int DayOfWeek( void ) const
    {
        return ( ( ( (int) ( lJulianDay % 7L ) ) + 1 ) % 7 );
    }
    int DayOfWorkWeek( void ) const
    {
        return ( (int) ( lJulianDay % 7L ) );
    }
    int IsLeapYear( void ) const
    {
        int y, m, d;
        JdToYmd( lJulianDay, &y, &m, &d );
        return IsLeapYear( y );
    }
    void YMD( int *pY, int *pM, int *pD )
    {
        JdToYmd( lJulianDay, pY, pM, pD );
        return;
    }

    //
    // Function      : Additive operators
    //
    // Author        : Todd Knarr
    //
    // Creation date : 30 Nov 1995
    //
    // Parameters    : Date value and integer, or
    //                 Two date values
    //
    // Return values : New Date, or difference between two Dates
    //
    // Description   :
    //
    // Adding an integral type to a Date adds the number of
    // days in the integral type to the Date. Adding two Dates
    // is not defined. Subtracting two dates yields the difference
    // between them in days.
    //
    friend Date operator+( const Date& Left, const long Right )
    {
        Date Temp = Left;
        Temp.lJulianDay += Right;
        return Temp;
    }
    friend Date operator+( const long Left, const Date& Right )
    {
        Date Temp = Right;
        Temp.lJulianDay += Left;
        return Temp;
    }
    Date& operator+=( const long Right )
    {
        lJulianDay += Right;
        return *this;
    }
    friend Date operator-( const Date& Left, const long Right )
    {
        Date Temp = Left;
        Temp.lJulianDay -= Right;
        return Temp;
    }
    friend Date operator-( const long Left, const Date& Right )
    {
        Date Temp = Right;
        Temp.lJulianDay -= Left;
        return Temp;
    }
    Date& operator-=( const long Right )
    {
        lJulianDay -= Right;
        return *this;
    }
    long operator-( const Date& Right )
    {
        return lJulianDay - Right.lJulianDay;
    }

    //
    // Function      : ++ and -- operators, prefix and postfix forms
    //
    // Author        : Todd Knarr
    //
    // Creation date : 1 Dec 1995
    //
    // Parameters    : none
    //
    // Return values : New Date
    //
    Date& operator++()
    {
        lJulianDay++;
        return *this;
    }
    Date operator++( int )
    {
        Date Temp = *this;
        lJulianDay++;
        return Temp;
    }
    Date& operator--()
    {
        lJulianDay--;
        return *this;
    }
    Date operator--( int )
    {
        Date Temp = *this;
        lJulianDay--;
        return Temp;
    }

    // Function      : to_string
    // Author        : Paul Wolfgang
    //
    // Creation date : 17 Feb 2006
    //
    // Parameters    : none
    //
    // Return value  : std::string
    //
    // Formats the Date into an ASCII representation.
    // This is in the form yyyy-mm-dd
    //
    //
    std::string to_string() const;

    // Function      : comparison operators
    //
    // Author        : Todd Knarr
    //
    // Creation date : 1 Dec 1995
    //
    // Parameters    :
    //
    // Return values : non-zero if the comparison succeeds
    //                 0 if it fails
    //
    int operator==( const Date& Right ) const
    {
        return lJulianDay == Right.lJulianDay;
    }
    int operator!=( const Date& Right ) const
    {
        return lJulianDay != Right.lJulianDay;
    }
    int operator<( const Date& Right ) const
    {
        return lJulianDay < Right.lJulianDay;
    }
    int operator<=( const Date& Right ) const
    {
        return lJulianDay <= Right.lJulianDay;
    }
    int operator>( const Date& Right ) const
    {
        return lJulianDay > Right.lJulianDay;
    }
    int operator>=( const Date& Right ) const
    {
        return lJulianDay >= Right.lJulianDay;
    }

    //
    // Function      : ToSysTime
    //
    // Author        : Todd Knarr
    //
    // Creation date : 29 Nov 1995
    //
    // Parameters    : none
    //
    // Return values : converted result
    //
    // Description   :
    //
    // Converts the date to a time_t value
    // representing midnight of that date.
    //
    time_t ToSysTime( void ) const;

    friend std::ostream& operator<<(std::ostream&, const Date&);
    friend std::istream& operator>>(std::istream&, Date&);
};

#endif
#include <sstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <cstdlib>

// $Id: Date.C,v 1.2 2002/10/18 05:56:15 tknarr Exp $
// Copyright (C) 2000, 2002
// Todd T. Knarr <tknarr@silverglass.org>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

//
// Classname      : Date
//
// Author         : Todd Knarr
//
// Creation Date  : 29 Nov 1995
//
// Superclasses   : none
//
// Subclasses     : none
//
// Required files : Date.h
//
// Description    :
//
// Provides a Date class which represents dates as
// Julian day numbers ( days since 1 Jan 4713 BC ).
// This class can handle all dates from  1 Jan 4713BC to 31 Dec 4999AD.
//
// Note: Years AD are positive, years BC are negative. There is
// no year 0AD, it goes from 1BC to 1AD. A year of 0 will be treated
// as 1BC. No attempt is made to validate ranges. Physical errors
// will not result from insane day-month combinations like the 87th
// day of the 45th month, but the results will obviously not make
// much sense.
//
// Date conversion routines  by Eric bergman-Terrell, Computer Language,
//     Dec 1990.
// Alternate method by David Burki, CUJ Feb 1993.
//
// To Do:
// * Add << and >> operators for iostreams. They should probably output
//   and input the string form.
//

#include <time.h>

//
//  Function      : YmdToJd
//
//  Author        : Todd Knarr
//
//  Creation date : 29 Nov 1995
//
//  Parameters    : int year, month, day
//
//  Return values : long julian day
//
//  Description   :
//
// Internal routine that does the physical conversion
// from YMD form to Julian day number.
//
long Date::YmdToJd( const int iYear, const int iMonth, const int iDay )
{
    long jul_day;

#ifndef JULDATE_USE_ALTERNATE_METHOD

    int a,b;
    int year = iYear, month = iMonth, day = iDay;
    float year_corr;

    if ( year < 0 )
        year++;
    year_corr = ( year > 0 ? 0.0 : 0.75 );
    if ( month <= 2 )
    {
        year--;
        month += 12;
    }
    b = 0;
    if ( year * 10000.0 + month * 100.0 + day >= 15821015.0 )
    {
        a = year / 100;
        b = 2 - a + a / 4;
    }
    jul_day = (long) ( 365.25 * year - year_corr ) +
              (long) ( 30.6001 * ( month + 1 ) ) + day + 1720995L + b;

#else

    long lmonth = (long) iMonth, lday = (long) iDay, lyear = (long) iYear;

    // Adjust BC years
    if ( lyear < 0 )
        lyear++;

    jul_day = lday - 32075L +
        1461L * ( lyear + 4800L + ( lmonth - 14L ) / 12L ) / 4L +
        367L * ( lmonth - 2L - ( lmonth - 14L ) / 12L * 12L ) / 12L -
        3L * ( ( lyear + 4900L + ( lmonth - 14L ) / 12L ) / 100L ) / 4L;

#endif

    return jul_day;
}

//
//  Function      : JdToYmd
//
//  Author        : Todd Knarr
//
//  Creation date : 29 Nov 1995
//
//  Parameters    : long julian day, pointers to int year, month, day
//
//  Return values : none
//
//  Description   :
//
// Internal routine that reverses the conversion, turning a Julian
// day number into YMD values.
//
void Date::JdToYmd( const long lJD, int *piYear, int *piMonth, int *piDay )
{
#ifndef JULDATE_USE_ALTERNATE_METHOD

    long a, b, c, d, e, z, alpha;

    z = lJD;
    if ( z < 2299161L )
        a = z;
    else
    {
        alpha = (long) ( ( z - 1867216.25 ) / 36524.25 );
        a = z + 1 + alpha - alpha / 4;
    }
    b = a + 1524;
    c = (long) ( ( b - 122.1 ) / 365.25 );
    d = (long) ( 365.25 * c );
    e = (long) ( ( b - d ) / 30.6001 );
    *piDay = (int) b - d - (long) ( 30.6001 * e );
    *piMonth = (int) ( e < 13.5 ) ? e - 1 : e - 13;
    *piYear = (int) ( *piMonth > 2.5 ) ? ( c - 4716 ) : c - 4715;
    if ( *piYear <= 0 )
        *piYear -= 1;

#else

    long t1, t2, yr, mo;

    t1 = lJD + 68569L;
    t2 = 4L * t1 / 146097L;
    t1 = t1 - ( 146097L * t2 + 3L ) / 4L;
    yr = 4000L * ( t1 + 1L ) / 1461001L;
    t1 = t1 - 1461L * yr / 4L + 31L;
    mo = 80L * t1 / 2447L;
    *piDay = (int) ( t1 - 2447L * mo / 80L );
    t1 = mo / 11L;
    *piMonth = (int) ( mo + 2L - 12L * t1 );
    *piYear = (int) ( 100L * ( t2 - 49L ) + yr + t1 );

    // Correct for BC years
    if ( *piYear <= 0 )
        *piYear -= 1;

#endif

    return;
}


int Date::DayOfYear( void ) const
{
    int y, m, d;
    long soy;

    JdToYmd( lJulianDay, &y, &m, &d );
    soy = YmdToJd( y, 1, 1 );
    return (int) ( lJulianDay - soy + 1 );
}

//
//  Function      : ToSysTime
//
//  Author        : Todd Knarr
//
//  Creation date : 29 Nov 1995
//
//  Parameters    : none
//
//  Return values : converted result
//
//  Description   :
//
// Converts the date to a time_t value
// representing midnight of that date.
//
time_t Date::ToSysTime( void ) const
{
    struct tm tmRep;
    int y, m, d;
    time_t t;
    
    JdToYmd( lJulianDay, &y, &m, &d );
    if ( y < 1970 )
    {
        y = 70;
        m = 1;
        d = 1;
    }
    tmRep.tm_year = y - 1900 ;
    tmRep.tm_mon = m-1;
    tmRep.tm_mday = d;
    tmRep.tm_hour = 0;
    tmRep.tm_min = 0;
    tmRep.tm_sec = 0;
    tmRep.tm_isdst = 0;
    
    t = mktime( &tmRep );
    return t;
}

// Function      : to_string
// Author        : Paul Wolfgang
//
// Creation date : 17 Feb 2006
//
// Parameters    : none
//
// Return value  : std::string
//
// Formats the Date into an ASCII representation.
// This is in the form yyyy-mm-dd
//
//
std::string Date::to_string() const {
  std::ostringstream oss;
  oss << std::setfill('0');
  oss << std::setw(4) << Year() 
      << '-' << std::setw(2) << Month()
      << '-' << std::setw(2) << Day();
  return oss.str();
}

// Function      : ostream operator<<
// Author        : Paul Wolfgang
//
// Creation date : 17 Feb 2006
//
// Parameters    : none
//
// Return value  : ostream&
//
// Formats the Date into an ASCII representation.
// This is in the form yyyy-mm-dd and inserts it
// into the ostream
//
//
std::ostream& operator<<(std::ostream& out, const Date& date)
{ return out << date.to_string(); }

// Function      : istream operator>>
// Author        : Paul Wolfgang
//
// Creation date : 17 Feb 2006
//
// Parameters    : none
//
// Return value  : istream&
//
// Extracts a date in the form yyyy-mm-dd from the istream
//
//
std::istream& operator>>(std::istream& in, Date& date)
{
  std::string date_string;
  in >> date_string;
  size_t pos1 = date_string.find('-');
  size_t pos2 = date_string.find('-', pos1 + 1);
  if (pos1 == std::string::npos || pos2 == std::string::npos) {
    in.clear(std::ios::failbit);
    return in;
  }
  std::string year_string = date_string.substr(0, pos1);
  std::string month_string = date_string.substr(pos1+1, pos2 - pos1 - 1);
  std::string day_string = date_string.substr(pos2 + 1);
  date = Date(std::atoi(day_string.c_str()),
	      std::atoi(month_string.c_str()),
	      std::atoi(year_string.c_str()));
  return in;
}
