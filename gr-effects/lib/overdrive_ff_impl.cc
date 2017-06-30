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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "overdrive_ff_impl.h"

// code from https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace gr {
  namespace effects {

    overdrive_ff::sptr
    overdrive_ff::make(int overdrive)
    {
      return gnuradio::get_initial_sptr
        (new overdrive_ff_impl(overdrive));
    }

    /*
     * The private constructor
     */
    overdrive_ff_impl::overdrive_ff_impl(int overdrive)
      : gr::block("overdrive_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      overdrive_ = overdrive;
      std::cout << "Delay value : " << overdrive_ << std::endl;
      input_buffer_ = (float *)calloc(overdrive_, sizeof(float));
      output_buffer_ = (float *)calloc(overdrive_, sizeof(float));
    }

    /*
     * Our virtual destructor.
     */
    overdrive_ff_impl::~overdrive_ff_impl()
    {
      free(input_buffer_);
      free(output_buffer_);
    }

    void
    overdrive_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    /*
     * Left shift input buffer
     */
    void overdrive_ff_impl::shift_left()
    {
      memmove((void *)input_buffer_, (void *)&input_buffer_[1], sizeof(float)*(overdrive_-1));
      memmove((void *)output_buffer_, (void *)&output_buffer_[1], sizeof(float)*(overdrive_-1));
    }

    int
    overdrive_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      std::cout << "noutput_items " << noutput_items <<std::endl;
      for(int i=0; i<noutput_items; i++){
        shift_left();
        // push into buffer
        input_buffer_[overdrive_-1] = in[i];

        // generate new output sample
//        out[i] = 0.5*input_buffer_[0]+0.5*in[i];
        out[i] = std::abs(in[i])>0.1?sgn(in[i])*0.1:in[i];
      }
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace effects */
} /* namespace gr */

