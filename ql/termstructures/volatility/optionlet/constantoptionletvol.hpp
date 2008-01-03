/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2004, 2005, 2007 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file constantoptionletvol.hpp
    \brief Constant caplet/floorlet volatility
*/

#ifndef quantlib_caplet_constant_volatility_hpp
#define quantlib_caplet_constant_volatility_hpp

#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

namespace QuantLib {

    //! Constant caplet volatility, no time-strike dependence
    class ConstantOptionletVol : public OptionletVolatilityStructure {
      public:
        //! floating reference date, floating market data
        ConstantOptionletVol(const Handle<Quote>& volatility,
                             const Calendar& cal,
                             const DayCounter& dayCounter = Actual365Fixed(),
                             BusinessDayConvention bdc = Following);
        //! fixed reference date, floating market data
        ConstantOptionletVol(const Date& referenceDate,
                             const Handle<Quote>& volatility,
                             const Calendar& cal,
                             const DayCounter& dayCounter = Actual365Fixed(),
                             BusinessDayConvention bdc = Following);
        //! floating reference date, fixed market data
        ConstantOptionletVol(Volatility volatility,
                             const Calendar& cal,
                             const DayCounter& dayCounter = Actual365Fixed(),
                             BusinessDayConvention bdc = Following);
        //! fixed reference date, fixed market data
        ConstantOptionletVol(const Date& referenceDate,
                             Volatility volatility,
                             const Calendar& cal,
                             const DayCounter& dayCounter = Actual365Fixed(),
                             BusinessDayConvention bdc = Following);
        //! \name TermStructure interface
        //@{
        Date maxDate() const;
        //@}
        //! \name VolatilityTermStructure interface
        //@{
        Real minStrike() const;
        Real maxStrike() const;
        //@}
      protected:
        Volatility volatilityImpl(Time t, Rate) const;
      private:
        Handle<Quote> volatility_;
    };


    // inline definitions

    inline Date ConstantOptionletVol::maxDate() const {
        return Date::maxDate();
    }

    inline Real ConstantOptionletVol::minStrike() const {
        return QL_MIN_REAL;
    }

    inline Real ConstantOptionletVol::maxStrike() const {
        return QL_MAX_REAL;
    }

    inline Volatility ConstantOptionletVol::volatilityImpl(Time,
                                                           Rate) const {
        return volatility_->value();
    }

}

#endif