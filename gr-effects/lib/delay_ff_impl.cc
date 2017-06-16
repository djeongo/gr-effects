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
#include "delay_ff_impl.h"

namespace gr {
  namespace effects {

    delay_ff::sptr
    delay_ff::make(int delay)
    {
      return gnuradio::get_initial_sptr
        (new delay_ff_impl(delay));
    }

    /*
     * The private constructor
     */
    delay_ff_impl::delay_ff_impl(int delay)
      : gr::block("delay_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      delay_ = delay;
      std::cout << "Delay value : " << delay_ << std::endl;
      input_buffer_ = (float *)calloc(delay_, sizeof(float));
    }

    /*
     * Our virtual destructor.
     */
    delay_ff_impl::~delay_ff_impl()
    {
      free(input_buffer_);
    }

    void
    delay_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    /*
     * Left shift input buffer
     */
    void delay_ff_impl::shift_left()
    {
      memmove((void *)input_buffer_, (void *)&input_buffer_[1], sizeof(float)*(delay_-1));
    }

    int
    delay_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      std::cout << "noutput_items " << noutput_items <<std::endl;
      for(int i=0; i<noutput_items; i++){
        shift_left();
        input_buffer_[delay_-1] = in[i];
        out[i] = 0.5*input_buffer_[0]+0.5*in[i];
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

