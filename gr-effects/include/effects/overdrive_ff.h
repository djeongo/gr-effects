/* -*- c++ -*- */
/*
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_EFFECTS_OVERDRIVE_FF_H
#define INCLUDED_EFFECTS_OVERDRIVE_FF_H

#include <effects/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace effects {

    /*!
     * \brief <+description of block+>
     * \ingroup effects
     *
     */
    class EFFECTS_API overdrive_ff : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<overdrive_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of effects::overdrive_ff.
       *
       * To avoid accidental use of raw pointers, effects::overdrive_ff's
       * constructor is in a private implementation
       * class. effects::overdrive_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make(int overdrive);
    };

  } // namespace effects
} // namespace gr

#endif /* INCLUDED_EFFECTS_OVERDRIVE_FF_H */

