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

#ifndef INCLUDED_EFFECTS_PITCH_DETECTOR_FF_IMPL_H
#define INCLUDED_EFFECTS_PITCH_DETECTOR_FF_IMPL_H

#include <effects/pitch_detector_ff.h>

namespace gr {
  namespace effects {

    // Implements a sliding window of configurable length.
    // Take the FFT of the sliding window, and report the frequency
    // at which the maximum value occurs.
    class pitch_detector_ff_impl : public pitch_detector_ff
    {
     private:
      int           n_fft_;             // input buffer size
      void        * d_plan_;             // FFTW plan
      float       * d_inbuf_;
      gr_complex  * d_outbuf_;
      float       * input_buffer_;  // input buffer to store input samples
      // TODO probably not needed
      float       * output_buffer_;  // output buffer to store output samples

     public:
        pitch_detector_ff_impl(int pitch_detector);
        ~pitch_detector_ff_impl();

        // Where all the action really happens
        void forecast (int noutput_items, gr_vector_int &ninput_items_required);

        int general_work(int noutput_items,
             gr_vector_int &ninput_items,
             gr_vector_const_void_star &input_items,
             gr_vector_void_star &output_items);

        int inbuf_length () {return n_fft_;}
        int outbuf_length () {return n_fft_;}
        void shift_left();
    };

  } // namespace effects
} // namespace gr

#endif /* INCLUDED_EFFECTS_PITCH_DETECTOR_FF_IMPL_H */

