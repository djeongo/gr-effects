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

#ifndef INCLUDED_EFFECTS_OVERDRIVE_FF_IMPL_H
#define INCLUDED_EFFECTS_OVERDRIVE_FF_IMPL_H

#include <effects/overdrive_ff.h>

namespace gr {
  namespace effects {

    class overdrive_ff_impl : public overdrive_ff
    {
     private:
      // Nothing to declare in this block.

     public:
      overdrive_ff_impl(int overdrive);
      ~overdrive_ff_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      void shift_left();

      int overdrive_;             // input buffer size
      float * input_buffer_;  // input buffer to store input samples
      float * output_buffer_;  // output buffer to store output samples
    };

  } // namespace effects
} // namespace gr

#endif /* INCLUDED_EFFECTS_OVERDRIVE_FF_IMPL_H */

